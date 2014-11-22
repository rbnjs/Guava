/*
 * =====================================================================================
 *
 *       Filename:  GuavaTemplates.cc
 *
 *    Description:  Templates de Guava para el lenguaje final.
 *
 *        Version:  1.0
 *        Created:  20/11/14 18:39:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *   Organization:  USB
 *
 * =====================================================================================
 */

#include "GuavaTemplates.hh"
#include "Symbol.hh"
#include <ostream>

using namespace std;

/** 
 * Constructor de GuavaTemplates.
 * @param g GuavaGenerator para poder escribir en el archivo.
 * @param tabla Tabla de simbolos
 * @param vars_ Descriptores de variable.
 * @param regs_ Descriptores de registros.
 */
GuavaTemplates::GuavaTemplates(GuavaGenerator* g, GuavaSymTable* tabla, GuavaDescTable* vars_, GuavaDescTable* regs_):
    gen(g),table(tabla),vars(vars_),regs(regs_){}

/** 
 * Set descriptor de registros.
 */
void GuavaTemplates::set_regs(GuavaDescTable* r){
    regs = r;
}

/** 
 * Set descriptor de variables.
 */
void GuavaTemplates::set_vars(GuavaDescTable* v){
    vars = v;
}

/** 
 * @return offset_actual
 */
int GuavaTemplates::get_offset(){
    return offset_actual;
}

/** 
 * Reinicia el offset_actual
 */
void GuavaTemplates::reset_offset(){
    offset_actual = 0;
}

/** 
 * Guarda un valor.
 * @param var Variable a guardar.
 * @param reg Descriptor del registro en donde se encuentra la variable.
 */
void MIPS::store(SimpleSymbol* var, GuavaDescriptor* reg){
    ostringstream convert;
    if (var->is_simple()){
        //
    }else{
        Symbol* s = (Symbol*) var;
        if (s->is_global() && !s->is_array()){
            //Caso variable global.
            vars->manage_store(s->sym_name);
            *gen << ("sw "+ s->sym_name+ ", "+ reg->get_nombre() + "\n");
        } else if (!s->is_array()) {
            convert << s->offset;
            vars->manage_store(s->sym_name);
            *gen << ("sw "+ convert.str() + "($sp) , "+ reg->get_nombre() + "\n" );
        }else{
            //Caso arreglo.
        }
    }
}

/** 
 * Guarda como normalmente haria un store pero se da cuenta cuando 
 * las variables son locales y hace un push.
 * @param reg Descriptor de registros o variables.
 */
void MIPS::store_spill(GuavaDescriptor* reg){
    for (set<SimpleSymbol*>::iterator it = reg->begin(); it != reg->end(); ++it){
        if ((*it)->is_temp()){
            this->push(reg);
        }else{
            this->store(*it,reg);
        }
    }
}

/** 
 * Guarda un conjunto de valores.
 * @param reg Descriptor del registro en donde se encuentra el conjunto de variables.
 */
void MIPS::store(GuavaDescriptor* reg){
    for (set<SimpleSymbol*>::iterator it = reg->begin(); it != reg->end(); ++it){
        MIPS::store(*it,reg);
    }
}

/** 
 * Retorna la direccion de la pila en donde
 * se encuentra la variable o registro.
 */
SymbolReg* lugar_pila(int lugar){
    ostringstream convert;
    convert << lugar;
    SymbolReg* reg;
    reg = new SymbolReg(convert.str() + "($sp)");
    return reg;
}

/** 
 * Guarda un valor en la pila. 
 * @param reg Descriptor del registro en donde se encuentra el conjunto de variables.
 */
void MIPS::push(GuavaDescriptor* reg){
    *gen << ("sw "+ reg->get_nombre() + ", 0($sp)\n");  
    *gen << "subu $sp, $sp, 4 \n";
    SymbolReg* pila = lugar_pila(offset_actual);
    reg->insert(pila);
    offset_actual = offset_actual + 4;
    if (reg->is_reg()){
        regs->manage_push(reg->get_nombre(),pila);
    }else{
        vars->manage_push(reg->get_nombre(),pila);
    }
}
