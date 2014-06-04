/*
 * =====================================================================================
 *
 *       Filename:  GuavaDriver.hh
 *
 *    Description:  
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, 
 *
 * =====================================================================================
 */
# ifndef GUAVADRIVER_HH
# define GUAVADRIVER_HH
# include <string>
# include <map> 
# include "GuavaParser.hh"
#include "globals.hh"


// Prototipo de lexer para Flex
# define YY_DECL                                      \
  yy::GuavaParser::token_type                         \
  yylex (yy::GuavaParser::semantic_type* yylval,      \
         yy::GuavaParser::location_type* yylloc,      \
         GuavaDriver& driver)
// Se declara.
YY_DECL;

// Se realiza el escaneo y parseo de Guava.
class GuavaDriver
{
public:    
    GuavaDriver();
    virtual ~GuavaDriver();

    GuavaSymTable tablaSimbolos;
    int result;

    // Scanner.
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;
    // Corre el parser. Retorna 0 si no hay error.
    int parse (const std::string& f);
    std::string file;
    bool trace_parsing;
    // Manejo de errores.
    void error (const yy::location& l, const std::string& m);
    void error (const std::string& m);
    void warning(const yy::location& l, const std::string& m);
};
#endif // ! GUAVADRIVER_HH


/* Funciones auxiliares. */

TypeS* obtener_tipo_simbolo(Symbol* id);

bool es_estructura_error(std::string categoria,std::string nombre ,  GuavaDriver* driver, const yy::location& loc);

bool es_estructura(std::string categoria);

Symbol* variable_no_declarada(std::string name, GuavaDriver* driver, const yy::location& loc, GuavaSymTable* t);

Symbol* variable_no_declarada(std::string name, GuavaDriver* driver, const yy::location& loc, int scope, GuavaSymTable* t);

std::string reportar_existencia(Symbol *s, std::string id);

std::string reportar_existencia_tipo(Symbol *s, std::string id);

std::string tipo_no_existe(std::string id);

std::string no_es_tipo(std::string id);

std::string mensaje_error_tipos(std::string esperado, std::string encontrado);

std::string mensaje_diff_operandos(std::string operador, std::string op1, std::string op2, std::string expected) ;

Symbol* obtener_tipo(std::string str, GuavaDriver *d, GuavaSymTable* t);

int encajar_en_palabra(int tam);

int tamano_tipo(TypeS* t);

void insertar_simboloSimple(LVar *vars, TypeS *t, std::string estilo, GuavaDriver *d, const yy::location& loc) ;

void insertar_simboloSimple(Identificador* identificador, TypeS *t, std::string estilo, GuavaDriver *d, const yy::location& loc) ;

void insertar_simboloArreglo(LVarArreglo *vars, TypeS *t, GuavaDriver *d, const yy::location& loc) ;

TypeS* obtener_tipo_real(std::string tipo ,GuavaDriver *d, const yy::location& loc, GuavaSymTable* t);

std::string reportar_tipo_recursivo(std::string t);

TypeS* insertar_simboloEstructura(LVar *vars, std::string tipo,std::string estilo,GuavaDriver *d, const yy::location& loc);

TypeS* insertar_simboloArregloEstructura(LVarArreglo *vars, std::string t, GuavaDriver *d, const yy::location& loc) ;

void insertar_funcion(TypeS* tipo, Identificador* id, LParam* lp ,GuavaDriver* d,int current_scope, const yy::location& loc);

TypeS* dereference(TypeS* referencia);

TypeS* verificar_acceso_atributos(Symbol* id, std::list<Identificador*> la, GuavaDriver* driver, const yy::location& loc);

void verificar_existencia_tipo(Identificador* id, GuavaDriver* d,const yy::location& loc, bool is_union);
