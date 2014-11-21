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
     * Busca un simbolo s
     * @return SimpleSymbol* Retorna un SimpleSymbol*
     */
    SimpleSymbol* find(SimpleSymbol* s){
        if (assoc_var.count(s) == 0) return 0;
        return *(assoc_var.find(s));
    }

    /** 
     * Tamaño del conjunto.
     */
    int size(){
        return assoc_var.size();
    }

    /** 
     * Borra
     */
    void erase(SimpleSymbol* var){
        assoc_var.erase(var);
    }

    /** 
     * Retorna un iterator al inicio
     */
    set<SimpleSymbol*>::iterator begin() const{
        return assoc_var.begin();
    }

    /** 
     * Retorna un iterator al fin
     */
    set<SimpleSymbol*>::iterator end() const{
        return assoc_var.end();
    }

    virtual bool is_var(){
        return false;
    }

    virtual bool is_reg(){
        return false;
    }

    /**  
     * Nos dice si las variables asociadas al descriptor
     * son todas globales.
     */
    bool todas_globales();

    /** 
     * Nos dice si las variables asociadas al descriptor
     * son todas globales y locales.
     */
    bool locales_globales();

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

   /** 
    * Operador [] para poder usar la tabla de descriptores.
    */
    GuavaDescriptor* operator[](string s);

    /** 
     * Retorna el primer registro que solo tenga asociado el simbolo s.
     */
    GuavaDescriptor* find_only_one(SimpleSymbol* s);

    /** 
     * Retorna el primer registro que este vacio.
     */
    GuavaDescriptor* find_empty();

    /** 
     * Retorna una lista con los registros que tienen el menor numero de registros asociados.
     */
    list<GuavaDescriptor*> obtain_min();

    /** 
     * Obtiene el numero minimo de variables asociadas.
     */
    int min_assoc();

    /**
     * Retorna una lista con los registros.
     */
    list<GuavaDescriptor*> get_desc();

    /**  
     * Revisa todos los descriptores/variables en la tabla
     * a ver si el simbolo se encuentra disponible.
     */
    bool available_in_other_location(SimpleSymbol* s, GuavaDescriptor* d);

    /** 
     * Iterador del inicio de la tabla.
     */
    std::unordered_map<string, GuavaDescriptor* >::iterator begin();

    /** 
     * Iterador del fin de la tabla.
     */
    std::unordered_map<string, GuavaDescriptor* >::iterator end();

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
