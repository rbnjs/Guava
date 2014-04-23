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
// Consideraciones:
// Falta is_array()
// Falta TypeArray
// Faltan funciones para ver que hay adentro del tipo
class TypeS{
public :
    virtual bool is_int() = 0; 
    virtual bool is_real() = 0;
    virtual bool is_error() = 0;
    virtual bool is_bool() = 0;
    virtual bool is_char() = 0;
    virtual bool is_str() = 0;
    virtual bool is_func() = 0;
    virtual bool is_structure() = 0;
    virtual bool is_union() = 0;
    virtual bool is_void() = 0;
    virtual bool is_reference() = 0;
    virtual TypeS* get_tipo() = 0;
    virtual std::pair<int,int*> get_dimensiones() = 0;
    virtual std::list<TypeS*> get_atributos()= 0; 
};

class TypeReal :public TypeS{
public :
    TypeReal();
    ~TypeReal();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    TypeS* get_tipo();
    std::pair<int,int*> get_dimensiones();
    std::list<TypeS*> get_atributos();
};

class TypeInt :public TypeS{
public :
    TypeInt();
    ~TypeInt();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    TypeS* get_tipo();
    std::pair<int,int*> get_dimensiones();
    std::list<TypeS*> get_atributos();
};

class TypeError :public TypeS{
public:
    TypeError();
    ~TypeError();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
};

class TypeVoid :public TypeS{
public:
    TypeVoid();
    ~TypeVoid();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
};

class TypeBool:public TypeS{
public:
    TypeBool();
    ~TypeBool();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
};

class TypeChar:public TypeS{
public:
    TypeChar();
    ~TypeChar();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
};
class TypeString:public TypeS{
public:
    TypeString();
    ~TypeString();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
};

class TypeFunction:public TypeS{
public:
    TypeFunction(TypeS*,std::list<TypeS*>); 
    ~TypeFunction(); 
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
private :
    TypeS* tipo;
    std::list<TypeS*> parametros;
};

class TypeStructure :public TypeS{
public :
    TypeStructure(std::list<TypeS*>);
    ~TypeStructure();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
private :
    std::list<TypeS*> atributos;
};

class TypeUnion :public TypeS{
public :
    TypeUnion(std::list<TypeS*>);
    ~TypeUnion();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
private:
    std::list<TypeS*> atributos;
};

class TypeArray:public TypeS{
public :
    TypeArray(TypeS*,int, int*);
    ~TypeArray();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
    std::pair<int,int*> get_dimensiones();
private:
    TypeS* tipo;
    int size;
    int* dimensiones;
};

class TypeReference: public TypeS{
public :
    TypeReference(TypeS*);
    ~TypeReference();
    bool is_int() ; 
    bool is_real ();
    bool is_error() ;
    bool is_bool() ;
    bool is_char() ;
    bool is_str() ;
    bool is_func() ;
    bool is_structure() ;
    bool is_union() ;
    bool is_void();
    bool is_reference();
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::list<TypeS*> get_atributos();
private:
    TypeS* referencia;   
};
