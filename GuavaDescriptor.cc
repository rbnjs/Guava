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

using namespace std;

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
