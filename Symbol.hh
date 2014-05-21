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
#include <unordered_map>
#include "Types.hh"


/** 
 * Clase simbolo de Guava.
 */
class Symbol{
public:

    std::string sym_name;   /* Nombre del simbolo */
    std::string sym_catg;   /* Categoria del simbolo */
    int scope;              /* Identificador del scope del simbolo */

    std::string type;       /* DEPRECATED */ 

    int *arreglo;           /* Dimensiones del arreglo */
    int dimensiones;         /* Tamaño de las dimensiones del arreglo */
    int fieldScope;         /* Alcance de los simbolos de una estructura, union o funcion */

    int line;               /* Linea en la que fue encontrado el simbolo */ 
    int column;             /* Columna en la que fue encontrado el simbolo */ 
    bool referencia;        /* Nos dice si el simbolo es una referencia o no. */  

    bool symbol_type;       /* Nos dice si el simbolo es un tipo */

    TypeS* true_type;       /* Tipo correcto */
    Symbol* type_pointer;   /* Apuntador a tipo */
    

    /**
     * Constructor para variable.
     */
    Symbol(std::string name, std::string catg, int scop, Symbol* type, int linea, int columna); // Variable que hace referencia a un tipo

    
    /**
     * Constructor para arreglos.
     */
    Symbol(std::string, std::string, int, TypeS*,int,int); 
   
    
    /**
     * Constructor para estructuras y funciones. 
     */
    Symbol(std::string,std::string,int,TypeS*,int,int,int);

    /**
     * Constructor para tipos primitivos basicos.
     */
    Symbol(std::string,std::string,int,TypeS*);
    
    /**
     * Constructor para estructuras, uniones y funciones.
     */
    Symbol(std::string,std::string,int,TypeS*, int);
    

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
     * Compara nombres y alcance 
     */
    bool compare(std::string s, int sc);
    
    /**
     * Muestra lo que tiene el Symbol. 
     */
    virtual void show(std::string);
};


