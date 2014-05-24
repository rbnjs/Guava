/*
 * =====================================================================================
 *
 *       Filename:  GuavaSymTable.cc
 *
 *    Description: Implementacion de GuavaSymTable 
 *
 *        Version:  1.0
 *        Created:  12/03/14 14:24:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GuavaSymTable.hh"
#include <iostream>

/**
 * Constructor de la clase
 */
GuavaSymTable::GuavaSymTable(){
    alcance = 0;
    this->pila.push_front(alcance);
}

GuavaSymTable::~GuavaSymTable(){
}

/**
 * Inserta un simbolo en la tabla de simbolos.
 * */
void GuavaSymTable::insert(Symbol elem) {
    /* Se verifica si el simbolo ya existe en la tabla */
    if(this->tabla.count(elem.sym_name) > 0) {
        for(std::list<Symbol>::iterator it = this->tabla[elem.sym_name].begin();
            it != this->tabla[elem.sym_name].end(); it++) {
            /* Caso en el que el simbolo se encuentra en el mismo scope. */
            if(elem == *it) {
                /* EL SIMBOLO EXISTE EN ESTE SCOPE */
            }
        }
        /* Caso en el que el simbolo no existe en el scope, pero si en otros */
        this->tabla[elem.sym_name].push_back(elem);
    }
    /* Caso en el que el simbolo no pertenece a la tabla. */
    else {
        std::list<Symbol> empty_list;
        empty_list.push_front(elem);
        this->tabla[elem.sym_name] = empty_list;
    }
}
/* Inserta un simbolo */
void GuavaSymTable::insert(std::string name, std::string catg, int sc, Symbol* type,int line, int column, int offset){
   Symbol* nuevo = new Symbol(name, catg, sc, type,line,column, offset); 
   this->insert(*nuevo);
}


/**
 * Agrega una variable arreglo o estructura a la tabla.
 */
void GuavaSymTable::insert(std::string name,std::string catg,int scop,TypeS* t,int li = 0,int co = 0, int offset = 0 ){
    Symbol* nuevo = new Symbol(name,catg,scop,t,li,co, offset);
    this->insert(*nuevo);
}


/**
 * Inserta un tipo simple.
 */
void GuavaSymTable::insert_type(std::string name, std::string catg, int sc, TypeS* type){
    Symbol* nuevo = new Symbol(name,catg,sc,type);
    this->insert(*nuevo);
}

/**
 * Busca el simbolo a ser evaluado.
 * 
 * Voy revisando por toda la pila de alcances 
 * a ver si encuentro el simbolo deseado. Si 
 * el elemento con el alcance concuerdan 
 * entonces retorno un apuntador 
 * a el simbolo deseado.
 */
Symbol* GuavaSymTable::lookup(const std::string elem){
    if (!this->tabla[elem].empty()){
    for (std::list<int>::iterator pilaIt = this->pila.begin();
         pilaIt != this->pila.end() ; 
         ++pilaIt){
            int alcance = *pilaIt;
            
            std::list<Symbol>::iterator it = this->tabla[elem].begin();

            for ( it ; it != this->tabla[elem].end() ; ++it){
                Symbol tmp = *it;
                if (tmp.compare(elem, alcance)) return &(*it);
            }

        }
    }
    return 0; /* Null si no lo encuentra */
}
/**
 * Busca un simbolo en el alcance actual
 */
Symbol* GuavaSymTable::simple_lookup(const std::string elem){
    if (!this->tabla[elem].empty()){
        int alcance = pila.front();
            
        std::list<Symbol>::iterator it = this->tabla[elem].begin();

        for ( it ; it != this->tabla[elem].end() ; ++it){
            Symbol tmp = *it;
            if (tmp.compare(elem, alcance)) return &(*it);
        }
    }
    return 0; /* Null si no lo encuentra */
}
/**
 * Busca un simbolo en el alcance sc
 */
Symbol* GuavaSymTable::lookup(const std::string elem, int sc){
    if (!this->tabla[elem].empty()){
        int alcance = sc;

        std::list<Symbol>::iterator it = this->tabla[elem].begin();

        for ( it ; it != this->tabla[elem].end() ; ++it){
            Symbol tmp = *it;
            if (tmp.compare(elem, alcance)) return &(*it);
        }

    }
    return 0; /* Null si no lo encuentra */
}

/**
 * Entra en un nuevo scope y empila el numero identificador del mismo.
 */
int GuavaSymTable::enterScope(){
    ++alcance;
    this->pila.push_front(alcance);
    return alcance;
}

/**
 * Aumenta en uno el alcance
 */
int GuavaSymTable::newScope(){
    ++alcance;
    return alcance;
}

/**
 * Sale del scope y desempila el identificador.
 */
int GuavaSymTable::exitScope(){
    if (!this->pila.empty()){
        int tmp = pila.front();
        pila.pop_front();
        return tmp;
    } else{
        return -1;
    }
}
/**
 * Retorna el entorno actual
 */
int GuavaSymTable::currentScope(){
    return pila.front();
}

/**
 * Muestra el contenido de la tabla de simbolos.
 * */
void GuavaSymTable::show(int scope, std::string identacion){
    std::unordered_map<std::string, std::list<Symbol> >::iterator itTabla = this->tabla.begin();
    for (itTabla ; itTabla != this->tabla.end() ; ++itTabla){
        std::list<Symbol>::iterator itList = itTabla->second.begin();
        for (itList ; itList != itTabla->second.end() ; ++itList){
            Symbol tmp = *itList;
            if (tmp.scope == scope) tmp.show(identacion);
        }
    }
}

std::list<TypeS*> GuavaSymTable::get_types(int sc){
    std::list<TypeS*> result;
    std::unordered_map<std::string, std::list<Symbol> >::iterator itTabla = this->tabla.begin();
    for (itTabla ; itTabla != this->tabla.end() ; ++itTabla){
        std::list<Symbol>::iterator itList = itTabla->second.begin();
        for (itList ; itList != itTabla->second.end() ; ++itList){
            Symbol tmp = *itList;
            if (tmp.scope == sc ){
                if (tmp.sym_catg != "unionType" && tmp.sym_catg != "recordType"){
                    if (tmp.true_type != 0) result.push_front(tmp.true_type);
                    else {
                        Symbol *tmp2 = tmp.type_pointer;
                        if (tmp2->true_type == 0) continue;
                        result.push_front(tmp2->true_type);
                    }
                }
            }
        }
    }
    return result;
}


/* class TypeStructure */

TypeStructure::TypeStructure(){ atributos = new GuavaSymTable();}

TypeStructure::TypeStructure(std::string n ):nombre(n){ atributos = new GuavaSymTable(); }

bool TypeStructure::is_real()      { return false; }
bool TypeStructure::is_int()       { return false; }
bool TypeStructure::is_error()     { return false; }
bool TypeStructure::is_bool()      { return false; }
bool TypeStructure::is_char()      { return false; }
bool TypeStructure::is_str()       { return false; }
bool TypeStructure::is_func()      { return false; }
bool TypeStructure::is_structure() { return true; }
bool TypeStructure::is_union()     { return false; }
bool TypeStructure::is_void()      { return false; }
bool TypeStructure::is_reference() { return false; }

TypeS* TypeStructure::get_tipo() { return 0; }

std::string TypeStructure::get_name() { return nombre; }

std::pair<int,int*> TypeStructure::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}


/* class TypeUnion */

TypeUnion::TypeUnion(){atributos = new GuavaSymTable(); }

TypeUnion::TypeUnion(std::string n ):nombre(n){ atributos = new GuavaSymTable();}

bool TypeUnion::is_real()      { return false; }
bool TypeUnion::is_int()       { return false; }
bool TypeUnion::is_error()     { return false; }
bool TypeUnion::is_bool()      { return false; }
bool TypeUnion::is_char()      { return false; }
bool TypeUnion::is_str()       { return false; }
bool TypeUnion::is_func()      { return false; }
bool TypeUnion::is_structure() { return false; }
bool TypeUnion::is_union()     { return true; }
bool TypeUnion::is_void()      { return false; }
bool TypeUnion::is_reference() { return false; }

TypeS* TypeUnion::get_tipo() { return 0; }

std::string TypeUnion::get_name() { return nombre; }

std::pair<int,int*> TypeUnion::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

