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

ExpParentizada::ExpParentizada(Exp e){
    Exp();
    exp = e;
}

ExpParentizada::~ExpParentizada(){}


/* Clase Identificador. */

Identificador::Identificador(std::string i){
    identificador = i;
}

Identificador::~Identificador(){}

/* Clase de tipo. */

Tipo::Tipo(){
}

Tipo::Tipo(std::string t){
    tipo = t;
}

Tipo::~Tipo(){}

void Tipo::show(std::string){

}

void Tipo::verificar(GuavaSymTable gst){

}

/* Clase Real */

Real::Real(float f){
    real = f;
}

Real::~Real(){}
 
/* Clase Integer */

Integer::Integer(int i){
    integer = i;
}
Integer::~Integer(){}
 

/* Class Char */

Char::Char(char c){
    ch = c;
}

Char::~Char(){}

/* Class String */

String::String(char* s){
    str = std::string(s);
}

String::String(std::string s){
    str = s;
}

String::~String(){}

/* Class Bool */

Bool::Bool(bool b2){
    b = b2;
}

Bool::~Bool(){}

/* Class LCorchetes */

LCorchetes::LCorchetes(Exp e, LCorchetes* l){
    exp = e;
    *lista = *l;
}

LCorchetes::LCorchetes::LCorchetes(Exp e){
    exp = e;
    lista = 0;
}

LCorchetes::~LCorchetes(){
   delete lista; 
}

/* Class ExpUn */

ExpUn::ExpUn(Exp e, std::string* op){
    Exp();
    exp = e;
    *operacion = *op;
}

ExpUn::ExpUn(Exp e1, Exp* e2, std::string* op){
    exp = e1;
    *exp2 = *e2;
}
    
ExpUn::ExpUn(Exp e1, LCorchetes* lc){
    exp = e1;
    *corchetes = *lc;
}

ExpUn::~ExpUn(){
    delete exp2;
    delete corchetes;
    delete operacion;
}

/* Class ExpBin */

ExpBin::ExpBin(Exp e1,Exp e2,std::string op){
    Exp();
    exp1 = e1;
    exp2 = e2;
    operacion = op;
}

ExpBin::~ExpBin(){}

/* Clase Instruccion */

Instruccion::Instruccion(){}

Instruccion::Instruccion(Instruccion* i){
    *instruccion = *i;
}

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

LVarArreglo::LVarArreglo(){}

LVarArreglo::LVarArreglo(std::string t, LVarArreglo* l){
    tipo = t;
    *lista = *l;
    corchetes = 0;
}

LVarArreglo::LVarArreglo(std::string t){
    tipo = t;
    corchetes = 0;
    lista = 0;
}

LVarArreglo::~LVarArreglo(){
    delete corchetes;
    delete lista;
}

/* Class LVar */

LVar::LVar(){}

LVar::LVar(std::string t, LVar* l = 0){
    tipo = t;
    *lista = *l;
}

LVar::LVar(std::string t){
    tipo = t;
}

LVar::~LVar(){
    delete lista;
}

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

Record::Record(){
    Estructura();
    lista = 0;
}

Record::Record(std::string id, LVariables* l = 0){
    Estructura();
    *lista = *l;
    identificador = id;
}

Record::~Record(){
    delete lista;
}

/* Class Union */

Union::Union(){
    Estructura();
    lista = 0;
}

Union::Union(std::string id, LVariables* l=0){
    Estructura();
    identificador = id;
    *lista = *l;
}

Union::~Union(){
    delete lista;
}



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

Arreglo::Arreglo(LArreglo* l){
    *listaA = *l;
}
    
Arreglo::~Arreglo(){ 
    delete listaA; 
}
 

/* Class BloqueDeclare */

BloqueDeclare::BloqueDeclare(){}

BloqueDeclare::BloqueDeclare(LVariables l) {
    listaVar = l;
}
    
BloqueDeclare::~BloqueDeclare(){}

/* Class LElseIf */

LElseIf::LElseIf(Exp e, BloqueDeclare d, ListaInstrucciones li, LElseIf* lif = 0){
    exp = e;
    declaraciones = d;
    listainstrucciones = li;
    *lelseif = *lif;
}

LElseIf::~LElseIf(){
    delete lelseif;
}
 

/* Class SelectorIf */

SelectorIf::SelectorIf(Exp e, BloqueDeclare* d = 0, ListaInstrucciones* l = 0, LElseIf* lif = 0){
    exp = e;
    *declaraciones = *d;
    *listainstrucciones = *l;
    *lelseif = *lif;
}

SelectorIf::SelectorIf(Exp e, Instruccion* i, Instruccion* i2 = 0){
    exp = e;
    *instruccion1 = *i;
    *instruccion2 = *i2;
}

SelectorIf::~SelectorIf(){
    delete declaraciones;
    delete listainstrucciones;
    delete instruccion1;
    delete instruccion2;
    delete lelseif;
}

/* Class LoopWhile */
LoopWhile::LoopWhile(Exp e, BloqueDeclare bd, ListaInstrucciones li){
    exp = e;
    declaraciones = bd;
    listainstrucciones = li;
}

LoopWhile::~LoopWhile(){}


/* Class Asignacion */

Asignacion::Asignacion(){}

Asignacion::Asignacion(std::string id, Exp* e = 0, LCorchetes* lc = 0 
                , std::string* id2 = 0, Arreglo* arr = 0){
    identificador = id;
    *exp = *e;
    *lcorchetes = *lc;
    *identificador2 = *id2;
    *arreglo = *arr;
}

Asignacion::~Asignacion(){
    delete identificador2;
    delete lcorchetes;
    delete arreglo;
    delete exp;
}

/* Class LoopFor */

LoopFor::LoopFor(std::string id, Exp e1,BloqueDeclare d, ListaInstrucciones l,
                Exp* e2 = 0, Asignacion* a = 0){
    identificador = id;
    exp = e1;
    *asignacion = *a;
    exp2 = e2;
    declaraciones = d;
    listainstrucciones = l;
}

LoopFor::~LoopFor(){
    delete asignacion;
    delete exp2;
}


/* Class PlusMinus */

PlusMinus::PlusMinus(Exp e, std::string t){
    exp = e;
    tipo = t;
}

PlusMinus::~PlusMinus(){}


/* Class LVaroValor */

LVaroValor::LVaroValor(Exp* e = 0, LVaroValor* lv = 0){
    *exp = *e;
    *lvarovalor = *lv;
}
        
LVaroValor::~LVaroValor(){
    delete exp;
    delete lvarovalor;
}

/* Class LlamadaFuncion */
LlamadaFuncion::LlamadaFuncion(std::string id, LVaroValor lv){
    identificador = id;
    lvarovalor = lv;
}

LlamadaFuncion::~LlamadaFuncion(){}

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
