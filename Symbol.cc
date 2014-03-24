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
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <iostream>
#include "Symbol.hh"
/**
 * Constructor de la clase Symbol.
 */
Symbol::Symbol(std::string name, std::string catg, int scop, Symbol s) {
    this->sym_name = name;
    this->sym_catg = catg;
    this->scope = scop;
    this->type = &s;
}

/**
 * Constructor de la clase Symbol.
 */
Symbol::Symbol(std::string name, std::string catg, int scop) {
    this->sym_name = name;
    this->sym_catg = catg;
    this->scope = scop;
    type = 0;
}

/**  
 * Destructor de la clase Symbol.
 */
Symbol::~Symbol(){
    delete type;
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
    std::cout << identacion << "Name: " + sym_name << '\n';
    std::cout << identacion <<"Category: " +sym_catg;

}
