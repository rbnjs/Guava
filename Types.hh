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
    virtual TypeS* get_tipo()=0;
    virtual std::string get_name() { return "defaulttype"; };
    virtual std::pair<int,int*> get_dimensiones()=0;
    virtual std::list<TypeS*> get_atributos()=0; 
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
    TypeS* get_tipo();
    std::string get_name();
    std::pair<int,int*> get_dimensiones();
    std::list<TypeS*> get_atributos();
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
    TypeS* get_tipo();
    std::string get_name();
    std::pair<int,int*> get_dimensiones();
    std::list<TypeS*> get_atributos();
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
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::string get_name();
    std::list<TypeS*> get_atributos();
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
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::string get_name();
    std::list<TypeS*> get_atributos();
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
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::string get_name();
    std::list<TypeS*> get_atributos();
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
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::string get_name();
    std::list<TypeS*> get_atributos();
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
    std::pair<int,int*> get_dimensiones();
    TypeS* get_tipo();
    std::string get_name();
    std::list<TypeS*> get_atributos();
private:
    TypeString(){};
    static TypeString* string_instance;
};

class TypeFunction:public TypeS{
public:
    TypeFunction(TypeS*,std::list<TypeS*>); 
    TypeFunction(TypeS*);
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
    std::string get_name();
    std::list<TypeS*> get_atributos();
private :
    TypeS* tipo;
    std::list<TypeS*> parametros;
};

class TypeStructure :public TypeS{
public :
    std::list<TypeS*> atributos;
    std::string nombre;
    TypeStructure();
    TypeStructure(std::list<TypeS*>, std::string n );
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
    std::string get_name();
    std::list<TypeS*> get_atributos();
};

class TypeUnion :public TypeS{
public :
    std::list<TypeS*> atributos;
    std::string nombre;
    TypeUnion();
    TypeUnion(std::list<TypeS*>, std::string n);
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
    std::string get_name();
    std::list<TypeS*> get_atributos();
};

class TypeArray:public TypeS{
public :
    TypeArray(TypeS*,int, int*);
    ~TypeArray();
    TypeS* get_tipo();
    std::string get_name();
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
    std::string get_name();
    std::list<TypeS*> get_atributos();
private:
    TypeS* referencia;   
};
