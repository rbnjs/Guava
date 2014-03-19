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
 *         Author:  Ruben Serradas, 
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
 * @param std::string& m: Referencia a nombre del token erroneo.
 */
void GuavaDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}
/**
 * Funcion que imprime un mensaje de error.
 * @param std::string& m: Referencia a nombre del token erroneo.
 */
void GuavaDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
