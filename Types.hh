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
    std::pair<int,int*> get_dimensiones();
    std::list<TypeS*> get_atributos();
protected:
    TypeReal();
private:
   static TypeReal* instance;
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
    std::pair<int,int*> get_dimensiones();
    std::list<TypeS*> get_atributos();
protected:
    TypeInt();
private:
   static TypeInt* instance;
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
    std::list<TypeS*> get_atributos();
protected:
    TypeError();
private:
   static TypeError* instance;
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
    std::list<TypeS*> get_atributos();
protected:
    TypeVoid();
private:
    static TypeVoid* instance;
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
    std::list<TypeS*> get_atributos();
protected:
    TypeBool();
private:
    static TypeBool* instance;
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
    std::list<TypeS*> get_atributos();
protected:
    TypeChar();
private:
    static TypeChar* instance;
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
    std::list<TypeS*> get_atributos();
protected:
    TypeString();
private:
    static TypeString* instance;
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
    TypeStructure();
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
    TypeUnion();
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
