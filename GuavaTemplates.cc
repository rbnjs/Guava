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
 * @param g Generator para poder escribir en el archivo.
 * @param tabla Tabla de simbolos
 * @param vars_ Descriptores de variable.
 * @param regs_ Descriptores de registros.
 */
GuavaTemplates::GuavaTemplates(Generator* g, GuavaSymTable* tabla, GuavaDescriptor* vars_, GuavaDescriptor* regs_):
    gen(g),table(tabla),vars(vars_),regs(regs_){}

/** 
 * Set descriptor de registros.
 */
void GuavaTemplates::set_regs(GuavaDescriptor* r){
    regs = r;
}

/** 
 * Set descriptor de variables.
 */
void GuavaTemplates::set_vars(GuavaDescriptor* v){
    vars = v;
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
            *gen << ("sw "+ var->sym_name+ ", "+ reg->get_nombre() + "\n");
        } else if (!s->is_array()) {
            convert << s->offset;
            *gen << ("sw "+ convert.str() + "($sp) , "+ reg->get_nombre() + "\n" );
        }else{
            //Caso arreglo.
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
 * Guarda un valor en la pila. 
 * @param reg Descriptor del registro en donde se encuentra el conjunto de variables.
 */
void MIPS::push(GuavaDescriptor* reg){
    *gen << ("sw "+ reg->get_nombre() + ", 0($sp)\n");  
    *gen << "subu $sp, $sp, 4 \n";
}
