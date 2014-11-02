/*
 * =====================================================================================
 *
 *       Filename:  GrafoBloques.hh
 *
 *    Description:  Especificacion de la clase GrafoBloques.
 *
 *        Version:  1.0
 *        Created:  01/11/14 17:09:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <list>
#include <boost/graph/adjacency_list.hpp>
#include "GuavaQuads.hh"
using namespace std;

/** 
 * Clase que representa un bloque 
 * de codigo en tres direcciones.
 */
class BloqueBasico{
public:

    BloqueBasico(list<GuavaQuads*>* lista): codigo(lista){}

    ~BloqueBasico(){}

    list<GuavaQuads*>* get_codigo(){ return codigo; }

private:
    list<GuavaQuads*>* codigo;
};

/**  
 * Clase que representa un grafo de flujo.
 * Usaremos las librerias de Boost para esto.
 */
class GrafoFlujo{
public:
    GrafoFlujo(){}
    ~GrafoFlujo(){}
};
