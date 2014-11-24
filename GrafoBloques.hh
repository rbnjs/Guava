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
#ifndef GRAFO_BLOQUES_HH
#define GRAFO_BLOQUES_HH
#include <list>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <unordered_map>
#include "GuavaQuads.hh"
#include "Generator.hh"
#include "GuavaTemplates.hh"

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

    GuavaTemplates* get_template(){ return template_gen; } 

    void set_template(GuavaTemplates* template_){
        template_gen = template_;
    }

    /** 
     * Realiza una copia profunda de un bloque con otro.
     */
    void clone(BloqueBasico* b){
        codigo = b->get_codigo();
        id = b->get_id();
        is_exit_ = b->is_exit();
        is_entry_ = b->is_entry();
        belongs_to = b->get_belongs_to();
        template_gen = b->get_template();
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

    bool belongs_to_func(string func) const;

    void generar_mips() const;

    void generar_entry_main_mips() const ;

    void generar_entry_mips() const;

    void generar_exit_mips() const;

    void generar_exit_main_mips() const;

    list<SimpleSymbol*> obtener_vars() const;

protected:
    list<GuavaQuads*> codigo; /* Codigo de tres direcciones */
    int id;                   /* Identificador para cada bloque. */
    bool is_exit_ = false;    
    bool is_entry_ = false;
    string* belongs_to = 0;             /* Nombre de la funcion a la que pertenece */
    GuavaTemplates* template_gen;       /* Generador mediante Templates */
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
 * Visitador del grafo que va a generar codigo final.
 */
class bfs_generator: public default_bfs_visitor{
protected:
    GuavaTemplates* templates;
public:

    /**
     * Constructor del visitador.
     */
    bfs_generator(GuavaTemplates* gen_): templates(gen_){}

    /** 
     * Destructor de la clase.
     */
    ~bfs_generator(){}


    void discover_vertex(Vertex u,const Graph& g);

};

/**  
 * Clase que representa un grafo de flujo.
 * Usaremos las librerias de Boost para esto.
 */
class GrafoFlujo{
private:
    Graph grafo;
    list<Vertex> entries;
    GuavaSymTable* tabla;
    GuavaGenerator* guava_gen;
    MIPS* mips; /* GuavaTemplates para el GrafoFlujo. */

    list<Graph::vertex_descriptor> agregar_entry(list<BloqueBasico*> bloques,std::unordered_map<BloqueBasico*, Graph::vertex_descriptor> dict);

    void agregar_exits(list<BloqueBasico*> bloques, std::unordered_map<BloqueBasico*, Graph::vertex_descriptor> dict);
public:
    /** 
     * Constructor de Grafo de Flujo.
     * @param codigo Lista de codigo de tres direcciones.
     * @param gen_ Generator de Guava.
     */
    GrafoFlujo(list<GuavaQuads*>* codigo, GuavaGenerator* gen_, GuavaSymTable *tabla_);
    /** 
     * Destructor de la clase.
     */
    ~GrafoFlujo(){}

    /** 
     * Imprime los nodos del grafo.
     */
    void imprimir_nodos(ostream& os);

    /** 
     * Imprime los lados del grafo.
     */
    void imprimir_lados(ostream& os);

    void imprimir();

    void generar_mips();
};
#endif
