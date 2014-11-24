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
#include "Types.hh"
#include <ostream>

using namespace std;


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

void GuavaTemplates::set_vars(list<SimpleSymbol*> simbolos){
    if (vars != 0) delete vars;
    vars = new GuavaDescTable(simbolos);
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
            *generador << ("sw "+ s->sym_name+ ", "+ reg->get_nombre() + "\n");
        } else if (!s->is_array()) {
            convert << s->offset;
            vars->manage_store(s->sym_name);
            *generador << ("sw "+ convert.str() + "($sp) , "+ reg->get_nombre() + "\n" );
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
    *generador << ("sw "+ reg->get_nombre() + ", 0($sp)\n");  
    *generador << "subu $sp, $sp, 4 \n";
    SymbolReg* pila = lugar_pila(offset_actual);
    reg->insert(pila);
    offset_actual = offset_actual + 4;
    if (reg->is_reg()){
        regs->manage_push(reg->get_nombre(),pila);
        regs_float->manage_push(reg->get_nombre(), pila);
    }else{
        vars->manage_push(reg->get_nombre(),pila);
    }
}

/** 
 * Genera codigo para el entry de un main.
 * Hay ciertas cosas que hay que considerar:
 *   1) Estoy usando _character para imprimir los caracteres en MIPS.
 *      Este solo usa 1 byte de todas formas.
 */
void MIPS::entry_main(){
    list<Symbol*> globals = table->obtain_globals();
    *generador << ".data\n";
    *generador << "_character: .space 4\n";
    for (list<Symbol*>::iterator it = globals.begin(); it != globals.end(); ++it){
        (*it)->generar_mips(generador); 
    }
    *generador << ".text\n";
}

/** 
 * Para el mips hace la llamada al sistema numero 10 (exit).
 */
void MIPS::exit_main(){
    *generador << "li $v0, 10\n";
    *generador << "syscall\n";
}

/** 
 * Escribe un label en el archivo.
 */
void MIPS::label(string label){
    *generador << label + ": \n";
}

/** 
 * Escribe un jump hacia la dirección de to
 * @param to Dirección adonde hay que saltar
 */
void MIPS::go_to(Symbol* to){
    *generador << "j " + to->sym_name + "\n";
}

/** 
 * Lee y coloca en result dependiendo del tipo
 * que contiene result. Por ahora solo lee enteros
 * y flotantes.
 *
 * @param reg Registro para colocar la lectura
 * @param result Donde se guardara el valor del reg
 */
void MIPS::read(GuavaDescriptor* reg,Symbol* result){
    if (result->get_tipo() == TypeInt::Instance() 
        ){
        *generador << "li $v0, 5 # READ_INT\n";
        *generador << "syscall\n";
        this->move(reg,"$v0",result);
    }else if (result->get_tipo() == TypeReal::Instance()) {
        *generador << "li $v0, 6 # READ_FLOAT";
        *generador << "syscall\n";
        this->move(reg,"$v0",result);
    }else if (result->get_tipo() == TypeChar::Instance()){
        *generador << "li $v0, 5 #READ_CHAR\n";
        *generador << "syscall\n";
        this->move(reg,"$v0",result);
    } else if (result->get_tipo() == TypeBool::Instance()){
        *generador << "li $v0, 5 #READ_BOOL\n";
        *generador << "syscall\n";
        this->move(reg,"$f0",result);
    }

}

/** 
 * Imprime en pantalla.
 * @param arg Argumento que se quiere imprimir.
 */
void MIPS::print(Symbol* arg){
    if (arg->get_tipo() == TypeString::Instance()){
        *generador << "la $a0, " + arg->sym_name + " #PRINT STRING\n";
        *generador << "li $v0, 4 \n";
        *generador << "syscall\n";
    }else if (arg->get_tipo() == TypeInt::Instance()){
        *generador << "li $a0, " + arg->sym_name + " #PRINT_INT\n";
        *generador << "li $v0, 1\n";
        *generador << "syscall\n";
    }else if (arg->get_tipo() == TypeReal::Instance()){
        *generador << "li $f12, "+ arg->sym_name + " #PRINT_FLOAT\n";
        *generador << "li $v0, 6 \n";
        *generador << "syscall\n";
    }else if (arg->get_tipo() == TypeChar::Instance()){
        *generador << "li $a0, " + arg->sym_name + " #PRINT CHAR\n";
        *generador << "sw $a0,  _character\n";
        *generador << "la $a0,  _character\n";
        *generador << "li $v0, 4 \n";
        *generador << "syscall\n";
    }
}

/** 
 * Imprime en pantalla un registro.
 * @param reg Registro en donde se encuentra lo que se quiere imprimir.
 */
void MIPS::print(GuavaDescriptor* reg){
    if (reg->get_tipo() == TypeString::Instance()){
        *generador << "move $a0, " + reg->get_nombre() + " #PRINT STRING\n";
        *generador << "li $v0, 4 \n";
        *generador << "syscall\n";
    }else if (reg->get_tipo() == TypeInt::Instance()){
        *generador << "move $a0, " + reg->get_nombre() + " #PRINT_INT\n";
        *generador << "li $v0, 1\n";
        *generador << "syscall\n";
    }else if (reg->get_tipo() == TypeReal::Instance()){
        *generador << "move $f12, "+ reg->get_nombre() + " #PRINT_FLOAT\n";
        *generador << "li $v0, 6 \n";
        *generador << "syscall\n";
    } else{
        *generador << "move $a0, " + reg->get_nombre() + " #PRINT_ELSE\n";
        *generador << "li $v0, 1\n";
        *generador << "syscall\n";
    }
}

/** 
 * Hace una copia entre dos registros de esta manera:
 *  reg := reg2
 *  
 *  En MIPS esto es move reg , reg2
 *
 *  @param reg Registro destino
 *  @param reg2 Registro fuente
 */
void MIPS::move(GuavaDescriptor* reg, GuavaDescriptor* reg2){
    GuavaDescTable* tabla_modificar;
    if (reg->get_tipo() == TypeReal::Instance() 
        || reg2->get_tipo() == TypeReal::Instance()){
        tabla_modificar = regs_float;
    }else{
        tabla_modificar = regs;
    }
    tabla_modificar->manage_move(reg->get_nombre(),reg2->get_nombre());
    *generador << "move " + reg->get_nombre() + ", " + reg2->get_nombre() + "#COPY\n";
}

/** 
 * Hace una copia del registro reg con el reg_2 de la misma
 * manera que move de dos descriptores pero con la diferencia
 * de que agrega result en el conjunto de variables asociadas de
 * reg y viceversa con result.
 *
 * @param reg Descriptor de registro reg
 * @param reg_2 Nombre del registro fuente que se movera.
 * @result Variable que se insertará en reg.
 */
void MIPS::move(GuavaDescriptor* reg, string reg_2, Symbol* result){
    GuavaDescTable* tabla_modificar;
    if (reg->get_tipo() == TypeReal::Instance() 
        || result->get_tipo() == TypeReal::Instance()){
        tabla_modificar = regs_float;
    }else{
        tabla_modificar = regs;
    }
    tabla_modificar->manage_move(reg->get_nombre(), result);
    *generador << "move " + reg->get_nombre() + ", " + reg_2 + " #COPY\n";
}
