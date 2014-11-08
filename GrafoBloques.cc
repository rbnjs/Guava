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
 * Constructor para BloqueBasico
 * @param lista Lista de instrucciones de codigo de tres direcciones.
 */
BloqueBasico::BloqueBasico(list<GuavaQuads*> lista): codigo(lista), id(id_unica){
    id_unica++; // Aumento el id_unico
    determinar_livenext(codigo);
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

    for ( list<GuavaQuads*>::iterator it = codigo->begin();  it != codigo->end() ;){
        temp = *it;

        if (temp->is_goto() && it != codigo->end() ){
            GuavaQuads* next_temp = *std::next(it);
            result.push_back(next_temp); // Instruccion que sigue a un salto es lider. (c)
        }
        /* 
         * Este if captura la regla a y b pues toda funcion comienza con un label (a)
         * y todo label es destino de salto (b)
         */
        if (temp->is_label()){
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
    ++it_lideres; // Ya se sabe que el primer lider es la primera instruccion.
    while (it_lideres != lideres.end()){
        list<GuavaQuads*> codigo_bloque;
        while (*it_codigo != *it_lideres){ 
            GuavaQuads* instruccion = *it_codigo;
            codigo_bloque.push_back(instruccion);
            ++it_codigo;
        }
        BloqueBasico* nuevo_bloque = new BloqueBasico(codigo_bloque);
        result.push_back(nuevo_bloque);
        ++it_lideres;
    }
    //Una vez obtenido todos los bloques coloco el bloque entry y el exit
    result.push_front(new BloqueEntry());
    result.push_front(new BloqueExit());
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
 *  FALTA CONSIDERAR QUE HACER CON EL ENTRY
 *
 * @param bloques Todos los bloques del grafo.
 * @return result Lista de lados.
 */
list<pair<BloqueBasico*,BloqueBasico*>> obtener_lados(list<BloqueBasico*> bloques){
    list<pair<BloqueBasico*, BloqueBasico*>> result;
    BloqueBasico* bloque;
    //Primero voy a poner los lados de los bloques secuenciales. (a)
    for (list<BloqueBasico*>::iterator it = bloques.begin() ; it != bloques.end(); ++it){
        bloque = *it;
        //Si tiene un salto incondicional al final entonces no colocar el lado.
        if ( it != bloques.begin() && !std::prev(bloque)->last()->is_jump()){
            pair<BloqueBasico*,BloqueBasico*> par_tmp (std::prev(bloque),bloque);
            result.push_back(par_tmp);
        }
    }
    // Agregando los lados resultados de saltos. (b)
    for (list<BloqueBasico*>::iterator it = bloques.begin(); it != bloques.end(); ++it){
        for (list<BloqueBasico*>::iterator it_2 = bloques.begin(); it_2 != bloques.end() ; ++it_2){
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
        grafo[v].set_bloque(tmp);
    }

    list<pair<BloqueBasico*,BloqueBasico*> > lados = obtener_lados(bloques);
    // Agregando los lados.
    for (list<pair<BloqueBasico*, BloqueBasico*> >::iterator it = lados.begin(); it != lados.end(); ++it){
        pair<BloqueBasico*, BloqueBasico*> tmp = *it;
        add_edge(dict[tmp.first],dict[tmp.second],grafo);
    }

}
