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
 * Constructor de la clase.
 * @param g GuavaGenerator para poder escribir en el archivo.
 * @param tabla Tabla de simbolos
 * @param vars_ Descriptores de variable.
 * @param regs_ Descriptores de registros.
 * @param floats Descriptores de registros para floats.
 *
 * En este constructor tambien se generan los get_reg.
 */
GuavaTemplates::GuavaTemplates(GuavaGenerator* g, GuavaSymTable* tabla, GuavaDescTable* vars_, GuavaDescTable* regs_, GuavaDescTable* floats):
                                generador(g),table(tabla),vars(vars_),regs(regs_), regs_float(floats){
    
    RegisterAllocator* nuevo_get_reg =  new RegisterAllocator(regs,vars,generador,this);
    RegisterAllocator* nuevo_get_reg_float = new RegisterAllocator(regs_float,vars,generador,this);
    get_reg = nuevo_get_reg;
    get_reg_float = nuevo_get_reg_float;
}

/** 
 * Set descriptor de registros.
 * Cada vez que cambia el GuavaTemplates, tambien cambia el RegisterAllocator.
 */
void GuavaTemplates::set_regs(GuavaDescTable* r){
    regs = r;
    RegisterAllocator *nuevo_get_reg = new RegisterAllocator(regs,vars,generador,this);
    get_reg = nuevo_get_reg;
}

/** 
 * Set descriptor de variables.
 * Cada vez que cambia el GuavaTemplates, tambien cambia el RegisterAllocator.
 */
void GuavaTemplates::set_vars(GuavaDescTable* v){
    vars = v;
    RegisterAllocator *nuevo_get_reg = new RegisterAllocator(regs,vars,generador,this);
    RegisterAllocator *nuevo_get_reg_float = new RegisterAllocator(regs_float,vars,generador,this);
    get_reg = nuevo_get_reg;
    get_reg_float = nuevo_get_reg_float; 
}

void GuavaTemplates::set_vars(list<SimpleSymbol*> simbolos){
    if (vars != 0) delete vars;
    vars = new GuavaDescTable(simbolos);
    RegisterAllocator* nuevo_get_reg = new RegisterAllocator(regs,vars,generador,this);
    RegisterAllocator *nuevo_get_reg_float = new RegisterAllocator(regs_float,vars,generador,this);
    get_reg = nuevo_get_reg;
    get_reg_float = nuevo_get_reg_float;
}

/** 
 * Retorna el asignador de registros para registros
 * normales
 * @return get_reg
 */
RegisterAllocator* GuavaTemplates::get_reg_alloc(){
    return get_reg;
}

RegisterAllocator* GuavaTemplates::get_reg_float_alloc(){
    return get_reg_float;
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
 * Agrega una variable en la pila.
 * Lo que voy a hacer es agregar espacio en la pila del tamaño de la variable
 * @param var Simbolo variable.
 */
void MIPS::push(Symbol* var){
    ostringstream convert;
    ostringstream convert_2;
    convert << var->width;
    offset_actual += var->width;
    *generador << "subu $sp, $sp, " + convert.str() + "\n"; 
    if ((*vars)[var->sym_name] != 0){
        GuavaDescriptor* desc_var = (*vars)[var->sym_name];
        convert_2 << offset_actual;
        SimpleSymbol* lugar = new SimpleSymbol(convert_2.str()+"($sp)");
        desc_var->set_symbol(lugar);
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
    *generador << "_aviso_div: .asciiz \"Div by 0 exception\"\n";
    for (list<Symbol*>::iterator it = globals.begin(); it != globals.end(); ++it){
        (*it)->generar_mips(generador); 
    }  
    *generador << ".text\n";
    list<Symbol*> lista_push = table->obtain_symbols(table->currentScope());

    for (list<Symbol*>::iterator it = lista_push.begin(); it != lista_push.end(); ++it){
       this->push(*it); 
    }

}

/** 
 * Para el mips hace la llamada al sistema numero 10 (exit).
 */
void MIPS::exit_main(){
    *generador << "li $v0, 10\n";
    *generador << "syscall\n";
    table->exitScope();
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

/** 
 * Hace li, lw o la
 */
void MIPS::load(GuavaDescriptor* reg, SimpleSymbol* tmp){
    if (reg->find_by_name(tmp->sym_name) != 0) return; //La variable ya se encuentra en el descriptor
    Symbol* var = (Symbol*) tmp;

    if (table->lookup(var->sym_name) == 0){
        //Caso constante.
        if (var->get_tipo() != TypeReal::Instance()){
            *generador << "li " + reg->get_nombre() + ", " + var->nombre_mips() + " #LOAD \n"; 
            regs->manage_LD(reg->get_nombre(),var);
            vars->manage_LD(reg->get_nombre(),var);
        }else {
            *generador << "li " + reg->get_nombre() + ", " + var->nombre_mips() + " #LOAD \n"; 
            regs_float->manage_LD(reg->get_nombre(),var);
            vars->manage_LD(reg->get_nombre(),var);
        }
    }else{
        //Caso variable
        *generador << "lw " + reg->get_nombre() + ", " + var->nombre_mips() + " #LOAD WORD \n";
        regs->manage_LD(reg->get_nombre(),var);
        regs_float->manage_LD(reg->get_nombre(),var);
        vars->manage_LD(reg->get_nombre(),var);
    }
}

/** 
 * Hace la revisión de que no puede existir division por cero.
 * @param Rz Descriptor del registro para z
 */
void MIPS::revision_div(GuavaDescriptor* Rz){
    ostringstream convert;
    convert << div_;
    div_++;
    *generador << "bneqz " + Rz->get_nombre() + " _label_div" + convert.str() + "\n ";
    *generador << "j _div_exception \n";
    *generador << "_label_div" + convert.str() + ": "; 
}

/**
 * Genera codigo para UFO, dependiendo del resultado de Rx.
 *  Esto es:
 *      Ry > Rz => Rx > 0 => Rx := 1
 *      Ry < Rz => Rx < 0 => Rx := -1
 *      Ry = Rz => Rx = 0 => Rx := 0
 *
 * @param Rx Descriptor del registro para x
 */
void MIPS::generar_ufo(GuavaDescriptor* Rx){
    ostringstream convert;
    convert << ufo;
    ufo++;
    *generador << "bgtz " + Rx->get_nombre() + " , _ufo_gtz"+convert.str() +"#>0 \n";
    *generador << "bltz " + Rx->get_nombre() + " , _ufo_ltz"+convert.str() +"#<0 \n";
    *generador << "beqz " + Rx->get_nombre() + ", _ufo_eqz" + convert.str() + "#=0\n";
    *generador << "_ufo_gtz" + convert.str() + ": ";
    *generador << "li " + Rx->get_nombre() + ", 1 \n";
    *generador << "j _ufo_final" + convert.str();
    *generador << "_ufo_ltz" + convert.str() + ": ";
    *generador << "li " + Rx->get_nombre() + ", -1 \n";
    *generador << "j _ufo_final" + convert.str();
    *generador << "_ufo_eqz" + convert.str() + ": \n";
    *generador << "j _ufo_final" + convert.str() + ": ";
}

/** 
 * Realiza una operacion unaria.
 * @param Rx Descriptor del registro para x
 * @param Ry Descriptor del registro para y
 * @param inst Isntruccion.
 */
void MIPS::operacion_unaria(GuavaDescriptor* Rx, GuavaDescriptor* Ry, GuavaQuadsExp* inst){
    if (inst->get_op().compare(string(":=")) == 0){
        this->load(Rx,inst->get_result());
    } else if (inst->get_op().compare(string("-")) == 0){
        *generador << "neg " + Rx->get_nombre() +", "+ Ry->get_nombre() + "#UMINUS \n";
    } else if (inst->get_op().compare("pincrease") == 0){
        *generador << "addi "+ Rx->get_nombre() + ", " + Ry->get_nombre() + " , 1 #PINCREASE\n";
    } else if (inst->get_op().compare("pdecrease") == 0){
        *generador << "addi "+ Rx->get_nombre() + ", " + Ry->get_nombre() + " , -1 #PDECREASE\n";
    }
}

/** 
 * Realiza una operacion ternaria.
 */
void MIPS::operacion_ternaria(GuavaDescriptor* Rx, GuavaDescriptor* Ry, GuavaDescriptor* Rz, GuavaQuadsExp* inst){
    // Operaciones Aritmeticas.
    if (inst->get_op().compare(string("+")) == 0){
        *generador << "add "+ Rx->get_nombre() + ", "+ Ry->get_nombre() + "," + Rz->get_nombre() + " #ADD\n";
    }else if (inst->get_op().compare(string("-")) == 0){
        *generador << "neg " + Rz->get_nombre() + ", " + Rz->get_nombre() + " #SUB\n";
        *generador << "add "+ Rx->get_nombre() + ", "+ Ry->get_nombre() + "," + Rz->get_nombre() + "\n";
        *generador << "neg " + Rz->get_nombre() + ", " + Rz->get_nombre() + "\n";
    }else if (inst->get_op().compare(string("*"))){
        *generador << "mul " + Rx->get_nombre() + ", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "\n #MUL\n";
    } else if (inst->get_op().compare(string("/")) == 0){
        this->revision_div(Rz); 
        *generador << "div " + Rx->get_nombre() + ", " + Ry->get_nombre() + ", "+ Rz->get_nombre() + "\n # /";
    }else if (inst->get_op().compare(string("DIV")) == 0){
        this->revision_div(Rz); 
        *generador << "div " + Ry->get_nombre()+ ", " + Rz->get_nombre() +" # DIV\n";
        *generador << "move "+ Rx->get_nombre() + ",  $lo \n";
    } else if (inst->get_op().compare(string("MOD")) == 0){
        this->revision_div(Rz);
        *generador << "div " + Ry->get_nombre()+ ", " + Rz->get_nombre() +" # DIV\n";
        *generador << "move "+ Rx->get_nombre() + ",  $hi \n";
    }else if (inst->get_op().compare(string("**"))){
        *generador << "#POW TODAVIA NO\n";
    }else if (inst->get_op().compare(string("<=>"))){
        *generador << "neg " + Rz->get_nombre() + ", " + Rz->get_nombre() + " #UFO\n";
        *generador << "add "+ Rx->get_nombre() + ", "+ Ry->get_nombre() + "," + Rz->get_nombre() + "\n";
        *generador << "neg " + Rz->get_nombre() + ", " + Rz->get_nombre() + "\n";
        this->generar_ufo(Rx);
    }
    // Operaciones de comparacion
    else if (inst->get_op().compare(string(">"))){
        *generador << "sgt " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Ry->get_nombre() + "# y > z \n";
    } else if (inst->get_op().compare(string("<"))){
        *generador << "slt " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Ry->get_nombre() + "# y < z \n";
    } else if (inst->get_op().compare(string("="))){
        *generador << "seq " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Ry->get_nombre() + "# y = z \n";
    } else if (inst->get_op().compare(string("!="))){
        *generador << "sne " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Ry->get_nombre() + "# y != z \n";
    } else if (inst->get_op().compare(string(">="))){
        *generador << "sge " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Ry->get_nombre() + "# y >= z \n";
    } else if (inst->get_op().compare(string("<="))){
        *generador << "sle " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Ry->get_nombre() + "# y <= z \n";
    }
}

/** 
 * Genera codigo para una operacion de tipo x := y + z
 * siendo '+' cualquier operador.
 */
void MIPS::operacion(list<GuavaDescriptor*> lregs, GuavaQuadsExp * instruccion){
    if (lregs.size() == 3){
        GuavaDescriptor* Ry = lregs.back();
        GuavaDescriptor* Rx = lregs.front();
        lregs.pop_front();
        GuavaDescriptor* Rz = lregs.front();
        this->operacion_ternaria(Rx, Ry, Rz, instruccion);
        regs->manage_OP(Rx->get_nombre(), instruccion->get_result());
        regs_float->manage_OP(Rx->get_nombre(), instruccion->get_result());
        vars->manage_OP(Rx->get_nombre(), instruccion->get_result());
    }else if (lregs.size() == 2){
        GuavaDescriptor* Ry = lregs.back();
        GuavaDescriptor* Rx = lregs.front();
        this->operacion_unaria(Rx,Ry, instruccion);
        regs->manage_OP(Rx->get_nombre(), instruccion->get_result());
        regs_float->manage_OP(Rx->get_nombre(), instruccion->get_result());
        vars->manage_OP(Rx->get_nombre(), instruccion->get_result());
    }
}
