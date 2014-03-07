/*
 * =====================================================================================
 *
 *       Filename:  GuavaSymTable.hh
 *
 *    Description:  Clase de tabla de simbolo para Guava.
 *
 *        Version:  1.0
 *        Created:  05/03/14 13:50:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization: USB 
 *
 * =====================================================================================
 */
#include <string>
/* Clase simbolo de Guava. */
class Symbol{
public:
    /**
     * Constructor de la clase Symbol.
     */
    Symbol(std::string name, std::string catg, int scop,Symbol s) {
        sym_name = name;
        sym_catg = catg;
        scope = scop;
        *type = s;
    }
    /**
     * Destructor de la clase Symbol.
     * */
    ~Symbol(){
        type = 0;
    }

    std::string sym_name; /* Nombre del simbolo */
    std::string sym_catg; /* Categoria del simbolo */
    int scope;            /* Identificador del scope del simbolo */
    Symbol *type;         /* Apuntador la descripcion del tipo del simbolo */


    /**
     * Se utiliza el operador == para comparar. 
     * Cambie el compare por este porque considere que se veia mas chevere.  */
    bool operator==(Symbol b) {
        return ((sym_name.compare(b.sym_name) == 0) && scope == b.scope);
    }
    /** 
     * Compara nombres y alcance 
     */
    bool compare(std::string s, int sc){
        return ((sym_name.compare(s) == 0) && scope == sc);
    }

};
/**
 * Declaracion de la clase para la tabla de simbolos.
 * */
class GuavaSymTable{
public:
    GuavaSymTable();                                      /* Constructor de la clase */
    virtual ~GuavaSymTable();                             /*  Destructor */

    void insert(Symbol elem);                             /* Inserta un simbolo a la tabla */
    void enterScope();                                    /* Entra un nuevo alcance  */
    void exitScope();                                     /* Sale del alcance  */
    Symbol lookup(std::string elem, int alcance);         /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    void show();                                          /* Muestra la tabla */
private:
    std::stack<int> pila;                                 /* Pila de alcances */
    std::map<std::string, std::list<Symbol>> tabla;       /* Tabla que representa la tabla de simbolos. */
    int alcance;                                          /* Alcance en numeros. */
};

/**
 * Inserta un simbolo en la tabla de simbolos.
 * */
void GuavaSymTable::insert(Symbol elem) {
    std::map<std::string, std::list<Symbol>>::iterator sym_list; /* Lista de colisiones, en caso de haber. OJO: No entiendo que estas haciendo aki*/

    /* Se verifica si el simbolo ya existe en la tabla */
    if(tabla.count(elem.sym_name) > 0) {
        sym_list = tabla.find(elem.sym_name);
        for(std::list<Symbol>::iterator it=sym_list.begin();
            it != sym_list.end(); it++) {
            /* Caso en el que el simbolo se encuentra en el mismo scope. */
            if(elem == it) {
                /* EL SIMBOLO EXISTE EN ESTE SCOPE */
            }
        }
        /* Caso en el que el simbolo no existe en el scope, pero si en otros */
        sym_list.push_back(elem);
    }
    /* Caso en el que el simbolo no pertenece a la tabla. */
    else {
        std::list<Symbol> empty_list;
        tabla.insert(std::pair<std::string, std::list<Symbol>> 
                     (elem.sym_name, empty_list));
    }
}
/**
 * Busca el simbolo a ser evaluado.
 */
Symbol GuavaSymTable::lookup(const std::string elem, int alcance){
    if (!tabla[elem].empty){
        std::list<Symbol>::iterator it = tabla[elem].begin();
        for ( it ; it != tabla[elem].end() ; it++){
            if (it.compare(elem, alcance)) return it;
        }
    }
    return NULL;
}

//enter_scope: Entra en un nuevo scope y empila el numero identificador del mismo.

//exit_scope: Sale del scope y desempila el identificador.
