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
 * Constructor de GuavaQuads.
 * Se asigna a cada quads un id unico de instruccion
 */
GuavaQuads::GuavaQuads(std::string op_): op(op_){
    id_quad = id_instruccion; //Este valor es unico.
    id_instruccion += 50; // Voy sumando de 50 en 50.
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

void GuavaParam::attach_info(){
    if (addr != 0){
       this->insert_vivas(addr);     
       this->insert_usos(addr);     
    }

/**
 * Funcion que verifica si un elemento del Quad es una estructura y, de serlo,
 * convierte su direccion en la base de la misma.
 */
std::string generar_base_estructura(Symbol* s) {
    std::string base = s->sym_name;
    if (s->true_type != 0 && (s->true_type->is_structure() || s->true_type->is_union())) {
        base += "[" + std::to_string(s->offset) + "]";
    }
    return base;
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
            code += result->sym_name + "[" + std::to_string(result->offset) + "]" + op
                    + arg1->sym_name + "[" + std::to_string(arg1->offset) + "]";
        }
        //Caso arg1 global
        else {
            //Se verifica la base de arg1 (verificacion de tipo estructura)
            base_arg1 = generar_base_estructura(arg1);
            code += result->sym_name + "[" + std::to_string(result->offset) + "]" + op
                    + base_arg1;
        }
    }
    //Caso arg1 local
    else if (arg1->sym_name.compare(std::string("bp")) == 0) {
        //Se verifica la base de result (verificacion de tipo estructura)
        base_res = generar_base_estructura(result);
        code += base_res + op + arg1->sym_name + "["
                + std::to_string(arg1->offset) + "]";
    }
    //Caso ambos globales
    else {
        //Se verifica la base de arg1 y result (verificacion de tipo estructura)
        base_arg1 = generar_base_estructura(arg1);
        base_res = generar_base_estructura(result);
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
    std::string code ("");
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
