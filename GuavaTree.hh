/*
 * =====================================================================================
 *
 *       Filename:  GuavaTree.hh
 *
 *    Description:  Clases para la construccion de arbol.
 *
 *        Version:  1.0
 *        Created:  07/03/14 23:14:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas (), 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include "GuavaSymTable"
/**
 * Clase de bloque principal.
 */
class BloquePrincipal{
public:
    BloqueDeclare globalD; /* Declaraciones globales. */
    LFunciones funciones;  /* Lista de funciones. */
    BloquePrincipal(BloqueDeclare b, LFunciones l) {
        globalD = b;
        funciones = l;
    }
    ~BloquePrincipal(){}
    void show(std::string);
    void verificacion(GuavaSymTable);
}
