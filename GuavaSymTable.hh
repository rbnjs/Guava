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
/**
 * Declaracion de la clase para la tabla de simbolos.
 * */
class GuavaSymTable{
public:
    std::list<int> pila;                                  /* Pila de alcances */
    std::map<std::string, std::list<Symbol> > tabla;      /* Tabla que representa la tabla de simbolos. */
    int alcance;                                          /* Alcance en numeros. */

    GuavaSymTable();                                      /* Constructor de la clase */
    ~GuavaSymTable();                                     /*  Destructor */

    Symbol* lookupType(std::string);
    void insert(Symbol elem);                             /* Inserta un simbolo a la tabla */
    void insert(std::string,std::string,int,Symbol*);
    void insert(std::string,std::string,int,std::string);  /* Inserta simbolo */
    void insert(std::string,std::string,int,std::string,int*); /* Agrega un arreglo a la tabla */
    void insert(std::string,std::string,int,std::string,int); /* Agrega una estructura a la tabla */
    int enterScope();                                     /* Entra un nuevo alcance  */
    int exitScope();                                      /* Sale del alcance  */
    Symbol* lookup(std::string elem);                     /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    void show(int,std::string);                           /* Muestra la tabla */
};
