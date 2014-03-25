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
#include <iostream>

/* Class de expresion  */

Exp::Exp() { 
    exp = 0;
}

Exp::Exp(Exp *e) {
    *exp = *e;    
}

Exp::~Exp() {
    //delete exp;
}

void Exp::show(std::string identacion) {
    exp->show(identacion);
}

void Exp::verificar(GuavaSymTable s) {}

/* Class ExpParentizada */

ExpParentizada::ExpParentizada(Exp e): Exp(), exp(e) {}

ExpParentizada::~ExpParentizada() {}

void ExpParentizada::show(std::string s) {
    exp.show(s); // No se si poner algo con respecto al parentesis.
}

void ExpParentizada::verificar(GuavaSymTable s) {}

/* Class Identificador. */

Identificador::Identificador(){
    Exp();
}

Identificador::Identificador(std::string i) {
    Exp();
    identificador = i;
}

Identificador::~Identificador() {}

void Identificador::show(std::string s) {
    std::cout << s << "Identificador: " << identificador << '\n' ;
}

void Identificador::verificar(GuavaSymTable s) {} 

/* Class tipo. */

Tipo::Tipo() {}

Tipo::Tipo(std::string t) {
    tipo = t;
}

Tipo::~Tipo() {}

void Tipo::show(std::string s) {
    std::cout << s << "Tipo: " << tipo << '\n' ;
}

void Tipo::verificar(GuavaSymTable s) {}

/* Class Valor */

Valor::Valor(Valor* v): Exp(this) {
    *valor = *v;
}

Valor::Valor(): Exp() {
    valor = 0;
}

Valor::~Valor() {
}

void Valor::show(std::string s) {
    valor->show(s);
} 

void Valor::verificar(GuavaSymTable s) {} 

/* Class Real */

Real::Real(float f){
    real = f;
}

Real::~Real() {}

void Real::show(std::string s) {
    std::cout << s << "Real: " << real << '\n';
}

void Real::verificar(GuavaSymTable s) {}

/* Class Integer */

Integer::Integer(): Valor(){
    integer = 0; 
}

Integer::Integer(int i): Valor(), integer(i) {}

Integer::~Integer() {}

void Integer::show(std::string s) {
    std::cout << s << "Entero: " << integer << '\n';
} 

void Integer::verificar(GuavaSymTable s) {}

/* Class Char */

Char::Char(char c): Valor(), ch(c) {
}

Char::~Char() {}

void Char::show(std::string s) {
    std::cout << s << "Caracter: " << ch << '\n';
}

void Char::verificar(GuavaSymTable s) {} 

/* Class String */

String::String(char* s): Valor() {
    str = std::string(s);
}

String::String(std::string s):Valor(), str(s) {
}

String::~String() {}

void String::show(std::string s){
    std::cout << s << "String: " << str << '\n';
}

void String::verificar(GuavaSymTable s) {} 

/* Class Bool */

Bool::Bool(bool b2): Valor(), b(b2){
}

Bool::~Bool(){}

void Bool::show(std::string s){
    std::cout << s << "Booleano: " << b << '\n';
}

void Bool::verificar(GuavaSymTable s) {} 

/* Class LCorchetes */

LCorchetes::LCorchetes(Exp e, LCorchetes* l): exp(e), lista(l) {
}

LCorchetes::~LCorchetes() {
   //delete lista; 
}

void LCorchetes::show(std::string s) {
    exp.show(s);
    if (lista !=0) lista->show(s);
}

void LCorchetes::verificar(GuavaSymTable s) {}

/* Class ExpUn */

ExpUn::ExpUn(Exp e, std::string* op):Exp() {
    exp = e;
    operacion = op;
    corchetes = 0;
}
    
ExpUn::ExpUn(Exp e1, LCorchetes* lc): Exp() {
    corchetes = lc;
    operacion = 0;
}

ExpUn::~ExpUn() {
    //delete corchetes;
    //delete operacion; 
}

void ExpUn::show(std::string s) {
    std::cout << s << "Expresion Unaria: \n";
    std::cout << s << "Exp: \n";
    exp.show(s+" ");
    if (operacion != 0) std::cout << s << "Operador: " << *operacion;
    if (corchetes != 0) corchetes->show(s+ "  ");
} 

void ExpUn::verificar(GuavaSymTable s) {} 

/* Class ExpBin */

ExpBin::ExpBin(Exp e1,Exp e2,std::string op){
    Exp();
    exp1 = e1;
    exp2 = e2;
    operacion = op;
}

ExpBin::~ExpBin() {}

void ExpBin::show(std::string s){
    std::cout << s << "Expresion Binaria: \n";
    exp1.show(s+"  ");
    exp2.show(s+"  ");
    std::cout << s << "Operador: " << operacion << '\n';
}

void ExpBin::verificar(GuavaSymTable s) {} 

/* Class Instruccion */

Instruccion::Instruccion() {}

Instruccion::Instruccion(Instruccion* i) {
    *instruccion = *i;
}

Instruccion::~Instruccion() {
    delete this->instruccion;
}

void Instruccion::show(std::string s) {
    std::cout << "Instruccion: \n";
    instruccion->show(s+"  ");
}

void Instruccion::verificar(GuavaSymTable s) {} 

/* Lista Instrucciones */

ListaInstrucciones::ListaInstrucciones() {
    instruccion = 0;
    listainstrucciones = 0;
}

ListaInstrucciones::ListaInstrucciones(Instruccion* inst, ListaInstrucciones* li = 0) {
    *instruccion = *inst;
    *listainstrucciones = *li;
}

ListaInstrucciones::~ListaInstrucciones() {
    delete instruccion;
    delete listainstrucciones;
}

void ListaInstrucciones::show(std::string s) {
    if (instruccion != 0) instruccion->show(s);
    if (listainstrucciones != 0) listainstrucciones->show(s);
}

void ListaInstrucciones::verificar(GuavaSymTable s) {} 

/* Class LVarArreglo */

LVarArreglo::LVarArreglo() {}

LVarArreglo::LVarArreglo(Identificador i, LCorchetes* lc, LVarArreglo* lva) {
    id = i;
    corchetes = lc;
    lista = lva;
}

LVarArreglo::~LVarArreglo() {
    delete corchetes;
    delete lista;
}

void LVarArreglo::show(std::string s) {
    id.show(s);
    corchetes->show(s);
    lista->show(s);
}

void LVarArreglo::verificar(GuavaSymTable s) {} 

/* Class LVar */

LVar::LVar() {}

LVar::LVar(Identificador i, LVar* l) {
    id = i;
    *lista = *l;
}

LVar::~LVar() {
    delete lista;
}

void LVar::show(std::string s) {} 
void LVar::verificar(GuavaSymTable s) {} 

/* Class Estructura */

Estructura::Estructura() { 
    estructura = 0; 
}

Estructura::Estructura(Estructura* e){
    *estructura = *e;
}

Estructura::~Estructura() { 
    delete estructura; 
}

void Estructura::show(std::string s) {} 
void Estructura::verificar(GuavaSymTable s) {} 

/* Class LVariables */

LVariables::LVariables() {}

LVariables::LVariables(Tipo tipo, LVar v, LVariables *listaVariables) {
    t = tipo;
    listaIds = v;
    listaVar = listaVariables;
}

LVariables::LVariables(Tipo tipo, LVarArreglo va, LVariables *listaVariables) {
    t = tipo;
    listaIdsAr = va;
    listaVar = listaVariables;
}
    
/*Caso definicion de Uniones*/
LVariables::LVariables(Estructura e, LVariables *listaVariables) {
    estructura = e;
    listaVar = listaVariables;
}

LVariables::~LVariables() { 
    delete this->listaVar;
}

void LVariables::show(std::string s) {} 
void LVariables::verificar(GuavaSymTable s) {} 

/* Class Record */

Record::Record() {
    Estructura();
    lista = 0;
}

Record::Record(Identificador i, LVariables* l) {
    Estructura();
    id = i;
    *lista = *l;
}

Record::~Record() {
    delete lista;
}

void Record::show(std::string s) {} 
void Record::verificar(GuavaSymTable s) {} 

/* Class Union */

Union::Union() {
    Estructura();
    lista = 0;
}

Union::Union(Identificador i, LVariables* l) {
    Estructura();
    id = i;
    *lista = *l;
}

Union::~Union() {
    delete lista;
}

void Union::show(std::string s) {} 
void Union::verificar(GuavaSymTable s) {} 

/* Class LArreglo */

LArreglo::LArreglo(Exp e, LArreglo* lar = 0): exp(&e),larr(lar) {
}
    
LArreglo::~LArreglo() {
    /* MEMORY LEAK -> Revisar */
    //delete exp;
    //delete larr;
}

void LArreglo::show(std::string s) {} 
void LArreglo::verificar(GuavaSymTable s) {}

/* Class Arreglo */

Arreglo::Arreglo():Valor(){
    listaA = 0;
}

Arreglo::Arreglo(LArreglo* l):Valor(),listaA(l) {
}
    
Arreglo::~Arreglo() { 
    /* MEMORY LEAK -> Revisar  */
    //delete listaA;
}

void Arreglo::show(std::string) {}
void Arreglo::verificar(GuavaSymTable) {}

/* Class BloqueDeclare */

BloqueDeclare::BloqueDeclare() {}

BloqueDeclare::BloqueDeclare(LVariables l) {
    listaVar = l;
}
    
BloqueDeclare::~BloqueDeclare() {}

void BloqueDeclare::show(std::string s) {} 
void BloqueDeclare::verificar(GuavaSymTable s) {} 

/* Class LElseIf */

LElseIf::LElseIf() {
    exp = 0;
    lelseif = 0;
}

LElseIf::LElseIf(Exp e, BloqueDeclare d, ListaInstrucciones li, LElseIf* lif = 0) {
    *exp = e;
    declaraciones = d;
    listainstrucciones = li;
    *lelseif = *lif;
}

LElseIf::LElseIf(BloqueDeclare d, ListaInstrucciones li) {
    exp = 0;
    lelseif = 0;
    declaraciones = d;
    listainstrucciones = li;
}

LElseIf::~LElseIf() {
    delete lelseif;
}

void LElseIf::show(std::string s) {} 
void LElseIf::verificar(GuavaSymTable s) {}  

/* Class SelectorIf */

SelectorIf::SelectorIf(Exp e, BloqueDeclare* d = 0, ListaInstrucciones* l = 0, LElseIf* lif = 0) {
    exp = e;
    *declaraciones = *d;
    *listainstrucciones = *l;
    *lelseif = *lif;
}

SelectorIf::SelectorIf(Exp e, Instruccion* i, Instruccion* i2 = 0) {
    exp = e;
    *instruccion1 = *i;
    *instruccion2 = *i2;
    listainstrucciones = 0;
    declaraciones = 0;
}

SelectorIf::~SelectorIf() {
    delete declaraciones;
    delete listainstrucciones;
    delete instruccion1;
    delete instruccion2;
    delete lelseif;
}

void SelectorIf::show(std::string s) {
    std::cout << s << "If: \n";
    exp.show("  "+s);
    std::cout << s << "Then: \n";
    if (listainstrucciones != 0) listainstrucciones->show("  "+s);
    if ( instruccion1 != 0)  instruccion1->show("  "+s);
    if ((lelseif!= 0 ) || (instruccion2 != 0))std::cout << s << "Else: \n";
    if (lelseif != 0) lelseif->show("  "+s);
    if (instruccion2 != 0) instruccion2->show("  "+s);
} 
void SelectorIf::verificar(GuavaSymTable s) {} 

/* Class LoopWhile */

LoopWhile::LoopWhile(Exp e, BloqueDeclare bd, ListaInstrucciones li) {
    exp = e;
    declaraciones = bd;
    listainstrucciones = li;
}

LoopWhile::~LoopWhile() {}

void LoopWhile::show(std::string s) {
    std::cout << s << "While:\n";
    exp.show("  "+s);
    std::cout << s << "do:\n";
    listainstrucciones.show("  "+s);
} 
void LoopWhile::verificar(GuavaSymTable s) {} 

/* Class Asignacion */

Asignacion::Asignacion() {}

Asignacion::Asignacion(Identificador i, Exp e) {
    identificador = i;
    *exp = e;
    lcorchetes = 0;
    identificador2 = 0;
    arreglo = 0;
}

Asignacion::Asignacion(Identificador id, LCorchetes lc, Exp e) {
    identificador = id;
    *lcorchetes = lc;
    *exp = e;
    identificador2 = 0;
    arreglo = 0;
}

Asignacion::Asignacion(Identificador id,Identificador id2,Exp e) {
    identificador = id;
    *identificador2 = id2;
    *exp = e;
    lcorchetes = 0;
    arreglo = 0;
}

Asignacion::Asignacion(Identificador id, Arreglo arr) {
    identificador = id;
    *arreglo = arr;
    lcorchetes = 0;
    identificador2 = 0;
    exp = 0;
}

Asignacion::~Asignacion() {
    delete identificador2;
    delete lcorchetes;
    delete arreglo;
    delete exp;
}

void Asignacion::show(std::string s) {
    std::cout << s << "Asignacion: \n";
    identificador.show(s + "  ");
    if (identificador2 != 0) identificador2->show(s+"  "); 
    if (lcorchetes != 0) lcorchetes->show(s+"  ");
    if (exp == 0){
        exp->show(s+"  ");
    }
    if (arreglo != 0) arreglo->show(s+ "  ");
} 

void Asignacion::verificar(GuavaSymTable s) {} 

/* Class LoopFor */

LoopFor::LoopFor(Identificador id, Exp e1,Exp e2,BloqueDeclare d, ListaInstrucciones l) {
    identificador = id;
    exp = e1;
    asignacion = 0;
    *exp2 = e2;
    declaraciones = d;
    listainstrucciones = l;
}

LoopFor::LoopFor(Identificador id, Exp e1,Asignacion asig,BloqueDeclare d, ListaInstrucciones l) {
    identificador = id;
    exp = e1;
    *asignacion = asig;
    exp2 = 0;
    declaraciones = d;
    listainstrucciones = l;
}

LoopFor::~LoopFor() {
    delete asignacion;
    delete exp2;
}

void LoopFor::show(std::string s) {
    std::cout << s << "Loop For: \n";
    identificador.show("  "+s);
    exp.show("  "+s);
    if (asignacion != 0) asignacion->show(" "+s);
    if (exp2 != 0) exp2->show("  "+s);
    listainstrucciones.show("  "+s);
} 

void LoopFor::verificar(GuavaSymTable s) {} 

/* Class PlusMinus */

PlusMinus::PlusMinus(Identificador id, int t) {
    identificador = id;
    tipo = t;
}

PlusMinus::~PlusMinus() {}

void PlusMinus::show(std::string s) {
    std::cout << s << "Instruccion : " << tipo << '\n';
    identificador.show("  "+s);
} 
void PlusMinus::verificar(GuavaSymTable s) {} 

/* Class LVaroValor */

LVaroValor::LVaroValor() {
    exp = 0;
    lvarovalor = 0;
}
 
LVaroValor::LVaroValor(Exp* e, LVaroValor* lv) {
    *exp = *e;
    *lvarovalor = *lv;
}
        
LVaroValor::~LVaroValor() {
    delete exp;
    delete lvarovalor;
}

void LVaroValor::show(std::string s) {
    exp->show(s);
    if (lvarovalor != 0) lvarovalor->show(s);
} 

void LVaroValor::verificar(GuavaSymTable s) {}

/* Class EntradaSalida */

EntradaSalida::EntradaSalida(int t, LVaroValor lv) {
    tipo = t;
    argumento = lv;
}

EntradaSalida::~EntradaSalida() {}

void EntradaSalida::show(std::string s) {}
void EntradaSalida::verificar(GuavaSymTable s) {}

/* Class LlamadaFuncion */

LlamadaFuncion::LlamadaFuncion(Identificador i, LVaroValor lv) {
    id = i;
    lvarovalor = lv;
}

LlamadaFuncion::~LlamadaFuncion() {}

void LlamadaFuncion::show(std::string s){
    std::cout << s << "Llamada Funcion : ";
    id.show(s);
    std::cout << s << "Argumentos: \n";
    //if (lvarovalor != 0) 
    lvarovalor.show(s+ "  ");
} 

void LlamadaFuncion::verificar(GuavaSymTable s) {} 

/* Class LParam */

LParam::LParam() { 
    tipo = 0;
    identificador = 0;
    lparam = 0; 
}

LParam::LParam(Tipo t, Identificador id, LParam lp) {
    *tipo = t;
    *identificador = id;
    *lparam = lp;
}

LParam::~LParam() {
    delete tipo;
    delete identificador;
    delete lparam; 
}

void LParam::show(std::string s) {
    if (tipo!= 0) tipo->show(s);
    if (identificador != 0) identificador->show(s);
    if (lparam != 0) lparam->show(s);
} 

void LParam::verificar(GuavaSymTable s) {} 

/* Class Funcion */

Funcion::Funcion() {
    retorno = 0;
}

Funcion::Funcion(Tipo t, Identificador id, LParam param, BloqueDeclare decl, ListaInstrucciones li, Exp r) {
    tipo = t;
    identificador = id;
    parametros = param;
    declaraciones = decl;
    listaI = li;
    *retorno = r;
}

Funcion::~Funcion() {
    delete retorno;
}

void Funcion::show(std::string s) {
    std::cout << s << "Funcion: \n";
    tipo.show(s+ "  ");
    identificador.show(s+ "  ");
    std::cout << s << "Parametros: \n";
    parametros.show(s+"  ");
    std::cout << s << "Instrucciones: \n";
    listaI.show(s+ "  ");
    if (retorno != 0) retorno->show(s+"  ");
} 

void Funcion::verificar(GuavaSymTable s) {} 

/* Class LFunciones */

LFunciones::LFunciones() {}
    
LFunciones::LFunciones(Funcion f, LFunciones* l) {
        funcion = f;
        lista = l;
}

LFunciones::~LFunciones() { delete lista; }

void LFunciones::show(std::string s) {
    funcion.show(s+"  ");
    if (lista != 0) lista->show(s + "  ");
} 

void LFunciones::verificar(GuavaSymTable s) {} 


/* Class BloquePrincipal */

BloquePrincipal::BloquePrincipal() {}

BloquePrincipal::BloquePrincipal(BloqueDeclare b, LFunciones l) {
    globalD = b;
    funciones = l;
}

BloquePrincipal::~BloquePrincipal() {}

void BloquePrincipal::show(std::string s) {
    funciones.show(s);
} 

void BloquePrincipal::verificar(GuavaSymTable s) {} 
 
/* Class Program */

Program::Program() {}

Program::Program(BloquePrincipal b) {
    bloque = b;
}

Program::~Program() {}

void Program::show(std::string s){
    std::cout << s << "Bloque: \n";
    bloque.show(s+"  ");
} 

void Program::verificar(GuavaSymTable s){} 
