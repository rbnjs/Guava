/*
 * =====================================================================================
 *
 *       Filename:  GuavaDriver.cc
 *
 *    Description:  Manejador de parser.
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo
 *
 * =====================================================================================
 */
#include "GuavaDriver.hh"
#include "GuavaParser.hh"
/**
 * Constructor de la clase GuavaDriver
 */
GuavaDriver::GuavaDriver ()
  : trace_scanning (false), trace_parsing (false)
{
    TypeS* integer = new TypeInt();
    TypeS* real = new TypeReal();
    TypeS* error = new TypeError();
    TypeS* boolean = new TypeBool();
    TypeS* character = new TypeChar();
    TypeS* string = new TypeString();
    TypeS* voidt = new TypeVoid(); 
    
    tablaSimbolos = *(new GuavaSymTable());
    tablaSimbolos.insert_type(std::string("integer"),std::string("type"),0,integer);
    tablaSimbolos.insert_type(std::string("real"),std::string("type"),0,real);
    tablaSimbolos.insert_type(std::string("error"),std::string("type"),0,error);
    tablaSimbolos.insert_type(std::string("boolean"),std::string("type"),0,boolean);
    tablaSimbolos.insert_type(std::string("character"),std::string("type"),0,character);
    tablaSimbolos.insert_type(std::string("string"),std::string("type"),0,string);
    tablaSimbolos.insert_type(std::string("void"),std::string("type"),0,voidt);
}
/**
 * Destructor de la clase GuavaDriver 
 */
GuavaDriver::~GuavaDriver ()
{
}

/** 
 * Funcion que llama al parser.
 * @param std::string &f: Referencia a nombre del string a parsear. 
 * @return int res: Resultado del parseo.
 */
int GuavaDriver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::GuavaParser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}
/**
 * Funcion que imprime un mensaje de error.
 * @param yy::location& l: Referencia al lugar del error.
 * @param std::string& m: Referencia a mensaje de error.
 */
void GuavaDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}
/**
 * Funcion que imprime un mensaje de error.
 * @param std::string& m: Referencia a mensaje de error.
 */
void GuavaDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
