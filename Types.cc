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

bool TypeReal::is_numeric() { return true; }

bool TypeReal::is_error() { return false; }

bool TypeReal::is_bool() { return false; } 

bool TypeReal::is_char() { return false; }

bool TypeReal::is_str() { return false; }

bool TypeReal::is_func(){ return false; }

bool TypeReal::is_structure() { return false; }

bool TypeReal::is_union() { return false; }

bool TypeReal::is_void(){ return false;  }

/* class TypeInt */

TypeInt::TypeInt(){}
TypeInt::~TypeInt(){}

bool TypeInt::is_numeric() { return true; }

bool TypeInt::is_error() { return false; }

bool TypeInt::is_bool() { return false; } 

bool TypeInt::is_char() { return false; }

bool TypeInt::is_str() { return false; }

bool TypeInt::is_func(){ return false; }

bool TypeInt::is_structure() { return false; }

bool TypeInt::is_union() { return false; }

bool TypeInt::is_void(){ return false;  }

/* class TypeError */

TypeError::TypeError(){}
TypeError::~TypeError(){}

bool TypeError::is_numeric() { return false; }

bool TypeError::is_error() { return true; }

bool TypeError::is_bool() { return false; } 

bool TypeError::is_char() { return false; }

bool TypeError::is_str() { return false; }

bool TypeError::is_func(){ return false; }

bool TypeError::is_structure() { return false; }

bool TypeError::is_union() { return false; }

bool TypeError::is_void(){ return false;  }

/* class TypeBool */
TypeBool::TypeBool(){}

TypeBool::~TypeBool(){}

bool TypeBool::is_numeric() { return false; }

bool TypeBool::is_error() { return false; }

bool TypeBool::is_bool() { return true; } 

bool TypeBool::is_char() { return false; }

bool TypeBool::is_str() { return false; }

bool TypeBool::is_func(){ return false; }

bool TypeBool::is_structure() { return false; }

bool TypeBool::is_union() { return false; }

bool TypeBool::is_void(){ return false;  }                                                                                                                                               
/* class TypeChar */

TypeChar::TypeChar(){}

TypeChar::~TypeChar(){}

bool TypeChar::is_numeric() { return false; }

bool TypeChar::is_error() { return false; }

bool TypeChar::is_bool() { return false; } 

bool TypeChar::is_char() { return true; }

bool TypeChar::is_str() { return false; }

bool TypeChar::is_func(){ return false; }

bool TypeChar::is_structure() { return false; }

bool TypeChar::is_union() { return false; }

bool TypeChar::is_void(){ return false;  }                                                                                                                                               
/* class TypeString */

TypeString::TypeString(){}

TypeString::~TypeString(){}

bool TypeString::is_numeric() { return false; }

bool TypeString::is_error() { return false; }

bool TypeString::is_bool() { return false; } 

bool TypeString::is_char() { return false; }

bool TypeString::is_str() { return true; }

bool TypeString::is_func(){ return false; }

bool TypeString::is_structure() { return false; }

bool TypeString::is_union() { return false; }

bool TypeString::is_void(){ return false;  }                                                                                                                                             

/* class TypeFunction */

TypeFunction::TypeFunction(TypeS* r,std::list<TypeS*> lp):rango (r),parametros(lp){}

TypeFunction::~TypeFunction(){}

bool TypeFunction::is_numeric() { return false; }

bool TypeFunction::is_error() { return false; }

bool TypeFunction::is_bool() { return false; } 

bool TypeFunction::is_char() { return false; }

bool TypeFunction::is_str() { return false; }

bool TypeFunction::is_func(){ return false; }

bool TypeFunction::is_structure() { return false; }

bool TypeFunction::is_union() { return false; }

bool TypeFunction::is_void(){ return false;  }                                                                                                                                           
/* class TypeStructure */

TypeStructure::TypeStructure(std::list<TypeS*> la): atributos(la){}

TypeStructure::~TypeStructure(){}

bool TypeStructure::is_numeric() { return false; }

bool TypeStructure::is_error() { return false; }

bool TypeStructure::is_bool() { return false; } 

bool TypeStructure::is_char() { return false; }

bool TypeStructure::is_str() { return false; }

bool TypeStructure::is_func(){ return false; }

bool TypeStructure::is_structure() { return true; }

bool TypeStructure::is_union() { return false; }

bool TypeStructure::is_void(){ return false;  }                                                                                                                                                 
/* class TypeUnion */

TypeUnion::TypeUnion(std::list<TypeS*> la):atributos(la){}

TypeUnion::~TypeUnion(){}

bool TypeUnion::is_numeric() { return false; }

bool TypeUnion::is_error() { return false; }

bool TypeUnion::is_bool() { return false; } 

bool TypeUnion::is_char() { return false; }

bool TypeUnion::is_str() { return false; }

bool TypeUnion::is_func(){ return false; }

bool TypeUnion::is_structure() { return false; }

bool TypeUnion::is_union() { return true; }

bool TypeUnion::is_void(){ return false;  }

/* class TypeVoid */

TypeVoid::TypeVoid(){}

TypeVoid::~TypeVoid(){}

bool TypeVoid::is_numeric(){ return false; }

bool TypeVoid::is_error(){ return false; }

bool TypeVoid::is_bool(){ return false; }

bool TypeVoid::is_char(){ return false; }

bool TypeVoid::is_str(){ return false; }

bool TypeVoid::is_func(){ return false;}

bool TypeVoid::is_structure(){return false; }

bool TypeVoid::is_union(){ return false; }

bool TypeVoid::is_void(){ return true;  }                                                                                                  

/* class TypeArray */

TypeArray::TypeArray(TypeS* t, int s, int* d ): tipo(t), size(s), dimensiones(d){}

TypeArray::~TypeArray(){}

bool TypeArray::is_numeric(){ return false; }

bool TypeArray::is_error(){ return false; }

bool TypeArray::is_bool(){ return false; }

bool TypeArray::is_char(){ return false; }

bool TypeArray::is_str(){ return false; }

bool TypeArray::is_func(){ return false;}

bool TypeArray::is_structure(){return false; }

bool TypeArray::is_union(){ return false; }

bool TypeArray::is_void(){ return false;  }
