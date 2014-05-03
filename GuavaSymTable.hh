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
    std::list<int> pila;                                            /* Pila de alcances */
    std::unordered_map<std::string, std::list<Symbol> > tabla;      /* Tabla que representa la tabla de simbolos. */
    int alcance;                                                    /* Alcance en numeros. */

    GuavaSymTable();                                      /* Constructor de la clase */
    ~GuavaSymTable();                                     /*  Destructor */

    void insert(Symbol elem);                                              /* Inserta un simbolo a la tabla */
    void insert(std::string,std::string,int,std::string,int,int);          /* Agrega un arreglo a la tabla */
    void insert(std::string,std::string,int,Symbol*,int,int);              /* Inserta simbolo */
    void insert(std::string,std::string,int,Symbol*,int,int,int*,int);     /* Agrega un arreglo a la tabla. Desactualizado, sera eliminado. */
    void insert(std::string,std::string,int,TypeS*,int,int);               /* Agrega un arreglo a la tabla. */
    void insert(std::string,std::string,int,std::string,int,int,int*,int); /* DEPRECADO Agrega un arreglo a la tabla */
    void insert(std::string,std::string,int,std::string,int,int,int);      /* Agrega una estructura a la tabla */
    void insert_type(std::string,std::string,int,TypeS*);                  /* Agrega un tipo basico a la tabla */
    void insert_type(std::string, std::string, int, TypeS*, int);          /* Agrega un tipo record o union a la tabla */
    int newScope();                                                        /* Aumenta en uno el alcance. */
    int enterScope();                                                      /* Entra un nuevo alcance  */
    int exitScope();                                                       /* Sale del alcance  */
    int currentScope();                                                    /* Muestra el alcance actual */ 
    Symbol* lookup(std::string elem);                                      /* Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    Symbol* lookup(std::string, int);                                      /* Busca un simbolo con un scope determinado */
    Symbol* simple_lookup(std::string elem);                               /* Busca un simbolo en el alcance actual */
    void show(int,std::string);                                            /* Muestra la tabla */
    std::unordered_map<std::string, std::list<Symbol> >::iterator find(std::string);

};
