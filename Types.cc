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

/* class TypeReal  */

TypeReal::TypeReal() { }
TypeReal::~TypeReal() { }

bool TypeReal::is_int() { return false; }

bool TypeReal::is_real() { return true; }

bool TypeReal::is_error() { return false; }

bool TypeReal::is_bool() { return false; } 

bool TypeReal::is_char() { return false; }

bool TypeReal::is_str() { return false; }

bool TypeReal::is_func(){ return false; }

bool TypeReal::is_structure() { return false; }

bool TypeReal::is_union() { return false; }

bool TypeReal::is_void(){ return false;  }

bool TypeReal::is_reference() { return false; }

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

TypeInt::TypeInt(){}
TypeInt::~TypeInt(){}

bool TypeInt::is_int() { return true; }

bool TypeInt::is_real() { return false; }

bool TypeInt::is_error() { return false; }

bool TypeInt::is_bool() { return false; } 

bool TypeInt::is_char() { return false; }

bool TypeInt::is_str() { return false; }

bool TypeInt::is_func(){ return false; }

bool TypeInt::is_structure() { return false; }

bool TypeInt::is_union() { return false; }

bool TypeInt::is_void(){ return false;  }

bool TypeInt::is_reference() { return false; }

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

TypeError* TypeError::instance = 0;

TypeError::TypeError(){}

TypeError* TypeError::Instance(){
    if (instance == 0){
        instance = new TypeError();
        return instance;
    } 
    return instance;
}


TypeError::~TypeError(){}

bool TypeError::is_int() { return false; }

bool TypeError::is_real() { return false; }

bool TypeError::is_error() { return true; }

bool TypeError::is_bool() { return false; } 

bool TypeError::is_char() { return false; }

bool TypeError::is_str() { return false; }

bool TypeError::is_func(){ return false; }

bool TypeError::is_structure() { return false; }

bool TypeError::is_union() { return false; }

bool TypeError::is_void(){ return false;  }

bool TypeError::is_reference() { return false; }

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
TypeBool::TypeBool(){}

TypeBool::~TypeBool(){}

bool TypeBool::is_int() { return false; }

bool TypeBool::is_real() { return false; }

bool TypeBool::is_error() { return false; }

bool TypeBool::is_bool() { return true; } 

bool TypeBool::is_char() { return false; }

bool TypeBool::is_str() { return false; }

bool TypeBool::is_func(){ return false; }

bool TypeBool::is_structure() { return false; }

bool TypeBool::is_union() { return false; }

bool TypeBool::is_void(){ return false;  }                                                                                                            

bool TypeBool::is_reference() { return false; }

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

TypeChar::TypeChar(){}

TypeChar::~TypeChar(){}

bool TypeChar::is_int() { return false; }

bool TypeChar::is_real() { return false; }

bool TypeChar::is_error() { return false; }

bool TypeChar::is_bool() { return false; } 

bool TypeChar::is_char() { return true; }

bool TypeChar::is_str() { return false; }

bool TypeChar::is_func(){ return false; }

bool TypeChar::is_structure() { return false; }

bool TypeChar::is_union() { return false; }

bool TypeChar::is_void(){ return false;  }                                                                                                             

bool TypeChar::is_reference() { return false; }

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

TypeString::TypeString(){}

TypeString::~TypeString(){}

bool TypeString::is_int() { return false; }

bool TypeString::is_real() { return false; }

bool TypeString::is_error() { return false; }

bool TypeString::is_bool() { return false; } 

bool TypeString::is_char() { return false; }

bool TypeString::is_str() { return true; }

bool TypeString::is_func(){ return false; }

bool TypeString::is_structure() { return false; }

bool TypeString::is_union() { return false; }

bool TypeString::is_void(){ return false;  }                                                                                                            

bool TypeString::is_reference() { return false; }

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

TypeFunction::~TypeFunction(){}

bool TypeFunction::is_int() { return false; }

bool TypeFunction::is_real() { return false; }

bool TypeFunction::is_error() { return false; }

bool TypeFunction::is_bool() { return false; } 

bool TypeFunction::is_char() { return false; }

bool TypeFunction::is_str() { return false; }

bool TypeFunction::is_func(){ return false; }

bool TypeFunction::is_structure() { return false; }

bool TypeFunction::is_union() { return false; }

bool TypeFunction::is_void(){ return false;  }                                                                                                            

bool TypeFunction::is_reference() { return false; }

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

TypeStructure::~TypeStructure(){}

bool TypeStructure::is_int() { return false; }

bool TypeStructure::is_real() { return false; }

bool TypeStructure::is_error() { return false; }

bool TypeStructure::is_bool() { return false; } 

bool TypeStructure::is_char() { return false; }

bool TypeStructure::is_str() { return false; }

bool TypeStructure::is_func(){ return false; }

bool TypeStructure::is_structure() { return true; }

bool TypeStructure::is_union() { return false; }

bool TypeStructure::is_void(){ return false;  }                                                                               

bool TypeStructure::is_reference() { return false; }

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

TypeUnion::~TypeUnion(){}

bool TypeUnion::is_int() { return false; }

bool TypeUnion::is_real() { return false; }

bool TypeUnion::is_error() { return false; }

bool TypeUnion::is_bool() { return false; } 

bool TypeUnion::is_char() { return false; }

bool TypeUnion::is_str() { return false; }

bool TypeUnion::is_func(){ return false; }

bool TypeUnion::is_structure() { return false; }

bool TypeUnion::is_union() { return true; }

bool TypeUnion::is_void(){ return false;  }

bool TypeUnion::is_reference() { return false; }

TypeS* TypeUnion::get_tipo() { return 0; }

std::pair<int,int*> TypeUnion::get_dimensiones(){
    std::pair<int,int*> p; 
    return p;
}

std::list<TypeS*> TypeUnion::get_atributos(){
    return atributos;
}


/* class TypeVoid */

TypeVoid::TypeVoid(){}

TypeVoid::~TypeVoid(){}

bool TypeVoid::is_int(){ return false; }

bool TypeVoid::is_real() { return false; }

bool TypeVoid::is_error(){ return false; }

bool TypeVoid::is_bool(){ return false; }

bool TypeVoid::is_char(){ return false; }

bool TypeVoid::is_str(){ return false; }

bool TypeVoid::is_func(){ return false;}

bool TypeVoid::is_structure(){return false; }

bool TypeVoid::is_union(){ return false; }

bool TypeVoid::is_void(){ return true;  }                                                                                                  

bool TypeVoid::is_reference() { return false; }

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

TypeArray::~TypeArray(){}

bool TypeArray::is_int(){ return false; }

bool TypeArray::is_real() { return false; }

bool TypeArray::is_error(){ return false; }

bool TypeArray::is_bool(){ return false; }

bool TypeArray::is_char(){ return false; }

bool TypeArray::is_str(){ return false; }

bool TypeArray::is_func(){ return false;}

bool TypeArray::is_structure(){return false; }

bool TypeArray::is_union(){ return false; }

bool TypeArray::is_void(){ return false;  }

bool TypeArray::is_reference() { return false; }

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

TypeReference::~TypeReference(){}

bool TypeReference::is_int(){ return false; }

bool TypeReference::is_real() { return false; }

bool TypeReference::is_error(){ return false; }

bool TypeReference::is_bool(){ return false; }

bool TypeReference::is_char(){ return false; }

bool TypeReference::is_str(){ return false; }

bool TypeReference::is_func(){ return false;}

bool TypeReference::is_structure(){return false; }

bool TypeReference::is_union(){ return false; }

bool TypeReference::is_void(){ return false;}

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
