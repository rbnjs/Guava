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
     * Constructor para Entries y Exits.
     * @param o Opcion a elegir 0 es Entry y todo lo demas es Exit
     */
    BloqueBasico(int o);

    /** 
     * Constructor de bloque basico 
     * @param lista Lista de instrucciones
     */
    BloqueBasico(list<GuavaQuads*> lista);

    ~BloqueBasico(){}

    list<GuavaQuads*> get_codigo(){ return codigo; }

    int get_id(){ return id; }

    virtual bool is_entry(){ return is_entry_; } 

    bool is_exit(){ return is_exit_; } 

    void clone(BloqueBasico* b){
        codigo = b->get_codigo();
        id = b->get_id();
        is_exit_ = b->is_exit();
        is_entry_ = b->is_entry();
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
    

    bool is_entryexit(){ return (is_exit_ || is_entry_); }

protected:
    list<GuavaQuads*> codigo; /* Codigo de tres direcciones */
    int id; /* Identificador para cada bloque. */
    bool is_exit_ = false;
    bool is_entry_ = false;
};

/** 
 * Overhead del operador << para ser cools.
 */
inline std::ostream& operator<<(std::ostream &os, BloqueBasico &state) {
    state.print(os);
    return os;
}




//Defino como tipo el grafo de Bloques.
typedef adjacency_list < listS, listS, directedS, BloqueBasico > Graph;

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

    /** 
     * Imprime los lados del grafo.
     */
    void imprimir_lados(ostream& os);
};
