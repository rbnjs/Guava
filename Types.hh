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
#include <unordered_map>
#include <string>


class TypeS{
public :
    virtual bool is_int() { return false; }; 
    virtual bool is_real() { return false; };
    virtual bool is_error() { return false; };
    virtual bool is_bool() { return false; };
    virtual bool is_char() { return false; };
    virtual bool is_str() { return false; };
    virtual bool is_func() { return false; };
    virtual bool is_structure() { return false; };
    virtual bool is_union() { return false; };
    virtual bool is_void() { return false; };
    virtual bool is_reference() { return false; };
    virtual bool is_array() { return false; }
    virtual TypeS* get_tipo()=0;
    virtual std::string get_name() { return "defaulttype"; };
    virtual int get_dimensiones() { return -1; };
    virtual std::list<TypeS*> get_parametros()  { std::list<TypeS*> s; return s; } 
};

class TypeReal :public TypeS{
public :
    ~TypeReal();
    static TypeReal* Instance();
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
    bool is_array();
    TypeS* get_tipo();
    std::string get_name();
    
private:
    TypeReal(){};
    static TypeReal* real_instance;
};

class TypeInt :public TypeS{
public :
    ~TypeInt();
    static TypeInt* Instance();
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
    
private:
    TypeInt(){};
    static TypeInt* int_instance;
};

class TypeError :public TypeS{
public:
    ~TypeError();
    static TypeError* Instance();
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
private:
    TypeError(){};
    static TypeError* error_instance;
};

class TypeVoid :public TypeS{
public:
    ~TypeVoid();
    static TypeVoid* Instance();
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
    
private:
    TypeVoid(){};
    static TypeVoid* void_instance;
};

class TypeBool:public TypeS{
public:
    ~TypeBool();
    static TypeBool* Instance();
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
private:
    TypeBool(){};
    static TypeBool* bool_instance;
};

class TypeChar:public TypeS{
public:
    ~TypeChar();
    static TypeChar* Instance();
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
    
private:
    TypeChar(){};
    static TypeChar* char_instance;
};

class TypeString:public TypeS{
public:
    ~TypeString();
    static TypeString* Instance();
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
    
private:
    TypeString(){};
    static TypeString* string_instance;
};

class TypeFunction:public TypeS{
public:
    TypeS* tipo;
    std::list<TypeS*> parametros;
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
    bool is_array();   
    std::list<TypeS*> get_parametros();
    TypeS* get_tipo();
    std::string get_name();
};

/**
 * Clase que representa un Tipo Arreglo de manera recursiva.
 */
class TypeArray:public TypeS{
public :
    TypeArray(TypeS*,int);
    ~TypeArray();
    TypeS* get_tipo();
    std::string get_name();
    bool is_array(); 
    int get_dimensiones();
private:
    TypeS* tipo;
    int size;
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
    bool is_array();   
    TypeS* get_tipo();
    std::string get_name();
    
private:
    TypeS* referencia;   
};
