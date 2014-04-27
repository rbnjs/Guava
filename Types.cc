/*
 * =====================================================================================
 *
 *       Filename:  Types.cc
 *
 *    Description: Implementacion de Types.hh 
 *
 *        Version:  1.0
 *        Created:  15/04/14 14:52:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas 
 *   Organization: USB 
 *
 * =====================================================================================
 */

#include "Types.hh"

/**
 * Apuntadores globales a las unicas instancias de las clases de cada tipo.
 */
TypeReal* TypeReal::real_instance = 0;
TypeInt* TypeInt::int_instance = 0;
TypeError* TypeError::error_instance = 0;
TypeBool* TypeBool::bool_instance = 0;
TypeChar* TypeChar::char_instance = 0;
TypeString* TypeString::string_instance = 0;
TypeVoid* TypeVoid::void_instance = 0;
//Faltaria definir para las uniones y records.

/* class TypeReal  */

TypeReal* TypeReal::Instance() {
    if(real_instance == 0)
        real_instance = new TypeReal;

    return real_instance;
}

bool TypeReal::is_real() { return true; }

TypeS* TypeReal::get_tipo() { return 0; }

std::pair<int,int*> TypeReal::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeReal::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeInt */

TypeInt* TypeInt::Instance() {
    if(int_instance == 0)
        int_instance = new TypeInt;

    return int_instance;
}

bool TypeInt::is_int() { return true; }

TypeS* TypeInt::get_tipo() { return 0; }

std::pair<int,int*> TypeInt::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeInt::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeError */

TypeError* TypeError::Instance() {
    if(error_instance == 0)
        error_instance = new TypeError;

    return error_instance;
}

bool TypeError::is_error() { return true; }

TypeS* TypeError::get_tipo() { return 0; }

std::pair<int,int*> TypeError::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeError::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeBool */

TypeBool* TypeBool::Instance() {
    if(bool_instance == 0)
        bool_instance = new TypeBool;

    return bool_instance;
}

bool TypeBool::is_bool() { return true; } 

TypeS* TypeBool::get_tipo() { return 0; }

std::pair<int,int*> TypeBool::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeBool::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeChar */

TypeChar* TypeChar::Instance() {
    if(char_instance == 0)
        char_instance = new TypeChar;

    return char_instance;
}

bool TypeChar::is_char() { return true; }

TypeS* TypeChar::get_tipo() { return 0; }

std::pair<int,int*> TypeChar::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeChar::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeString */

TypeString* TypeString::Instance() {
    if(string_instance == 0)
        string_instance = new TypeString;

    return string_instance;
}

bool TypeString::is_str() { return true; }

TypeS* TypeString::get_tipo() { return 0; }

std::pair<int,int*> TypeString::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeString::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeFunction */

TypeFunction::TypeFunction(TypeS* r,std::list<TypeS*> lp):tipo (r),parametros(lp){}

bool TypeFunction::is_func(){ return true; }

TypeS* TypeFunction::get_tipo() { return tipo; }

std::pair<int,int*> TypeFunction::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeFunction::get_atributos(){
    return parametros;
}

/* class TypeStructure */

TypeStructure::TypeStructure(std::list<TypeS*> la): atributos(la){}

bool TypeStructure::is_structure() { return true; }

TypeS* TypeStructure::get_tipo() { return 0; }

std::pair<int,int*> TypeStructure::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeStructure::get_atributos(){
    return atributos;
}

/* class TypeUnion */

TypeUnion::TypeUnion(std::list<TypeS*> la):atributos(la){}

bool TypeUnion::is_union() { return true; }

TypeS* TypeUnion::get_tipo() { return 0; }

std::pair<int,int*> TypeUnion::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeUnion::get_atributos(){
    return atributos;
}


/* class TypeVoid */

TypeVoid* TypeVoid::Instance() {
    if(void_instance == 0)
        void_instance = new TypeVoid;

    return void_instance;
}

bool TypeVoid::is_void(){ return true;  }                                                                                                  

TypeS* TypeVoid::get_tipo() { return 0; }

std::pair<int,int*> TypeVoid::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeVoid::get_atributos(){
    std::list<TypeS*> r;
    return r;
}

/* class TypeArray */

TypeArray::TypeArray(TypeS* t, int s, int* d ): tipo(t), size(s), dimensiones(d){}

TypeS* TypeArray::get_tipo() { return tipo; }

std::pair<int,int*> TypeArray::get_dimensiones(){
    std::pair<int,int*> p; 
    p.first = size;
    p.second = dimensiones;
    return p;
}

std::list<TypeS*> TypeArray::get_atributos(){
    std::list<TypeS*> r;
    return r;
}
/* class Reference */

TypeReference::TypeReference(TypeS* t): referencia(t){}

bool TypeReference::is_reference() { return true; }

TypeS* TypeReference::get_tipo() { return referencia; }

std::pair<int,int*> TypeReference::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeReference::get_atributos(){
    std::list<TypeS*> r;
    return r;
}
