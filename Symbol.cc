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
#include <regex>

using namespace std;

bool is_number_func(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || std::ispunct(*it))) ++it;
    return !s.empty() && it == s.end();
}


/** 
 * Indica que un Simbolo es temporal.
 * @return true si el nombre del simbolo comienza por _t o false en el caso contrario.
 */
bool SimpleSymbol::is_temp(){
    std::regex underscore ("_t.*"); //Cualquier cosa que comience con _t es temporal.
    return std::regex_match (sym_name, underscore);
}

Symbol::Symbol(){}

/**
 * Constructor para variable
 */
Symbol::Symbol(std::string name, std::string catg, 
               int scop, Symbol* p,int linea, int columna, 
               int offset_): SimpleSymbol(name), sym_catg(catg), scope(scop), 
                             true_type(0), type_pointer(p), line(linea), column(columna), offset(offset_){}

/**
 * Constructor para tipos basicos, estructuras, uniones y arreglos.
 */
Symbol::Symbol(std::string name, std::string catg,
               int scop, TypeS* type,int linea,
               int columna, int offset_): SimpleSymbol(name),sym_catg(catg),
                                                 scope(scop),true_type(type), type_pointer(0),
                                                 line(linea),column(columna), offset(offset_){} 

/**
 * Constructor basico para nombres y valores.
 */
Symbol::Symbol(std::string name): SimpleSymbol(name), true_type(0), type_pointer(0) {}

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

/** 
 * Funcion que nos dice si el simbolo es global.
 */
bool Symbol::is_global(){
    return (scope == 1);
}

/**  
 * Traduce un nombre de simbolo a mips.
 */
string Symbol::nombre_mips(){
    regex underscore ("bp.*");
    ostringstream convert; 
    convert << offset;
    if (regex_match (sym_name, underscore)){
        return convert.str()+"($fp)";
    }else{
        return sym_name;
    }

}

/** 
 * Obtiene recursivamente el tipo de un simbolo.
 */
TypeS* Symbol::get_tipo(){
    if (true_type != 0) return true_type;
    if (type_pointer != 0) return type_pointer->get_tipo();
    return 0;
}

/** 
 * Genera codigo para mips.
 * @param g Generador
 */
void Symbol::generar_mips(GuavaGenerator* g){
    ostringstream convert;
    if (contenido.empty()){
        if (width > 0){
            convert << width;
            *g << sym_name + ": .space " + convert.str() + "\n";
        }
    }else{
        *g << sym_name+ ": .asciiz " +contenido + "\n";
    }
}

/** 
 * Convierte un TypeS* en string.
 * @param t TypeS*
 * @return string Retorna un string
 */
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
        result += "] of " + to_string(t->get_tipo()); 

        return result;
    }
    return t->get_name();
}

/**
 * Impresion del simbolo.
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
        std::cout << " Scope: ";
        std::cout << scope;
        std::cout << "\n";
}
