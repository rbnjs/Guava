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
    regex underscore ("_t.*"); //Cualquier cosa que comience con _t es temporal.
    for (set<SimpleSymbol*>::iterator it = assoc_var.begin(); it != assoc_var.end(); ++it){
        if (std::regex_match ((*it)->sym_name, underscore ))
            return false;
    }
    return true;
}


/**  
 * Constructor de la clase.
 * @param vars Lista de variables a pasar.
 */
GuavaDescTable::GuavaDescTable(list<string> vars, bool reg_): reg(reg_){
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
 * Destructor de la clase.
 * Voy eliminando cada uno de sus Descriptores.
 */
GuavaDescTable::~GuavaDescTable(){
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        delete (*it).second;
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
        if (it->second->size() == 1 && it->second->find(s) != 0 ) return it->second;
    }
    return 0;
}

/** 
 * Retorna el primer registro vacio
 * @return GuavaDescriptor* Descriptor de registro.
 */
GuavaDescriptor* GuavaDescTable::find_empty(){
    for (std::unordered_map<string, GuavaDescriptor* >::iterator it = tabla.begin() ; it != tabla.end(); ++it){
        if (it->second->size() == 0 ) return it->second;
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
 * Construye una lista con las variables de MIPS.
 *
 * Vamos a usar las variables a, t y s como nos parezca
 * ya que el compilador no se va a equivocar.
 *
 * @return result Lista con nombres de variables.
 */
list<string> variables_mips(){
    ostringstream convert;
    list<string> result;
    string a ("$a");
    string t ("$t");
    string s ("$s");
    /* a0-a3 */
    for (int i = 0; i != 4 ; ++i){
        convert << i;
        result.push_back(a+convert.str());
        convert.flush();
    }
    /* t0-t9 */
    for (int i = 0 ; i != 10 ; ++i ){
        convert << i;
        result.push_back(t+convert.str());
        convert.flush();
    }
    /* s0-s7 */
     for (int i = 0 ; i != 8 ; ++i ){
        convert << i;
        result.push_back(s+convert.str());
        convert.flush();
    }   
    return result;
}

/** 
 * Construye una lista con variables flotantes de MIPS.
 *
 * @return result Lista con nombres de variables.
 */
list<string> variables_float_mips(){
    ostringstream convert;
    list<string> result;
    string f ("$f");
    /* f0-f31 */
    for (int i = 0 ; i != 32 ; ++i ){
        convert << i;    
        result.push_back(f+convert.str());
        convert.flush();
    }
    return result;
}

DescTableMIPS::DescTableMIPS(): GuavaDescTable(variables_mips(),true){
}

DescTableFloatMIPS::DescTableFloatMIPS(): GuavaDescTable(variables_float_mips(),true){
}
