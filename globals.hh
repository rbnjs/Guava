/*
 * =====================================================================================
 *
 *       Filename:  globals.hh
 *
 *    Description: Archivo con variables globales. 
 *
 *        Version:  1.0
 *        Created:  03/06/14 22:27:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GuavaParser.hh"
#include <string>
#include <list>
#ifndef GLOBAL_H // header guards
#define GLOBAL_H

extern int current_scope;
extern int attribute_scope;  
extern int declare_scope;
extern int error_state;
extern std::string identacion;
extern std::list<int> offset_actual;
extern std::list<GuavaSymTable*> tabla_actual;
#endif
