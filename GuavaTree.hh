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

/**
 * PARTE DE OBSERVACIONES:
 *
 * 1- Para la regla de lvariables: tipo no puede ser void, no puede existir
 *    una variable que sea de tipo void.
 * 2- Para la regla de lcorchetes: Esta regla es para la declaracion de
 *    arreglos, estamos permitiendo que entre corchetes pueda existir una
 *    exp, solo puede ser una expresion si esta retorna un valor integer.
 *    Lo dejaremos asi y lo verificamos en la verificacion estatica de tipos?
 *    O lo cambiaremos a solo expresiones de tipo integer?
 * 3- Me tienes que explicar la regla de arreglo y larreglo.
 * 4- Podemos considerar las uniones y records como tipo o son los IDs de
 *    cada uno los que definen el nombre del tipo?
 * 5- Se debe definir de abajo hacia arriba, sino la compilacion no funcionara.
 *
 */
 
#include "GuavaSymTable.hh"

/**
 * Clase que define una lista de variables a ser declaradas.
 */

/**
 * No se si sea bueno, o se vea bien, colocar todos los tipos de clases que
 * puede tener LVariables dependiendo de lo que se este declarando. Si no
 * entiendes preguntame para que te lo explique mejor.
 */
class LVariables {
public:
    Tipo t;              /*Tipo de las variables a declarar */
    /* Aqui pensaba colocar 'Modo' para ver si son pasadas por valor o por referencia*/
    LVar listaIds;          /* Lista de identificadores de variables */
    LVarArreglo listaIdsAr; /* Lista de identificadores de variables de tipo arreglo */
    Union u;                /* Bloque que define una union */
    Record r;               /* Bloque que defina un record */
    LVariables listaVar;    /* En caso de declarar mas de una lista de variables. */
    /*Constructores*/
    /*Caso en el que se declaran variables simples*/
    LVariables(Tipo tipo, LVar v) {
        t = tipo;
        listaIds = v;
    }
    LVariables(Tipo tipo, LVar v, LVariables listaVariables) {
        t = tipo;
        listaIds = v;
        listaVar = listaVariables;
    }
    /*Caso en el que se declaran variables de tipo arreglo*/
    LVariables(Tipo tipo, LVarArreglo va) {
        t = tipo;
        listaIdsAr = va;
    }
    LVariables(Tipo tipo, LVarArreglo va, LVariables listaVariables) {
        t = tipo;
        listaIdsAr = va;
        listaVar = listaVariables;
    }
    /*Para el caso en que se declaran uniones y records, simplemente no se
     *podria poner que el Tipo t = Union o Record o el ID de la estructura?
     *VER OBSERVACION 4
     */
    
    /*Caso definicion de Uniones*/
    LVariables(Union estructura) {
        u = estructura;
    }
    LVariables(Union estructura, LVariables listaVariables) {
        u = estructura;
        listaVar = listaVariables;
    }
    /*Caso definicion de Records*/
    LVariables(Record estructura) {
        r = estructura;
    }
    LVariables(Record estructura, LVariables listaVariables) {
        r = estructura;
        listaVar = listaVariables;
    }
    ~LVariables(){}
    void show(std::string);
    /*Investigar: Como realizar la verificacion si los tipos de listas de
     *            variables son diferentes? No es como python que por ser
     *            debilmente tipado una misma verificacion servia para todo.
     */
    void verificacion(GuavaSymTable);
}

/**
 * Clase de bloque de declaraciones.
 */
class BloqueDeclare {
public:
    LVariables listaVar; /* Lista de variables a declarar */
    BloqueDeclare(LVariables l) {
        listaVar = l;
    }
    ~BloqueDeclare(){}
    void show(std::string);
    void verificacion(GuavaSymTable);
}

/**
 * Clase de bloque principal.
 */
class BloquePrincipal {
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
};

