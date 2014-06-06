/*
 * =====================================================================================
 *
 *       Filename:  Guava.cc
 *
 *    Description:  Main del frontend para el compilador de Guava.
 *
 *        Version:  1.0
 *        Created:  03/03/14 14:24:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas , Michael Woo 
 *   Organization:  USB
 *
 * =====================================================================================
 */
#include <iostream>
#include "GuavaDriver.hh"

void mensajeAyuda(){
    std::cout << "Compiler for the Guava Programming Language.\n";
    std::cout << "Usage: "<< "guava [-p] [-s] [-t] [-st] [source code]" << std::endl ;
    std::cout << "-p: Trace the parsing of the file.\n";
    std::cout << "-s: Trace the scanning of the file.\n";
    std::cout << "-t: Print the Abstract Syntax Tree of the file's source code.\n";
    std::cout << "-st: Print the Symbol Table.\n";
}

int main (int argc, char *argv[]){
    bool uso_ninguna_opcion = true; 
    GuavaDriver driver;
    /* Revisamos las opciones. */
    for (int i = 1; i < argc; ++i){
        if (argv[i] == std::string ("-p")){
            driver.trace_parsing = true;
            uso_ninguna_opcion = false;
        }
        else if (argv[i] == std::string ("-s")){
            driver.trace_scanning = true;
            uso_ninguna_opcion = false;
        }
        else if (!driver.parse (argv[i])){
            uso_ninguna_opcion = false;
        }else if (argv[i] == std::string("-t")){
            uso_ninguna_opcion = false;
            driver.print_tree = true;
        }else if(argv[i] == std::string("st")){
            uso_ninguna_opcion = false;
            driver.print_table = true;
        }
    }
    if (uso_ninguna_opcion){
        mensajeAyuda();
    }
}
