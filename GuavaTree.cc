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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "Identificador: " << identificador << " ,linea: " << linea <<" ,columna: " << columna << "\n" ;
}


/* Class LCorchetes */

LCorchetes::LCorchetes(bool error) {
    if (error){
        tipo = TypeError::Instance();
    } else {
        tipo = TypeInt::Instance();
    }
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();

    std::cout << s << "Expresion Unaria , linea: " << linea << " , columna: " << columna  << "\n" ;
    std::cout << s << "Exp: \n";
    exp->show(s+" ");
    if (corchetes != 0) corchetes->show(s+ "  ");
    if (operacion != 0) std::cout << s << "Operador: " << *operacion << '\n';
} 

std::string ExpUn::revision_unaria(Exp* exp_1, TypeS* tipo_esperado1, TypeS* tipo_esperado2, ExpUn* tmp, std::string (*f)(std::string,std::string) ){
    std::string msg ("");
    if (exp_1 == 0){ 
        tmp->tipo = TypeError::Instance();
        return msg;
    }
    // Verificación de un solo tipo válido
    else if (tipo_esperado2 == 0) {
        if (exp_1->get_tipo() == tipo_esperado1)
        { 
            tmp->tipo = exp_1->get_tipo();
        }
        else {
            msg = f(tipo_esperado1->get_name(),exp_1->get_tipo()->get_name());
            tmp->tipo = TypeError::Instance();
        }
    }
    // Verificación de dos tipos válidos
    else {
        if (exp_1->get_tipo() == tipo_esperado1 ||
            exp_1->get_tipo() == tipo_esperado2)
        {
            tmp->tipo = exp_1->get_tipo();
        }
        else {
            std::string expected = tipo_esperado1->get_name()+"' or '"+tipo_esperado2->get_name();
            msg = f(expected,exp_1->get_tipo()->get_name());
            tmp->tipo = TypeError::Instance();
        }
    }
    return msg;
}



/* Class ExpBin */

ExpBin::ExpBin(){
    tipo = TypeError::Instance();
}

ExpBin::ExpBin(Exp* e1,Exp* e2,std::string op):exp1(e1), exp2(e2), operacion(op){
}

ExpBin::~ExpBin() {}

void ExpBin::show(std::string s){
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();

    std::cout << s << "Expresion Binaria ,linea: " << linea << " ,columna: " << columna << "\n";
    exp1->show(s+"  ");
    exp2->show(s+"  ");
    std::cout << s << "Operador: " << operacion << '\n';
}


std::string ExpBin::revision_binaria(Exp* exp_1, Exp* exp_2, ExpBin* tmp,
                                     TypeS* tipo_esperado1, TypeS* tipo_esperado2,
                                     std::string (*mensaje_error_tipos)(std::string,std::string),
                                     std::string (*mensaje_diff_operandos)(std::string,std::string,std::string,std::string)){
    std::string msg ("");
    if (exp_1 == 0 || exp_2 == 0){ 
        tmp->tipo = TypeError::Instance();
        return msg;
    }
    else if (tipo_esperado2 == 0) {
        if (exp_1->get_tipo() == tipo_esperado1 &&
            exp_2->get_tipo() == tipo_esperado1)
        { 
            tmp->tipo = exp_1->get_tipo();
        } 
        else if (exp_1->get_tipo() != tipo_esperado1) {
            msg = mensaje_error_tipos(tipo_esperado1->get_name(),exp_1->get_tipo()->get_name());
            tmp->tipo = TypeError::Instance();
        }
        else {
            msg = mensaje_error_tipos(tipo_esperado1->get_name(),exp_2->get_tipo()->get_name());
            tmp->tipo = TypeError::Instance();
        } 
    }
    else {
        if (exp_1->get_tipo() == exp_2->get_tipo() &&
            (exp_1->get_tipo() == tipo_esperado1 ||
             exp_1->get_tipo() == tipo_esperado2))
        {
            tmp->tipo = exp_1->get_tipo();
        }
        else if (exp_1->get_tipo() != exp_2->get_tipo() &&
                 (exp_1->get_tipo() == tipo_esperado1 &&
                  exp_2->get_tipo() == tipo_esperado2) ||
                 (exp_1->get_tipo() == tipo_esperado2 &&
                  exp_2->get_tipo() == tipo_esperado1)) {
            std::string expected = exp_1->get_tipo()->get_name()+"' or '"+exp_2->get_tipo()->get_name();
            msg = mensaje_diff_operandos(tmp->operacion,exp_1->get_tipo()->get_name(),exp_2->get_tipo()->get_name(),expected);
            tmp->tipo = TypeError::Instance();
        }
        else {
            std::string expected = tipo_esperado1->get_name()+"' or '"+tipo_esperado2->get_name();
            if (exp_1->get_tipo() != tipo_esperado1 &&
                exp_1->get_tipo() != tipo_esperado2) {
                msg = mensaje_error_tipos(expected,exp_1->get_tipo()->get_name());
            }
            else {
                msg = mensaje_error_tipos(expected,exp_2->get_tipo()->get_name());
            }
            tmp->tipo = TypeError::Instance();
        }
    }
    return msg;
}

std::string ExpBin::revision_comparison(Exp* exp_1, Exp* exp_2, ExpBin* tmp,int cmpv, 
                                        std::string (*mensaje_error_tipos)(std::string,std::string), 
                                        std::string (*mensaje_diff_operandos)(std::string,std::string,std::string,std::string)){
    std::string msg ("");
    if (exp_1 == 0 || exp_2 == 0){
        tmp->tipo = TypeError::Instance();
        return msg;
    }
    if (exp_1->get_tipo() == exp_2->get_tipo() &&
        (exp_1->get_tipo() == TypeInt::Instance() ||
        exp_1->get_tipo() == TypeReal::Instance())) {
        tmp->tipo = TypeBool::Instance();
    } 
    else if (exp_1->get_tipo() != exp_2->get_tipo() &&
            (exp_1->get_tipo() == TypeInt::Instance() &&
            exp_2->get_tipo() == TypeReal::Instance()) ||
            (exp_1->get_tipo() == TypeReal::Instance() &&
            exp_2->get_tipo() == TypeInt::Instance())) {
        std::string expected = exp_1->get_tipo()->get_name()+"' or '"+exp_2->get_tipo()->get_name();
        std::string msg = mensaje_diff_operandos(std::string("<, <=, >, >=, =, !="),exp_1->get_tipo()->get_name(),exp_2->get_tipo()->get_name(),expected);
        tmp->tipo = TypeError::Instance();
    }
    else if ( exp_1->get_tipo() == exp_2->get_tipo() && 
              exp_1->get_tipo() == TypeBool::Instance() &&
              (cmpv == 5 || cmpv == 6)){
        tmp->tipo = TypeBool::Instance();
    }
    else {
        tmp = new ExpBin();
        if (exp_1->get_tipo() != TypeInt::Instance() &&
            exp_1->get_tipo() != TypeReal::Instance()) {
            msg = mensaje_error_tipos("integer' or 'real",exp_1->get_tipo()->get_name());
        }
        else {
            std::string msg = mensaje_error_tipos("integer' or 'real",exp_2->get_tipo()->get_name());
        }
        tmp->tipo = TypeError::Instance();
    }
    return msg;
}


/* Lista Instrucciones */

ListaInstrucciones::ListaInstrucciones() {
    instruccion = 0;
    listainstrucciones = 0;
    tipo = TypeVoid::Instance();
}

ListaInstrucciones::ListaInstrucciones(Instruccion* inst, ListaInstrucciones* li = 0) {
    instruccion = inst;
    listainstrucciones = li;
    tipo = TypeVoid::Instance();
}

ListaInstrucciones::~ListaInstrucciones() {
}

void ListaInstrucciones::show(std::string s) {
    if (listainstrucciones != 0) listainstrucciones->show(s);
    if (instruccion != 0) instruccion->show(s);
}
/**
 * Funcion que obtiene todos los returns dentro de una lista de instrucciones.
 * Faltan pruebas.
 */
std::list<Instruccion*> ListaInstrucciones::obtener_return(){
    std::list<Instruccion*> resultado;
    if (instruccion == 0 ) goto lista;

    if (instruccion->es_return()) resultado.push_front(instruccion);

   if (instruccion->tiene_lista_instrucciones()){
        InstruccionConLista* tmp = (InstruccionConLista*) instruccion;
        ListaInstrucciones* tmp_lista = tmp->obtener_lista_instrucciones(); 
        if (tmp_lista != 0) resultado.splice(resultado.end(), tmp_lista->obtener_return() ); 
    }

    lista:
    if (listainstrucciones != 0 ) resultado.splice(resultado.end(),listainstrucciones->obtener_return());
    return resultado;
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "Lista de Variables de Arreglo ,linea: " << linea << " ,columna: " << columna << " :"; 

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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s <<"Variables , linea: " << linea << ", columna: " << column << " ";
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
        )
    {
        Exp* tmp = *it;
        tmp->show(s+ "  ");
    }
    std::cout <<  s << "]\n";
} 

/* Class Arreglo */

Arreglo::Arreglo(){
}

Arreglo::Arreglo(LArreglo* la_):la(la_){
    TypeS* tipo = new TypeArray(la->get_tipo(),la->get_tipoEstructura(),la->size());
}
    
Arreglo::~Arreglo() { 
}

void Arreglo::show(std::string s) {
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout <<  s << "Arreglo  ,linea: " << linea << ", columna: " << column << "\n";
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();

    std::cout << s << "If, linea: " << linea << ", columna: " << columna << "\n";
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();

    std::cout << s << "While, linea: " << linea << ", columna: " << column << "\n";
    if (exp != 0 ) exp->show("  "+s);
    std::cout << s << "do:\n";
    if (listainstrucciones != 0)listainstrucciones->show("  "+s);
} 

/* Class Asignacion */

Asignacion::Asignacion() {
    id = 0;
    exp = 0;
    tipo = TypeError::Instance();
}

Asignacion::Asignacion(Exp* i, Exp* e) {
    id = i;
    exp = e;
    tipo = TypeVoid::Instance();
}

Asignacion::~Asignacion() {
}

void Asignacion::show(std::string s) {

    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();

    std::cout << s << "Asignacion, linea: " << linea << ", columna: " << columna << "\n";
    if(id != 0) id->show(s + "  ");
    if (exp != 0){
        exp->show(s+"  ");
    }
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();

    std::cout << s << "Loop For, linea: " << linea << ", columna: " << columna << " \n";
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "Instruccion : ";;
    switch(tipo_inst){
        case 0:
            std::cout << "-- Prefijo";
            break;
        case 1:
            std::cout << "-- Postfijo";
            break;
        case 2:
            std::cout << "++ Prefijo";
            break;
        case 3:
            std::cout << "++ Postfijo";
            break;
    }
    std::cout << ", linea: " << linea << ", columna: " << columna << "\n";
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
    std::cout << s << "Lista de Valores o Variables: \n";
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    if (tipo == 0){
        std::cout << s << "Read linea: " << linea << ", columna: " << columna << "\n";
    } else {
        std::cout << s << "Print: linea: " << linea << ", columna: " << columna << "\n";
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
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "Llamada Funcion linea: " << linea << ", columna: " << columna << "\n";
    id->show(s+ "  ");
    std::cout << s << "Argumentos: \n";
    lvarovalor->show(s+ "  ");
} 


/* Class LParam */

LParam::LParam(){}

void LParam::append(TypeS* t, Identificador* id){
    std::pair<TypeS*, Identificador*> par (t,id);
    lParam.push_back(par);
}

void LParam::appendTipo(TypeS* t) {
    lTipos.push_back(t);
}

std::list<std::pair<TypeS*,Identificador*> > LParam::get_list(){
    return lParam;
}

std::list<TypeS*> LParam::get_tipos() {
   return lTipos; 
}

LParam::~LParam() {
}

void LParam::show(std::string s) {
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "Parametros: linea: " << linea << ", columna: " << columna << "\n";
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
    tipo = TypeError::Instance();
}

Funcion::Funcion(TypeS* t, Identificador* id, LParam* param, BloqueDeclare* decl, ListaInstrucciones* li) {
    tipo = t;
    identificador = id;
    parametros = param;
    declaraciones = decl;
    listaI = li;
}

Funcion::~Funcion() {
}

void Funcion::show(std::string s) {
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "Funcion: linea: " << linea << ", columna: " << columna << "\n";
    std::cout << tipo->get_name() << "  ";
    identificador->show(s+ "  ");
    std::cout << s << "Parametros: \n";
    parametros->show(s+"  ");
    std::cout << s << "Instrucciones: \n";
    listaI->show(s+ "  ");
} 


/* Class LFunciones */

LFunciones::LFunciones() {}
    
LFunciones::LFunciones(Funcion* f, LFunciones* l) {
        funcion = f;
        lista = l;
}

LFunciones::~LFunciones() {  }

void LFunciones::show(std::string s) {
    if (funcion != 0) funcion->show(s+"  ");
    if (lista != 0) lista->show(s + "  ");
} 



/* Class BloquePrincipal */

BloquePrincipal::BloquePrincipal() {}

BloquePrincipal::BloquePrincipal(BloqueDeclare* b, LFunciones* l) {
    globalD = b;
    funciones = l;
}

BloquePrincipal::~BloquePrincipal() {}

void BloquePrincipal::show(std::string s) {
    funciones->show(s);
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

