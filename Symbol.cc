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
Symbol::Symbol(){}
/**
 * Constructor de la clase Symbol.
 */
Symbol::Symbol(std::string name, std::string catg, int scop, std::string s,int linea, int columna) {
    this->sym_name = name;
    this->sym_catg = catg;
    this->scope = scop;
    this->type = s;
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
    fieldScope = 0;   
    line = linea;
    column = columna;
}
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
    fieldScope = fsc;   
    column = columna;
    line =  linea;
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
    if (size == 0){
        std::cout << identacion << "Name: " + sym_name;
        std::cout << " Category: " +sym_catg;
        std::cout << " Type: "+ type << '\n';
    } else{
        std::cout << identacion << "Name: " + sym_name;
        std::cout << " Category: " +sym_catg;
        std::cout << " Type: " +type ;
        std::cout << " Max Index: "; 
        for (int i = 0; i != size; i++){
            std::cout << "[" << arreglo[i] << "] ";
        }
        std::cout <<'\n';
    }
}

/*SymbolArray::SymbolArray(std::string name, std::string catg,int scop, std::string type, int* array,int siz):
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

void SymbolStructure::show(std::string){

}

SymbolFunction::SymbolFunction(std::string name, std::string catg, int scop, std::string type, int fscop):
                    Symbol(name,catg,scop,type), paramScope(fscop){}

SymbolFunction::~SymbolFunction(){
}

void SymbolFunction::show(std::string){}

SymbolReference::SymbolReference(std::string name, std::string catg, int scope, std::string type):
        Symbol(name,catg,scope,type){}

SymbolReference::~SymbolReference(){}*/
