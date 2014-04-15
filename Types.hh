/*
 * =====================================================================================
 *
 *       Filename :  Types.hh
 *
 *    Description :  Clases de tipos para el sistema de tipos de Guava.
 *
 *        Version :  1.0
 *        Created :  08/05/14 11 :17 :16
 *       Revision :  none
 *       Compiler :  gcc
 *
 *         Author :  YOUR NAME (), 
 *   Organization :  
 *
 * =====================================================================================
 */
#include <list>

class TypeS{
public :
   virtual bool is_numeric() = 0; 
   virtual bool is_error() = 0;
   virtual bool is_bool() = 0;
   virtual bool is_char() = 0;
   virtual bool is_str() = 0;
   virtual bool is_func() = 0;
   virtual bool is_structure() = 0;
   virtual bool is_union() = 0;
};

class TypeReal :public TypeS{
public :
    TypeReal();
    ~TypeReal();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
};

class TypeInt :public TypeS{
public :
    TypeInt();
    ~TypeInt();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
};

class TypeError :public TypeS{
public:
    TypeError();
    ~TypeError();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
};

class TypeBool:public TypeS{
public:
    TypeBool();
    ~TypeBool();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
};

class TypeChar:public TypeS{
public:
    TypeChar();
    ~TypeChar();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
};
class TypeString:public TypeS{
public:
    TypeString();
    ~TypeString();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
};
class TypeFunction:public TypeS{
public:
    TypeFunction(TypeS*,std::list<TypeS*>); 
    ~TypeFunction(); 
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
private :
    TypeS* rango;
    std::list<TypeS*> parametros;
};

class TypeStructure :public TypeS{
public :
    TypeStructure(std::list<TypeS*>);
    ~TypeStructure();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
private :
    std::list<TypeS*> atributos;
};

class TypeUnion :public TypeS{
public :
    TypeUnion(std::list<TypeS*>);
    ~TypeUnion();
    bool is_numeric() ; 
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
private:
    std::list<TypeS*> atributos;
};
