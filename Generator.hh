/*
 * =====================================================================================
 *
 *       Filename:  Generator.hh
 *
 *    Description:  Clase que sirve para escribir en archivos finales. 
 *
 *        Version:  1.0
 *        Created:  22/11/14 15:27:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo. 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef GENERATOR_HH
#define GENERATOR_HH
#include <string>
#include <fstream>

using namespace std;
/**
 * Clase escritora de archivos finales.
 */
class GuavaGenerator{
private:
    string file_name; /* Nombre del archivo intermedio. */
    ofstream file;    /* Archivo intermedio. */
public:

    /**
     * Constructor de la clase Generator
     * @param name: Nombre del archivo intermedio a escribir. A este se le agrega .asm para MIPS.
     */
    GuavaGenerator(string name): file_name(name+".asm"){
    }

    ~GuavaGenerator();

    void close();

    void gen(std::string code);

    void operator<<(string code);
};
#endif
