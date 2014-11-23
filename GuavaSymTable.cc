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
    if(catg.compare(std::string("array")) != 0) {
        Symbol* nuevo = new Symbol(name,catg,scop,t,li,co,offset);
        this->insert(nuevo);
        return nuevo;
    }
    else {
        SymbolArray * nuevo = new SymbolArray(name,catg,scop,t,li,co,offset);
        this->insert(nuevo);
        return nuevo;
    }
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
 * Retorna un lista de tipos.
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

/** 
 * Obtiene una lista de simbolos en el scope determinado.
 * @param sc Scope
 * @param result Lista de simbolos.
 */
std::list<Symbol*> GuavaSymTable::obtain_symbols(int sc){
    std::list<Symbol*> result;
    for (std::unordered_map<std::string, std::list<Symbol*> >::iterator it = this->tabla.begin() ; it != this->tabla.end() ; ++it){
        for (std::list<Symbol*>::iterator it_lista = it->second.end(); it_lista != it->second.end(); ++it_lista){
           if ((*it_lista)->scope == sc) result.push_back(*it_lista); 
        }
    }
    return result;
}

/** 
 * Obtiene la lista de los simbolos globales.
 * @param result Lista de simbolos.
 */
std::list<Symbol*> GuavaSymTable::obtain_globals(){
    return this->obtain_symbols(1);
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

/**
 * "Encaja" el tamaño dado de un TypeS
 * en la palabra.
 * @param tam Tamaño que se quiere "encajar" en palabra 
 */
int encajar_en_palabra(int tam){
    if (tam % WORD == 0) return tam;
    return (tam + (WORD - (tam % WORD)));  
}

/**
 * Dado un tipo basico, retorna el tamaño de este.
 * En caso de que TypeS* sea otra cosa aparte de un tipo basico
 * se retorna -1.
 * @param t Tipo al que se quiere calcular el tamano.
 * @return int
 */
int tamano_tipo(TypeS* t){
    if (t == 0) return -1; //Error
    if (t->is_error()) return 0;
    if (t->is_bool()) return encajar_en_palabra(SIZE_BOOL);
    if (t->is_real()) return encajar_en_palabra(SIZE_REAL);
    if (t->is_int()) return encajar_en_palabra(SIZE_INT);
    if (t->is_char()) return encajar_en_palabra(SIZE_CHAR);
    if (t->is_reference()) return encajar_en_palabra(SIZE_REFERENCE);
    if (t->is_str()) return encajar_en_palabra(SIZE_REFERENCE);
    int result;

    if (t->is_structure()){
        result = 0;
        TypeS* tmp;
        TypeRecord *s = (TypeRecord*) t;
        std::list<TypeS*> list = s->atributos->get_types(0);
        
        while (!list.empty()){
            tmp = list.front();
            result += encajar_en_palabra(tamano_tipo(tmp));
            list.pop_front();
        }

        return result;
    }

    /* FALTA TAMBIEN ARREGLAR ESTE CASO */
    if (t->is_union()){
        result = 0;
        TypeS* tmp;
        TypeUnion* u = (TypeUnion*) t;
        std::list<TypeS*> list = u->atributos->get_types(0);
        while (!list.empty()){
            tmp = list.front();
            result = std::max(result, encajar_en_palabra(tamano_tipo(tmp)));
            list.pop_front();
        }
        return result;
    }

    if (t->is_array()){
        int tam = t->get_dimensiones();
        result = 1;
        return (result * tam * encajar_en_palabra(tamano_tipo(t->get_tipo())) ); 
    }
    return -1; 
}

