/*
 * =====================================================================================
 *
 *       Filename:  GrafoBloques.cc
 *
 *    Description:  Implementacion de GrafoBloques
 *
 *        Version:  1.0
 *        Created:  01/11/14 18:12:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GrafoBloques.hh"
#include <unordered_map>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/two_bit_color_map.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/graph_traits.hpp>

using namespace std;
int id_unica = 0 ; /* Id unica para BloqueBasico  */

/** 
 * Funcion que determina la información de proximo uso y liveness
 * @param codigo_bloque Codigo de tres direcciones de un bloque basico.
 */
void determinar_livenext(list<GuavaQuads*> codigo_bloque){
    // Voy de atras pa alante.
    for (list<GuavaQuads*>::reverse_iterator it = codigo_bloque.rbegin() ; it != codigo_bloque.rend() ; ++it){ 
        GuavaQuads* tmp = *it; 
        tmp->attach_info();
        tmp->update_use(); // En esta misma funcion se mata a la variable que se debe matar.
    }
}

/** 
 * Constructor vacio para bloquebasico
 * Aqui no se hace nada, es decir, no se 
 * asigna una id_unica.
 */
BloqueBasico::BloqueBasico(){
}

/** 
 * Constructor para Entries y Exits.
 * @param o Opcion a elegir 0 es Entry y todo lo demas es Exit
 */
BloqueBasico::BloqueBasico(int o, string* belongs): id(id_unica), belongs_to(belongs){
    if (o == 0){
        is_entry_ = true;
    }else {
        is_exit_ = true;
    }
    id_unica++; // Aumento el id_unico
}

/** 
 * Constructor para BloqueBasico
 * @param lista Lista de instrucciones de codigo de tres direcciones.
 */
BloqueBasico::BloqueBasico(list<GuavaQuads*> lista): codigo(lista), id(id_unica){
    id_unica++; // Aumento el id_unico
    determinar_livenext(codigo);
}

void BloqueBasico::print(ostream &os){
    if (this->is_entry()){
        os << "Bloque Entry : " << id << endl;
    } else if (this->is_exit()){
        os << "Bloque Exit : " << id << endl;
    } else{
        os << "Bloque :" << id << endl;
    }
    for (list<GuavaQuads*>::iterator it = codigo.begin(); it != codigo.end(); ++it){
        os << (*it)->gen() << endl;
    }
    if (this->get_belongs_to() != 0) os << "Pertenece: " << *this->get_belongs_to() << endl; 
    os << "----" <<endl;
}


/**
 * Funcion que retorna una lista de los lideres del programa.
 * Lider es: La primera instruccion de una funcion (a)
 *           Instruccion destino salto (b)
 *           Instruccion que sigue a un salto (c)
 * @param codigo Codigo de tres direcciones.
 * @param result Lideres de bloques.
 */
list<GuavaQuads*> obtener_lideres(list<GuavaQuads*>* codigo){
    list<GuavaQuads*> result;
    GuavaQuads* temp;

    for ( list<GuavaQuads*>::iterator it = codigo->begin();  it != codigo->end() ; ++it){
        temp = *it;

        if ((temp->is_goto() || temp->is_return()) && it != codigo->end() ){
            GuavaQuads* next_temp = *std::next(it);
            result.push_back(next_temp); // Instruccion que sigue a un salto es lider. (c)
        }
        /* 
         * Este if captura la regla a y b pues toda funcion comienza con un label (a)
         * y todo label es destino de salto (b)
         */
        else if (temp->is_label() || temp->is_return()){
            result.push_back(temp); 
        }
    }
    return result;
}

/** 
 * Genera los bloques basicos y los guarda en una lista.
 * @param codigo Codigo de tres direcciones.
 * @param lideres Lideres de los bloques.
 * @return result Retorna una lista de bloques.
 */
list<BloqueBasico*> obtener_bloques(list<GuavaQuads*>* codigo, list<GuavaQuads*> lideres){
    list<GuavaQuads*>::iterator it_lideres = lideres.begin();
    list<BloqueBasico*> result;
    list<GuavaQuads*>::iterator it_codigo = codigo->begin();


    while (it_lideres != lideres.end()){
        list<GuavaQuads*> codigo_bloque;

        while (it_codigo != codigo->end() && *it_codigo != *std::next(it_lideres)){
            if (!(*it_codigo)->is_guava_comment()) {
                codigo_bloque.push_back(*it_codigo);
            }
            ++it_codigo;
        }

        if (!codigo_bloque.empty()){
            BloqueBasico* nuevo_bloque = new BloqueBasico(codigo_bloque);
            result.push_back(nuevo_bloque);
        }
        ++it_lideres;
    }
    return result;
}

/** 
 * Obtiene todos los lados del grafo.
 *
 * Los lados obtenidos son los siguientes:
 *
 * a) C immediately follows B in the original order of the three-address instruc-
 *    tions, and B does not end in an unconditional jump.
 *
 *  b) There is a conditional or unconditional jump from the end of B to the 
 *     beginning of C.     
 *
 *
 * @param bloques Todos los bloques del grafo.
 * @return result Lista de lados.
 */
list<pair<BloqueBasico*,BloqueBasico*>> obtener_lados(list<BloqueBasico*>* bloques){
    list<pair<BloqueBasico*, BloqueBasico*>> result;
    BloqueBasico* bloque;

    //Primero voy a poner los lados de los bloques secuenciales. (a)
    for (list<BloqueBasico*>::iterator it = bloques->begin() ; it != bloques->end(); ++it){
        bloque = *it;
        //Si tiene un salto incondicional al final entonces no colocar el lado.
        if ( it != bloques->begin() && !(*std::prev(it))->last()->is_jump() &&  !(*std::prev(it))->last()->is_return()){
            pair<BloqueBasico*,BloqueBasico*> par_tmp (*std::prev(it),bloque);
            result.push_back(par_tmp);
        }
    }

    // Agregando los lados resultados de saltos. (b)
    for (list<BloqueBasico*>::iterator it = bloques->begin(); it != bloques->end(); ++it){
        for (list<BloqueBasico*>::iterator it_2 = bloques->begin(); it_2 != bloques->end() ; ++it_2){
            BloqueBasico* b = *it;
            BloqueBasico* c = *it_2;
            if (b->last()->is_goto()){
                if ( b->last()->same_label(c->first()) ){
                    pair<BloqueBasico*,BloqueBasico*> par_tmp (b,c);
                    result.push_back(par_tmp);
                }
            }
        }
    }

    return result;
}

/**
 * Agrega los exit a cada funcion junto con sus lados. 
 * @param g Grafo
 * @param dict Diccionario que contiene los bloques basicos junto con su descriptor de nodo.
 */
void agregar_exits(list<BloqueBasico*> bloques, std::unordered_map<BloqueBasico*, Graph::vertex_descriptor> dict, Graph& grafo){
    std::unordered_map<string, Graph::vertex_descriptor> bloques_exit; /* De esta manera guardamos todos los bloques exit para que no se repitan. */

    for (list<BloqueBasico*>::iterator it = bloques.begin();  it != bloques.end(); ++it){
       if ( !(*it)->is_entryexit() && (*it)->last()->is_return()){
            Graph::vertex_descriptor v;
            if ( grafo[dict[*it]].get_belongs_to() != 0){
                if (bloques_exit.count(*grafo[dict[*it]].get_belongs_to()) == 0){
                    //Bloque no existe aun. Lo agrego en el grafo y en el diccionario.
                    bloques_exit[*grafo[dict[*it]].get_belongs_to()] = add_vertex(grafo);
                    v = bloques_exit[*grafo[dict[*it]].get_belongs_to()];
                    BloqueBasico tmp(1,grafo[dict[*it]].get_belongs_to());
                    grafo[v].clone(&tmp);
                }else{
                   v = bloques_exit[*grafo[dict[*it]].get_belongs_to()]; 
                }
                add_edge(dict[*it],v,grafo);
            }else {
                remove_vertex(dict[*it],grafo); // Elimino nodo al que no se puede llegar.
            }
       }
    }
}

/** 
 * Agrega los bloque entry a cada funcion junto con sus lados.
 * @param g Grafo
 * @param dict Diccionario que contiene los bloques basicos junto con su descriptor de nodo.
 * @returns Lista de nodos entry.
 */
list<Graph::vertex_descriptor> agregar_entry(list<BloqueBasico*> bloques,std::unordered_map<BloqueBasico*, Graph::vertex_descriptor> dict, Graph& grafo){
    list<Graph::vertex_descriptor> result;
    for (list<BloqueBasico*>::iterator it = bloques.begin();  it != bloques.end(); ++it){
       if ((*it)->first()->is_func_label()){
            BloqueBasico entry(0,new string((*it)->first()->get_op()));
            Graph::vertex_descriptor v = add_vertex(grafo);
            result.push_back(v);
            grafo[v].clone(&entry);
            add_edge(v, dict[*it],grafo);
       }
    }
    return result;
}

/** 
 * Hace algo asi como un dfs (creo) identificando cada uno de los nodos observados.
 * @root Raiz.
 */
void identificador_recursivo(Vertex root, Graph& grafo){
    typename graph_traits<Graph>::out_edge_iterator out_i, out_end;  
    typename graph_traits<Graph>::edge_descriptor e;
    for (boost::tie(out_i, out_end) = out_edges(root, grafo);
                out_i != out_end; ++out_i){
        e = *out_i;        
        Vertex targ = target(e, grafo);
        if (grafo[targ].get_belongs_to() == 0) grafo[targ].set_belonging(grafo[root].get_belongs_to());
        identificador_recursivo(targ,grafo);
    }
}

/** 
 * Identifica cada bloque segun la función a la que pertenece. 
 * Por ejemplo a cada bloque asociado al bloque entry main le asocio el nombre main.
 */
void identificar_bloques(list<Vertex> entries, Graph& grafo){

    for (list<Vertex>::iterator entry = entries.begin(); entry != entries.end(); ++entry){
        identificador_recursivo(*entry,grafo);
    }
}



/**  
 * Constructor de GrafoFlujo.
 * En esta funcion realizo todos los bloquesbasicos y los coloco en el grafo junto con sus lados.
 * @param codigo Codigo de tres direcciones de todo el codigo fuente
 */
GrafoFlujo::GrafoFlujo(list<GuavaQuads*>* codigo){
    using namespace boost;
    std::unordered_map<BloqueBasico*, Graph::vertex_descriptor> dict; //Quiero guardar todos los bloques en un diccionario para agregar los lados.
    list<GuavaQuads*> lideres = obtener_lideres(codigo);
    list<BloqueBasico*> bloques = obtener_bloques(codigo, lideres);

    // Agregando los nodos del grafo.
    for (list<BloqueBasico*>::iterator it = bloques.begin(); it != bloques.end(); ++it){
        BloqueBasico* tmp = *it;
        Graph::vertex_descriptor v = add_vertex(grafo);
        pair<BloqueBasico*, Graph::vertex_descriptor> par_tmp (tmp,v);
        dict.insert(par_tmp); 
        grafo[v].clone(tmp);
    }

    list<pair<BloqueBasico*,BloqueBasico*> > lados = obtener_lados(&bloques);

    //Agregando los lados.
    for (list<pair<BloqueBasico*, BloqueBasico*> >::iterator it = lados.begin(); it != lados.end(); ++it){
        pair<BloqueBasico*, BloqueBasico*> tmp = *it;
        add_edge(dict[tmp.first],dict[tmp.second],grafo);
    }
    entries = agregar_entry(bloques,dict,grafo);
    identificar_bloques(entries,grafo);
    agregar_exits(bloques,dict,grafo);

    this->imprimir_nodos(cout);
    this->imprimir_lados(cout);
}

/** 
 * Imprime los nodos del grafo.
 */
void GrafoFlujo::imprimir_nodos(ostream& os){
    graph_traits<Graph>::vertex_iterator vi, vi_end, next;
    boost::tie(vi, vi_end) = vertices(grafo);
    for (next = vi; next != vi_end; ++next){
        os << grafo[*next];
    }

}

/** 
 * Imprime los lados.
 */
void GrafoFlujo::imprimir_lados(ostream& os){
    graph_traits<Graph>::vertex_iterator vi, vi_end, next;
    typename graph_traits<Graph>::out_edge_iterator out_i, out_end;  
    typename graph_traits<Graph>::edge_descriptor e;
    boost::tie(vi, vi_end) = vertices(grafo);
    for (next = vi; next != vi_end; ++next){
        os << "Lados del Bloque :" << grafo[*next].get_id() << endl;
        for (boost::tie(out_i, out_end) = out_edges(*next, grafo);
                    out_i != out_end; ++out_i){
            e = *out_i;        
            Vertex src = source(e, grafo), targ = target(e, grafo);
            os << grafo[src].get_id() << " , " << grafo[targ].get_id() << endl;
        }
    }
}
