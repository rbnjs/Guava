/*
 * =====================================================================================
 *
 *       Filename:  Generator.cc
 *
 *    Description:  Implementacion de Generator.
 *
 *        Version:  1.0
 *        Created:  14/11/14 11:13:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo. 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include "Generator.hh"
#include <list>

using namespace std;

/**  
 * Constructor de la clase.
 * @param vars Lista de variables a pasar.
 */
GuavaDescReg::GuavaDescReg(list<string> vars){
    for (list<string>::iterator it = vars.begin(); it != vars.end(); ++it){
        GuavaRegister nuevo_reg (*it);
        tabla[*it] = nuevo_reg; 
    }
}

