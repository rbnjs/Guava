/*
 * =====================================================================================
 *
 *       Filename:  GuavaDescriptor.cc
 *
 *    Description:  Implementacion de Generator.
 *
 *        Version:  1.0
 *        Created:  14/11/14 11:13:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo. 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include "GuavaDescriptor.hh"
#include <sstream>
#include <list>
#include <climits>
#include <regex>
#include <iostream>

using namespace std;


/**
 * Nos dice si todas las variables asociadas a un descriptor son globales.
 * @return bool Retorna un booleano.
 */
bool GuavaDescriptor::todas_globales(){
    Symbol* tmp;
    for (set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if ((*it)->is_simple()) {
            return false;
        }
        else{
            tmp = (Symbol*) *it;
            if (tmp->scope != 1) return false;
        }
    }
    return true;
}

/**
 * Nos dice si todas las variables asociadas a un descriptor son globales y locales.
 * @return bool Retorna un booleano.
 */
bool GuavaDescriptor::locales_globales(){
    Symbol* tmp;
    for (set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if ((*it)->is_temp())
            return false;
    }
    return true;
}

/** 
 * Funcion que retorna el numero de variables temporales asociadas
 * a un descriptor.
 * @return int Numero de temporales.
 */
int GuavaDescriptor::count_temp(){
    int count = 0;
    for (set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if ((*it)->is_temp()) ++count;
    }
    return count;
}

/** 
 * Borra todas las variables asociadas a la variable o 
 * al registro.
 */
void GuavaDescriptor::clear(){
    assoc_var.clear();
}


/** 
 * Genera el codigo de finalización de bloque
 * para un descriptor de registros.
 */
void GuavaDescriptor::end_block(GuavaGenerator* g){

    for (set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if ((*it)->is_global()){
            Symbol* tmp = (Symbol*) *it;
            if (tmp->get_tipo() != TypeReal::Instance())
                *g << "sw " + nombre + ", "+ (*it)->get_mips_name() + " \n";
            else *g << "s.s " + nombre + ", " + (*it)->get_mips_name() + " \n";
        }else if ((*it)->is_bp()){
            Symbol* tmp = (Symbol*) *it;
            if (tmp->get_tipo() != TypeReal::Instance())
                *g << "sw " + nombre + ", " + (*it)->bp_mips() + " \n";
            else *g << "s.s " + nombre + ", " + (*it)->bp_mips() + "\n";
        }
    }
}

/** 
 * Imprime las variables asociadas al GuavaDescriptor.
 */
void GuavaDescriptor::print(){
    if (assoc_var.size() != 0){
        cout << "Descriptor:" << nombre; 
        cout << " / Associated Variables: ";
        for (set<SimpleSymbol*>::iterator it = assoc_var.begin() ; it != assoc_var.end(); ++it){
            cout << (*it)->get_mips_name();
            if (next(it) != assoc_var.end())
                cout << ", ";
        }
        cout << endl;
    }
}


/**  
 * Constructor de la clase.
 * @param vars Lista de variables a pasar.
 */
GuavaDescTable::GuavaDescTable(list<string> vars): reg(true){
    for (list<string>::iterator it = vars.begin(); it != vars.end(); ++it){
        GuavaDescriptor *nuevo_reg; 
        if (reg){
            nuevo_reg = new GuavaRegister (*it);
        }else{
            nuevo_reg = new GuavaVar(*it);
        }
        tabla[*it] = nuevo_reg; 
    }
}

/** 
 * Constructor de la clase para variables.
 * @param s Lista de simbolos
 */    
GuavaDescTable::GuavaDescTable(list<SimpleSymbol*> s): reg(false){
    for (list<SimpleSymbol*>::iterator it = s.begin(); it != s.end(); ++it){
        GuavaDescriptor *nueva_var;
        nueva_var = new GuavaVar(*it);
        tabla[(*it)->get_mips_name()] = nueva_var;
    }
}

/** 
 * Destructor de la clase.
 * Voy eliminando cada uno de sus Descriptores.
 */
GuavaDescTable::~GuavaDescTable(){
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        //delete (*it).second;
    }
}

/** 
 * Retorna 0 cuando no existe el elemento y un descriptor cuando si.
 * @param s String s que buscamos
 * @return GuavaDescriptor Retorna 0 si el string no existe dentro de la tabla y una dirección a GuavaDescriptor en el caso contrario.
 */
GuavaDescriptor* GuavaDescTable::operator[](string s){
    if (tabla.count(s) == 0) return 0;
    return tabla[s];
}


/** 
 * Maneja el store en la tabla de descriptores.
 *
 * Esto es:
 * sw R, x
 * Availability (x ) ← Availability (x ) ∪ {x }
 * @param R nombre del registro R
 * @param x Ubicación en memoria o nombre de variable global.
 */
void GuavaDescTable::manage_ST(string R, SimpleSymbol* x){
    if (reg){
        if (tabla.find(R) != tabla.end()){
            GuavaDescriptor* desc = tabla[R]; // Esto debe ser obvio. Pero no le hace daño a nadie.
            desc->insert(x);
        }
    }else{
        std::unordered_map<string,GuavaDescriptor*>::const_iterator it;
        if ((it = tabla.find(x->get_mips_name())) != tabla.end()){
            it->second->insert(it->second->get_symbol());
        }
    }
}


/** 
 * Nos dice si un simbolo s se encuentra en otro registro o variable que no sea d.
 *
 * @param s Simbolo que nos interesa buscar.
 * @param d Descriptor que no nos interesa.
 * @return bool Retorna true si se encuentra en otra ubicación y false en el caso contrario.
 */
bool GuavaDescTable::available_in_other_location(SimpleSymbol* s, GuavaDescriptor* d){
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second == d ) continue;
        if (it->second->find(s) != 0) return true;
    }
    return false;
}

/** 
 * Retorna el primer registro que solo tenga asociado el simbolo s.
 * @param s Simbolo a buscar asociado al registro.
 * @return GuavaDescriptor* Descriptor de registro.
 */
GuavaDescriptor* GuavaDescTable::find_only_one(SimpleSymbol* s){
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second->size() == 1 && it->second->find_by_name(s->get_mips_name()) != 0 ) return it->second;
    }
    return 0;
}

/** 
 * Retorna el primer registro vacio
 * @return GuavaDescriptor* Descriptor de registro.
 */
GuavaDescriptor* GuavaDescTable::find_empty(){
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second->size() == 0 ) 
        {
            return it->second;
        }
    }
    return 0;
}

/** 
 * Retorna una lista con los registros que tienen el menor numero de registros asociados.
 * @return result Lista con los registros que tienen pocas variables asociadas.
 */
list<GuavaDescriptor*> GuavaDescTable::obtain_min(){
    list<GuavaDescriptor*> result; 
    int tam_min = INT_MAX;
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second->size() < tam_min ) tam_min = it->second->size();
        if (tam_min <= 1) break; // Ya se que no puede haber tamaño mas pequeño.
    }
    
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second->size() == tam_min) result.push_back(it->second);
    }
    return result;
}

int GuavaDescTable::min_assoc(){
    int tam_min = INT_MAX;
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second->size() < tam_min ) tam_min = it->second->size();
        if (tam_min <= 1) return tam_min; // Ya se que no va a haber algo menor.
    }
    return tam_min;
}


/**
 * Retorna una lista con los registros.
 *
 * Esto esta un poco ineficiente.
 *
 * @return result Lista con todos los descriptores de registros.
 */
list<GuavaDescriptor*> GuavaDescTable::get_desc(){
    list<GuavaDescriptor*> result;
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
            result.push_back(it->second);
    }
    return result;
}


/** 
 * Iterador del inicio de la tabla.
 */
std::unordered_map<string, GuavaDescriptor* >::iterator GuavaDescTable::begin(){
    return tabla.begin();
}

/** 
 * Iterador del fin de la tabla.
 */
std::unordered_map<string, GuavaDescriptor* >::iterator GuavaDescTable::end(){
    return tabla.end();
}


/** 
 * Maneja la instrucción de tipo LD R, x
 * @param x Nombre del simbolo a guardar.
 * @param R Nombre del registro.
 */
void GuavaDescTable::manage_LD(string R, SimpleSymbol* x){
    if (reg){
        //Caso tabla de registros
        if (tabla.count(R) != 0){
            GuavaDescriptor* desc = tabla[R];
            desc->clear();
            desc->insert(x);
            tabla[R] = desc;
        }
    } else{
        if (tabla.find(x->get_mips_name()) != tabla.end()){
            GuavaDescriptor* desc = tabla[x->get_mips_name()];
            SimpleSymbol* nuevo = new SymbolReg(R);
            desc->insert(nuevo);
            tabla[R] = desc;
        }
    }
}

/** 
 * Maneja el caso de instrucciones de 3 direcciones, del tipo x:= y + z.
 *
 * Para esto se realizan varias cosas:
 *  Cambia el descriptor del registro Rx para que solo tenga x
 *  Cambia el descriptor de variable para que solo tenga a Rx
 *  Quita Rx del descriptor de variable de cualquier otra variable que no sea x.
 *
 * @param x Nombre del simbolo. 
 * @param Rx Nombre del registro.
 *
 */
void GuavaDescTable::manage_OP(string Rx, SimpleSymbol* x){
    if (reg){
        if (tabla.find(Rx) != tabla.end()){
            GuavaDescriptor* desc = tabla[Rx];
            desc->clear();
            desc->insert(x);
        }
    }else{
        this->borrar_por_nombre(Rx);
        if (tabla.find(x->get_mips_name()) != tabla.end()){
            GuavaDescriptor* desc = tabla[x->get_mips_name()];
            SimpleSymbol* nuevo = new SymbolReg(Rx);
            desc->clear();
            desc->insert(nuevo);
        }
    }
}

/** 
 * Copia el contenido del set de desc en el descriptor
 * @param desc Otro descriptor.
 */
void GuavaDescriptor::copy(GuavaDescriptor* desc){
    assoc_var = desc->get_assoc_var();
}

/** 
 * Maneja la copia x := y.
 *
 * Esto es:
 *  (a) Add x to the register descriptor for Ry.
 *  (b) Change the address descriptor for x so that its only location is Ry
 *
 *  @param Ry nombre del registro Ry
 *  @param x Simbolo de la variable x
 */
void GuavaDescTable::manage_copy(string Ry, SimpleSymbol* x){
    if (reg){
        if (tabla.find(Ry) != tabla.end()){
            GuavaDescriptor* desc = tabla[Ry];
            desc->insert(x);
        }
    }else {
        if (tabla.find(x->get_mips_name()) != tabla.end()){
            GuavaDescriptor* desc = tabla[x->get_mips_name()];
            SimpleSymbol* nuevo = new SymbolReg(Ry);
            desc->clear();
            desc->insert(nuevo);
        }
    }
}

/** 
 * Maneja la copia de dos registros, esto es move $Rx, $Ry
 */
void GuavaDescTable::manage_move(string Rx, string Ry){
    if (tabla.find(Rx) != tabla.end() && tabla.find(Ry) != tabla.end()){
        GuavaDescriptor* desc = tabla[Rx];
        GuavaDescriptor* desc2 = tabla[Ry];
        desc->clear();
        desc->copy(desc2);
    }
}

/** 
 * Maneja el move que se hace entre dos registros cuando
 * uno de esos registros tiene asociado un variable var.
 *
 * @param Rx Nombre del registro que se le hace move
 * @param var Variable que se le va a asociar al registro Rx.
 */
void GuavaDescTable::manage_move(string Rx, SimpleSymbol * var){
    if (reg){
         if (tabla.find(Rx) != tabla.end()){
            GuavaDescriptor* desc = tabla[Rx];
            desc->insert(var);
        }       
    }else{
         if (tabla.find(var->get_mips_name()) != tabla.end()){
            GuavaDescriptor* desc = tabla[var->get_mips_name()];
            SimpleSymbol* nuevo = new SymbolReg(Rx);
            desc->insert(nuevo);
        }       

    }
}

/** 
 * Borra un elemento por nombre.
 * @param nombre Nombre del elemento a borrar. Tipicamente un registro.
 */
void GuavaDescriptor::borrar_por_nombre(string nombre){
    set<SimpleSymbol*> nuevo;
    for ( set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if ((*it)->get_mips_name().compare(nombre) != 0){
            nuevo.insert((*it));
        }else{
            //delete *it;
        }
    }
    assoc_var = nuevo;
}

/** 
 * Obtiene el tipo asociado a un registro.
 * @return TypeS* Retorna un tipo.
 */
TypeS* GuavaDescriptor::get_tipo(){
    regex flotante ("$f.*");
    if (regex_match (nombre, flotante)) return TypeReal::Instance();
    for (set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if (!(*it)->is_simple()){
            Symbol* tmp = (Symbol*) (*it);
            return tmp->get_tipo();
        }
    }
    return 0;
}

/** 
 * Encuentra un valor o variable en el descriptor por su nombre.
 * @return SimpleSymbol Retorna la variable encontrada o 0 si no la encuentra.
 */
SimpleSymbol* GuavaDescriptor::find_by_name(string n){
    for (set<SimpleSymbol*>::iterator it = assoc_var.begin() ; it != assoc_var.end(); ++it){
        if ((*it)->get_mips_name().compare(n) == 0) return *it;
    }
    return 0;
}

/** 
 * Borra un elemento por nombre en toda la tabla.
 * @param nombre Nombre del elemento a borrar. Tipicamente un registro.
 */
void GuavaDescTable::borrar_por_nombre(string nombre){
   for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin(); it != tabla.end(); ++it){
        it->second->borrar_por_nombre(nombre);
   }
}


/**  
 * Maneja el push en la tabla de descriptores.
 * @param reg Nombre del registro
 * @param nuevo Ubicacion en la pila
 */
void GuavaDescTable::manage_push(string reg, SymbolReg* nuevo){
    if (tabla.find(reg) != tabla.end()){
        GuavaDescriptor* desc = tabla[reg];
        desc->insert(nuevo);
    }
}

/**  
 * Maneja el push en la tabla de descriptores.
 * @param var Apuntador a simbolo de la variable.
 * @param nuevo Ubicacion en la pila
 */
void GuavaDescTable::manage_push(SimpleSymbol* var, SymbolReg* nuevo){
    if (tabla.find(var->get_mips_name()) != tabla.end()){
        GuavaDescriptor* desc = tabla[var->get_mips_name()];
        desc->insert(nuevo);
    }
}

/**
 * Imprime todo lo que tiene la tabla de descriptores.
 */
void GuavaDescTable::print(){
    for(std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin(); it != tabla.end(); ++it){
        it->second->print();
    }
}

/** 
 * Construye una lista con los registros de MIPS.
 *
 * Vamos a usar las registros a, t y s como nos parezca
 * ya que el compilador no se va a equivocar.
 * No voy a usar $a0 ni $a1 porque son usados en cuestiones del sistema.
 *
 * @return result Lista con nombres de registros.
 */
list<string> registros_mips(){
    list<string> result;
    string a ("$a");
    string t ("$t");
    string s ("$s");
    /* a2-a3 */
    for (int i = 2; i != 4 ; ++i){
        ostringstream convert;
        convert << i;
        result.push_back(a+convert.str());
        convert.flush();
    }
    /* t0-t9 */
    for (int i = 0 ; i != 10 ; ++i ){
        ostringstream convert;
        convert << i;
        result.push_back(t+convert.str());
        convert.flush();
    }
    /* s0-s7 */
     for (int i = 0 ; i != 8 ; ++i ){
        ostringstream convert;
        convert << i;
        result.push_back(s+convert.str());
        convert.flush();
    }   
    return result;
}

/** 
 * Construye una lista con registros flotantes de MIPS.
 * No voy a poner $f0 ni $f12 porque son usados para cuestiones de
 * llamadas.
 *
 * @return result Lista con nombres de registros.
 */
list<string> registros_float_mips(){
    list<string> result;
    string f ("$f");
    /* f1-f31 */
    for (int i = 1 ; i != 32 ; ++i ){
        ostringstream convert;
        convert << i; 
        if (i != 12){
            result.push_back(f+convert.str());
        }
        convert.flush();
    }
    return result;
}

DescTableMIPS::DescTableMIPS(): GuavaDescTable(registros_mips()){
    reg = true;
}

DescTableFloatMIPS::DescTableFloatMIPS(): GuavaDescTable(registros_float_mips()){
    reg = true;
}
