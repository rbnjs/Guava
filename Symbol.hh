/*
 * =====================================================================================
 *
 *       Filename:  Symbol.hh
 *
 *    Description:  Symbol.
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

typedef union {
    float* real;
    std::string* str;
    int* integer;
    char* ch;
    bool* boolean;   
} Referencia;

typedef union {
    float real;
    int integer;
    char ch;
    std::string * str;
    bool boolean;
    
} ValorUnion;

typedef union {
    ValorUnion valor;
    Referencia referencia;
} ValorSimbolo;

/** 
 * Clase simbolo de Guava.
 */
class Symbol{
public:
    std::string sym_name; /* Nombre del simbolo */
    std::string sym_catg; /* Categoria del simbolo */
    int scope;            /* Identificador del scope del simbolo */
    std::string type;
    int *arreglo;
    int size;
    int fieldScope;
    int line;
    int column;
    ValorSimbolo contenido;
    bool referencia;

    /**
     * Constructor de la clase Symbol para variable.
     */
    Symbol(std::string name, std::string catg, int scop, std::string type, int linea, int columna);

    /**
     * Constructor para arreglo 
     */
    Symbol(std::string, std::string, int, std::string,int,int, int*,int); 
   
    /**
     * Constructor para estructuras.
     */
    Symbol(std::string,std::string,int,std::string,int,int,int);

    Symbol();

    /**
     * Destructor de la clase Symbol.
     * */
    ~Symbol();

    /**
     * Se utiliza el operador == para comparar. 
     */
    bool operator==(Symbol b);

    /** 
     * Compara nombres y alcance 
     */
    bool compare(std::string s, int sc);
    
    /**
     * Muestra lo que tiene el Symbol. 
     */
    virtual void show(std::string);
};


