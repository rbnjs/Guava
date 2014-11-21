/*
 * =====================================================================================
 *
 *       Filename:  GuavaTemplates.cc
 *
 *    Description:  Templates de Guava para el lenguaje final.
 *
 *        Version:  1.0
 *        Created:  20/11/14 18:39:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "GuavaTemplates.hh"

/** 
 * Guarda un valor.
 * @param nombre de la variable a guardar.
 * @param nombre del registro en donde se encuentra la variable.
 * return string Retorna un string con el codigo.
 */
string MIPS::store(string var, string reg){
    return ("sw "+ var + ", "+ reg + "\n");
}

/** 
 * Guarda un conjunto de valores.
 * @param reg Nombre del registro en donde se encuentra el conjunto de variables.
 * @param begin Iterador al comienzo
 * @param end Iterador al final.
 * return result Codigo en mips.
 */
string MIPS::store(string reg,set<SimpleSymbol*>::iterator begin, set<SimpleSymbol*>::iterator end){
    string result ("");
    for (set<SimpleSymbol*>::iterator it = begin; it != end; ++it){
        result += MIPS::store((*it)->sym_name,reg);
    }
    return result;
}
