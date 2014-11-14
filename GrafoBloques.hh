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
#include <boost/graph/depth_first_search.hpp>
#include <unordered_map>
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
    BloqueBasico(int o, string* belongs);

    /** 
     * Constructor de bloque basico 
     * @param lista Lista de instrucciones
     */
    BloqueBasico(list<GuavaQuads*> lista);

    ~BloqueBasico(){}

    list<GuavaQuads*> get_codigo(){ return codigo; }

    int get_id(){ return id; }

    virtual bool is_entry() const { return is_entry_; } 

    bool is_exit(){ return is_exit_; } 

    /** 
     * Realiza una copia profunda de un bloque con otro.
     */
    void clone(BloqueBasico* b){
        codigo = b->get_codigo();
        id = b->get_id();
        is_exit_ = b->is_exit();
        is_entry_ = b->is_entry();
        belongs_to = b->get_belongs_to();
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

    void set_belonging(string* belonging){
        belongs_to = belonging;
    }

    string* get_belongs_to() const {
        return belongs_to;
    }

protected:
    list<GuavaQuads*> codigo; /* Codigo de tres direcciones */
    int id; /* Identificador para cada bloque. */
    bool is_exit_ = false;
    bool is_entry_ = false;
    string* belongs_to = 0; /* Nombre de la funcion a la que pertenece */
};

/** 
 * Overhead del operador << para ser cools.
 */
inline std::ostream& operator<<(std::ostream &os, BloqueBasico &state) {
    state.print(os);
    return os;
}

//Defino como tipo el grafo de Bloques.
typedef adjacency_list < vecS, vecS, directedS, BloqueBasico > Graph;
//Defino lo que seria un Vertex o nodo.
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;


/**  
 * Clase que representa un grafo de flujo.
 * Usaremos las librerias de Boost para esto.
 */
class GrafoFlujo{
private:
    Graph grafo;
    list<Vertex> entries;
    GuavaSymTable* tabla;
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
