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
 */
BloqueBasico::BloqueBasico(): id(id_unica){
    id_unica++;
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
 * Lider es: El primer elemento
 *           Instruccion destino salto
 *           Instruccion que sigue a un salto
 * @param codigo Codigo de tres direcciones.
 * @param result Lideres de bloques.
 */
list<GuavaQuads*> obtener_lideres(list<GuavaQuads*>* codigo){
    list<GuavaQuads*> result;
    list<GuavaQuads*>::iterator it = codigo->begin(); 
    GuavaQuads* temp = *it;
    result.push_back(temp); //Primer elemento es lider
    ++it;

    for (it ; it != codigo->end(); ++it){
        temp = *it;
        if (temp->is_goto() && it != codigo->end() ){
            list<GuavaQuads*>::iterator it_temp = it;
            ++it_temp;
            GuavaQuads* next_temp = *it_temp;
            result.push_back(next_temp); // Instruccion que sigue a un salto es lider.
        }

        if (temp->is_label()){
            result.push_back(temp); // Destinos a salto son lider.
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
        ++it_lideres;
        list<GuavaQuads*> codigo_bloque;
        while (it_codigo != it_lideres){ // No se si esto se pueda. Revisar
            GuavaQuads* instruccion = *it_codigo;
            codigo_bloque.push_back(instruccion);
            ++it_codigo;
        }
        BloqueBasico* nuevo_bloque = new BloqueBasico(codigo_bloque);
        result.push_back(nuevo_bloque);
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
    list<BloqueBasico*> bloques = obtener_bloques(codigo, obtener_lideres(codigo));
    // Agregando los nodos del grafo.
    for (list<BloqueBasico*>::iterator it = bloques.begin(); it != bloques.end(); ++it){
        BloqueBasico* tmp = *it;
        Graph::vertex_descriptor v = add_vertex(grafo);
        
    }
}
