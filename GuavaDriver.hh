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
//# ifndef GUAVADRIVER_HH
# define GUAVADRIVER_HH
# include <string>
# include <map> 
# include "GuavaParser.hh"
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

    std::map<std::string, int> variables;

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
};
//#endif // ! GUAVADRIVER_HH
