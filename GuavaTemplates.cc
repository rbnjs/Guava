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
            *generador << ("sw "+ reg->get_nombre()+ ", "+ s->sym_name + "\n");
        } else if (!s->is_array()) {
            convert << (-s->offset-8); //A partir de -8 es que estan las variables locales.
            vars->manage_store(s->sym_name);
            *generador << ("sw "+ reg->get_nombre() +", " + convert.str() + "($fp) \n" );
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
        SimpleSymbol* lugar = lugar_pila(offset_actual);
        desc_var->set_symbol(lugar);
    }
}

/** 
 * Resta un offset_ determinado a la pila.
 */
void MIPS::push(int offset_){
    offset_actual += offset_;
    ostringstream convert;
    convert << offset_;
    *generador << "sub $sp, $sp, " + convert.str()+ "\n";
}

/** 
 * Este codigo siempre se ejecuta antes
 * de una función.
 */
void MIPS::prologo(){
    *generador << "subu $sp, $sp, 8 \n";
    *generador << "sw $ra, 0($sp) \n";
    *generador << "sw $fp , 4($sp) \n";
    *generador << "add $fp, $sp, 8\n";
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

    this->prologo();
    int resta_ = 0;
    for (list<Symbol*>::iterator it = lista_push.begin(); it != lista_push.end(); ++it){
           resta_ += (*it)->width;
    }
    this->push(resta_);

}

/** 
 * Hace un pop simple en la pila.
 * @param r Registro que se quiere popear.
 */
void MIPS::pop_simple(string r){
    *generador << "addi $sp, $sp, 4 \n"; 
    *generador << "lw " + r + ", 0($sp)\n";    
}
/**
 * Hace un push simple en la pila.
 * @param r Registro que se quiere pushear.
 */
void MIPS::push_simple(string r){
    *generador << "sw "+ r +" , 0($sp)\n";
    *generador << "addi $sp, $sp, 4\n";
}

void MIPS::epilogo(){
    ostringstream convert;
    convert << offset_actual;
    *generador << "addi $sp ,  $sp , " +convert.str() + " #EPILOGUE\n";
    this->pop_simple("$fp");
    this->pop_simple("$ra");
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
        if (!arg->is_global()){
            *generador << "li $a0, " + arg->sym_name + " #PRINT_INT\n";
        } else{
            *generador << "lw $a0, " + arg->sym_name + " #PRINT_INT\n";
        }
        *generador << "li $v0, 1\n";
        *generador << "syscall\n";
    }else if (arg->get_tipo() == TypeReal::Instance()){
        if (!arg->is_global()){
            *generador << "li $f12, " + arg->sym_name + " #PRINT_INT\n";
        } else{
            *generador << "lw $f12, " + arg->sym_name + " #PRINT_INT\n";
        }
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
    
    if (table->lookup(tmp->sym_name) == 0){
        //Caso variable que no esta en la tabla de simbolos.
        if (tmp->is_simple()){
            if (tmp->is_reg()){
                *generador << "lw " + reg->get_nombre() + ", " + tmp->sym_name + "\n";                 
            }else{
                *generador << "li " + reg->get_nombre() + ", " + tmp->sym_name + "\n";
            }
        } else if (tmp->is_bool()){
            if (tmp->is_true()) *generador << "li " + reg->get_nombre() + ", 1 \n";
            else                *generador << "li " + reg->get_nombre() + ", 0 \n";
        }else if (tmp->is_number()){
            *generador << "li " + reg->get_nombre() + ", " + tmp->sym_name + "\n";
        }else if (tmp->is_bp()){
            *generador << "lw " + reg->get_nombre() + ", " + tmp->bp_mips()+ "\n";
        }
    }else{
        //Caso variable se encuentra en la tabla de simbolos.
        Symbol * var = (Symbol*) tmp;
        if (var->is_global()){
            if (var->sym_catg.compare(string("var")) == 0) *generador << "lw "+ reg->get_nombre() + ", " + var->sym_name + "\n";
            else  *generador << "la " + reg->get_nombre() + ", " + var->sym_name + "\n";
        }else{
            if (var->sym_catg.compare(string("var")) == 0) *generador << "lw "+ reg->get_nombre() + ", " + var->bp_mips() + "\n";
            else  *generador << "la " + reg->get_nombre() + ", " + var->bp_mips() + "\n";
        }
    }
    vars->manage_LD(reg->get_nombre(),tmp);
    regs->manage_LD(reg->get_nombre(),tmp);
    regs_float->manage_LD(reg->get_nombre(),tmp);
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
        if (inst->get_result()->is_bp()){
            //Caso []:=
            this->store(inst->get_result(),Rx);
        }else if (inst->get_result()->is_global()){
            this->store(inst->get_result(),Rx);
        }else{
            this->load(Rx,inst->get_result());
        }
    } else if (inst->get_op().compare(string("-")) == 0){
        *generador << "neg " + Rx->get_nombre() +", "+ Ry->get_nombre() + "#UMINUS \n";
    } else if (inst->get_op().compare("pincrease") == 0){
        *generador << "addi "+ Rx->get_nombre() + ", " + Ry->get_nombre() + " , 1 #PINCREASE\n";
    } else if (inst->get_op().compare("pdecrease") == 0){
        *generador << "subu "+ Rx->get_nombre() + ", " + Ry->get_nombre() + " , -1 #PDECREASE\n";
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
        *generador << "sub "+ Rx->get_nombre() + ", "+ Ry->get_nombre() + "," + Rz->get_nombre() + "\n";
    }else if (inst->get_op().compare(string("*")) == 0){
        *generador << "mul " + Rx->get_nombre() + ", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "#MUL\n";
    } else if (inst->get_op().compare(string("/")) == 0){
        this->revision_div(Rz); 
        *generador << "div " + Rx->get_nombre() + ", " + Ry->get_nombre() + ", "+ Rz->get_nombre() + "# / \n";
    }else if (inst->get_op().compare(string("DIV")) == 0){
        this->revision_div(Rz); 
        *generador << "div " + Ry->get_nombre()+ ", " + Rz->get_nombre() +" # DIV\n";
        *generador << "move "+ Rx->get_nombre() + ",  $lo \n";
    } else if (inst->get_op().compare(string("MOD")) == 0){
        this->revision_div(Rz);
        *generador << "div " + Ry->get_nombre()+ ", " + Rz->get_nombre() +" # MOD\n";
        *generador << "move "+ Rx->get_nombre() + ",  $hi \n";
    }else if (inst->get_op().compare(string("**")) == 0){
        *generador << "#POW TODAVIA NO\n";
    }else if (inst->get_op().compare(string("<=>")) == 0){
        *generador << "sub "+ Rx->get_nombre() + ", "+ Ry->get_nombre() + "," + Rz->get_nombre() + "\n";
        this->generar_ufo(Rx);
    }
    // Operaciones de comparacion
    else if (inst->get_op().compare(string(">")) == 0){
        *generador << "sgt " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# y > z \n";
    } else if (inst->get_op().compare(string("<")) == 0){
        *generador << "slt " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# y < z \n";
    } else if (inst->get_op().compare(string("=")) == 0){
        *generador << "seq " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# y = z \n";
    } else if (inst->get_op().compare(string("!=")) == 0){
        *generador << "sne " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# y != z \n";
    } else if (inst->get_op().compare(string(">=")) == 0){
        *generador << "sge " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# y >= z \n";
    } else if (inst->get_op().compare(string("<=")) == 0){
        *generador << "sle " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# y <= z \n";
    }else if (inst->get_op().compare(string("AND")) == 0){
        *generador << "and " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# AND \n";
    }else if (inst->get_op().compare(string("OR")) == 0){
        *generador << "or " + Rx->get_nombre() +", " + Ry->get_nombre() + ", " + Rz->get_nombre() + "# AND \n";
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

/** 
 * Genera codigo para if.
 */
void MIPS::condicional(list<GuavaDescriptor*> lregs, GuavaQuadsExp* instruccion){
    if (lregs.size() == 3){
         GuavaDescriptor* Ry = lregs.back();
        GuavaDescriptor* Rx = lregs.front();
        lregs.pop_front();
        GuavaDescriptor* Rz = lregs.front();
        this->operacion_ternaria(Rx, Ry, Rz, instruccion);
        regs->manage_OP(Rx->get_nombre(), instruccion->get_result());
        regs_float->manage_OP(Rx->get_nombre(), instruccion->get_result());
        vars->manage_OP(Rx->get_nombre(), instruccion->get_result());
        ostringstream convert;
        convert << sec_if;
        sec_if++;
        *generador << "beqz " + Rx->get_nombre() + " _if_lab" + convert.str() + "\n";
        this->go_to(instruccion->get_result());
        *generador << "_if_lab"+convert.str()+": ";
    }else{
        GuavaDescriptor* Rx = lregs.front();
        ostringstream convert;
        convert << sec_if;
        sec_if++;
        *generador << "beqz " + Rx->get_nombre() + " _if_lab" + convert.str() + "\n";
        this->go_to(instruccion->get_result());
        *generador << "_if_lab"+convert.str()+": \n";
    }
}

/** 
 * Genera codigo para if not.
 */
void MIPS::condicional_not(list<GuavaDescriptor*> lregs, GuavaQuadsExp* instruccion){
    if (lregs.size() == 3){
         GuavaDescriptor* Ry = lregs.back();
        GuavaDescriptor* Rx = lregs.front();
        lregs.pop_front();
        GuavaDescriptor* Rz = lregs.front();
        this->operacion_ternaria(Rx, Ry, Rz, instruccion);
        regs->manage_OP(Rx->get_nombre(), instruccion->get_result());
        regs_float->manage_OP(Rx->get_nombre(), instruccion->get_result());
        vars->manage_OP(Rx->get_nombre(), instruccion->get_result());
        ostringstream convert;
        convert << sec_if;
        sec_if++;
        *generador << "bnez " + Rx->get_nombre() + " _if_lab" + convert.str() + "\n";
        this->go_to(instruccion->get_result());
        *generador << "_if_lab"+convert.str()+": ";
    }else{
        GuavaDescriptor* Rx = lregs.front();
        ostringstream convert;
        convert << sec_if;
        sec_if++;
        *generador << "bnez " + Rx->get_nombre() + " _if_lab" + convert.str() + "\n";
        this->go_to(instruccion->get_result());
        *generador << "_if_lab"+convert.str()+": \n";
    }
}

/** 
 * Genera codigo para return
 */
void MIPS::return_t(GuavaDescriptor* desc, GuavaQuadsExp* i){
    if (desc != 0) *generador << "sw " + desc->get_nombre()+ " 4($fp) #RETURN\n";
    this->epilogo();
    //*generador << "jr\n";
}

/** 
 * Llama a una funcion.
 */
void MIPS::gen_call(GuavaQuadsExp* i){
    *generador << "jal " + i->get_op() + "\n"; 
}

