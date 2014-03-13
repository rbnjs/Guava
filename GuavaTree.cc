/*
 * =====================================================================================
 *
 *       Filename:  GuavaTree.cc
 *
 *    Description:  Implementacion de 
 *
 *        Version:  1.0
 *        Created:  12/03/14 14:54:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include "GuavaTree.hh"

/* Clase de expresion  */

/**
 * Destructor de la clase.
 */
Exp::~Exp(){
    delete this->exp;
}

void Exp::show(std::string){

}

void Exp::verificar(GuavaSymTable gst){

}

/* Clase ExpParentizada */

/* Clase Identificador. */

/* Clase de tipo. */

Tipo::Tipo(){
}

Tipo::~Tipo(){}

void Tipo::show(std::string){

}

void Tipo::verificar(GuavaSymTable gst){

}

/* Clase Real */

/* Clase Integer */

/* Class Char */

/* Class String */

/* Class Bool */

/* Class LCorchetes */

/* Class ExpUn */

/* Class ExpBin */

/* Clase Instruccion */

Instruccion::~Instruccion(){
    delete this->instruccion;
}


/* Lista Instrucciones */
ListaInstrucciones::ListaInstrucciones(){}

ListaInstrucciones::ListaInstrucciones(Instruccion* inst, ListaInstrucciones* li = 0){
    *instruccion = *inst;
    *li = *li;
}
 
ListaInstrucciones::~ListaInstrucciones(){
        delete instruccion;
        delete listainstrucciones;
}

/* Class LVarArreglo */

/* Class LVar */

/* Class Estructura */

Estructura::Estructura(){ estructura = 0; }

Estructura::Estructura(Estructura* e){
        *estructura = *e;
}

Estructura::~Estructura(){ delete estructura; }

/* Class LVariables */

LVariables::LVariables(){}

LVariables::LVariables(Tipo tipo, LVar v) {
    this->t = tipo;
    this->listaIds = v;
}

LVariables::LVariables(Tipo tipo, LVar v, LVariables listaVariables) {
    this->t = tipo;
    this->listaIds = v;
    this->listaVar = &listaVariables;
}

LVariables::LVariables(Tipo tipo, LVarArreglo va) {
    this->t = tipo;
    this->listaIdsAr = va;
}

LVariables::LVariables(Tipo tipo, LVarArreglo va, LVariables listaVariables) {
    this->t = tipo;
    this->listaIdsAr = va;
    this->listaVar = &listaVariables;
}
    
/*Caso definicion de Uniones*/
LVariables::LVariables(Estructura e) {
    estructura = e;
}

LVariables::LVariables(Estructura e, LVariables listaVariables) {
    estructura = e;
    *listaVar = listaVariables;
}

LVariables::~LVariables(){ delete this->listaVar; }

/* Class Record */

/* Class Union */

/* Class LArreglo */

LArreglo::LArreglo(IArreglo* a, LArreglo* lar = 0){
    *arr = *a;
    exp = 0;
    *larr = *lar;
}

LArreglo::LArreglo(Exp e, LArreglo* lar = 0){
    *exp = e;
    arr = 0;
    *larr = *lar;
}
    
LArreglo::~LArreglo(){
    delete exp;
    delete arr;
    delete larr;
}

/* Class Arreglo */

/* Class BloqueDeclare */

BloqueDeclare::BloqueDeclare(){}

BloqueDeclare::BloqueDeclare(LVariables l) {
    listaVar = l;
}
    
BloqueDeclare::~BloqueDeclare(){}

/* Class LElseIf */

/* Class SelectorIf */

/* Class LoopWhile */

/* Class Asignacion */

/* Class LoopFor */

/* Class PlusMinus */

/* Class LVaroValor */

/* Class LlamadaFuncion */

/* Class LParam */

LParam::LParam(){ }

LParam::LParam(Tipo t, std::string* id = 0 ){
    tipo = t;
    *identificador = *id; 
}

LParam::~LParam(){ delete identificador; }


/* Class Funcion */

Funcion::Funcion(){}

Funcion::Funcion(Tipo t, std::string id, LParam* param = 0, BloqueDeclare* decl = 0,
    ListaInstrucciones* li = 0, Exp * r = 0){
    tipo = t;
    *parametros = *param;
    *declaraciones = *decl;
    *listaI = *li;
    *retorno = *r;
}

Funcion::~Funcion(){
    delete parametros;
    delete declaraciones;
    delete listaI;
    delete retorno;
}


/* Class LFunciones */

LFunciones::LFunciones(){}
    
LFunciones::LFunciones(Funcion f, LFunciones* l = 0){
        funcion = f;
        *lista = *l;
}

LFunciones::~LFunciones(){delete lista;}


/* Class BloquePrincipal */

BloquePrincipal::BloquePrincipal(){}

BloquePrincipal::BloquePrincipal(BloqueDeclare b, LFunciones l) {
    globalD = b;
    funciones = l;
}

BloquePrincipal::~BloquePrincipal(){}
 
/* Class Program */

Program::Program(){}

Program::Program(BloquePrincipal b){
    bloque = b;
}

Program::~Program(){}
