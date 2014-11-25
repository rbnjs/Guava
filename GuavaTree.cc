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

std::string Exp::gen() {
    std::string interCode("");
    for (std::list<GuavaQuads*>::iterator it = listaQuads->begin();it!=listaQuads->end();++it) {
        GuavaQuads* actual = *it;
        interCode += actual->gen();
    }
    return interCode;
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

/* Class ExpUnBool  */

ExpUnBool::ExpUnBool(Exp* e, std::string* s): ExpUn(e,s),ExpBool() {

}
/**  
 * Genera los quads para la expresion NOT
 * La unica expresion Booleana unaria es NOT
 */
std::list<GuavaQuads*>* ExpUnBool::generar_quads(){
    BoolLabel *label_exp = exp->bool_label(); 
    if (label_exp == 0) return 0;
    label_exp->true_label = labels_bool->false_label;
    label_exp->false_label = labels_bool->true_label;
    return exp->generar_quads();
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
        else if ((exp_1->get_tipo() != exp_2->get_tipo() &&
                 (exp_1->get_tipo() == tipo_esperado1 &&
                  exp_2->get_tipo() == tipo_esperado2)) ||
                 ((exp_1->get_tipo() == tipo_esperado2 &&
                  exp_2->get_tipo() == tipo_esperado1))) {
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
    else if ((exp_1->get_tipo() != exp_2->get_tipo() &&
            (exp_1->get_tipo() == TypeInt::Instance() &&
            exp_2->get_tipo() == TypeReal::Instance())) ||
            ((exp_1->get_tipo() == TypeReal::Instance() &&
            exp_2->get_tipo() == TypeInt::Instance()))) {
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

/* ExpBinBoolComparison  */

/**
 * Se construye ExpBinBoolComparison de la misma forma que un ExpBin
 */
ExpBinBoolComparison::ExpBinBoolComparison(Exp* exp_1,Exp* exp_2,std::string op): ExpBin(exp_1,exp_2,op),ExpBool() {
}

/** 
 * Retorna una lista de GuavaQuads.
 */
std::list<GuavaQuads*>* ExpBinBoolComparison::generar_quads(){
    std::list<GuavaQuads*>* result = exp1->generar_quads();
    std::list<GuavaQuads*>* code = exp2->generar_quads();
    if (code != 0) result->splice(result->end(), *code);
    Symbol* test_symbol = temp->newtemp();
    GuavaQuads* test = new GuavaQuadsExp(operacion, exp1->addr,exp2->addr,test_symbol);
    result->push_back(test);

    if ( !labels_bool->true_label->fall() && !labels_bool->false_label->fall()){
        GuavaQuads* if_quad = new GuavaQuadsIf(operacion,test_symbol,0,labels_bool->true_label); 
        GuavaQuads* go_to = new GuavaGoTo(labels_bool->false_label);
        result->push_back(if_quad);
        result->push_back(go_to);
    }else if (!labels_bool->true_label->fall()){
        GuavaQuads* if_quad = new GuavaQuadsIf(operacion,test_symbol,0,labels_bool->true_label); 
        result->push_back(if_quad);
    }else if (!labels_bool->false_label->fall()) {
        GuavaQuads* if_not = new GuavaQuadsIfNot(operacion,test_symbol,0,labels_bool->false_label);
        result->push_back(if_not);
    }

    GuavaQuads* comentario = new GuavaComment("EXPRESION COMPARACIÓN.",line, column);
    result->push_front(comentario);
    return result;
}

/* ExpBinBoolLogic */

ExpBinBoolLogic::ExpBinBoolLogic(Exp* exp_1,Exp* exp_2,std::string op): ExpBin(exp_1,exp_2,op),ExpBool() {
    if (op.compare("AND") == 0){
        AND = true;
    }
}

std::list<GuavaQuads*>* ExpBinBoolLogic::generar_quads(){
    if (AND){
        BoolLabel* label1 = exp1->bool_label();
        BoolLabel* label2 = exp2->bool_label();
        label1->true_label = new GuavaFall();
        label1->false_label = (!labels_bool->false_label->fall() ? labels_bool->false_label : new GuavaLabel());
        label2->true_label = labels_bool->true_label;
        label2->false_label = labels_bool->false_label;
        std::list<GuavaQuads*>* result = exp1->generar_quads();
        std::list<GuavaQuads*>* code = exp2->generar_quads();
        result->splice(result->end(),*code);
        if (labels_bool->false_label->fall()){
           result->push_back(label1->false_label); 
        }
        GuavaQuads* comentario = new GuavaComment("EXPRESION AND.",line, column);
        result->push_front(comentario);
        return result;
    } else {
        BoolLabel* label1 = exp1->bool_label();
        BoolLabel* label2 = exp2->bool_label();
        label1->false_label = new GuavaFall();
        label1->true_label = (!labels_bool->true_label->fall() ? labels_bool->true_label : new GuavaLabel());
        label2->true_label = labels_bool->true_label;
        label2->false_label = labels_bool->false_label;
        std::list<GuavaQuads*>* result = exp1->generar_quads();
        std::list<GuavaQuads*>* code = exp2->generar_quads();
        result->splice(result->end(),*code);
        if (labels_bool->false_label->fall()){
           result->push_back(label1->false_label); 
        }
        GuavaQuads* comentario = new GuavaComment("EXPRESION OR.",line, column);
        result->push_front(comentario);
        return result;

    }
    return 0;
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
/**
 * Obtiene todas las instrucciones continue o break de una lista de instrucciones.
 * No lo hace recursivo.
 */
std::list<Instruccion*> ListaInstrucciones::obtener_continue_break(){
    std::list<Instruccion*> result;
    if (instruccion == 0) return result;
    if (instruccion->continue_break()) result.push_front(instruccion);

    if (listainstrucciones != 0 ){
        result.splice(result.end(),listainstrucciones->obtener_continue_break());
    }
    
    return result;
}
/** 
 * Funcion que coloca el label begin a cada una de las instrucciones
 * continue
 */
void ListaInstrucciones::set_begin(GuavaQuads* begin){
    if (instruccion == 0) return; 

    if (instruccion->continue_break()){
        instruccion->set_begin(begin);
    }

   if (instruccion->tiene_lista_instrucciones()){
        InstruccionConLista* tmp = (InstruccionConLista*) instruccion;
        ListaInstrucciones* tmp_lista = tmp->obtener_lista_instrucciones(); 
        if (tmp_lista != 0) tmp_lista->set_begin(begin);
    }
   if (listainstrucciones != 0) listainstrucciones->set_begin(begin);
}


/**
 * Genera los quads para una lista de instrucciones
 * Falta colocar los labels.
 */
std::list<GuavaQuads*>* ListaInstrucciones::generar_quads(){
    std::list<GuavaQuads*>* l_quads1 = 0;
    std::list<GuavaQuads*>* l_quads2 = 0;
    next = new GuavaLabel();

    if (instruccion != 0){
        instruccion->next = next;
        l_quads1 = instruccion->generar_quads();  
        if (l_quads1 == 0){
            l_quads1 = new std::list<GuavaQuads*>();
        }
        l_quads1->push_back(instruccion->next); //Coloco al final del codigo el label de instruccion.
    }

    if (listainstrucciones != 0) l_quads2 = listainstrucciones->generar_quads();

    if (l_quads2 == 0){
        l_quads2 = new std::list<GuavaQuads*>();
    }

    if (l_quads1 != 0) l_quads2->splice(l_quads2->end(), (*l_quads1));
    return l_quads2;
}

void ListaInstrucciones::set_next(Instruccion* instr){
    if (instruccion == 0 || instr == 0) return;
    instruccion->next = instr->next;
}

/* Class Retorno */

/**
 * Genera los quads de retorno.
 * Al final de realizar lo que hace la expresion me voy para next
 */
std::list<GuavaQuads*>* Retorno::generar_quads(){
    std::list<GuavaQuads*>* result;
    if (exp != 0) result = exp->generar_quads();
    else result = new std::list<GuavaQuads*>;

    GuavaQuads* retorno;
    if (exp!= 0) retorno = new GuavaQuadsReturn(exp->addr,tmp_return) ;
    else retorno = new GuavaQuadsReturn();
    result->push_back(retorno);
    return result;
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

/** 
 * Agrega un nuevo elemento a la lista de expresiones
 * de LArreglo.
 * Cada vez que se agrega un elemento se modifica su tipo.
 */
void LArreglo::append(Exp* e){
    larr.push_back(e);

    if (tipo_estructura == 0){
        //Caso en el que es nuevo.
        if (!e->is_array()){
            tipo_estructura = new TypeArray(tipo_primitivo,0,larr.size());  
        } else {
            tipo_estructura = new TypeArray(tipo_primitivo,e->get_tipo(), larr.size());
        }
    }else{
        if (!e->is_array()){
            tipo_estructura->size_inc();
        }else{
            Arreglo* arr = (Arreglo*) e; 
            int tam = arr->get_tipoEstructura()->get_dimensiones();
            tipo_estructura = new TypeArray(tipo_primitivo,new TypeArray(tipo_primitivo,arr->get_tipoEstructura(),tam),larr.size());
        }
    }
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

/** 
 * Genero quads para un arreglo de expresiones o de valores.
 * Para esto voy a obtener cada uno de los quads de las expresiones y 
 * asignarle su valor a la dirección del arreglo.
 * @return result Lista de Quads.
 */
std::list<GuavaQuads*>* Arreglo::generar_quads(){

    /* NOTA:
     * Para que las lineas a continuacion funcionen correctamente, se debe de
     * arreglar el generador de quads para expresiones del tipo arreglo.
     *
     * Ver GuavaDriver.cc:936 
     */


    std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>;
    int offset_actual = 0; // Voy a moverme por los distintos offsets del arreglo.

    for (std::list<Exp*>::iterator it = la->larr.begin(); it != la->larr.end(); ++it){
        Exp* exp_indice = *it;
        //Se generan los quads de la expresion que define una celda del arreglo
        std::list<GuavaQuads*>* exp_quads = exp_indice->generar_quads();
        //Se agregan los quads relativos a la expresion de la celda del arreglo
        if(exp_quads != 0)
            result->splice(result->end(), *exp_quads);
        /* Se genera el quad que guarda el valor de la expresion en la posicion
         * del arreglo constante respectiva.
         */
        direccion->offset = offset_actual;
        //OJO CON LA SIGUIENTE LINEA
        GuavaQuads* constante_arr = new GuavaQuadsExp("[]",direccion,exp_indice->addr,direccion);
        result->push_front(constante_arr);
        offset_actual += tam_tipo_primitivo;

    }
    return result;
}

/* Class BloqueDeclare */

BloqueDeclare::BloqueDeclare(): scope(0){}

BloqueDeclare::BloqueDeclare(int sc): scope(sc){}
    
BloqueDeclare::~BloqueDeclare() {}

void BloqueDeclare::show(std::string s) {} 

/* Class LElseIf */

LElseIf::LElseIf(bool error) {
    if (error){
        tipo = TypeError::Instance();
    } else{
        tipo = TypeVoid::Instance();
    }
}

LElseIf::LElseIf(Exp* e, BloqueDeclare* d, ListaInstrucciones* li, LElseIf* lif = 0):exp(e),declaraciones(d),listainstrucciones(li),lelseif(lif),tipo(TypeVoid::Instance()) {
}

LElseIf::LElseIf(BloqueDeclare* d, ListaInstrucciones* li, LElseIf* lif = 0): declaraciones(d), listainstrucciones(li), tipo(TypeVoid::Instance()), lelseif(lif){
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

std::list<GuavaQuads*>* LElseIf::generar_quads(){
    return 0;    
}

/* Class Else */

Else::Else(BloqueDeclare* b, ListaInstrucciones* li, LElseIf* leif): LElseIf(b,li,leif){
}

std::list<GuavaQuads*>* Else::generar_quads(){
    listainstrucciones->next = next;
    std::list<GuavaQuads*>* result;
    if (lelseif != 0){
       lelseif->next = next;
       result = lelseif->generar_quads(); 
       std::list<GuavaQuads*>* code = listainstrucciones->generar_quads();
       if (code != 0) result->splice(result->end(),*code);
    }else {
        result = listainstrucciones->generar_quads();
    }
    GuavaQuads* comentario = new GuavaComment("ELSE IF",line,column);
    result->push_front(comentario);
    return result;
}

/* Class ElseIf */

ElseIf::ElseIf(Exp* e, BloqueDeclare* bd, ListaInstrucciones* li, LElseIf* leif): LElseIf(e,bd,li,leif){}


std::list<GuavaQuads*>* ElseIf::generar_quads(){
    BoolLabel* label = exp->bool_label();
    label->true_label = new GuavaLabel();
    std::list<GuavaQuads*>* result;
    std::list<GuavaQuads*>* code_leif = 0;
    listainstrucciones->next = next;

    if (lelseif != 0){
        label->false_label = new GuavaLabel();
        lelseif->next = next;
        code_leif = lelseif->generar_quads();
    } else{
        label->false_label = next;
    }

    result = exp->generar_quads();
    result->push_back(label->true_label);
    std::list<GuavaQuads*>* code_li = listainstrucciones->generar_quads();
    if (code_li != 0) result->splice(result->end(),*code_li);

    if (code_leif != 0){
        GuavaQuads* go_to = new GuavaGoTo(next);
        result->push_back(go_to);
        result->push_back(label->false_label);
        result->splice(result->end(),*code_leif);
    }    
    GuavaQuads* comentario = new GuavaComment("ELSE IF",line,column);
    result->push_front(comentario);
    return result;
}


/* Class SelectorIf */

std::list<GuavaQuads*>* SelectorIf::generar_quads(){
    return 0;
}

/* Class SelectorIfSimple */


SelectorIfSimple::SelectorIfSimple(Exp* e, Instruccion* i1, Instruccion* i2): SelectorIf(e), instruccion1(i1),instruccion2(i2){
}

void SelectorIfSimple::show(std::string s){
    std::ostringstream convert; 
    convert << line;
    std::string linea = convert.str();
    convert.flush();
    convert << column;
    std::string columna = convert.str();
    std::cout << s << "If, linea: " << linea << ", columna: " << columna << "\n";
    exp->show("  "+s);
    std::cout << s << "Then: \n";
    if ( instruccion1 != 0)  instruccion1->show("  "+s);
    if (instruccion2 != 0) std::cout << s << "Else: \n";
    if (instruccion2 != 0) instruccion2->show("  "+s);
}

std::list<GuavaQuads*>* SelectorIfSimple::generar_quads(){
    BoolLabel* label = exp->bool_label(); 
    label->true_label = new GuavaFall();
    instruccion1->next = next;

    if (instruccion2 == 0){
        label->false_label = next;
    } else {
        label->false_label = new GuavaLabel();
        instruccion2->next = next;
    }

    std::list<GuavaQuads*>* result = exp->generar_quads();
    ///result->push_back(label->true_label); Se deja caer.
    std::list<GuavaQuads*>* code_1 = instruccion1->generar_quads();
    result->splice(result->end(), *code_1);

    if (instruccion2 != 0){
        GuavaQuads* go_to = new GuavaGoTo(next);  
        result->push_back(go_to);
        result->push_back(label->false_label);
        std::list<GuavaQuads*>* code_2 = instruccion2->generar_quads();
        result->splice(result->end(),*code_2);
    }

    GuavaQuads* comentario = new GuavaComment("SELECTOR IF SIMPLE",line,column);
    result->push_front(comentario);
    return result;
}

/* Class SelectorIfComplejo */

SelectorIfComplejo::SelectorIfComplejo(Exp* e, BloqueDeclare* bd, 
                                       ListaInstrucciones* li, LElseIf* lei): SelectorIf(e), declaraciones(bd), listainstrucciones(li), lelseif(lei) {}

void SelectorIfComplejo::show(std::string s) {
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
    if (lelseif!= 0)std::cout << s << "Else: \n";
    if (lelseif != 0) lelseif->show("  "+s);
} 

/** 
 * Genera el codigo de tres direcciones para los if complejos.
 */
std::list<GuavaQuads*>* SelectorIfComplejo::generar_quads(){
    BoolLabel* label = exp->bool_label(); 
    label->true_label = new GuavaFall();
    
    bool sin_else = lelseif->es_vacio();

    if ( sin_else ){
        label->false_label = next;
    } else {
        label->false_label = new GuavaLabel();
        lelseif->next = next;    
    }

    std::list<GuavaQuads*>* result = exp->generar_quads();
    //result->push_back(label->true_label); Me dejo caer
    std::list<GuavaQuads*>* code_1 = listainstrucciones->generar_quads(); 
    result->splice(result->end(),*code_1);

    if (!sin_else){
        GuavaQuads* go_to = new GuavaGoTo(next);
        result->push_back(go_to);
        result->push_back(label->false_label);
        std::list<GuavaQuads*>* code_2 = lelseif->generar_quads();
        result->splice(result->end(),*code_2);
    }     
    GuavaQuads* comentario = new GuavaComment("SELECTOR IF COMPLEJO",line,column);
    result->push_front(comentario);
    return result;
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

/* Class WhileDo */

WhileDo::WhileDo(Exp* e, BloqueDeclare* bd, ListaInstrucciones* li): LoopWhile(e,bd,li){}

std::list<GuavaQuads*>* WhileDo::generar_quads(){
    begin = new GuavaLabel(); 
    BoolLabel* label = exp->bool_label();
    label->true_label = new GuavaFall();
    label->false_label = next;
    listainstrucciones->next = next;
    listainstrucciones->set_begin(begin);
    std::list<GuavaQuads*>* result = exp->generar_quads();
    result->push_front(begin);
    //result->push_back(label->true_label);
    std::list<GuavaQuads*>* code_li = listainstrucciones->generar_quads();
    result->splice(result->end(), *code_li);
    GuavaQuads* go_to = new GuavaGoTo(begin);
    result->push_back(go_to);
    GuavaQuads* comentario = new GuavaComment("LOOP WHILE DO",line,column);
    result->push_front(comentario);
    return result;

}

/* Class DoWhile */

DoWhile::DoWhile(Exp* e, BloqueDeclare* bd, ListaInstrucciones* li): LoopWhile(e,bd,li){}


std::list<GuavaQuads*>* DoWhile::generar_quads(){
    begin = new GuavaLabel(); 
    BoolLabel* label = exp->bool_label();
    label->true_label = new GuavaFall();
    label->false_label = next;
    listainstrucciones->next = next;
    listainstrucciones->set_begin(begin);
     
    std::list<GuavaQuads*>* result = listainstrucciones->generar_quads();
    result->push_front(begin);
    std::list<GuavaQuads*>* code_exp = exp->generar_quads();
    result->splice(result->end(), *code_exp);
    //result->push_back(label->true_label);
    GuavaQuads* go_to = new GuavaGoTo(begin);
    result->push_back(go_to);
    GuavaQuads* comentario = new GuavaComment("LOOP DO WHILE",line,column);
    result->push_front(comentario);
    return result;
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
/** 
 * Genera Quads para asignacion.
 * Se consideran dos casos principalmente. Uno en el que 
 * la expresion es booleana y con cortocircuito y otro en el
 * que es una expresion normal.
 */
std::list<GuavaQuads*>* Asignacion::generar_quads(){
    std::list<GuavaQuads*>* result = id->generar_quads();
    if (exp->exp_bool()){
        //Caso en el que es una expresion booleana vamos a aprovechar 
        //jumping code
        BoolLabel* label = exp->bool_label();
        label->true_label = new GuavaLabel();
        label->false_label = new GuavaLabel();
        std::list<GuavaQuads*>* code = exp->generar_quads();
        if (code != 0) result->splice(result->end(),*code);
        result->push_back(label->true_label);
        GuavaQuads* exp_true = new GuavaQuadsExp(":=",new Symbol("true"),0,id->addr);
        result->push_back(exp_true);
        GuavaQuads* go_to = new GuavaGoTo(next);
        result->push_back(go_to);
        result->push_back(label->false_label);
        GuavaQuads* exp_false = new GuavaQuadsExp(":=",new Symbol("false"),0,id->addr);
        result->push_back(exp_false);
    }else {
        std::list<GuavaQuads*>* code = exp->generar_quads();
        if (code != 0) result->splice(result->end(),*code);
        GuavaQuads* exp_result = new GuavaQuadsExp(":=",exp->addr,0,id->addr);
        result->push_back(exp_result);
    }
    GuavaQuads* comentario = new GuavaComment("ASIGNACION",line,column);
    result->push_front(comentario);
    return result;
}


/* Class LoopFor */

LoopFor::LoopFor(ExpID* id, Exp* e1,Exp* e2,BloqueDeclare* d, ListaInstrucciones* l) {
    identificador = id;
    exp_bool = e1; // e1 expresion booleana
    asignacion = 0;
    exp_aritmetica = e2;
    declaraciones = d;
    listainstrucciones = l;
    tipo = TypeVoid::Instance();
}

LoopFor::LoopFor(ExpID* id, Exp* e1,Asignacion* asig,BloqueDeclare* d, ListaInstrucciones* l) {
    identificador = id;
    exp_bool = e1;
    asignacion = asig;
    exp_aritmetica = 0;
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
    exp_bool->show("  "+s);
    if (asignacion != 0) asignacion->show(" "+s);
    if (exp_aritmetica != 0) exp_aritmetica->show("  "+s);
    listainstrucciones->show("  "+s);
} 

/* Class LoopForExp */

LoopForExp::LoopForExp(ExpID* id, Exp* e1,Exp* e2,BloqueDeclare* d, ListaInstrucciones* l): LoopFor(id,e1,e2,d,l){}

std::list<GuavaQuads*>* LoopForExp::generar_quads(){
    begin = new GuavaLabel();
    BoolLabel* label = exp_bool->bool_label();
    label->true_label = new GuavaFall();
    label->false_label = next;
    listainstrucciones->next = begin;
    listainstrucciones->set_begin(begin);
    std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>;
    result->push_back(begin);
    std::list<GuavaQuads*>* bool_code = exp_bool->generar_quads();
    result->splice(result->end(),*bool_code);
    //result->push_back(label->true_label);
    std::list<GuavaQuads*>* code_l = listainstrucciones->generar_quads(); 
    result->splice(result->end(), *code_l);
    std::list<GuavaQuads*>* code_step = exp_aritmetica->generar_quads();
    result->splice(result->end(),*code_step);
    GuavaQuads* go_to = new GuavaGoTo(begin);
    result->push_back(go_to);
    GuavaQuads* comentario = new GuavaComment("LOOP FOR con EXPRESION",line,column);
    result->push_front(comentario);
    return result;
}


/* Class LoopForAsignacion */

LoopForAsignacion::LoopForAsignacion(ExpID* id, Exp* e1,Asignacion* asig,BloqueDeclare* d, ListaInstrucciones* l): LoopFor(id,e1,asig,d,l){}

std::list<GuavaQuads*>* LoopForAsignacion::generar_quads(){
    begin = new GuavaLabel();
    BoolLabel* label = exp_bool->bool_label();
    label->true_label = new GuavaFall();
    label->false_label = next;
    listainstrucciones->next = begin;
    listainstrucciones->set_begin(begin);
    std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>;
    result->push_back(begin);
    std::list<GuavaQuads*>* bool_code = exp_bool->generar_quads();
    result->splice(result->end(),*bool_code);
    //result->push_back(label->true_label);
    std::list<GuavaQuads*>* code_l = listainstrucciones->generar_quads(); 
    result->splice(result->end(), *code_l);
    std::list<GuavaQuads*>* code_step = asignacion->generar_quads();
    result->splice(result->end(),*code_step);
    GuavaQuads* go_to = new GuavaGoTo(begin);
    result->push_back(go_to);
    GuavaQuads* comentario = new GuavaComment("LOOP FOR con ASIGNACION",line,column);
    result->push_front(comentario);
    return result;

}
   

/* Class PlusMinus */

PlusMinus::PlusMinus(ExpID* id, int t):identificador(id), tipo_inst(t), tipo(TypeVoid::Instance()) {
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
/** 
 * Genera quads para la instruccion PlusMinus.
 */
std::list<GuavaQuads*>* PlusMinus::generar_quads(){
    /**
     * Cuestiones a modificar:
     * 
     * El postincremento evalúa toda la expresión y luego es que incrementa
     * su valor. Quiere decir que para el caso:
     *
     * ...
     * (1) x := 1;
     * (2) y := x++;
     * ...
     *
     * El valor de 'y' luego de la instrucción (2) es 1 y el de 'x' es 2, lo
     * que a nivel intermedio se traduce en:
     *
     * ...
     * y := x;
     * x := x + 1;
     * ...
     *
     * Por otro lado, el caso:
     *
     * ...
     * (1) x := 1;
     * (2) y := ++x;
     * ...
     *
     * El valor de 'y' luego de la instrucción (2) es 2 y el de 'x' es 2, lo
     * que a nivel intermedio se traduce en:
     *
     * ...
     * x := x + 1;
     * y := x;
     * ...
     *
     * Pensar caso de expresiones más complejas, casos más interesantes.
     * Este cambio tambien debe de ser implementado en la clase ExpUn de
     * GuavaTree.hh, donde se hace referencia a cuando el incremento/decremento
     * se hace en una expresion (a asignar) y no como una instruccion.
     *
     * Para este caso no es mas que una simple instruccion, basta con solo
     * traducir el incremento o decremento. Que sea anterior o posterior no
     * influye en el contexto.
     *
     * Para el caso en el que exista un incremento o decremento dentro de una
     * expresion es mas delicado: en caso de ser posterior debe de evaluarse
     * la expresion primero y luego el incremento, caso contrario cuando es
     * anterior. Mosca con casos como:
     *
     * ...
     * while (i < N) {
     *
     *  x := a[i++]; //vs. x := a[++i];
     *
     * }
     * ...
     *
     * Ver articulo de Wikipedia para explicacion del operador.
     **/
    //Se generan los quads asociados a la expresion operando.
    std::list<GuavaQuads*>* quads_exp = identificador->generar_quads();
    std::list<GuavaQuads*>* result = (quads_exp != 0 ? quads_exp : new std::list<GuavaQuads*>());
    GuavaQuads* operacion;
    GuavaQuads* comentario;

    if (tipo_inst < 2){
        operacion = new GuavaQuadsExp("-",identificador->addr, new Symbol("1"), identificador->addr);
        result->push_back(operacion);
        comentario = new GuavaComment("DECREMENTO",line,column);
        result->push_front(comentario);
    } else {
        operacion = new GuavaQuadsExp("+",identificador->addr, new Symbol("1"), identificador->addr);
        result->push_back(operacion);
        comentario = new GuavaComment("INCREMENTO",line,column);
        result->push_front(comentario);
    }

    return result;
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

std::list<GuavaQuads*>* LlamadaFuncion::generar_quads(){
    addr = temp->newtemp();
    std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>();

    for (std::list<Exp*>::iterator it = lvarovalor->begin(); it != lvarovalor->end(); ++it){
        Exp* expresion = *it;
        std::list<GuavaQuads*> * code = expresion->generar_quads();
        if (code != 0 ) result->splice(result->end(),*code);
    }

    for (std::list<Exp*>::iterator it = lvarovalor->begin(); it != lvarovalor->end(); ++it){
        Exp* expresion = *it;
        GuavaParam* param = new GuavaParam(expresion->addr);
        result->push_back(param);
    }
    std::ostringstream convert; 
    convert << lvarovalor->size();
    GuavaQuads* call = new GuavaCall(id->identificador,new Symbol(convert.str()),addr);
    result->push_back(call);
    GuavaQuads* comentario = new GuavaComment("LLAMADA FUNCION",line,column);
    result->push_front(comentario);
    return result;
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

/* class ExpID  */


/**
 * Realiza una revision sencilla de exp_id e inicializa result
 * @param id Simbolo buscado en la tabla de simbolos
 * @param identificador Identificador
 * @param result Resultado que se desea inicializar
 * @param line Linea
 * @param column Columna
 * @param obtener_tipo_simbolo Apuntador a funcion que obtiene un simbolo y retorna un TypeS*
 * @return msg Mensaje de error.
 */
std::string ExpID::revision_exp_id(Symbol* id,Identificador* identificador,ExpID* result, int line, int column, TypeS* (*obtener_tipo_simbolo)(Symbol*)){
    std::string msg ("");
    TypeS* tipo;
    if (id == 0){
        result = new ExpID();
        result->set_line_column(line,column);
        return msg;
    }
    if((tipo = obtener_tipo_simbolo(id)) != 0) {
        result = new ExpID(identificador);
        result->tipo = tipo;
        result->set_line_column(line,column);
        
        //Asigno una nueva tabla a ExpID
        if (tipo->is_structure()){
           TypeStructure* structure = (TypeStructure *) tipo; 
           result->tabla = structure->get_tabla(); 
        }

    }
    else {
        std::string msg ("Type has not been declared or doesn't exists in current context");
        result = new ExpID();
        result->set_line_column(line,column);
    }
    result->offset = id->offset; 
    return msg;
}

/**
 * Revision de expresiones id de tipo arreglo
 * @param id Simbolo de la variable a revisar. Esta sale de la Tabla de simbolos.
 * @param identificador Identificador de la variable
 * @param newtemp Clase que se utiliza para generar los temporales
 * @param lce Lista de expresiones de corchete
 * @oaram result Resultado. Esta variable sera inicializada o modificada.
 * @param line Linea
 * @param column Columna
 * @param obtener_tipo_simbolo Funcion que dado un simbolo retorna un tipo
 * @param mensaje_error_tipos Funcion que dado dos nombres de tipo retorna un mensaje de error.
 * @return msg Retorna un string que contiene un mensaje de error para imprimir luego por pantalla.
 */
std::string ExpID::revision_exp_id_arreglo(Symbol* id ,Identificador* identificador, NewTemp* newtemp,
                                            LCorchetesExp* lce,ExpID* result,int line, int column,
                                            TypeS* (*obtener_tipo_simbolo)(Symbol*),std::string (*mensaje_error_tipos)(std::string,std::string)){

    TypeS* tipo = obtener_tipo_simbolo(id);
    std::string msg ("");

    if (tipo != 0){
        result = new ExpID(identificador, lce);
        result->set_line_column(line,column);

        if (lce->get_tipo() == TypeInt::Instance() &&
            tipo->is_array()) {
            //Se asigna el tipo del arreglo a la variable.
            result->tipo = tipo->get_tipo();
            //Asigno una nueva tabla a ExpID
            if (result->tipo->is_structure()){
                TypeStructure* structure = (TypeStructure*) result->tipo;
                result->tabla = structure->get_tabla();
            }
        }

        //Caso en el que el identificador NO es un arreglo
                                            
        else if (!tipo->is_array()){
            std::string msg = mensaje_error_tipos("array",tipo->get_name());
            result->tipo = TypeError::Instance();
            return msg;
        }
        //Caso en el que la estructura del arreglo no es de tipo integer
        else {
            result->tipo = TypeError::Instance();
        }
    }
    result->temp = newtemp;
    return msg;
}

bool ExpID::operator==(ExpID id){
    bool result_recursivo;
    if (exp_id != 0 && id.exp_id != 0) result_recursivo = (exp_id == id.exp_id);
    if ((exp_id == 0 && id.exp_id != 0) || (exp_id != 0 && id.exp_id == 0)) return false;
    return ( result_recursivo && (identificador == id.identificador) && (lcorchetesexp == id.lcorchetesexp));
}


/* Class ExpIdentificador */

ExpIdentificador::ExpIdentificador(Identificador* id):ExpID(id){}

ExpIdentificador::ExpIdentificador(ExpID* exp_,Identificador* id): ExpID(exp_,id){}

std::list<GuavaQuads*>* ExpIdentificador::generar_quads(){
    std::list<GuavaQuads*>* result = new std::list<GuavaQuads*>();
    //SE VERIFICA SI LA EXPRESION PADRE ES UN ARREGLO, EN TAL CASO SE CALCULAN SUS QUADS
    if(exp_id != 0)
        result = exp_id->generar_quads();
    //Caso en que el padre es una arreglo de estructuras.
    if(exp_id != 0 && exp_id->is_array()) {
        Symbol* est_padre = exp_id->addr;
        //Se suma el desplazamiento del arreglo la base del atributo
        Symbol* base_atr = new Symbol(offset);
        Symbol* t1 = temp->newtemp();
        Symbol* t2 = temp->newtemp();
        GuavaQuadsExp* nuevo_q = new GuavaQuadsExp("+",est_padre->desp,base_atr,t1);
        result->push_back(nuevo_q);
        nuevo_q = new GuavaQuadsExp("[]",addr,t1,t2);
        result->push_back(nuevo_q);
        addr->desp = t1;
        addr->elem = t2;
    }
    //Caso en que el padre es una estructura.
    else if(exp_id != 0 && !exp_id->is_array()) {
        /*El calculo de offset para estructuras solo se realizara si se trata
         *de una variable global. El calculo de offset esta predeterminado en
         *las variables locales.
         */
        if(addr->sym_name.compare(std::string("bp")) != 0)
            addr->offset += exp_id->addr->offset;
        Symbol* est_padre = exp_id->addr;
        addr->desp = est_padre->desp;
        addr->elem = est_padre->elem;
    }
    else {
        addr->desp = 0;
        addr->elem = 0;
        GuavaQuads* comentario = new GuavaComment("EXP IDENTIFICADOR",line,column);
        result->push_front(comentario);
    }
    return result;
}

/* Class ExpIDLCorchetes */

ExpIDLCorchetes::ExpIDLCorchetes(Identificador* id, LCorchetesExp* lce ): ExpID(id,lce){}

ExpIDLCorchetes::ExpIDLCorchetes(ExpID* exp_,Identificador* id, LCorchetesExp* lce): ExpID(exp_,id,lce){}
