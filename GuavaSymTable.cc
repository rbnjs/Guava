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
    parent = 0;
}

GuavaSymTable::~GuavaSymTable(){
}

/**
 * Inserta un simbolo en la tabla de simbolos.
 * */
void GuavaSymTable::insert(Symbol* elem) {
    /* Se verifica si el simbolo ya existe en la tabla */
    if(this->tabla.count(elem->sym_name) > 0) {
        for(std::list<Symbol*>::iterator it = this->tabla[elem->sym_name].begin();
            it != this->tabla[elem->sym_name].end(); it++) {
            /* Caso en el que el simbolo se encuentra en el mismo scope. */
            if(elem == *it) {
                /* EL SIMBOLO EXISTE EN ESTE SCOPE */
            }
        }
        /* Caso en el que el simbolo no existe en el scope, pero si en otros */
        this->tabla[elem->sym_name].push_back(elem);
    }
    /* Caso en el que el simbolo no pertenece a la tabla. */
    else {
        std::list<Symbol*> empty_list;
        empty_list.push_front(elem);
        this->tabla[elem->sym_name] = empty_list;
    }
}

void GuavaSymTable::insert(Symbol elem){
    this->insert(&elem);
}

/* Inserta un simbolo */
Symbol* GuavaSymTable::insert(std::string name, std::string catg, int sc, Symbol* type,int line, int column, int offset){
   Symbol* nuevo = new Symbol(name, catg, sc, type,line,column, offset); 
   this->insert(nuevo);
    return nuevo;
}

/**
 * Agrega una variable arreglo o estructura a la tabla.
 */
Symbol* GuavaSymTable::insert(std::string name,std::string catg,int scop,TypeS* t,int li = 0,int co = 0, int offset = 0 ){
    Symbol* nuevo = new Symbol(name,catg,scop,t,li,co, offset);
    this->insert(nuevo);
    return nuevo;
}

/**
 * Inserta un tipo simple.
 */
void GuavaSymTable::insert_type(std::string name, std::string catg, int sc, TypeS* type){
    Symbol* nuevo = new Symbol(name,catg,sc,type);
    this->insert(nuevo);
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
            

            for (std::list<Symbol*>::iterator it = this->tabla[elem].begin() ; it != this->tabla[elem].end() ; ++it){
                Symbol* tmp = *it;
                if (tmp->compare(elem, alcance)) return *it;
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
            

        for ( std::list<Symbol*>::iterator it = this->tabla[elem].begin() ; it != this->tabla[elem].end() ; ++it){
            Symbol* tmp = *it;
            if (tmp->compare(elem, alcance)) return *it;
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


        for (std::list<Symbol*>::iterator it = this->tabla[elem].begin() ; it != this->tabla[elem].end() ; ++it){
            Symbol* tmp = *it;
            if (tmp->compare(elem, alcance)) return *it;
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

    for (std::unordered_map<std::string, std::list<Symbol*> >::iterator itTabla = this->tabla.begin() ; itTabla != this->tabla.end() ; ++itTabla){

        for (std::list<Symbol*>::iterator itList = itTabla->second.begin() ; itList != itTabla->second.end() ; ++itList){
            Symbol* tmp = *itList;
            if (tmp->scope == scope) tmp->show(identacion);
        }
    }
}

/**
 * PUEDE QUE AQUI ESTE EL PEO DE CALCULO DE TAMANO DE ESTRUCTURAS
 */
std::list<TypeS*> GuavaSymTable::get_types(int sc){
    std::list<TypeS*> result;

    for (std::unordered_map<std::string, std::list<Symbol*> >::iterator itTabla = this->tabla.begin() ; itTabla != this->tabla.end() ; ++itTabla){
        for (std::list<Symbol*>::iterator itList = itTabla->second.begin() ; itList != itTabla->second.end() ; ++itList){
            Symbol* tmp = *itList;
           

            if (tmp->scope ==sc) {
                if(tmp->true_type != 0) {
                    /* Verificacion de si se trata de una definicion de tipo:
                     * se checkea que el nombre del simbolo no sea el mismo de
                     * la estructura que define el tipo nuevo.
                     * (ALERTA: CABLE)
                     */
                    if(tmp->sym_name.compare(tmp->true_type->get_name()) != 0)
                        result.push_front(tmp->true_type);
                }
                else if (tmp->type_pointer != 0 && tmp->type_pointer->true_type != 0) {
                    if(tmp->sym_name.compare(tmp->type_pointer->true_type->get_name()) != 0)
                        result.push_front(tmp->type_pointer->true_type);
                }
            }
        }
    }
    
    return result;
}


/* class TypeRecord */

TypeRecord::TypeRecord():atributos(new GuavaSymTable()){}

TypeRecord::TypeRecord(std::string n ):nombre(n), atributos(new GuavaSymTable()){
                                                }

bool TypeRecord::is_real()      { return false; }
bool TypeRecord::is_int()       { return false; }
bool TypeRecord::is_error()     { return false; }
bool TypeRecord::is_bool()      { return false; }
bool TypeRecord::is_char()      { return false; }
bool TypeRecord::is_str()       { return false; }
bool TypeRecord::is_func()      { return false; }
bool TypeRecord::is_structure() { return true; }
bool TypeRecord::is_union()     { return false; }
bool TypeRecord::is_void()      { return false; }
bool TypeRecord::is_reference() { return false; }

TypeS* TypeRecord::get_tipo() { return 0; }

std::string TypeRecord::get_name() { return nombre; }

/* class TypeUnion */

TypeUnion::TypeUnion(): atributos(new GuavaSymTable()){}

TypeUnion::TypeUnion(std::string n ):nombre(n), atributos(atributos = new GuavaSymTable()){}

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

