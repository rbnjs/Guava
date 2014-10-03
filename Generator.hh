/*
 * =====================================================================================
 *
 *       Filename:  Generator.hh
 *
 *    Description:  Clase generadora de codigo intermedio.
 *
 *        Version:  1.0
 *        Created:  14/09/14 14:26:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization:  USB 
 *
 * =====================================================================================
 */
#include <string>
#include <fstream>

class Generator{
private:
    std::string file_name; /* Nombre del archivo intermedio. */
    std::ofstream file;    /* Archivo intermedio. */
public:
    /**
     * Constructor de la clase Generator
     * @param name: Nombre del archivo intermedio a escribir.
     */
    Generator(std::string name): file_name(name+".ic"){
    }


    /**
     * Destructor de la clase Generator.
     */
    ~Generator(){
        if (file.is_open()){
            file.close();
        }
    }

    /**
     * Escribe el codigo de tres direcciones en el archivo.
     * @param code: Codigo de tres direcciones.
     */
    void gen(std::string code){
        if (file.is_open()){
            file << code + "\n";
        } else {
            file.open(file_name); 
            if (file.is_open()) file << code + "\n";
        }
    }
};
