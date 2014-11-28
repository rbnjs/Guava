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
#include "Symbol.hh"
#include "Generator.hh"

using namespace std;


/** 
 * Clase que representa un descriptor de un registro o variable.
 */
class GuavaDescriptor{
    string nombre;                 /* Nombre del registro */
    SimpleSymbol* addr = 0;        /* Simbolo asociado a la variable si es una variable. */
    set<SimpleSymbol*> assoc_var;  /* Conjunto de variables asociadas al registro. */ 
public:
    
    /** 
     * Constructor
     * @param nombre_ Nombre del descriptor
     */
    GuavaDescriptor(string nombre_): nombre(nombre_){
    }

    /** 
     * Constructor
     * @param nombre_ Nombre del descriptor
     * @param s Simbolo asociado para la variable.
     */
    GuavaDescriptor(string nombre_, SimpleSymbol* s):nombre(nombre_),addr(s) {
    }

    ~GuavaDescriptor(){}
    
    /**
     * @return nombre
     */
    string get_nombre() const{
        return nombre;
    }

    SimpleSymbol* get_symbol(){
        return addr;
    }

    /** 
     * Cambia la dirección de simbolo.
     */
    void set_symbol(SimpleSymbol* s){
        addr = s;
    }

    /** 
     * Inserta variable.
     */
    void insert(SimpleSymbol* var){
        assoc_var.insert(var);
    }

    void insert(GuavaDescriptor* reg);

    void copy(GuavaDescriptor* reg);

    /** 
     * Busca un simbolo s
     * @return SimpleSymbol* Retorna un SimpleSymbol*
     */
    SimpleSymbol* find(SimpleSymbol* s){
        if (assoc_var.count(s) == 0) return 0;
        return *(assoc_var.find(s));
    }

    SimpleSymbol* find_by_name(string n);

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
     * Borra el set por nombre.
     */
    void borrar_por_nombre(string nombre);

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

    /** 
     * Funcion que retorna el numero de variables temporales asociadas
     * a un descriptor.
     * @return int Numero de temporales.
     */
    int count_temp();

    void clear();

    TypeS* get_tipo();

    /** 
     * Retorna el conjunto de variables asociadas al 
     * registro.
     * @return assoc_var
     */
    set<SimpleSymbol*> get_assoc_var(){
        return assoc_var;
    }

    void end_block(GuavaGenerator *g);

    void print();

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

    GuavaVar(SimpleSymbol* s): GuavaDescriptor(s->sym_name,s){}

    ~GuavaVar(){}

    bool is_var(){
        return true;
    }
};

/** 
 * Clase para la descripcion de registros.
 */
class GuavaDescTable{
protected:
    std::unordered_map<string, GuavaDescriptor* > tabla;  /* Tabla que guarda las variables/registros disponibles junto con sus simbolos. */
    bool reg; /* Variable booleana que nos dice si guarda registros o variables. */
    void borrar_por_nombre(string reg);
public:

   /** 
    * Constructores de la clase.
    * @param vars Lista de nombres de registro.
    */
   GuavaDescTable(list<string> vars);

   /** 
    * Constructor vacio de la clase.
    * @param reg Nos dice si la tabla esta guardando registros, en el caso contrario guarda variables.
    */
   GuavaDescTable(bool reg_): reg(reg_){}


   void set_reg(bool t){
       reg = t;
   }


   GuavaDescTable(list<SimpleSymbol*> simbols);

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

    void manage_store(string var);

    void manage_LD(string R, SimpleSymbol* x);

    void manage_OP(string R, SimpleSymbol* x);

    void manage_copy(string Ry, SimpleSymbol* x);

    void manage_move(string Rx, string Ry);

    void manage_move(string Rx, SimpleSymbol* var);

    void manage_push(SimpleSymbol* var, SymbolReg* nuevo);

    void manage_push(string reg, SymbolReg* nuevo);

    void copy(GuavaDescriptor* desc);

    void print();

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
