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

std::string Symbol::show(){
    std::string result;
    result = "Name: " + this->sym_name;
    result +="\nCategory: " +this->sym_catg;
    //result +="\ntype: " + type->this->sym_name;
    return result;
}
