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


/* Class Identificador. */

Identificador::Identificador(){
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


/* Class LCorchetes */

LCorchetes::LCorchetes() {
}

void LCorchetes::append(int e){
    lista.push_back(e);
}

LCorchetes::~LCorchetes() {
}

void LCorchetes::show(std::string s) {
   for (std::list<int>::iterator it = lista.begin();
        it != lista.end() ;
        ++it
       ) {
            std::cout << "[" ;
            std::cout << *it;
            std::cout << "]";
       }
}

/* CLass LCorchetesExp */
LCorchetesExp::LCorchetesExp() {
}

LCorchetesExp::~LCorchetesExp() {
}

/* Class ExpUn */

ExpUn::ExpUn(Exp *e, std::string* op){
    exp = e;
    operacion = op;
    corchetes = 0;
}
    
ExpUn::ExpUn(Exp* e1, LCorchetes* lc) {
    exp = e1;
    corchetes = lc;
    operacion = 0;
}

ExpUn::~ExpUn() {
    //delete corchetes;
    if (operacion != 0) delete operacion; 
}

void ExpUn::show(std::string s) {
    std::cout << s << "Expresion Unaria: \n";
    std::cout << s << "Exp: \n";
    exp->show(s+" ");
    if (corchetes != 0) corchetes->show(s+ "  ");
    if (operacion != 0) std::cout << s << "Operador: " << *operacion;
} 


/* Class ExpBin */

ExpBin::ExpBin(){}

ExpBin::ExpBin(Exp* e1,Exp* e2,std::string op):exp1(e1), exp2(e2), operacion(op){
}

ExpBin::~ExpBin() {}

void ExpBin::show(std::string s){
    std::cout << s << "Expresion Binaria: \n";
    exp1->show(s+"  ");
    exp2->show(s+"  ");
    std::cout << s << "Operador: " << operacion << '\n';
}


/* Lista Instrucciones */

ListaInstrucciones::ListaInstrucciones() {
    instruccion = 0;
    listainstrucciones = 0;
    tipo = TypeVoid::Instance();
}

ListaInstrucciones::ListaInstrucciones(Instruccion* inst, ListaInstrucciones* li = 0) {
    *instruccion = *inst;
    *listainstrucciones = *li;
    tipo = TypeVoid::Instance();
}

ListaInstrucciones::~ListaInstrucciones() {
}

void ListaInstrucciones::show(std::string s) {
    if (listainstrucciones != 0) listainstrucciones->show(s);
    if (instruccion != 0) instruccion->show(s);
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
   std::cout << s <<"Lista de Variables de Arreglo: "; 

   for (std::list<std::pair <Identificador, LCorchetes> >::iterator it = lista.begin();
        it != lista.end() ; 
        ++it)
        {
            std::pair<Identificador, LCorchetes> tmp = *it;
            std::cout << tmp.first.identificador << " ";
            tmp.second.show("");
            std::cout << " ";
       }
       std::cout <<std::endl;
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

void LVar::show(std::string s) {
    std::cout << s <<"Variables: ";
    for (std::list<Identificador>::iterator it = lista.begin();
         it != lista.end();
         ++it
        ){
            Identificador tmp = *it;
            std::cout << tmp.identificador;
            std::cout << " ";
        }
        std::cout << "\n";
} 

/* Class LVariables */

LVariables::LVariables():listaVar(0) {}

LVariables::LVariables(TypeS* t, LVar* v): tipo(t),listaIds(v),listaVar(0){
}

LVariables::LVariables(TypeS* t, LVarArreglo* va): tipo(t),listaIdsAr(va),listaVar(0) {
}
    
/**
 *Caso definicion de Uniones
 */
LVariables::LVariables(Estructura* e): estructura(e) {
}
/**
 * Obtiene una lista de tipos.
 */
std::list<TypeS*> LVariables::get_type_list(){
   LVariables *tmp = this;
   std::list<TypeS*> result;
   while (tmp != 0){
       result.push_back(tipo); 
       tmp = tmp->listaVar;
    }
   return result;
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

void LArreglo::append(Exp* e){
    larr.push_back(e);
}

LArreglo::~LArreglo() {
}

void LArreglo::show(std::string s) {
   std::cout << s <<"[\n"; 
   for ( std::list<Exp*>::iterator it = larr.begin();
         it != larr.end();
         ++it
       ){
            Exp* tmp = *it;
            tmp->show(s+ "  ");
       }
    std::cout << "]\n";
} 

/* Class Arreglo */

Arreglo::Arreglo(){
}

Arreglo::Arreglo(LArreglo* la_):la(la_){
}
    
Arreglo::~Arreglo() { 
}

void Arreglo::show(std::string s) {
    std::cout <<  s << "Arreglo: \n";
    la->show(s+ "  ");
}

/* Class BloqueDeclare */

BloqueDeclare::BloqueDeclare(): scope(0){}

BloqueDeclare::BloqueDeclare(int sc): scope(sc){}
    
BloqueDeclare::~BloqueDeclare() {}

void BloqueDeclare::show(std::string s) {} 

/* Class LElseIf */

LElseIf::LElseIf(bool error) {
    exp = 0;
    lelseif = 0;
    if (error){
        tipo = TypeError::Instance();
    } else{
        tipo = TypeVoid::Instance();
    }
}

LElseIf::LElseIf(Exp* e, BloqueDeclare* d, ListaInstrucciones* li, LElseIf* lif = 0) {
    exp = e;
    declaraciones = d;
    listainstrucciones = li;
    lelseif = lif;
    tipo = TypeVoid::Instance();
}

LElseIf::LElseIf(BloqueDeclare* d, ListaInstrucciones* li) {
    exp = 0;
    lelseif = 0;
    declaraciones = d;
    listainstrucciones = li;
    tipo = TypeVoid::Instance();
}

LElseIf::~LElseIf() {
    delete this;
}

void LElseIf::show(std::string s) {
    if (exp == 0 || lelseif == 0){
        std::cout << s << "Else :\n";
        listainstrucciones->show(s+ "  ");
    } else{
        std::cout << s << "Else If: \n";
        exp->show(s+"  ");
        std::cout << s << "Then: \n";
        listainstrucciones->show(s+ "  ");
    }
} 

/* Class SelectorIf */

SelectorIf::SelectorIf(Exp* e, BloqueDeclare* d = 0, ListaInstrucciones* l = 0, LElseIf* lif = 0) {
    exp = e;
    declaraciones = d;
    listainstrucciones = l;
    lelseif = lif;
    instruccion1 = 0;
    instruccion2 = 0;
    tipo = TypeVoid::Instance();
}

SelectorIf::SelectorIf(Exp* e, Instruccion* i, Instruccion* i2 = 0) {
    exp = e;
    instruccion1 = i;
    instruccion2 = i2;
    listainstrucciones = 0;
    declaraciones = 0;
    tipo = TypeVoid::Instance();
}

SelectorIf::~SelectorIf() {
}

void SelectorIf::show(std::string s) {
    std::cout << s << "If: \n";
    exp->show("  "+s);
    std::cout << s << "Then: \n";
    if (listainstrucciones != 0) listainstrucciones->show("  "+s);
    if ( instruccion1 != 0)  instruccion1->show("  "+s);
    if ((lelseif!= 0 ) || (instruccion2 != 0))std::cout << s << "Else: \n";
    if (lelseif != 0) lelseif->show("  "+s);
    if (instruccion2 != 0) instruccion2->show("  "+s);
} 

/* Class LoopWhile */

LoopWhile::LoopWhile(Exp* e, BloqueDeclare* bd, ListaInstrucciones* li) {
    exp = e;
    declaraciones = bd;
    listainstrucciones = li;
    tipo = TypeVoid::Instance();
}

LoopWhile::~LoopWhile() {}

void LoopWhile::show(std::string s) {
    std::cout << s << "While:\n";
    exp->show("  "+s);
    std::cout << s << "do:\n";
    listainstrucciones->show("  "+s);
} 

/* Class Asignacion */

Asignacion::Asignacion() {}

Asignacion::Asignacion(Identificador* i, Exp* e) {
    identificador = i;
    exp = e;
    lcorchetes = 0;
    identificador2 = 0;
    arreglo = 0;
}

Asignacion::Asignacion(Identificador* id, LCorchetes* lc, Exp* e) {
    identificador = id;
    lcorchetes = lc;
    exp = e;
    identificador2 = 0;
    arreglo = 0;
}

Asignacion::Asignacion(Identificador* id,Identificador* id2,Exp* e) {
    identificador = id;
    identificador2 = id2;
    exp = e;
    lcorchetes = 0;
    arreglo = 0;
}

Asignacion::Asignacion(Identificador* id, Arreglo* arr) {
    identificador = id;
    arreglo = arr;
    lcorchetes = 0;
    identificador2 = 0;
    exp = 0;
}

Asignacion::~Asignacion() {
}

void Asignacion::show(std::string s) {
    std::cout << s << "Asignacion: \n";
    identificador->show(s + "  ");
    if (identificador2 != 0) identificador2->show(s+"  "); 
    if (lcorchetes != 0) lcorchetes->show(s+"  ");
    if (exp != 0){
        exp->show(s+"  ");
    }
    if (arreglo != 0) arreglo->show(s+ "  ");
} 


/* Class LoopFor */

LoopFor::LoopFor(Identificador* id, Exp* e1,Exp* e2,BloqueDeclare* d, ListaInstrucciones* l) {
    identificador = id;
    exp = e1;
    asignacion = 0;
    exp2 = e2;
    declaraciones = d;
    listainstrucciones = l;
    tipo = TypeVoid::Instance();
}

LoopFor::LoopFor(Identificador* id, Exp* e1,Asignacion* asig,BloqueDeclare* d, ListaInstrucciones* l) {
    identificador = id;
    exp = e1;
    asignacion = asig;
    exp2 = 0;
    declaraciones = d;
    listainstrucciones = l;
    tipo = TypeVoid::Instance();
}

LoopFor::~LoopFor() {
}

void LoopFor::show(std::string s) {
    std::cout << s << "Loop For: \n";
    identificador->show("  "+s);
    exp->show("  "+s);
    if (asignacion != 0) asignacion->show(" "+s);
    if (exp2 != 0) exp2->show("  "+s);
    listainstrucciones->show("  "+s);
} 


/* Class PlusMinus */

PlusMinus::PlusMinus(Identificador* id, int t):identificador(id), tipo_inst(t), tipo(TypeVoid::Instance()) {
}

PlusMinus::~PlusMinus() {}

void PlusMinus::show(std::string s) {
    std::cout << s << "Instruccion : " << tipo << '\n';
    identificador->show("  "+s);
} 

/* Class LVaroValor */

LVaroValor::LVaroValor(bool error) {
    if (error){
        tipo = TypeError::Instance();
    } else{
        tipo = TypeVoid::Instance();
    }
}

void LVaroValor::append(Exp* e){
    lvarovalor.push_back(e);
}
        
LVaroValor::~LVaroValor() {
}

void LVaroValor::show(std::string s) {
    std::cout << "Lista de Valores o Variables: \n";
    for (std::list<Exp*>::iterator it = lvarovalor.begin();
         it != lvarovalor.end();
         ++it
        ){
            Exp* tmp = *it;
            tmp->show(s+ "  ");
        }
} 


/* Class EntradaSalida */

EntradaSalida::EntradaSalida(int t,Exp* lv) {
    tipo = t;
    argumento = lv;
}

EntradaSalida::~EntradaSalida() {}

void EntradaSalida::show(std::string s) {
    if (tipo == 0){
        std::cout << s << "Read: \n";
    } else {
        std::cout << s << "Print: \n";
    }
    argumento->show(s + "  ");
}

/* Class LlamadaFuncion */

LlamadaFuncion::LlamadaFuncion(Identificador* i, LVaroValor* lv) {
    id = i;
    lvarovalor = lv;
}

LlamadaFuncion::~LlamadaFuncion() {}

void LlamadaFuncion::show(std::string s){
    std::cout << s << "Llamada Funcion : ";
    id->show(s);
    std::cout << s << "Argumentos: \n";
    lvarovalor->show(s+ "  ");
} 


/* Class LParam */

LParam::LParam(){}

void LParam::append(TypeS* t, Identificador* id){
    std::pair<TypeS*, Identificador*> par (t,id);
    lParam.push_back(par);
}
std::list<std::pair<TypeS*,Identificador*> > LParam::get_list(){
    return lParam;
}

LParam::~LParam() {
}

void LParam::show(std::string s) {
    std::cout << s << "Parametros: \n";
    for (std::list<std::pair<TypeS*, Identificador*> >::iterator it = lParam.begin();
         it != lParam.end();
         ++it
        ){
            std::pair<TypeS*, Identificador*> tmp = *it;
            std::cout<<  "Tipo: " << tmp.first->get_name() << " , Identificador: " << tmp.second->identificador;
            std::cout << std::endl;
        }
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
    if (retorno != 0) {
        std::cout << s << "Retorna: \n";
        retorno->show(s+"  ");
    }
} 


/* Class LFunciones */

LFunciones::LFunciones() {}
    
LFunciones::LFunciones(Funcion f, LFunciones* l) {
        funcion = f;
        lista = l;
}

LFunciones::~LFunciones() {  }

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

