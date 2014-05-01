/*
 * =====================================================================================
 *
 *       Filename:  Symbol.cc
 *
 *    Description:  Implementacion de Symbol.
 *
 *        Version:  1.0
 *        Created:  12/03/14 14:25:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <iostream>
#include "Symbol.hh"

Symbol::Symbol(){}

/* Constructor de la clase Symbol deprecado */
Symbol::Symbol(std::string name, std::string catg, int scop, std::string p,int linea, int columna) {
    sym_name = name;
    sym_catg = catg;
    scope = scop;

    type = p;

    size = 0;
    arreglo = 0;
    fieldScope = 0;
    line = linea;
    column = columna;

}

Symbol::Symbol(std::string name, std::string catg, int scop, Symbol* p,int linea, int columna) {
    sym_name = name;
    sym_catg = catg;
    scope = scop;

    type_pointer = p;
    true_type = 0;
    size = 0;
    arreglo = 0;
    fieldScope = 0;
    line = linea;
    column = columna;
}

/**
 * Constructor para arreglo 
 */
Symbol::Symbol(std::string name, std::string catg, int scop, std::string s,int linea, int columna, int* array,int tam){
    this->sym_name = name;
    this->sym_catg = catg;
    this->scope = scop;
    this->type = s;
    size = tam;
    arreglo = array;
    true_type = 0;
    fieldScope = 0;   
    line = linea;
    column = columna;
}
/**
 * Constructor para arreglo actualizado.
 */
Symbol(std::string name, std::string catg,
       int scop, TypeS* type,int linea,int columna): sym_name(name),sym_catg(catg),scope(scop),true_type(type),line(linea),column(columna){} 

/**
 * Constructor para estructuras.
 */
Symbol::Symbol(std::string name,std::string catg ,int scop,std::string s,int linea, int columna,int fsc){
    this->sym_name = name;
    this->sym_catg = catg;
    this->scope = scop;
    this->type = s;
    size = 0;
    arreglo = 0;
    true_type = 0;
    fieldScope = fsc;   
    column = columna;
    line =  linea;
}


/**
 * Constructor para types
 */
Symbol::Symbol(std::string name, std::string catg,int s,TypeS* type): sym_name(name), sym_catg (catg), scope(s), true_type(type) {}

/**
 * Constructor para records y unions
 */
Symbol::Symbol(std::string name, std::string catg,int s,TypeS* type, int fsc): sym_name(name), sym_catg (catg), scope(s), true_type(type), fieldScope(fsc) {}

/**  
 * Destructor de la clase Symbol.
 */
Symbol::~Symbol(){
}

/**
 * Se utiliza el operador == para comparar. 
 */
bool Symbol::operator==(Symbol b) {
    return ((this->sym_name.compare(b.sym_name) == 0) && this->scope == b.scope);
}

/** 
 * Compara nombres y alcance 
 */
bool Symbol::compare(std::string s, int sc){
    return ((this->sym_name.compare(s) == 0) && this->scope == sc);
}

void Symbol::show(std::string identacion){
    if (size == 0){
        std::cout << identacion << "Name: " + sym_name;
        std::cout << " Category: " +sym_catg;
        std::cout << " Line: ";
        std::cout << line;
        std::cout << " Column: ";
        std::cout << column;
    } else{
        std::cout << identacion << "Name: " + sym_name;
        std::cout << " Category: " +sym_catg;
        std::cout << " Line: ";
        std::cout << line;
        std::cout << " Column: ";
        std::cout << column;
        std::cout << " Max Index: "; 
        for (int i = 0; i != size; i++){
            std::cout << "[" << arreglo[i] << "] ";
        }
        std::cout <<'\n';
    }
}


