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
 * Funcion que genera codigo a partir de un Quad
 * El generador muestra el codigo de esta manera:
 * resultado := arg1 op arg2 (dos argumentos)
 * resultado := op arg1 (un argumentos)
 */
std::string GuavaQuadsExp::gen(){
    std::string code ("");
    //Caso Operaciones Binarias
    if (arg2 != 0){
        //Acceso a elementos de arreglo, base pointer.
        if (this->get_op().compare(std::string("[]")) == 0) {
            code += result->sym_name + ":=" + arg1->sym_name + "[" + arg2->sym_name + "]";
        }
        else {
            code += result->sym_name + ":=" + arg1->sym_name+ " " + this->get_op() +" "+ arg2->sym_name;
        }
    //Caso Operaciones Unarias
    } else {
        if (this->get_op().compare(std::string(":=")) == 0) {
            code += result->sym_name + ":=" + arg1->sym_name;
        }
        // Menos unario
        if (this->get_op().compare(std::string("uminus")) == 0) {
            code += result->sym_name + ":=-" + arg1->sym_name;
        }
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

}
