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
    std::string show(int scope);                          /* Muestra la tabla */
    std::list<int> pila;                                  /* Pila de alcances */
    std::map<std::string, std::list<Symbol> > tabla;      /* Tabla que representa la tabla de simbolos. */
    int alcance;                                          /* Alcance en numeros. */

    GuavaSymTable();                                      /* Constructor de la clase */
    ~GuavaSymTable();                                     /*  Destructor */

    void insert(Symbol elem);                             /* Inserta un simbolo a la tabla */
    int enterScope();                                     /* Entra un nuevo alcance  */
    int exitScope();                                      /* Sale del alcance  */
    Symbol* lookup(std::string elem);                     /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
};
