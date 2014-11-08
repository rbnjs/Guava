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
using namespace boost;


/** 
 * Clase que representa un bloque 
 * de codigo en tres direcciones.
 */
class BloqueBasico{
public:

    /** 
     * Constructor Vacio.
     */
    BloqueBasico();

    /** 
     * Constructor de bloque basico 
     * @param lista Lista de instrucciones
     */
    BloqueBasico(list<GuavaQuads*> lista);

    ~BloqueBasico(){}

    list<GuavaQuads*> get_codigo(){ return codigo; }

    int get_id(){ return id; }

    virtual bool is_entry(){ return false; } 

    virtual bool is_exit(){ return false; } 

    void set_bloque(BloqueBasico* b){
        codigo = b->get_codigo();
        id = b->get_id();
    }

    /** 
     * @return codigo.front() Retorna el primer elemento de la lista.
     */
    GuavaQuads* first(){
        return codigo.front();
    }


    /** 
     * @return codigo.last() Retorna el primer elemento de la lista.
     */
    GuavaQuads* last(){
        return codigo.back();
    }

    /** 
     * Imprime el codigo dentro del bloque.
     */
    void print(ostream &os);


protected:
    list<GuavaQuads*> codigo; /* Codigo de tres direcciones */
    int id; /* Identificador para cada bloque. */
};

/** 
 * Overhead del operador << para ser cools.
 */
inline std::ostream& operator<<(std::ostream &os, BloqueBasico &state) {
    state.print(os);
    return os;
}

/** 
 * Clase que representa un bloque de entrada
 */
class BloqueEntry: public BloqueBasico{
public:

    BloqueEntry(GuavaQuads* label_);

    ~BloqueEntry(){}

    bool is_entry(){ return true; } 
private:
    string label;
};

/** 
 * Clase que representa un bloque de salida.
 */
class BloqueExit: public BloqueBasico{
public:

    BloqueExit();

    ~BloqueExit(){}

    bool is_exit(){ return true; } 
};


//Defino como tipo el grafo de Bloques.
typedef adjacency_list < listS, listS, undirectedS, BloqueBasico > Graph;

/**  
 * Clase que representa un grafo de flujo.
 * Usaremos las librerias de Boost para esto.
 */
class GrafoFlujo{
private:
    Graph grafo;
public:
    /** 
     * Constructor de Grafo de Flujo.
     * @param codigo Lista de codigo de tres direcciones.
     */
    GrafoFlujo(list<GuavaQuads*>* codigo);
    ~GrafoFlujo(){}

    /** 
     * Imprime los nodos del grafo.
     */
    void imprimir_nodos(ostream& os);
};
