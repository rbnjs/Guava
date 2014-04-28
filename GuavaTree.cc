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
 *         Author:  Ruben Serradas, Michael Woo 
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


/* Class ExpParentizada */

ExpParentizada::ExpParentizada(Exp e): Exp(), exp(e) {}

ExpParentizada::~ExpParentizada() {}

void ExpParentizada::show(std::string s) {
    exp.show(s); // No se si poner algo con respecto al parentesis.
}


/* Class Identificador. */

Identificador::Identificador():Exp(){
}

Identificador::Identificador(std::string i):Exp(),identificador(i) {
}

Identificador::~Identificador() {}

void Identificador::show(std::string s) {
    std::cout << s << "Identificador: " << identificador << '\n' ;
}


/* Class tipo. */

Tipo::Tipo() {}

Tipo::Tipo(std::string t, TypeS* t2) {
    tipo = t;
    tipoS = t2;
}

Tipo::~Tipo() {}

void Tipo::show(std::string s) {
    std::cout << s << "Tipo: " << tipo << '\n' ;
}


/* Class Valor */

Valor::Valor(){}

Valor::Valor(float f) {
    valor.real = f;
}

Valor::Valor(int i) {
    valor.integer = i;
}

Valor::Valor(char c) {
    valor.ch = c;
}

Valor::Valor(std::string s) {
    valor.str = &s;
}

Valor::Valor(bool b){
    valor.boolean;
}

Valor::Valor(LArreglo* l){
    valor.listaA = l;
}

Valor::~Valor() {
}

void Valor::show(std::string s) {
} 


/* Class Real */

Real::Real(float f):Valor(f){
}

Real::~Real() {}

void Real::show(std::string s) {
    std::cout << s << "Real: " << valor.real << '\n';
}


/* Class Integer */

Integer::Integer(): Valor(0){
}

Integer::Integer(int i): Valor(i) {}

Integer::~Integer() {}

int Integer::getValor(){return valor.integer;}

void Integer::show(std::string s) {
    std::cout << s << "Entero: " << valor.integer << '\n';
} 


/* Class Char */

Char::Char(char c): Valor(c){
}

Char::~Char() {}

void Char::show(std::string s) {
    std::cout << s << "Caracter: " << valor.ch << '\n';
}


/* Class String */
  
String::String(char* s): Valor(*(new std::string(s))) {
}

String::String(std::string s):Valor(), str(s) {
}

String::~String() {}

void String::show(std::string s){
    std::cout << s << "String: " << str << '\n';
}


/* Class Bool */

Bool::Bool(bool b2): Valor(b2){
}

Bool::~Bool(){}

void Bool::show(std::string s){
    std::cout << s << "Booleano: " << valor.boolean << '\n';
}


/* Class LCorchetes */

LCorchetes::LCorchetes() {
}

void LCorchetes::append(Integer e){
    lista.push_back(e);
}

LCorchetes::~LCorchetes() {
}

void LCorchetes::show(std::string s) {
}


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


/* Class ExpBin */

ExpBin::ExpBin():Exp(){}

ExpBin::ExpBin(Exp e1,Exp e2,std::string op):Exp(), exp1(e1), exp2(e2), operacion(op){
}

ExpBin::~ExpBin() {}

void ExpBin::show(std::string s){
    std::cout << s << "Expresion Binaria: \n";
    exp1.show(s+"  ");
    exp2.show(s+"  ");
    std::cout << s << "Operador: " << operacion << '\n';
}


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


/* Class LVarArreglo */

LVarArreglo::LVarArreglo() {}

LVarArreglo::LVarArreglo(Identificador i, LCorchetes lc) {
   std::pair <Identificador, LCorchetes> nuevo (i,lc);
   lista.push_back(nuevo);
}

void LVarArreglo::append(Identificador id,LCorchetes lc){
   std::pair <Identificador, LCorchetes> nuevo (id,lc);
   lista.push_back(nuevo);
}

std::list<std::pair <Identificador, LCorchetes> > LVarArreglo::get_list(){
    return lista;
}

LVarArreglo::~LVarArreglo() {
}

void LVarArreglo::show(std::string s) {
}


/* Class LVar */

LVar::LVar() {
}

LVar::LVar(std::list<Identificador> l): lista(l) {
}

void LVar::append(Identificador id){
    lista.push_back(id);
}

LVar::~LVar() {
}

std::list<Identificador> LVar::get_list(){
    return lista;
}

void LVar::show(std::string s) {} 

/* Class LVariables */

LVariables::LVariables() {}

LVariables::LVariables(TypeS* t, LVar* v): tipo(t),listaIds(v){
}

LVariables::LVariables(TypeS* t, LVarArreglo* va): tipo(t),listaIdsAr(va) {
}
    
//Caso definicion de Uniones
LVariables::LVariables(Estructura* e): estructura(e) {
}

LVariables::~LVariables() { 
    delete this;
}

void LVariables::show(std::string s) {} 



/* Class Record */

Record::Record():lista(0) {
}

Record::Record(Identificador i, LVariables* l):id(i),lista(l) {
}

Record::~Record() {
    delete this;
}

void Record::show(std::string s) {} 

LVariables* Record::get_lvar(){ return lista; }

Identificador Record::get_id(){ return id; }

/* Class Union */

Union::Union():lista(0) {
}

Union::Union(Identificador i, LVariables* l):id(i),lista(l) {
}

Union::~Union() {
    delete this;
}

void Union::show(std::string s) {} 

LVariables* Union::get_lvar(){ return lista; }

Identificador Union::get_id(){ return id; }

/* Class LArreglo */

LArreglo::LArreglo(){
}

void LArreglo::append(Exp e){
    larr.push_back(e);
}

LArreglo::~LArreglo() {
}

void LArreglo::show(std::string s) {} 

/* Class Arreglo */

Arreglo::Arreglo():Valor(){
    valor.listaA = 0;
}

Arreglo::Arreglo(LArreglo* l):Valor(l){
}
    
Arreglo::~Arreglo() { 
    /* MEMORY LEAK -> Revisar  */
    //delete listaA;
}

void Arreglo::show(std::string) {}

/* Class BloqueDeclare */

BloqueDeclare::BloqueDeclare(): scope(0){}

BloqueDeclare::BloqueDeclare(int sc): scope(sc){}
    
BloqueDeclare::~BloqueDeclare() {}

void BloqueDeclare::show(std::string s) {} 

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


/* Class PlusMinus */

PlusMinus::PlusMinus(Identificador id, int t):Instruccion(), identificador(id), tipo(t) {
}

PlusMinus::~PlusMinus() {}

void PlusMinus::show(std::string s) {
    std::cout << s << "Instruccion : " << tipo << '\n';
    identificador.show("  "+s);
} 

/* Class LVaroValor */

LVaroValor::LVaroValor() {
}

void LVaroValor::append(Exp e){
    lvarovalor.push_back(e);
}
        
LVaroValor::~LVaroValor() {
}

void LVaroValor::show(std::string s) {
} 


/* Class EntradaSalida */

EntradaSalida::EntradaSalida(int t, LVaroValor lv) {
    tipo = t;
    argumento = lv;
}

EntradaSalida::~EntradaSalida() {}

void EntradaSalida::show(std::string s) {}

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


/* Class LParam */

LParam::LParam(){}

void LParam::append(Tipo t, Identificador id){
    std::pair<Tipo, Identificador> par (t,id);
    lParam.push_back(par);
}
std::list<std::pair<Tipo,Identificador> > LParam::get_list(){
    return lParam;
}

LParam::~LParam() {
}

void LParam::show(std::string s) {
} 


/* Class Funcion */

Funcion::Funcion() {
    retorno = 0;
}

Funcion::Funcion(Tipo t, Identificador id, LParam param, BloqueDeclare decl, ListaInstrucciones li, Exp* r) {
    tipo = t;
    identificador = id;
    parametros = param;
    declaraciones = decl;
    listaI = li;
    retorno = r;
}

Funcion::~Funcion() {
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

