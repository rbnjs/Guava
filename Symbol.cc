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
Symbol::Symbol(std::string name, std::string catg, int scop, std::string s) {
    this->sym_name = name;
    this->sym_catg = catg;
    this->scope = scop;
    this->type = s;
}

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
    std::cout << identacion << "Name: " + sym_name;
    std::cout << " Category: " +sym_catg;
    std::cout << " Type: "+ type << '\n';
}

SymbolArray::SymbolArray(std::string name, std::string catg,int scop, std::string type, int* array,int siz):
        Symbol(name,catg,scop,type), arreglo(array), size(siz){}

SymbolArray::~SymbolArray(){
    delete[] arreglo;
}

void SymbolArray::show(std::string identacion){
    std::cout << identacion << "Name: " + sym_name;
    std::cout << " Category: " +sym_catg;
    std::cout << " Size: ";
    for (int i = 0; i  !=  size; i++){
        std::cout << "[" << arreglo[i] << "] ";
    }
    std::cout << "Type: "+ type << '\n';
}

SymbolStructure::SymbolStructure(std::string name, std::string catg, int scop, std::string type, int fscop):
                    Symbol(name,catg,scop,type), fieldScope(fscop){}

SymbolStructure::~SymbolStructure(){
}
