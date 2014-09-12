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
    std::cout << "Usage: "<< "guava [-p] [-s] [-t] [-st] [-h] [source code]" << std::endl ;
    std::cout << "-p: Trace the parsing of the file.\n";
    std::cout << "-s: Trace the scanning of the file.\n";
    std::cout << "-t: Print the Abstract Syntax Tree of the file's source code.\n";
    std::cout << "-st: Print the Symbol Table.\n";
    std::cout << "-h: Print this help text.\n";
}

int main (int argc, char *argv[]){
    bool uso_ninguna_opcion = true; 
    GuavaDriver driver;
    driver.print_table = false;
    driver.print_tree = false;
    int i;
    /* Revisamos las opciones. */
    for (i = 1; i < argc; ++i){
        std::string arg (argv[i]);
        if (arg.compare(std::string ("-p")) == 0){
            driver.trace_parsing = true;
        }
        else if (arg.compare(std::string ("-s")) == 0 ){
            driver.trace_scanning = true;
        }
        else if (arg.compare(std::string("-t")) == 0){
            uso_ninguna_opcion = false;
        }else if(arg.compare(std::string("-st")) == 0){
            uso_ninguna_opcion = false;
            driver.print_table = true;
        } else if (arg.compare(std::string("-h")) == 0){
            mensajeAyuda();
        } else if (!driver.parse (argv[argc - 1])) {
            uso_ninguna_opcion = false;
        }
    }
    if (argc == 1){
        mensajeAyuda();
    }
}
