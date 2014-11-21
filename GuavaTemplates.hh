/*
 * =====================================================================================
 *
 *       Filename:  GuavaTemplates.hh
 *
 *    Description:  Funciones templates.
 *
 *        Version:  1.0
 *        Created:  14/11/14 21:27:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization:  USB
 *
 * =====================================================================================
 */

# ifndef GUAVA_TEMPLATES_HH
# define GUAVA_TEMPLATES_HH
# include <set>
# include "Symbol.hh"

using namespace std;

/** 
 * Clase que contiene las plantillas para el lenguaje MIPS. 
 */
class MIPS{
    //static string load();
    static string store(string var, string reg);
    static string store(string reg,set<SimpleSymbol*>::iterator begin, set<SimpleSymbol*>::iterator end);
};

# endif
