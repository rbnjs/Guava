/*
 * =====================================================================================
 *
 *       Filename:  GuavaSymTable.hh
 *
 *    Description:  Definicion de clase de tabla de simbolo para Guava.
 *
 *        Version:  1.0
 *        Created:  05/03/14 13:50:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization: USB 
 *
 * =====================================================================================
 */
#include "Symbol.hh"
#include <string>
#include <list>
#include <map>
#include <unordered_map>

/**
 * Declaracion de la clase para la tabla de simbolos.
 */
class GuavaSymTable{
public:
    std::list<int> pila;                                                  /* Pila de alcances */
    std::unordered_map<std::string, std::list<Symbol> > tabla;            /* Tabla que representa la tabla de simbolos. */
    int alcance;                                                          /* Alcance en numeros. */

    GuavaSymTable();                                                       /* Constructor de la clase */
    ~GuavaSymTable();                                                      /*  Destructor */

    void insert(Symbol elem);                                              /* Inserta un simbolo a la tabla */

    void insert(std::string,std::string,int,Symbol*,int,int,int);          /* Inserta simbolo */
    void insert(std::string,std::string,int,TypeS*,int,int,int);           /* Agrega un arreglo a la tabla. */
    void insert_type(std::string,std::string,int,TypeS*);                  /* Agrega un tipo basico a la tabla */

    int newScope();                                                        /* Aumenta en uno el alcance. */
    int enterScope();                                                      /* Entra un nuevo alcance  */
    int exitScope();                                                       /* Sale del alcance  */
    int currentScope();                                                    /* Muestra el alcance actual */ 
    Symbol* lookup(std::string elem);                                      /* Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    Symbol* lookup(std::string, int);                                      /* Busca un simbolo con un scope determinado */
    Symbol* simple_lookup(std::string elem);                               /* Busca un simbolo en el alcance actual */
    void show(int,std::string);                                            /* Muestra la tabla */
    std::list<TypeS*> get_types(int sc);                                   /* Obtiene todos los tipos de un alcance determinado. */
};

class TypeStructure :public TypeS{
public :
    GuavaSymTable* atributos;
    std::string nombre;
    int size;
    TypeStructure();
    TypeStructure(std::string n);
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
    GuavaSymTable* atributos;
    std::string nombre;
    int size;
    std::list<int> offsets;
    TypeUnion();
    TypeUnion(std::string n);
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

