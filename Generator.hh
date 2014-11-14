/*
 * =====================================================================================
 *
 *       Filename:  Generator.hh
 *
 *    Description:  Clase generadora de codigo final.
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
#include <set>
#include <unordered_map>
#include <list>
#include "GuavaQuads.hh"


using namespace std;
/**
 * Clase escritora de archivos finales.
 */
class Generator{
private:
    std::string file_name; /* Nombre del archivo intermedio. */
    std::ofstream file;    /* Archivo intermedio. */
public:
    /**
     * Constructor de la clase Generator
     * @param name: Nombre del archivo intermedio a escribir.
     */
    Generator(std::string name): file_name(name+".asm"){
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
/** 
 * Clase que representa un registro.
 */
class GuavaRegister{
    string nombre;                 /* Nombre del registro */
    set<SimpleSymbol*> assoc_var; /* Conjunto de variables asociadas al registro. */ 
public:
    
    /** 
     * Constructor
     */
    GuavaRegister(string nombre_): nombre(nombre_){
    }

    ~GuavaRegister(){}
    
    /**
     * @return nombre
     */
    string get_nombre() const{
        return nombre;
    }

    /** 
     * Inserta variable.
     */
    void insert(SimpleSymbol* var){
        assoc_var.insert(var);
    }

    /** 
     * Borra
     */
    void erase(SimpleSymbol* var){
        assoc_var.erase(var);
    }

    set<SimpleSymbol*>::iterator begin() const{
        return assoc_var.begin();
    }

};

/** 
 * Clase para la descripcion de registros.
 */
class GuavaDescReg{
    std::unordered_map<string, GuavaRegister > tabla;  /* Tabla que guarda las variables/registros disponibles junto con sus simbolos. */
public:

   /** 
    * Constructor de la clase.
    */
   GuavaDescReg(list<string> vars);

   GuavaDescReg(){}

   /** 
    * Destructor de la clase.
    */
   ~GuavaDescReg(){};
};
