/*
 * =====================================================================================
 *
 *       Filename:  GuavaLexer.l
 *
 *    Description:  Lexer del lenguaje Guava.
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben Serradas, Michael Woo
 *
 * =====================================================================================
 */
%{
#include <iostream>
#include <fstream>
# include "GuavaDriver.hh"
# include "GuavaParser.hh"

typedef yy::GuavaParser::token token;
int myline;
%} 
%{
#define yyterminate() return token::END
%}
%option noyywrap yylineno batch debug  

DIGIT    [0-9]
ID       [A-Za-z][A-Za-z0-9_]*
STRING   \"[^\n"]+\"
CHAR     \'[^']\'|\'\\n\'
WS       [ \t]+
%{
// Code run each time a pattern is matched.
# define YY_USER_ACTION  yylloc->columns (yyleng);
%}

%%

%{
  yylloc->step ();
%}


{WS}     yylloc->step (); 

[\n]+    yylloc->lines (yyleng); yylloc->step ();    


"//".*\n  yylloc->lines (1); /* Comentarios de una sola linea */

"/*"    { /* Acciones para el bloque de comentarios. */
        int c;
        int line = 0;
        while((c = yyinput()) != 0){
	    if (c == '\n') line++;
            if(c == '*')
                {
                if((c = yyinput()) == '/')
                    break;
                else
                    unput(c);
                }
            }
	yylloc->lines (line);
        }

true { yylval->boolval = true; return token::BOOL; } 

false { yylval->boolval = false; return token::BOOL; }

integer   { return token::TYPE_INTEGER; }
real      { return token::TYPE_REAL; }
boolean   { return token::TYPE_BOOLEAN; }
character { return token::TYPE_CHAR; }
string    { return token::TYPE_STRING; }
void      { return token::TYPE_VOID; }

for       { return token::FOR; }
main      { return token::MAIN; }
if        { return token::IF; }
then      { return token::THEN; }
else      { return token::ELSE; }
while     { return token::WHILE; }
do        { return token::DO;}
return    { return token::RETURN; }
break     { return token::BREAK; }
continue  { return token::CONTINUE; }
record    { return token::RECORD; }
union     { return token::UNION; }
reference { return token::REFERENCE; }
array     { return token::ARRAY; }
function  { return token::FUNCTION; }
declare   { return token::DECLARE; }

print    { return token::PRINT; } /* Funciones reservadas */
read     { return token::READ; } 

{DIGIT}+ {
	     int digit = atoi(yytext);
             yylval->intval = digit;
             return token::INTEGER;
         }

{DIGIT}+"."{DIGIT}* {
                        float digit = atof(yytext);
                        yylval->realval = digit;
                        return token::REAL;
                    }



{STRING} {
             yylval->strval = yytext;
             return token::STRING;
         }

\"[^\n"]*$  { driver.error (*yylloc, "missing terminating character \"");
              strcpy(yylval->strval, "");
              return token::STRING;
            }

\'[^\n'][^\n']+\' { driver.error (*yylloc, "multi-character character constant.");
                    yylval->charval = '0';
                    return token::CHAR;
                  }

{CHAR} {
           if (strcmp(yytext,"\'\\n\'") == 0) { /* Hay que poner todos los caracteres especiales */
               yylval->charval = '\n';
               return token::CHAR;
           }
           yylval->charval = yytext[1]; 
           return token::CHAR;
       }

and { return token::AND; }
or  { return token::OR;  }
not { return token::NOT; }

div { return token::DIV; }
mod { return token::MOD; }



{ID} {
       yylval->strval = yytext;
       return token::ID;
     }


[+-/*(){}.,;] { return yy::GuavaParser::token_type (yytext[0]); } /* [+-*()/{}.,;] */

"["|"]" { return yy::GuavaParser::token_type (yytext[0]); }

"**" { return token::POW; }
"--" { return token::MINUSMINUS; }
"++" { return token::PLUSPLUS; }

":=" { return token::ASSIGN; }

">"   { yylval->subtok = 1; return token::COMPARISON; } 
"<"   { yylval->subtok = 2; return token::COMPARISON; }
"<="  { yylval->subtok = 3; return token::COMPARISON; }
">="  { yylval->subtok = 4; return token::COMPARISON; }
"="   { yylval->subtok = 5; return token::COMPARISON; }
"!="  { yylval->subtok = 6; return token::COMPARISON; }
"<=>" { return token::UFO; }

. driver.error (*yylloc, "invalid character");

%%

/*int main( int argc, char** argv )
{
    if (argc > 1) { 
        std::ifstream archivo(argv[1]);
        if (archivo.is_open()){
            FlexLexer* lexer = new yyFlexLexer(&archivo);
            while (lexer->yylex() != 0);
            exit(0);
        }
    }
    FlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0);
    return 0;
}*/

void GuavaDriver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}

void GuavaDriver::scan_end ()
{
  fclose (yyin);
}

