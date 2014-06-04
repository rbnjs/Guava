/*
 * =====================================================================================
 *
 *       Filename:  globals.cc
 *
 *    Description:  Archivo con variables globales.
 *
 *        Version:  1.0
 *        Created:  03/06/14 22:27:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "globals.hh"
/* Variables globales. */
int current_scope;
int attribute_scope;  
int declare_scope;
int error_state;
std::string identacion ("");
std::list<int> offset_actual;
std::list<GuavaSymTable*> tabla_actual;
