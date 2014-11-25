/*
 * =====================================================================================
 *
 *       Filename:  GuavaQuads.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/09/14 18:32:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  
 *
 * ====================================================================================
 */
#include "GuavaQuads.hh"
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream

int secuencia_label_unico = 0;
int id_instruccion = 0;


std::string to_string(int a){
    std::ostringstream convert;
    convert << a;
    return convert.str();
}

/** 
  * Constructor de GuavaLabel que sirve como
  * un newlabel
  */
GuavaLabel::GuavaLabel(): GuavaQuads("label"){
    std::ostringstream convert;
    convert << secuencia_label_unico;
    secuencia_label_unico++;
    this->set_op("label"+convert.str());
}

/** 
 * Genera codigo mips para el un label de Guava.
 * @param g Generator.
 */
void GuavaLabel::generar_mips(GuavaTemplates* g){
    g->label(this->get_op());
}

/** 
 * Constructor de GuavaQuads.
 * Se asigna a cada quads un id unico de instruccion
 */
GuavaQuads::GuavaQuads(std::string op_): op(op_){
    id_quad = id_instruccion; //Este valor es unico.
    id_instruccion += 50; // Voy sumando de 50 en 50.
}

/** 
 * Retorna -1 si no tiene usos.
 */
int GuavaQuads::uso(SimpleSymbol* s){
    if (usos.count(s) == 0) return -1;
    return usos[s];
}


/** 
 * Agrega informacion con respecto a la vida y uso en la instruccion.
 */
void GuavaQuadsExp::attach_info(){
    if (result != 0){
       this->insert_vivas(result);     
       this->insert_usos(result);     
    }
    if (arg1 != 0){
       this->insert_vivas(arg1);     
       this->insert_usos(arg1);     
    }

    if (arg2 != 0){
       this->insert_vivas(arg2);     
       this->insert_usos(arg2);     
    }
}

/**
 * Nos indica si una expresion es de uso general. Es decir que no sea asignación o arreglo.
 * @return bool true si es una expresion de uso general, false si no.
 */
bool GuavaQuadsExp::is_general_exp(){
    if (this->get_op().compare(std::string("[]")) == 0 || this->get_op().compare(std::string(":=")) == 0)
        return false;
    return true;
}

/** 
 * Retorna una lista con todos los argumentos del Quad
 *
 * Esto es bastante chevere para iterar.
 * @return args Lista de argumentos. El orden es {result, arg1 , arg2}. 
 */
std::list<SimpleSymbol*> GuavaQuadsExp::get_args(){
    std::list<SimpleSymbol*> args;
    if (result != 0){
        args.push_back(result);
    }
    if (arg1 != 0){
        args.push_back(arg1);
    }

    if (arg2 != 0){
        args.push_back(arg2);
    }   
    return args;
}


/** 
 * Retorna una lista con todos los argumentos del QuadIf
 *
 * @return args Lista de argumentos. El orden es {arg1 , arg2} para hacer las comparaciones. 
 */
std::list<SimpleSymbol*> GuavaQuadsIf::get_args(){
    std::list<SimpleSymbol*> args;

    if (arg1 != 0){
        args.push_back(arg1);
    }

    if (arg2 != 0){
        args.push_back(arg2);
    }
    return args;
}

/**
 * Genera mips para expresiones condicionales.
 */
void GuavaQuadsIf::generar_mips(GuavaTemplates* gen){
    RegisterAllocator* get_reg;
    if (this->get_result()->get_tipo() != TypeReal::Instance()){
       get_reg = gen->get_reg_alloc(); 
    }else{
       get_reg = gen->get_reg_float_alloc(); 
    }
    list<GuavaDescriptor*> registros = get_reg->getReg(this);
    gen->condicional(registros, this);
}

/** 
 * Retorna una lista con todos los argumentos del QuadIf
 *
 * @return args Lista de argumentos. El orden es {arg1 , arg2} para hacer las comparaciones. 
 */
std::list<SimpleSymbol*> GuavaQuadsIfNot::get_args(){
    std::list<SimpleSymbol*> args;

    if (arg1 != 0){
        args.push_back(arg1);
    }

    if (arg2 != 0){
        args.push_back(arg2);
    }
    return args;
}

void GuavaQuadsIfNot::generar_mips(GuavaTemplates* gen){
    RegisterAllocator* get_reg;
    if (this->get_result()->get_tipo() != TypeReal::Instance()){
       get_reg = gen->get_reg_alloc(); 
    }else{
       get_reg = gen->get_reg_float_alloc(); 
    }
    list<GuavaDescriptor*> registros = get_reg->getReg(this);
    gen->condicional_not(registros, this);
}
 
/** 
 * Actualiza la informacion de uso para los simbolos que se encuentran
 * dentro del quad.
 * 
 * El orden en el que se esta haciendo la actualizacion es particularmente
 * importante ya que la variable en donde se guardan los resultados puede usarse
 * nuevamente tipo x := x + 2
 */
void GuavaQuadsExp::update_use(){
    if (result != 0){
        result->kill(); // Mato la variable a la que se va a guardar primero.
    }
    if (arg1 != 0){
       arg1->update_use(this->get_id());
    }

    if (arg2 != 0){
       arg2->update_use(this->get_id());
    }
}
/** 
 * El uso de parametros tambien modifica la información de proximo uso.
 */
void GuavaParam::update_use(){
    if (addr != 0) addr->update_use(this->get_id());
}

void GuavaParam::generar_mips(GuavaTemplates* gen){
    RegisterAllocator* get_reg;
    if (this->addr->get_tipo() != TypeReal::Instance()){
       get_reg = gen->get_reg_alloc(); 
    }else{
       get_reg = gen->get_reg_float_alloc(); 
    }
    list<GuavaDescriptor*> registros = get_reg->getReg(this);   
    gen->push(registros.front());
}

/** 
 * Inserta información en el quad.
 */
void GuavaParam::attach_info(){
    if (addr != 0){
       this->insert_vivas(addr);     
       this->insert_usos(addr);     
    }
}

void GuavaCall::generar_mips(GuavaTemplates* t){
    t->gen_call(this);
}


/**
 * Genera mips para el GoTo de Guava.
 * @param g Generador de codigo en templates.
 */
void GuavaGoTo::generar_mips(GuavaTemplates* g){
    g->go_to(go_to);
}


/** 
 * Genera mips para entrada o salida.
 */
void GuavaEntradaSalida::generar_mips(GuavaTemplates* t){
    if (this->get_op().compare("read") == 0){
        RegisterAllocator* get_reg;
        if (this->get_result()->get_tipo() != TypeReal::Instance()){
           get_reg = t->get_reg_alloc(); 
        }else{
           get_reg = t->get_reg_float_alloc(); 
        }
        list<GuavaDescriptor*> registros = get_reg->getReg(this);
        t->read(registros.front(), this->get_result());
    }else{
        t->print(this->get_arg1());
    }
}

void GuavaQuadsReturn::generar_mips(GuavaTemplates* t){
    RegisterAllocator* get_reg;
    if (this->get_result() != 0 && this->get_arg1() != 0){
    if (this->get_result()->get_tipo() != TypeReal::Instance()){
       get_reg = t->get_reg_alloc(); 
    }else{
       get_reg = t->get_reg_float_alloc(); 
    }
    
    list<GuavaDescriptor*> registros = get_reg->getReg(this);   
    t->return_t(registros.front(), this);
    }
    else {
        t->return_t(0,this);
    }
}

/**
 * Funcion que verifica si un elemento del Quad es una estructura y, de serlo,
 * convierte su direccion en la base de la misma.
 */
std::string generar_base_estructura(Symbol* s){
    std::string base = s->sym_name;
    std::string desplazamiento = "";

    if (s->true_type != 0 && (s->true_type->is_structure() || s->true_type->is_union())) {
        //Se verifica si se posee algun arreglo dentro del simbolo
        if(s->desp != 0)
            desplazamiento = s->desp->sym_name;
        else
            desplazamiento = std::to_string(s->offset);

        base += "[" + desplazamiento + "]";
    }

    return base;
}

/**
 * Funcion que verifica si el resultado de una expresion (el l-value) es un
 * elemento de arreglo. En caso de serlo, se asigna el desplazamiento
 * correspondiente al arreglo.
 */
std::string generar_desplazamiento_arreglo(Symbol* s, std::string alcance) {
    std::string base = "";
    std::string desplazamiento = "";

    //Caso en el que el l-value es arreglo
    if(s->sym_catg.compare(std::string("array")) == 0) {
        /* Para este caso no hay necesidad de verificar si el arreglo es una
         * estructura, puesto que el generador de quads se encargara de eso.
         */
        base += s->sym_name + "[" + s->desp->sym_name + "]";
    }
    //Caso en el que el l-value no es arreglo
    else {
        if(alcance.compare(std::string("local")) == 0) {
            //Se verifica si se posee algun arreglo dentro del simbolo
            if(s->desp != 0)
                desplazamiento = s->desp->sym_name;
            else
                desplazamiento = std::to_string(s->offset);

            base += s->sym_name + "[" + desplazamiento + "]";
        }
        else
            base = generar_base_estructura(s);
    }

    return base;
        
}

/**
 * Verifica si una variable es local o se trata de un parametro de una funcion.
 */
std::string verificacion_categoria(Symbol* s, std::string alcance) {
    std::string base = "";
    //Caso en el que se supone como variable global
    if(alcance.compare(std::string("global")) == 0) {
        //Caso en el que sea un parametro de funcion
        if(s->sym_catg.compare(std::string("param")) == 0)
            base += "bp[-" + std::to_string(s->offset) + "]";
        //Caso en el que es efectivamente una variable global
        else
            base = generar_base_estructura(s);
    }
    //Caso en el que se supone como variable local
    else {
        
    }
}

/**
 * Para efectos de esta funcion:
 * - arg1 es el r-value.
 * - result es e l-value.
 */
std::string generacionIntermedia_unaria(std::string op, Symbol* arg1, Symbol* result) {
    std::string code = "";
    //Variables que describen la base de los addr en caso de ser estructuras
    std::string base_arg1 = "";
    std::string base_res = "";

    //Caso result local
    if (result->sym_name.compare(std::string("bp")) == 0) {
        //Caso arg1 local
        if (arg1->sym_name.compare(std::string("bp")) == 0) {
            code += generar_desplazamiento_arreglo(result, "local") + op
                    + arg1->sym_name + "[" + std::to_string(arg1->offset) + "]";
        }
        //Caso arg1 global
        else {
            //Se verifica la base de arg1 (verificacion de tipo estructura)
            base_arg1 = generar_base_estructura(arg1);
            code += generar_desplazamiento_arreglo(result, "local") + op
                    + base_arg1;
        }
    }
    //Caso arg1 local
    else if (arg1->sym_name.compare(std::string("bp")) == 0) {
        //Se verifica la base de result (verificacion de tipo estructura)
        base_res = generar_desplazamiento_arreglo(result, "global");
        code += base_res + op + arg1->sym_name + "["
                + std::to_string(arg1->offset) + "]";
    }
    //Caso ambos globales
    else {
        //Se verifica la base de arg1 y result (verificacion de tipo estructura)
        base_arg1 = generar_base_estructura(arg1);
        base_res = generar_desplazamiento_arreglo(result, "global");
        code += base_res + op + base_arg1;
    }

    return code;
}

/**
 * Para efectos de esta funcion:
 * - result es el l-value
 * - arg1 y arg2 son los r-values.
 */
std::string generacionIntermedia_binaria(std::string op, Symbol* arg1, Symbol* arg2, Symbol* result) {
    std::string code = "";
    //Caso result local
    if (result->sym_name.compare(std::string("bp")) == 0) {
        std::string result_local = result->sym_name + "[" + std::to_string(result->offset) + "]";
        //Caso arg1 local y arg2 global
        if ((arg1->sym_name.compare(std::string("bp")) == 0) &&
            (arg2->sym_name.compare(std::string("bp")) != 0)) {
            //Caso arreglos
            if (op.compare(std::string("[]")) == 0) {
                code += result_local + ":=" + arg1->sym_name + "[" + arg2->sym_name + "]";
            }
            else {
                code += result_local + ":=" + arg1->sym_name + "[" + std::to_string(arg1->offset) + "]"
                        + op + arg2->sym_name;
            }
        }
        //Caso arg1 global y arg2 local
        else if ((arg1->sym_name.compare(std::string("bp")) != 0) &&
                 (arg2->sym_name.compare(std::string("bp")) == 0)) {
            code += result_local + ":=" + arg1->sym_name + op
                    + arg2->sym_name + "[" + std::to_string(arg2->offset) + "]"; 
        }
        //Caso arg1 y arg2 locales
        else if ((arg1->sym_name.compare(std::string("bp")) == 0) &&
                 (arg2->sym_name.compare(std::string("bp")) == 0)) {
            code += result_local + ":=" + arg1->sym_name + "[" + std::to_string(arg1->offset) + "]"
                    + op + arg2->sym_name + "[" + std::to_string(arg2->offset) + "]";
        }
        //Caso arg1 y arg2 globales
        else {
            //Caso arreglos
            if (op.compare(std::string("[]")) == 0) {
                code += result_local + ":=" + arg1->sym_name + "[" + arg2->sym_name + "]";
            }
            else {
                code += result_local + ":=" + arg1->sym_name + op + arg2->sym_name;
            }
        }
    }
    //Caso result global
    else {
        //Caso arg1 local y arg2 global
        if ((arg1->sym_name.compare(std::string("bp")) == 0) &&
            (arg2->sym_name.compare(std::string("bp")) != 0)) {
            //Caso arreglos
            if (op.compare(std::string("[]")) == 0) {
                code += result->sym_name + ":=" + arg1->sym_name + "[" + arg2->sym_name + "]";
            }
            else {
                code += result->sym_name + ":=" + arg1->sym_name + "[" + std::to_string(arg1->offset) + "]"
                        + op + arg2->sym_name;
            }
        }
        //Caso arg1 global y arg2 local
        else if ((arg1->sym_name.compare(std::string("bp")) != 0) &&
                 (arg2->sym_name.compare(std::string("bp")) == 0)) {
            code += result->sym_name + ":=" + arg1->sym_name + op
                    + arg2->sym_name + "[" + std::to_string(arg2->offset) + "]"; 
        }
        //Caso arg1 y arg2 locales
        else if ((arg1->sym_name.compare(std::string("bp")) == 0) &&
                 (arg2->sym_name.compare(std::string("bp")) == 0)) {
            code += result->sym_name + ":=" + arg1->sym_name + "[" + std::to_string(arg1->offset) + "]"
                    + op + arg2->sym_name + "[" + std::to_string(arg2->offset) + "]";
        }
        //Caso arg1 y arg2 globales
        else {
            //Caso arreglos
            if (op.compare(std::string("[]")) == 0) {
                code += result->sym_name + ":=" + arg1->sym_name + "[" + arg2->sym_name + "]";
            }
            else {
                code += result->sym_name + ":=" + arg1->sym_name + op + arg2->sym_name;
            }
        }   
    }

    return code;
}


std::string GuavaQuadsExp::gen(){
    std::string code ("");
    //Caso Operaciones Binarias
    if (arg2 != 0){
        code = generacionIntermedia_binaria(this->get_op(),arg1,arg2,result);
    }
    //Caso Operaciones Unarias
    else {
        //Asignacion
        if (this->get_op().compare(std::string(":=")) == 0) {
            code = generacionIntermedia_unaria(std::string(":="),arg1,result);
        }
        // Menos unario
        if (this->get_op().compare(std::string("uminus")) == 0) {
            code = generacionIntermedia_unaria(std::string(":=-"),arg1,result);
        }

        //ESTOS CAPAZ Y SE TENGAN QUE BORRAR

        // Post incremento
        if (this->get_op().compare(std::string("pincrease")) == 0) {
            code += result->sym_name + ":=" + arg1->sym_name + "++";
        }
        // Post decremento
        if (this->get_op().compare(std::string("pdecrease")) == 0) {
            code += result->sym_name + ":=" + arg1->sym_name + "--";
        }
    }
    code += "\n";
    return code;
}

void GuavaQuadsExp::generar_mips(GuavaTemplates* gen){
    RegisterAllocator* get_reg;
    if (this->get_result()->get_tipo() != TypeReal::Instance()){
       get_reg = gen->get_reg_alloc(); 
    }else{
       get_reg = gen->get_reg_float_alloc(); 
    }
    list<GuavaDescriptor*> registros = get_reg->getReg(this);
    gen->operacion(registros, this);
}


/** 
 * Retorna true si la expresion es de tipo real
 *
 * Una expresion es de tipo real si tiene alguno de sus simbolos es real.
 *
 * @return bool
 */
bool GuavaQuadsExp::is_real(){
    bool exp_true_type = (arg1->true_type == TypeReal::Instance() || arg2->true_type == TypeReal::Instance() || 
                         result->true_type == TypeReal::Instance());
    bool exp_symbol_type = ((arg1->type_pointer != 0 && arg1->type_pointer->true_type == TypeReal::Instance())
                            || (arg2->type_pointer != 0 && arg2->type_pointer->true_type == TypeReal::Instance())
                            || (result->type_pointer != 0 && result->type_pointer->true_type == TypeReal::Instance()));
    return (exp_true_type || exp_symbol_type);
}
