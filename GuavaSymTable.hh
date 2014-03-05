/*
 * =====================================================================================
 *
 *       Filename:  GuavaSymTable.hh
 *
 *    Description:  Clase de tabla de simbolo para Guava.
 *
 *        Version:  1.0
 *        Created:  05/03/14 13:50:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas (), 
 *   Organization: USB 
 *
 * =====================================================================================
 */
# include "Symbol.hh"
class GuavaSymTable{
public:
    GuavaSymTable(); /* Constructor de la clase */
    virtual ~GuavaSymTable(); /*  Destructor */

    void enterScope();
    void exitScope();
    void insert(/*  Simbolo a insertar  */);              /* Inserta un simbolo a la tabla */
    Symbol lookup(const std::string elem, int alcance);     /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
    void show();                                          /* Muestra la tabla */
private:
    std::stack<int> pila;
    std::map<std::string, std::list<Symbol>> tabla;
    int alcance;
}
