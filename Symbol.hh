/*
 * =====================================================================================
 *
 *       Filename:  Symbol.hh
 *
 *    Description:  Contiene los headers para las clases referentes a simbolos.
 *
 *        Version:  1.0
 *        Created:  12/03/14 14:25:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo 
 *   Organization:  
 *
 * =====================================================================================
 */

# ifndef SYMBOL_HH
# define SYMBOL_HH
#include <string>
#include <unordered_map>
#include <sstream>
#include "Types.hh"
#define UNDEF -1

/**
 * Simbolo que solo tiene el nombre, utilizado en la generacion de codigo
 * intermedio.
 */
class SimpleSymbol{
public: 
    std::string sym_name;                  /* Nombre del simbolo */
    /* Informacion con respecto a proximo uso. */
    int proximo_uso = UNDEF ;          
    /* Informacion con respecto a la vida del simbolo. */
    bool live = true;                    

    SimpleSymbol(){}

    /** 
     * Construye un Simbolo Simple 
     * @param name Nombre del simbolo
     */
    SimpleSymbol(std::string name): sym_name(name){}

    /**
     * Convierte un numero a string y construye el simbolo
     * @param a Entero.
     */
    SimpleSymbol(int a){
        std::ostringstream convert;         
        convert << a;
        sym_name = convert.str(); 
    }

    ~SimpleSymbol(){}

    virtual bool is_simple(){ return true; }

    /** 
     * Funcion que "mata" a un simbolo, es decir, 
     * coloca los atributos tiene_uso y live en false
     */
    void kill(){
        proximo_uso = UNDEF;
        live = false;
    }

    /** 
     * Actualiza la informacion de uso y liveness.
     * @param Numero del statement. Este es el que es usado como id en cualquier GuavaQuad.
     */
    void update_use(unsigned int statement){
        live = true;
        proximo_uso = statement;
    }

    /** 
     * Operador de comparacion para SimpleSymbol.
     */
    bool operator==(SimpleSymbol s){
        return (sym_name.compare(s.sym_name) == 0);
    }

    /** 
     * Indica que un Simbolo es temporal.
     * @return true si el nombre del simbolo comienza por _t o false en el caso contrario.
     */
    bool is_temp();

    /** 
     * Nos dice si el simbolo es global.
     */
    virtual bool is_global(){
        return false;
    }

    /** 
     * Nos dice si es arreglo
     */
    virtual bool is_array(){
        return false;
    }

    virtual bool is_reg(){
        return false;
    }

};

/** 
 * Clase que representa un Registro.
 */
class SymbolReg: public SimpleSymbol{
public:


    /** 
     * Construye un Simbolo registro con su nombre.
     */
    SymbolReg(std::string nombre): SimpleSymbol(nombre){}

    /** 
     * Destructor de la clase
     */
    ~SymbolReg(){}


    virtual bool is_reg(){
        return true;
    }
};

/** 
 * Clase simbolo de Guava.
 */
class Symbol: public SimpleSymbol{
public:

    std::string sym_catg;   /* Categoria del simbolo */
    int scope;              /* Identificador del scope del simbolo */

    int line;               /* Linea en la que fue encontrado el simbolo */ 
    int column;             /* Columna en la que fue encontrado el simbolo */ 

    TypeS* true_type;       /* Tipo correcto */
    Symbol* type_pointer;   /* Apuntador a tipo */

    int offset;             /* Offset del simbolo. */
    int width;              /* Anchura del simbolo: tamano del tipo del simbolo. */
    

    /**
     * Constructor para variable.
     */
    Symbol(std::string name, std::string catg, int scop, Symbol* type, int linea, int columna, int offset); // Variable que hace referencia a un tipo


    /**
     * Constructor para tipos basicos, estructuras, uniones y arreglos.
     */
    Symbol(std::string name, std::string catg,int scop, TypeS* type,int linea = 0,int columna = 0, int offset = 0);

    /**
     * Constructor basico para nombres y valores.
     */
    Symbol(std::string name);


    /** 
     * Constructor para offsets y valores enteros.
     */
    Symbol(int o): SimpleSymbol(o){}

    /**
     * Constructor para simbolo vacio.
     */
    Symbol();

    /**
     * Destructor de la clase Symbol.
     */
    ~Symbol();

    /**
     * Se utiliza el operador == para comparar. 
     */
    bool operator==(Symbol b);

    /** 
     * Compara nombres y alcance con un simbolo. 
     */
    bool compare(std::string s, int sc);
    
    /**
     * Muestra lo que tiene el Symbol. 
     */
    virtual void show(std::string);

    bool is_simple(){ return false; }

    bool is_global();


    TypeS* get_tipo();


};

/**
 * Especializacion de la clase Symbol, describe un simbolo arreglo.
 *
 * Posee las direcciones necesarias para la generacion de codigo relativo al
 * calculo de direcciones y obtencion de elementos de un arreglo.
 */
class SymbolArray: public Symbol {
public:
    /* Direccion relativa al desplazamiento para alcanzar un elemento del
     * arreglo.
     */   
    Symbol* desp = 0;
    /* Direccion del elemento del arreglo buscado, necesaria para el calculo
     * de expresiones que involucren el elemento en cuestion.
     */  
    Symbol* elem = 0;

    /**
     * Constructores de la clase SymbolArray.
     */
    SymbolArray();

    SymbolArray(std::string name, std::string catg, int scop, Symbol* type, int linea, int columna, int offset); 

    SymbolArray(std::string name, std::string catg,int scop, TypeS* type,int linea = 0,int columna = 0, int offset = 0);
    
    /**
     * Destructor de la clase SymbolArray.
     */
    ~SymbolArray();

    bool is_array(){
        return true;
    }
};
#endif
