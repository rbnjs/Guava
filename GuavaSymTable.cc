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
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GuavaSymTable.hh"

/**
 * Constructor de la clase
 */
GuavaSymTable::GuavaSymTable(){
    alcance = 0;
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

void GuavaSymTable::insert(std::string name, std::string catg, int sc, Symbol* symbol){
   Symbol* nuevo = new Symbol(name, catg, sc, symbol); 
   this->insert(*nuevo);
}

void GuavaSymTable::insert(std::string name,std::string catg,int sc,std::string tipo){    
    Symbol* type = this->lookupType(tipo);
    this->insert(name,catg,sc,type);
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
 * Busca un tipo determinado.
 */
Symbol* GuavaSymTable::lookupType(std::string type){
    if (!tabla[type].empty()){
        if (tabla[type].size() == 1){
            std::list<Symbol> l = tabla[type];
            return &l.front();
        }
        return 0;
    }
    return 0;
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
 * Muestra el contenido de la tabla de simbolos.
 * */
void GuavaSymTable::show(int scope, std::string identacion){
    std::map<std::string, std::list<Symbol> >::iterator itTabla = this->tabla.begin();
    for (itTabla ; itTabla != this->tabla.end() ; ++itTabla){
        std::list<Symbol>::iterator itList = itTabla->second.begin();
        for (itList ; itList != itTabla->second.end() ; ++itList){
            Symbol tmp = *itList;
            if (tmp.scope == scope) tmp.show(identacion);
        }
    }
}

/* falta la funcion update */
