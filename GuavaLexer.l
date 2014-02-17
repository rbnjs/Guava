%{
int mylineno = 0;
%} 

%option noyywrap

DIGIT    [0-9]
ID       [A-Za-z][A-Za-z0-9]*
STRING   \"[^\n"]+\"
CHAR     \'[A-Za-z]i\'
WS      [ \t]+
%%

{WS} /* No hago nada con los espacios vacios */

"//.*\n"  {  ++mylineno; }

"/*"    { /* Acciones para el bloque de comentarios. */
        int c;

        while((c = yyinput()) != 0)
            {
            if(c == '\n')
                ++mylineno;

            else if(c == '*')
                {
                if((c = yyinput()) == '/')
                    break;
                else
                    unput(c);
                }
            }
        }

true|false { 
                std::cout << "booleano: " << YYText() << '\n'; 
           }

integer|real|boolean|character|string|void {
                                               std::cout << "tipo: " << YYText() << '\n';
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

\n   ++mylineno;

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
    FlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0)
        ;
    return 0;
    }
