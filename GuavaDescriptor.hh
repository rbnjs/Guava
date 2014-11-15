/*
 * =====================================================================================
 *
 *       Filename:  GuavaDescriptor.hh
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

# ifndef GUAVA_DESCRIPTOR_HH
# define GUAVA_DESCRIPTOR_HH
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
     * Escribe el codigo en el archivo.
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

    void operator<<(string code){
       this->gen(code); 
    }
};
/** 
 * Clase que representa un descriptor de un registro o variable.
 */
class GuavaDescriptor{
    string nombre;                 /* Nombre del registro */
    set<SimpleSymbol*> assoc_var; /* Conjunto de variables asociadas al registro. */ 
public:
    
    /** 
     * Constructor
     */
    GuavaDescriptor(string nombre_): nombre(nombre_){
    }

    ~GuavaDescriptor(){}
    
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

    virtual bool is_var(){
        return false;
    }

    virtual bool is_reg(){
        return false;
    }

};

/** 
 * Clase que representa un registro.
 */
class GuavaRegister: public GuavaDescriptor{
public:

    GuavaRegister(string nombre_): GuavaDescriptor(nombre_){
    }

    ~GuavaRegister(){}

    bool is_reg(){
        return true;
    }
};

/** 
 * Clase que representa una Variable de Guava.
 */
class GuavaVar: public GuavaDescriptor{
public:
    GuavaVar(string nombre_): GuavaDescriptor(nombre_){}

    ~GuavaVar(){}

    bool is_var(){
        return true;
    }
};

/** 
 * Clase para la descripcion de registros.
 */
class GuavaDescTable{
    std::unordered_map<string, GuavaDescriptor* > tabla;  /* Tabla que guarda las variables/registros disponibles junto con sus simbolos. */
    bool reg;
public:

   /** 
    * Constructores de la clase.
    * @param vars Lista de variables o nombres de registros.
    * @param reg Nos dice si la tabla esta guardando registros, en el caso contrario guarda variables.
    */
   GuavaDescTable(list<string> vars, bool reg);
   GuavaDescTable(bool reg_): reg(reg_){}

   /** 
    * Destructor de la clase.
    */
   ~GuavaDescTable();

   /** 
    * Nos dice si la tabla guarda o no registros.
    */
   bool stores_reg(){
       return reg;
   }
};

/** 
 * Descriptor de Registros para MIPS.
 */
class DescTableMIPS: public GuavaDescTable{
public:

    DescTableMIPS();

    ~DescTableMIPS(){}

};

class DescTableFloatMIPS: public GuavaDescTable{
public:

    DescTableFloatMIPS();

    ~DescTableFloatMIPS(){}
};

#endif // GUAVAQUADS_HH
