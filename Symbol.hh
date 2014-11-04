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
    int width;              /* Anchura del simbolo. */
    

    /**
     * Constructor para variable.
     */
    Symbol(std::string name, std::string catg, int scop, Symbol* type, int linea, int columna, int offset); // Variable que hace referencia a un tipo


    /**
     * Constructor para tipos basicos, estructuras, uniones y arreglos.
     */
    Symbol(std::string name, std::string catg,int scop, TypeS* type,int linea = 0,int columna = 0, int offset = 0);

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
};


