%{
#include <iostream>
#include <fstream>

%} 

%option noyywrap yylineno

DIGIT    [0-9]
ID       [A-Za-z][A-Za-z0-9]*
STRING   \"[^\n"]+\"
CHAR     \'\\?[A-Za-z0-9]\'
WS      [ \t]+
%%

{WS} /* No hago nada con los espacios vacios */

"//.*\n"  /* No logro hacer que este funcione. */

"/*"    { /* Acciones para el bloque de comentarios. */
        int c;

        while((c = yyinput()) != 0)
            {

            if(c == '*')
                {
                if((c = yyinput()) == '/')
                    break;
                else
                    unput(c);
                }
            }
        }

true|false { 
                std::cout << "booleano: " << YYText() << " linea: " << lineno() << '\n'; 
           }

integer|real|boolean|character|string|void {
                                               std::cout << "tipo: " << YYText() << " linea: " << lineno() <<'\n';
                                           }

for      |
if       |
then     |
else     |
while    |
do       |
return   |
break    |
continue |
record   |
union    |
var      |
function |
print    |
read { std::cout << "palabra reservada: " << YYText() << '\n';
                                                                    }
{DIGIT}+ {
              std::cout << "entero: " << YYText() << '\n';
         }

{DIGIT}+"."{DIGIT}* {
                        std::cout << "flotante: " << YYText() << '\n';
                    }

{STRING} {
             std::cout << "string: " << YYText() << '\n';
         }

{CHAR} {
           std::cout << "caracter: " << YYText() << '\n';
       }

{ID} {
         std::cout << "identificador: " << YYText() << '\n';
     }

\n   

"+"|"-"|"*"|"/"|"div"|"mod"|"**"|"--"|"++"|"." {
                                                   std::cout << "operador numerico: " << YYText() << '\n';
                                               }

:= {
       std::cout << "asignacion: " << YYText() << '\n';
   }

">"|"<"|"<="|">="|"="|"!="|"<=>"|"and"|"or"|"not" {
                                                      std::cout << "operador booleano: " << YYText() << '\n';
                                                  }

"("|")" {
            std::cout << "parentesis: " << YYText() << '\n';
        }

"["|"]" { std::cout << "corchete: " << YYText() << '\n'; }

"{"|"}" { std::cout << "llave: " << YYText() << '\n'; }


","|";" { std::cout << "separador: " << YYText() << '\n'; }

. std::cout << "caracter no reconocido" << YYText() << '\n';

%%

int main( int argc, char** argv )
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
    while(lexer->yylex() != 0)
        ;
    return 0;
}
