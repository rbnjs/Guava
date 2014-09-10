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
    int i = 0;
    bool uso_opcion = true; 
    GuavaDriver driver;
    /* Si no son elegidas opciones */
    if (argc == 1){
        mensajeAyuda();
    }
    /* Revisamos y colocamos las opciones. */
    for (i = 1; i < argc; ++i){
        if (argv[i] == std::string("-p")){
            driver.trace_parsing = true;
        }
        else if (argv[i] == std::string("-s")){
            driver.trace_scanning = true;
        }
        /*else if (!driver.parse (argv[i])){
            uso_ninguna_opcion = false;
        }*/else if (argv[i] == std::string("-t")){
            driver.print_tree = true;
        }
        else if(argv[i] == std::string("-st")){
            driver.print_table = true;
        }
        else if(argv[i] == std::string("-h")){
            uso_opcion = false;
            mensajeAyuda();
        }
        else {
            uso_opcion = false;
            std::cout << "Not recognized option.\n";
        }
    }
    /* Se realiza el parseo del archivo */
    if(uso_opcion) {
        driver.parse(argv[i]);
    }
}
