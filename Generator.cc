/*
 * =====================================================================================
 *
 *       Filename:  Generator.cc
 *
 *    Description:  Implementacion de Generator.
 *
 *        Version:  1.0
 *        Created:  22/11/14 15:28:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Generator.hh"

using namespace std;

/**
 * Destructor de Generator.
 * Cierra el archivo si esta abierto.
 */
GuavaGenerator::~GuavaGenerator(){
    if (file.is_open()){
        file.close();
    }
}

/**
 * Escribe el codigo en el archivo.
 * @param code: Codigo final
 */
void  GuavaGenerator::gen(std::string code){
    if (file.is_open()){
        file << code + "\n";
    } else {
        file.open(file_name); 
        if (file.is_open()) file << code + "\n";
    }
}

/** 
 * Operador << para poder escribir en el archivo de manera transparente.
 * @param code: Codigo final.
 */
void GuavaGenerator::operator<<(string code){
    this->gen(code); 
}
