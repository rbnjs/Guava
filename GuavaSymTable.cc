/*
 * =====================================================================================
 *
 *       Filename:  GuavaSymTable.cc
 *
 *    Description:  Implementación de la tabla de simbolos.
 *
 *        Version:  1.0
 *        Created:  05/03/14 14:29:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */
# include "GuavaSymTable.hh"
# include "Symbol.hh"
GuavaSymTable::GuavaSymTable(){} /* Constructor de la clase */

GuavaSymTable::~GuavaSymTable(){} /*  Destructor */

void GuavaSymTable::enterScope(){}

void GuavaSymTable::exitScope(){}
    
void GuavaSymTable::insert(Symbol s) {}              /* Inserta un simbolo a la tabla */
Symbol GuavaSymTable::lookup(std::string elem, int alcance){}     /*  Busca un simbolo en la tabla y retorna NULL o el simbolo. */
void GuavaSymTable::show(){}                                        /* Muestra la tabla */

