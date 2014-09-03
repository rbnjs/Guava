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
#include <sstream>

Symbol::Symbol(){}

/**
 * Constructor para variable
 */
Symbol::Symbol(std::string name, std::string catg, 
               int scop, Symbol* p,int linea, int columna, 
               int offset_): sym_name(name), sym_catg(catg), scope(scop), 
                             true_type(0), type_pointer(p), line(linea), column(columna), offset(offset_){}

/**
 * Constructor para tipos basicos, estructuras, uniones y arreglos.
 */
Symbol::Symbol(std::string name, std::string catg,
               int scop, TypeS* type,int linea,
               int columna, int offset_): sym_name(name),sym_catg(catg),
                                                 scope(scop),true_type(type), type_pointer(0),
                                                 line(linea),column(columna), offset(offset_){} 


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

std::string to_string(TypeS* t){
    if (t->is_func()){
        std::string result ("(");
        std::list<TypeS*> tmp = t->get_parametros();
        while (!tmp.empty()){
            TypeS* parametro = tmp.front();
            result += to_string(parametro);
            tmp.pop_front();
            result += (!tmp.empty() ? ", " : "");
        }
        result += ") -> ";
        result += to_string(t->get_tipo());
        return result;
    }
    if (t->is_array()){
        std::string result ("array[");
        int tam = t->get_dimensiones();
        std::ostringstream convert;
        convert << tam;
        result += convert.str();
        result += "] of" + to_string(t->get_tipo()); 

        return result;
    }
    return t->get_name();
}

/**
 * Impresion del simbolo.
 * Falta imprimir todo bien.
 */
void Symbol::show(std::string identacion){
        std::cout << identacion << "Name: " + sym_name;
        std::cout << " Category: " +sym_catg;
        std::cout << " Line: ";
        std::cout << line;
        std::cout << " Column: ";
        std::cout << column;
        std::cout << " Type: " + ( (true_type != 0) ? to_string(true_type) : to_string(this->type_pointer->true_type) );
        std::cout << " Offset: ";
        std::cout << offset;
        std::cout << "\n";
}
