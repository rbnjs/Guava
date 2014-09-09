/* A Bison parser, made by GNU Bison 2.6.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */


/* Line 278 of lalr1.cc  */
#line 39 "GuavaParser.cc"


#include "GuavaParser.hh"

/* User implementation prologue.  */


/* Line 284 of lalr1.cc  */
#line 48 "GuavaParser.cc"
/* Unqualified %code blocks.  */

/* Line 285 of lalr1.cc  */
#line 77 "GuavaParser.yy"

# include "GuavaDriver.hh"




/* Line 285 of lalr1.cc  */
#line 60 "GuavaParser.cc"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {

/* Line 352 of lalr1.cc  */
#line 156 "GuavaParser.cc"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  GuavaParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  GuavaParser::GuavaParser (GuavaDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  GuavaParser::~GuavaParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  GuavaParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  GuavaParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  GuavaParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  GuavaParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  GuavaParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  GuavaParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  GuavaParser::debug_level_type
  GuavaParser::debug_level () const
  {
    return yydebug_;
  }

  void
  GuavaParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  GuavaParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  GuavaParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  GuavaParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 538 of lalr1.cc  */
#line 24 "GuavaParser.yy"
{
  yylloc.begin.filename = yylloc.end.filename = &driver.file;
}

/* Line 538 of lalr1.cc  */
#line 352 "GuavaParser.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 663 of lalr1.cc  */
#line 153 "GuavaParser.yy"
    { //$$ = Program(*$1); 
                         }
    break;

  case 3:

/* Line 663 of lalr1.cc  */
#line 156 "GuavaParser.yy"
    { 
                     tabla_actual.push_front(&driver.tablaSimbolos);
                     driver.tablaSimbolos.enterScope(); 
                     offset_actual.push_front(0);
                 }
    break;

  case 4:

/* Line 663 of lalr1.cc  */
#line 162 "GuavaParser.yy"
    { (yyval.classBloquePrincipal) = new BloquePrincipal((yysemantic_stack_[(3) - (2)].classBloqueDeclare), (yysemantic_stack_[(3) - (3)].classLFunciones));
                                            if (!error_state && driver.print_table) {
                                                //std::cout << "Funciones: " << '\n';
                                                //driver.tablaSimbolos.show(0,identacion+ "  ");
                                                std::cout << "Variables globales: \n";
                                                driver.tablaSimbolos.show(1,identacion+ "  ");
                                            }
                                         }
    break;

  case 5:

/* Line 663 of lalr1.cc  */
#line 171 "GuavaParser.yy"
    { (yyval.classBloqueDeclare) = new BloqueDeclare(-1); 
                            }
    break;

  case 6:

/* Line 663 of lalr1.cc  */
#line 173 "GuavaParser.yy"
    { declare_scope = driver.tablaSimbolos.currentScope(); 
               }
    break;

  case 7:

/* Line 663 of lalr1.cc  */
#line 175 "GuavaParser.yy"
    { (yyval.classBloqueDeclare) = new BloqueDeclare(declare_scope); 
                                          }
    break;

  case 8:

/* Line 663 of lalr1.cc  */
#line 178 "GuavaParser.yy"
    { LVariables *tmp = new LVariables((yysemantic_stack_[(4) - (2)].classTipo),(yysemantic_stack_[(4) - (3)].classLVar));
                                                          (yysemantic_stack_[(4) - (1)].classLVariables)->listaVar = tmp;
                                                          (yyval.classLVariables) = (yysemantic_stack_[(4) - (1)].classLVariables);
                                                          insertar_simboloSimple((yysemantic_stack_[(4) - (3)].classLVar),(yysemantic_stack_[(4) - (2)].classTipo),std::string("var"),&driver,yylloc); 
                                                        }
    break;

  case 9:

/* Line 663 of lalr1.cc  */
#line 183 "GuavaParser.yy"
    { 
                                                          (yyval.classLVariables) = new LVariables((yysemantic_stack_[(3) - (1)].classTipo),(yysemantic_stack_[(3) - (2)].classLVar));
                                                          insertar_simboloSimple((yysemantic_stack_[(3) - (2)].classLVar),(yysemantic_stack_[(3) - (1)].classTipo),std::string("var"),&driver,yylloc); 
                                                        }
    break;

  case 10:

/* Line 663 of lalr1.cc  */
#line 187 "GuavaParser.yy"
    { 
                                                          insertar_simboloArreglo((yysemantic_stack_[(4) - (3)].classLVarArreglo),(yysemantic_stack_[(4) - (1)].classTipo),&driver,yylloc); 
                                                          (yyval.classLVariables) = new LVariables((yysemantic_stack_[(4) - (1)].classTipo),(yysemantic_stack_[(4) - (3)].classLVarArreglo));
                                                        }
    break;

  case 11:

/* Line 663 of lalr1.cc  */
#line 191 "GuavaParser.yy"
    { 
                                                          insertar_simboloArreglo((yysemantic_stack_[(5) - (4)].classLVarArreglo),(yysemantic_stack_[(5) - (2)].classTipo),&driver,yylloc); 
                                                          LVariables *tmp = new LVariables((yysemantic_stack_[(5) - (2)].classTipo), (yysemantic_stack_[(5) - (4)].classLVarArreglo));
                                                          (yysemantic_stack_[(5) - (1)].classLVariables)->listaVar = tmp;
                                                          (yyval.classLVariables) = (yysemantic_stack_[(5) - (1)].classLVariables);
                                                        }
    break;

  case 12:

/* Line 663 of lalr1.cc  */
#line 197 "GuavaParser.yy"
    {
                                                          TypeS* tmp = insertar_simboloArregloEstructura((yysemantic_stack_[(4) - (3)].classLVarArreglo),(yysemantic_stack_[(4) - (1)].classIdentificador)->identificador,&driver,yylloc);
                                                          LVariables *tmpLV = new LVariables(tmp,(yysemantic_stack_[(4) - (3)].classLVarArreglo));
                                                          (yyval.classLVariables) = tmpLV;
                                                        }
    break;

  case 13:

/* Line 663 of lalr1.cc  */
#line 202 "GuavaParser.yy"
    { 
                                                              TypeS* tmp = insertar_simboloArregloEstructura((yysemantic_stack_[(5) - (4)].classLVarArreglo),(yysemantic_stack_[(5) - (2)].classIdentificador)->identificador,&driver,yylloc);
                                                              LVariables *tmpLV = new LVariables(tmp,(yysemantic_stack_[(5) - (4)].classLVarArreglo));
                                                              (yysemantic_stack_[(5) - (1)].classLVariables)->listaVar = tmpLV;
                                                              (yyval.classLVariables) = (yysemantic_stack_[(5) - (1)].classLVariables);
                                                            }
    break;

  case 14:

/* Line 663 of lalr1.cc  */
#line 208 "GuavaParser.yy"
    { 
                                                          TypeS* tmp = insertar_simboloEstructura((yysemantic_stack_[(4) - (3)].classLVar),(yysemantic_stack_[(4) - (1)].classIdentificador)->identificador,std::string("unionType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,(yysemantic_stack_[(4) - (3)].classLVar)); 
                                                          (yyval.classLVariables) = tmpLV;
                                                        }
    break;

  case 15:

/* Line 663 of lalr1.cc  */
#line 213 "GuavaParser.yy"
    { 
                                                          TypeS* tmp = insertar_simboloEstructura((yysemantic_stack_[(5) - (4)].classLVar),(yysemantic_stack_[(5) - (2)].classIdentificador)->identificador,std::string("unionType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,(yysemantic_stack_[(5) - (4)].classLVar)); 
                                                          (yysemantic_stack_[(5) - (1)].classLVariables)->listaVar = tmpLV;
                                                          (yyval.classLVariables) = (yysemantic_stack_[(5) - (1)].classLVariables);
                                                        }
    break;

  case 16:

/* Line 663 of lalr1.cc  */
#line 219 "GuavaParser.yy"
    {
                                                          TypeS* tmp = insertar_simboloEstructura((yysemantic_stack_[(3) - (3)].classLVar),(yysemantic_stack_[(3) - (1)].classIdentificador)->identificador,std::string("recordType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,(yysemantic_stack_[(3) - (3)].classLVar)); 
                                                          (yyval.classLVariables) = tmpLV;
                                                        }
    break;

  case 17:

/* Line 663 of lalr1.cc  */
#line 224 "GuavaParser.yy"
    { 
                                                          TypeS* tmp = insertar_simboloEstructura((yysemantic_stack_[(5) - (4)].classLVar),(yysemantic_stack_[(5) - (2)].classIdentificador)->identificador,
                                                          std::string("recordType"),&driver,yylloc); 
                                                          LVariables *tmpLV = new LVariables(tmp,(yysemantic_stack_[(5) - (4)].classLVar)); 
                                                          (yysemantic_stack_[(5) - (1)].classLVariables)->listaVar = tmpLV;
                                                          (yyval.classLVariables) = (yysemantic_stack_[(5) - (1)].classLVariables);
                                                        }
    break;

  case 18:

/* Line 663 of lalr1.cc  */
#line 231 "GuavaParser.yy"
    {
                                                          LVariables * tmp = new LVariables((yysemantic_stack_[(3) - (2)].classUnion));
                                                          (yysemantic_stack_[(3) - (1)].classLVariables)->listaVar = tmp;
                                                          (yyval.classLVariables) = (yysemantic_stack_[(3) - (1)].classLVariables);
                                                        }
    break;

  case 19:

/* Line 663 of lalr1.cc  */
#line 236 "GuavaParser.yy"
    {
                                                          LVariables * tmp = new LVariables((yysemantic_stack_[(3) - (2)].classRecord));
                                                          (yysemantic_stack_[(3) - (1)].classLVariables)->listaVar = tmp;
                                                          (yyval.classLVariables) = (yysemantic_stack_[(3) - (1)].classLVariables);
                                                        }
    break;

  case 20:

/* Line 663 of lalr1.cc  */
#line 241 "GuavaParser.yy"
    {
                                                          (yyval.classLVariables) = new LVariables((yysemantic_stack_[(2) - (1)].classUnion));
                                                        }
    break;

  case 21:

/* Line 663 of lalr1.cc  */
#line 244 "GuavaParser.yy"
    {
                                                          (yyval.classLVariables) = new LVariables((yysemantic_stack_[(2) - (1)].classRecord));
                                                        }
    break;

  case 22:

/* Line 663 of lalr1.cc  */
#line 248 "GuavaParser.yy"
    {
                                                          /*Error en la declaracion del tipo y modo de la variable*/
                                                          (yyval.classLVariables) = new LVariables();
                                                        }
    break;

  case 23:

/* Line 663 of lalr1.cc  */
#line 253 "GuavaParser.yy"
    { 
                                verificar_existencia_tipo((yysemantic_stack_[(3) - (2)].classIdentificador), &driver,yylloc,true);
                               }
    break;

  case 24:

/* Line 663 of lalr1.cc  */
#line 256 "GuavaParser.yy"
    { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                std::string identificador = (yysemantic_stack_[(6) - (2)].classIdentificador)->identificador;
                                                if (!error_state && driver.print_table) {
                                                    identacion.erase(0,2);
                                                    std::cout << identacion << "Union " << identificador << " {\n";
                                                    tabla->show(tabla->currentScope(),identacion+ "  "); 
                                                    std::cout << identacion <<"}\n";
                                                }
                                                offset_actual.pop_front();
                                                tabla_actual.pop_front();
                                             }
    break;

  case 25:

/* Line 663 of lalr1.cc  */
#line 269 "GuavaParser.yy"
    {
                                    verificar_existencia_tipo((yysemantic_stack_[(3) - (2)].classIdentificador),&driver,yylloc, false);
                                }
    break;

  case 26:

/* Line 663 of lalr1.cc  */
#line 272 "GuavaParser.yy"
    { 
                                                GuavaSymTable* tabla = tabla_actual.front();
                                                if (!error_state && driver.print_table) {
                                                std::cout << identacion << "Union " << (yysemantic_stack_[(6) - (2)].classIdentificador)->identificador << " {\n";
                                                tabla->show(tabla->currentScope(),identacion+ "  "); 
                                                std::cout << identacion <<"}\n";
                                                identacion.erase(0,2);
                                               }
                                                offset_actual.pop_front();
                                                tabla_actual.pop_front();
                                             }
    break;

  case 27:

/* Line 663 of lalr1.cc  */
#line 284 "GuavaParser.yy"
    { 
                                LVar *tmp = new LVar();
                                tmp->append(*(yysemantic_stack_[(1) - (1)].classIdentificador));
                                tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                (yyval.classLVar) = tmp;
                              }
    break;

  case 28:

/* Line 663 of lalr1.cc  */
#line 290 "GuavaParser.yy"
    { 
                                (yysemantic_stack_[(3) - (3)].classIdentificador)->line = yylloc.begin.line;
                                (yysemantic_stack_[(3) - (3)].classIdentificador)->column = yylloc.begin.column;
                                (yysemantic_stack_[(3) - (1)].classLVar)->append(*(yysemantic_stack_[(3) - (3)].classIdentificador));
                                (yyval.classLVar) = (yysemantic_stack_[(3) - (1)].classLVar);
                              }
    break;

  case 29:

/* Line 663 of lalr1.cc  */
#line 297 "GuavaParser.yy"
    { LVar *tmp = new LVar ();
                                tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                (yyval.classLVar) = tmp;
                              }
    break;

  case 30:

/* Line 663 of lalr1.cc  */
#line 301 "GuavaParser.yy"
    { (yyval.classLVar) = (yysemantic_stack_[(3) - (1)].classLVar); }
    break;

  case 31:

/* Line 663 of lalr1.cc  */
#line 303 "GuavaParser.yy"
    { LVarArreglo* tmp = new LVarArreglo(*(yysemantic_stack_[(2) - (1)].classIdentificador),*(yysemantic_stack_[(2) - (2)].classLCorchetes));
                                                         tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                         (yyval.classLVarArreglo) = tmp;
                                                       }
    break;

  case 32:

/* Line 663 of lalr1.cc  */
#line 307 "GuavaParser.yy"
    { (yysemantic_stack_[(4) - (1)].classLVarArreglo)->append(*(yysemantic_stack_[(4) - (3)].classIdentificador),*(yysemantic_stack_[(4) - (4)].classLCorchetes));
                                                         (yyval.classLVarArreglo) = (yysemantic_stack_[(4) - (1)].classLVarArreglo);
                                                       }
    break;

  case 33:

/* Line 663 of lalr1.cc  */
#line 311 "GuavaParser.yy"
    { LVarArreglo* tmp = new LVarArreglo();
                                                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                        (yyval.classLVarArreglo) = tmp;
                                                       }
    break;

  case 34:

/* Line 663 of lalr1.cc  */
#line 315 "GuavaParser.yy"
    {
                                                        LVarArreglo* tmp = new LVarArreglo();
                                                        (yyval.classLVarArreglo) = tmp;
                                                       }
    break;

  case 35:

/* Line 663 of lalr1.cc  */
#line 322 "GuavaParser.yy"
    { 
                                        LCorchetes *tmp =  new LCorchetes(false);
                                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                        tmp->append((yysemantic_stack_[(3) - (2)].intval));
                                        (yyval.classLCorchetes) = tmp;
                                       }
    break;

  case 36:

/* Line 663 of lalr1.cc  */
#line 328 "GuavaParser.yy"
    { 
                                         (yysemantic_stack_[(4) - (1)].classLCorchetes)->append((yysemantic_stack_[(4) - (3)].intval));
                                         (yyval.classLCorchetes) = (yysemantic_stack_[(4) - (1)].classLCorchetes); 
                                       }
    break;

  case 37:

/* Line 663 of lalr1.cc  */
#line 333 "GuavaParser.yy"
    {/*Definicion erronea del tamano del arreglo*/
                                      (yyval.classLCorchetes) = new LCorchetes(true);
                                    }
    break;

  case 38:

/* Line 663 of lalr1.cc  */
#line 336 "GuavaParser.yy"
    {
                                      (yyval.classLCorchetes) = new LCorchetes(true);
                                     }
    break;

  case 39:

/* Line 663 of lalr1.cc  */
#line 340 "GuavaParser.yy"
    { LCorchetesExp* tmp = new LCorchetesExp();
                                           tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                           if( (yysemantic_stack_[(3) - (2)].classExp) != 0 && (yysemantic_stack_[(3) - (2)].classExp)->get_tipo() == TypeInt::Instance()) {
                                                tmp->tipo = (yysemantic_stack_[(3) - (2)].classExp)->get_tipo();
                                           }
                                            else {
                                                std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(3) - (2)].classExp)->get_tipo()->get_name());
                                                driver.error(yylloc,msg);
                                                tmp->tipo = TypeError::Instance();
                                           }
                                           tmp->append((yysemantic_stack_[(3) - (2)].classExp));
                                           (yyval.classLCorchetesExp) = tmp;
                                         }
    break;

  case 40:

/* Line 663 of lalr1.cc  */
#line 353 "GuavaParser.yy"
    { 
                                           if ((yysemantic_stack_[(4) - (3)].classExp) != 0 && (yysemantic_stack_[(4) - (3)].classExp)->get_tipo() != TypeInt::Instance()){
                                               std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(4) - (3)].classExp)->get_tipo()->get_name());
                                               driver.error(yylloc,msg);
                                               (yysemantic_stack_[(4) - (1)].classLCorchetesExp)->tipo = TypeError::Instance();
                                           }
                                           (yysemantic_stack_[(4) - (1)].classLCorchetesExp)->append((yysemantic_stack_[(4) - (3)].classExp));
                                           (yyval.classLCorchetesExp) = (yysemantic_stack_[(4) - (1)].classLCorchetesExp);
                                         }
    break;

  case 41:

/* Line 663 of lalr1.cc  */
#line 362 "GuavaParser.yy"
    {
                                            LCorchetesExp* tmp = new LCorchetesExp();
                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            tmp->tipo = TypeError::Instance();
                                         }
    break;

  case 42:

/* Line 663 of lalr1.cc  */
#line 367 "GuavaParser.yy"
    {
                                                LCorchetesExp* tmp = new LCorchetesExp();
                                                tmp->tipo = TypeError::Instance();
                                            }
    break;

  case 43:

/* Line 663 of lalr1.cc  */
#line 373 "GuavaParser.yy"
    { (yyval.classLFunciones) = new LFunciones((yysemantic_stack_[(1) - (1)].classFuncion),0);
                                           }
    break;

  case 44:

/* Line 663 of lalr1.cc  */
#line 375 "GuavaParser.yy"
    { 
                                             LFunciones* main_ = new LFunciones((yysemantic_stack_[(2) - (2)].classFuncion),0);
                                             (yysemantic_stack_[(2) - (1)].classLFunciones)->lista = main_;
                                             (yyval.classLFunciones) = (yysemantic_stack_[(2) - (1)].classLFunciones);
                                           }
    break;

  case 45:

/* Line 663 of lalr1.cc  */
#line 381 "GuavaParser.yy"
    { (yyval.classLFunciones) = new LFunciones((yysemantic_stack_[(1) - (1)].classFuncion),0);
                                           }
    break;

  case 46:

/* Line 663 of lalr1.cc  */
#line 383 "GuavaParser.yy"
    { 
                                             LFunciones* func = new LFunciones((yysemantic_stack_[(2) - (2)].classFuncion),0);
                                             (yysemantic_stack_[(2) - (1)].classLFunciones)->lista = func;
                                             (yyval.classLFunciones) = (yysemantic_stack_[(2) - (1)].classLFunciones);
                                           }
    break;

  case 47:

/* Line 663 of lalr1.cc  */
#line 389 "GuavaParser.yy"
    { current_scope = driver.tablaSimbolos.enterScope(); 
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   int line = yylloc.begin.line;
                                                   int column = yylloc.begin.column;
                                                   driver.tablaSimbolos.insert(std::string("main"),std::string("function"),
                                                                                0,tipo,line,column, current_scope);
                                                   identacion += "  ";
                                                   offset_actual.push_front(0);
                                                 }
    break;

  case 48:

/* Line 663 of lalr1.cc  */
#line 398 "GuavaParser.yy"
    { LParam* lp = new LParam();
                                                   TypeS* tipo = new TypeFunction(TypeVoid::Instance(),std::list<TypeS*>());
                                                   Funcion* tmp = new  Funcion(tipo, new Identificador(std::string("main")),lp,(yysemantic_stack_[(10) - (8)].classBloqueDeclare),(yysemantic_stack_[(10) - (9)].classListaInstrucciones)); 
                                                   tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                   (yyval.classFuncion) = tmp;
                                                   if (!error_state && driver.print_table) {
                                                       std::cout <<  "main {\n"; 
                                                       std::cout << "Parametros y variables:\n";
                                                       driver.tablaSimbolos.show(current_scope,identacion);
                                                       driver.tablaSimbolos.exitScope(); 
                                                       std::cout << "}\n";
                                                       identacion.erase(0,2);
                                                   }
                                                   if (driver.print_tree){
                                                        (yysemantic_stack_[(10) - (9)].classListaInstrucciones)->show("");
                                                   }
                                                 }
    break;

  case 49:

/* Line 663 of lalr1.cc  */
#line 417 "GuavaParser.yy"
    { current_scope = driver.tablaSimbolos.enterScope();
                                                         identacion += "  ";
                                                       }
    break;

  case 50:

/* Line 663 of lalr1.cc  */
#line 420 "GuavaParser.yy"
    { TypeS* t = TypeError::Instance();
                                                         LParam* lp = new LParam();
                                                         (yyval.classFuncion) = new Funcion(t, new Identificador(std::string("main")),lp,(yysemantic_stack_[(11) - (9)].classBloqueDeclare),(yysemantic_stack_[(11) - (10)].classListaInstrucciones));
                                                       }
    break;

  case 51:

/* Line 663 of lalr1.cc  */
#line 426 "GuavaParser.yy"
    { current_scope = driver.tablaSimbolos.enterScope();
                                            offset_actual.push_front(0);
                                          }
    break;

  case 52:

/* Line 663 of lalr1.cc  */
#line 429 "GuavaParser.yy"
    { 
                                                 insertar_funcion((yysemantic_stack_[(6) - (2)].classTipo),(yysemantic_stack_[(6) - (3)].classIdentificador),(yysemantic_stack_[(6) - (6)].classLParam),&driver,current_scope,yylloc); 
                                                 identacion += "  ";
                                               }
    break;

  case 53:

/* Line 663 of lalr1.cc  */
#line 433 "GuavaParser.yy"
    { TypeS* tipo = new TypeFunction((yysemantic_stack_[(12) - (2)].classTipo)->get_tipo(),(yysemantic_stack_[(12) - (6)].classLParam)->get_tipos());
                                                                               std::list<Instruccion*> lretorno = (yysemantic_stack_[(12) - (11)].classListaInstrucciones)->obtener_return();
                                                                               Funcion* tmp;
                                                                               if (lretorno.size() == 0) {
                                                                                    funcion_sin_return((yysemantic_stack_[(12) - (3)].classIdentificador),&driver,yylloc); 
                                                                               } else{
                                                                                    if ( verificar_return((yysemantic_stack_[(12) - (3)].classIdentificador),(yysemantic_stack_[(12) - (2)].classTipo),lretorno,&driver) ){
                                                                                        tmp = new Funcion(tipo,(yysemantic_stack_[(12) - (3)].classIdentificador),(yysemantic_stack_[(12) - (6)].classLParam),(yysemantic_stack_[(12) - (10)].classBloqueDeclare),(yysemantic_stack_[(12) - (11)].classListaInstrucciones));
                                                                                    } else {
                                                                                        tmp = new Funcion();
                                                                                    }
                                                                               }
                                                                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                               (yyval.classFuncion) = tmp;
                                                                               if (!error_state && driver.print_table) {
                                                                                    std::cout << (yysemantic_stack_[(12) - (3)].classIdentificador)->identificador << "{\n";
                                                                                    std::cout << "Parametros y variables:\n";
                                                                                    driver.tablaSimbolos.show(current_scope,identacion);
                                                                                    std::cout << "}\n";
                                                                                    driver.tablaSimbolos.exitScope();
                                                                                                identacion.erase(0,2);
                                                                               }
                                                                               if (driver.print_tree){
                                                                                    (yysemantic_stack_[(12) - (10)].classBloqueDeclare)->show("");
                                                                               }
                                                                            }
    break;

  case 54:

/* Line 663 of lalr1.cc  */
#line 460 "GuavaParser.yy"
    { current_scope = driver.tablaSimbolos.enterScope(); 
                                                offset_actual.push_front(0);
                                              }
    break;

  case 55:

/* Line 663 of lalr1.cc  */
#line 463 "GuavaParser.yy"
    {  
                                                      TypeS* v = TypeVoid::Instance();
                                                      insertar_funcion(v,(yysemantic_stack_[(6) - (3)].classIdentificador),(yysemantic_stack_[(6) - (6)].classLParam),&driver,current_scope,yylloc); 
                                                      identacion += "  ";
                                                    }
    break;

  case 56:

/* Line 663 of lalr1.cc  */
#line 468 "GuavaParser.yy"
    {  TypeS* tipo = new TypeFunction(TypeVoid::Instance(),(yysemantic_stack_[(12) - (6)].classLParam)->get_tipos());
                                                                                   Funcion* tmp = new Funcion(tipo,(yysemantic_stack_[(12) - (3)].classIdentificador),(yysemantic_stack_[(12) - (6)].classLParam),(yysemantic_stack_[(12) - (10)].classBloqueDeclare),(yysemantic_stack_[(12) - (11)].classListaInstrucciones));
                                                                                   tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                                   (yyval.classFuncion) = tmp;
                                                                                   if (!error_state && driver.print_table) {
                                                                                        std::cout << (yysemantic_stack_[(12) - (3)].classIdentificador)->identificador << "{\n";
                                                                                        std::cout << "Parametros y variables:\n";
                                                                                        driver.tablaSimbolos.show(current_scope,identacion);
                                                                                        std::cout << "}\n";
                                                                                        driver.tablaSimbolos.exitScope();
                                                                                        identacion.erase(0,2);
                                                                                    }
                                                                                    if (driver.print_tree){
                                                                                        (yysemantic_stack_[(12) - (10)].classBloqueDeclare)->show("");
                                                                                    }
                                                                                }
    break;

  case 57:

/* Line 663 of lalr1.cc  */
#line 487 "GuavaParser.yy"
    { current_scope =  driver.tablaSimbolos.enterScope(); 
                                                         identacion += "  ";
                                                       }
    break;

  case 58:

/* Line 663 of lalr1.cc  */
#line 490 "GuavaParser.yy"
    { (yyval.classFuncion) = new Funcion(); 
                                                                                                }
    break;

  case 59:

/* Line 663 of lalr1.cc  */
#line 494 "GuavaParser.yy"
    { current_scope = driver.tablaSimbolos.enterScope(); 
                                                              identacion += "  ";
                                                            }
    break;

  case 60:

/* Line 663 of lalr1.cc  */
#line 497 "GuavaParser.yy"
    {  (yyval.classFuncion) = new Funcion();
                                                                                           }
    break;

  case 61:

/* Line 663 of lalr1.cc  */
#line 500 "GuavaParser.yy"
    { LParam* tmp = new LParam(); 
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               (yyval.classLParam) = tmp;
                             }
    break;

  case 62:

/* Line 663 of lalr1.cc  */
#line 504 "GuavaParser.yy"
    { (yyval.classLParam) = (yysemantic_stack_[(1) - (1)].classLParam); 
                             }
    break;

  case 63:

/* Line 663 of lalr1.cc  */
#line 507 "GuavaParser.yy"
    { LParam* tmp = new LParam(); 
                                            tmp->append((yysemantic_stack_[(2) - (1)].classTipo),(yysemantic_stack_[(2) - (2)].classIdentificador));
                                            tmp->appendTipo((yysemantic_stack_[(2) - (1)].classTipo));
                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            (yyval.classLParam) = tmp;
                                            insertar_simboloSimple((yysemantic_stack_[(2) - (2)].classIdentificador),(yysemantic_stack_[(2) - (1)].classTipo),std::string("param"),&driver,yylloc);
                                          }
    break;

  case 64:

/* Line 663 of lalr1.cc  */
#line 514 "GuavaParser.yy"
    { LParam* tmp = new LParam(); 
                                            tmp->append((yysemantic_stack_[(3) - (1)].classTipo),(yysemantic_stack_[(3) - (3)].classIdentificador));
                                            tmp->appendTipo((yysemantic_stack_[(3) - (1)].classTipo));
                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            (yyval.classLParam) = tmp;
                                            insertar_simboloSimple((yysemantic_stack_[(3) - (3)].classIdentificador),(yysemantic_stack_[(3) - (1)].classTipo),std::string("param"),&driver,yylloc); // llamada a otra funcion
                                          }
    break;

  case 65:

/* Line 663 of lalr1.cc  */
#line 521 "GuavaParser.yy"
    { 
                                            (yysemantic_stack_[(4) - (1)].classLParam)->append((yysemantic_stack_[(4) - (3)].classTipo),(yysemantic_stack_[(4) - (4)].classIdentificador));
                                            (yysemantic_stack_[(4) - (1)].classLParam)->appendTipo((yysemantic_stack_[(4) - (3)].classTipo));
                                            (yyval.classLParam) = (yysemantic_stack_[(4) - (1)].classLParam);
                                            insertar_simboloSimple((yysemantic_stack_[(4) - (4)].classIdentificador),(yysemantic_stack_[(4) - (3)].classTipo),std::string("param"),&driver,yylloc);
                                          }
    break;

  case 66:

/* Line 663 of lalr1.cc  */
#line 527 "GuavaParser.yy"
    { 
                                                          (yysemantic_stack_[(5) - (1)].classLParam)->append((yysemantic_stack_[(5) - (3)].classTipo),(yysemantic_stack_[(5) - (5)].classIdentificador));
                                                          (yysemantic_stack_[(5) - (1)].classLParam)->appendTipo((yysemantic_stack_[(5) - (3)].classTipo));
                                                          (yyval.classLParam) = (yysemantic_stack_[(5) - (1)].classLParam);
                                                          insertar_simboloSimple((yysemantic_stack_[(5) - (5)].classIdentificador),(yysemantic_stack_[(5) - (3)].classTipo),std::string("param"),&driver,yylloc);
                                                        }
    break;

  case 67:

/* Line 663 of lalr1.cc  */
#line 533 "GuavaParser.yy"
    { (yyval.classLParam) = new LParam();    }
    break;

  case 68:

/* Line 663 of lalr1.cc  */
#line 534 "GuavaParser.yy"
    { (yyval.classLParam) = new LParam();    }
    break;

  case 69:

/* Line 663 of lalr1.cc  */
#line 535 "GuavaParser.yy"
    { (yyval.classLParam) = new LParam();    }
    break;

  case 70:

/* Line 663 of lalr1.cc  */
#line 536 "GuavaParser.yy"
    { (yyval.classLParam) = new LParam();    }
    break;

  case 71:

/* Line 663 of lalr1.cc  */
#line 539 "GuavaParser.yy"
    { 
                                                            (yyval.classListaInstrucciones) = new ListaInstrucciones(); 
                                                        }
    break;

  case 72:

/* Line 663 of lalr1.cc  */
#line 542 "GuavaParser.yy"
    { 
                                                          ListaInstrucciones * result;
                                                          if ( (yysemantic_stack_[(3) - (1)].classListaInstrucciones)->get_tipo() == TypeError::Instance()
                                                               || (yysemantic_stack_[(3) - (2)].classInstruccion)->get_tipo() == TypeError::Instance()) {
                                                             result = new ListaInstrucciones((yysemantic_stack_[(3) - (2)].classInstruccion),(yysemantic_stack_[(3) - (1)].classListaInstrucciones)); 
                                                             result->tipo = TypeError::Instance();
                                                          }
                                                          else {
                                                             result = new ListaInstrucciones((yysemantic_stack_[(3) - (2)].classInstruccion),(yysemantic_stack_[(3) - (1)].classListaInstrucciones)); 
                                                          }
                                                          (yyval.classListaInstrucciones) = result;
                                                        }
    break;

  case 73:

/* Line 663 of lalr1.cc  */
#line 554 "GuavaParser.yy"
    {
                                                          ListaInstrucciones * result;
                                                          if ( (yysemantic_stack_[(2) - (1)].classListaInstrucciones)->get_tipo() == TypeError::Instance()
                                                               || (yysemantic_stack_[(2) - (2)].classInstruccion)->get_tipo() == TypeError::Instance()) {
                                                            result = new ListaInstrucciones((yysemantic_stack_[(2) - (2)].classInstruccion),(yysemantic_stack_[(2) - (1)].classListaInstrucciones)); 
                                                            result->tipo = TypeError::Instance();
                                                          }
                                                          else {
                                                            result = new ListaInstrucciones((yysemantic_stack_[(2) - (2)].classInstruccion),(yysemantic_stack_[(2) - (1)].classListaInstrucciones)); 
                                                          }
                                                          (yyval.classListaInstrucciones) = result;
                                                        }
    break;

  case 74:

/* Line 663 of lalr1.cc  */
#line 567 "GuavaParser.yy"
    { 
                            }
    break;

  case 75:

/* Line 663 of lalr1.cc  */
#line 569 "GuavaParser.yy"
    { 
                            }
    break;

  case 76:

/* Line 663 of lalr1.cc  */
#line 571 "GuavaParser.yy"
    {
                                         Symbol *id;
                                         PlusMinus *result;
                                         result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                         if ( (id = variable_no_declarada((yysemantic_stack_[(2) - (2)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus((yysemantic_stack_[(2) - (2)].classIdentificador),0);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             (yyval.classInstruccion) = result;
                                         } 
                                         else {
                                             (yyval.classInstruccion) = new PlusMinus();
                                         }
                                       }
    break;

  case 77:

/* Line 663 of lalr1.cc  */
#line 596 "GuavaParser.yy"
    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                         if ( (id = variable_no_declarada((yysemantic_stack_[(2) - (1)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus((yysemantic_stack_[(2) - (1)].classIdentificador),1);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             (yyval.classInstruccion) = result;
                                         } 
                                         else {
                                             (yyval.classInstruccion) = new PlusMinus();
                                         }
                                       }
    break;

  case 78:

/* Line 663 of lalr1.cc  */
#line 621 "GuavaParser.yy"
    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                         if ( (id = variable_no_declarada((yysemantic_stack_[(2) - (2)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus((yysemantic_stack_[(2) - (2)].classIdentificador),2);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             (yyval.classInstruccion) = result;
                                         } 
                                         else {
                                             (yyval.classInstruccion) = new PlusMinus();
                                         }
                                       }
    break;

  case 79:

/* Line 663 of lalr1.cc  */
#line 646 "GuavaParser.yy"
    { 
                                         Symbol *id;
                                         PlusMinus *result;
                                         result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                         if ( (id = variable_no_declarada((yysemantic_stack_[(2) - (1)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                             TypeS* tipo = obtener_tipo_simbolo(id);
                                             if (tipo == TypeInt::Instance()){
                                                 result = new PlusMinus((yysemantic_stack_[(2) - (1)].classIdentificador),3);
                                             } 
                                             else {
                                                 result = new PlusMinus();
                                                 std::string msg;
                                                 if (tipo == 0){
                                                     msg = mensaje_error_tipos("null","integer");
                                                 } else{
                                                     msg = mensaje_error_tipos(tipo->get_name(),"integer");
                                                 }
                                                 driver.error(yylloc,msg);
                                             }
                                             (yyval.classInstruccion) = result;
                                         } 
                                         else {
                                             (yyval.classInstruccion) = new PlusMinus();
                                         }
                                       }
    break;

  case 80:

/* Line 663 of lalr1.cc  */
#line 671 "GuavaParser.yy"
    { 
                            }
    break;

  case 81:

/* Line 663 of lalr1.cc  */
#line 673 "GuavaParser.yy"
    {
                              ContinueBreak* tmp = new ContinueBreak(0);
                              tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                              (yyval.classInstruccion) = tmp;
                            }
    break;

  case 82:

/* Line 663 of lalr1.cc  */
#line 678 "GuavaParser.yy"
    {
                              ContinueBreak* tmp = new ContinueBreak(1);
                              tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                              (yyval.classInstruccion) = tmp;
                            }
    break;

  case 83:

/* Line 663 of lalr1.cc  */
#line 685 "GuavaParser.yy"
    {/*Error en la especificacion del incremento o decremento*/
                                         (yyval.classInstruccion) = new Error();
                                       }
    break;

  case 84:

/* Line 663 of lalr1.cc  */
#line 688 "GuavaParser.yy"
    {/*Error en la especificacion del incremento o decremento*/
                                         (yyval.classInstruccion) = new Error();
                                       }
    break;

  case 85:

/* Line 663 of lalr1.cc  */
#line 691 "GuavaParser.yy"
    {
                                       }
    break;

  case 86:

/* Line 663 of lalr1.cc  */
#line 696 "GuavaParser.yy"
    { 
                             }
    break;

  case 87:

/* Line 663 of lalr1.cc  */
#line 698 "GuavaParser.yy"
    { 
                             }
    break;

  case 88:

/* Line 663 of lalr1.cc  */
#line 700 "GuavaParser.yy"
    { 
                             }
    break;

  case 89:

/* Line 663 of lalr1.cc  */
#line 703 "GuavaParser.yy"
    { /*Caso en el que alguno de los dos tipos sea de tipo error.*/
                                 Asignacion* tmp;
                                 if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeError::Instance() ||
                                     (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeError::Instance()){
                                     if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos((yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),"null");
                                        driver.error(yylloc, msg);
                                     } else if ((yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos((yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),"null");
                                        driver.error(yylloc, msg);
                                     } else {
                                        std::string msg = mensaje_error_tipos((yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(), (yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                        driver.error(yylloc, msg);
                                     }
                                    tmp = new Asignacion();
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    (yyval.classAsignacion) = tmp;
                                 } else {
                                    tmp = new Asignacion((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp));
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    (yyval.classAsignacion) = tmp;
                                 }
                               }
    break;

  case 90:

/* Line 663 of lalr1.cc  */
#line 727 "GuavaParser.yy"
    {
                                 (yyval.classAsignacion) = new Asignacion();
                               }
    break;

  case 91:

/* Line 663 of lalr1.cc  */
#line 730 "GuavaParser.yy"
    {
                                 (yyval.classAsignacion) = new Asignacion();
                               }
    break;

  case 92:

/* Line 663 of lalr1.cc  */
#line 735 "GuavaParser.yy"
    {
                                    EntradaSalida* tmp = new EntradaSalida(0,(yysemantic_stack_[(4) - (3)].classExp));  
                                    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos("type","error");
                                        driver.error(yylloc,msg);
                                    }
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    (yyval.classEntradaSalida) = tmp;
                                  }
    break;

  case 93:

/* Line 663 of lalr1.cc  */
#line 744 "GuavaParser.yy"
    { 
                                    EntradaSalida* tmp = new EntradaSalida(1,(yysemantic_stack_[(4) - (3)].classExp));  
                                    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                        std::string msg = mensaje_error_tipos("type","error");
                                        driver.error(yylloc,msg);
                                    }
                                    tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                    (yyval.classEntradaSalida) = tmp;
                                  }
    break;

  case 94:

/* Line 663 of lalr1.cc  */
#line 754 "GuavaParser.yy"
    { 
			    (yyval.classRetorno) = new Retorno(0,yylloc.begin.line,yylloc.begin.column); 
                      }
    break;

  case 95:

/* Line 663 of lalr1.cc  */
#line 757 "GuavaParser.yy"
    {
			    Retorno* tmp =  new Retorno((yysemantic_stack_[(2) - (2)].classExp),yylloc.begin.line, yylloc.begin.column); 
			    if (tmp->get_tipo() == TypeError::Instance() || tmp->get_tipo() == 0){
                                std::string msg = mensaje_error_tipos("type","error");
                                driver.error(yylloc,msg);
			    }
                            (yyval.classRetorno) = tmp;
                          }
    break;

  case 96:

/* Line 663 of lalr1.cc  */
#line 766 "GuavaParser.yy"
    { 
                                                                      variable_no_declarada((yysemantic_stack_[(9) - (3)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front()); 
                                                                      driver.tablaSimbolos.enterScope();   
                                                                      identacion += "  "; 
                                                                    }
    break;

  case 97:

/* Line 663 of lalr1.cc  */
#line 772 "GuavaParser.yy"
    {  ErrorLoopFor* asign_exp = (yysemantic_stack_[(13) - (7)].classErrorLoopFor);
                                                                        LoopFor* tmp;
                                                                            if (asign_exp->is_error()
                                                                                    || (yysemantic_stack_[(13) - (3)].classIdentificador)->get_tipo() == TypeError::Instance()
                                                                                    || (yysemantic_stack_[(13) - (5)].classExp)->get_tipo() == TypeError::Instance()
                                                                               ){
                                                                                tmp = new LoopFor();
                                                                                std::string msg = mensaje_error_tipos("error","void");
                                                                                driver.error(yylloc,msg);
                                                                            } else{
                                                                                if (asign_exp->exp != 0){
                                                                                    tmp = new 
                                                                                        LoopFor((yysemantic_stack_[(13) - (3)].classIdentificador), (yysemantic_stack_[(13) - (5)].classExp),asign_exp->exp,(yysemantic_stack_[(13) - (11)].classBloqueDeclare),(yysemantic_stack_[(13) - (12)].classListaInstrucciones));
                                                                                    tmp->tipo = TypeVoid::Instance();
                                                                                } else {
                                                                                    tmp = new 
                                                                                        LoopFor((yysemantic_stack_[(13) - (3)].classIdentificador), (yysemantic_stack_[(13) - (5)].classExp),asign_exp->asign,(yysemantic_stack_[(13) - (11)].classBloqueDeclare),(yysemantic_stack_[(13) - (12)].classListaInstrucciones));
                                                                                    tmp->tipo = TypeVoid::Instance();
                                                                                }
                                                                            }
                                                                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                            (yyval.classLoopFor) = tmp;
                                                                            if (!error_state &&  driver.print_table ) {
                                                                                std::cout << identacion << "for {\n";
                                                                                int cscope = driver.tablaSimbolos.currentScope();
                                                                                driver.tablaSimbolos.show(cscope,identacion+ "  ");
                                                                                std::cout << identacion << "}\n";
                                                                                driver.tablaSimbolos.exitScope();
                                                                                identacion.erase(0,2);
                                                                            }
                                                                         }
    break;

  case 98:

/* Line 663 of lalr1.cc  */
#line 804 "GuavaParser.yy"
    { 
                                                            }
    break;

  case 99:

/* Line 663 of lalr1.cc  */
#line 806 "GuavaParser.yy"
    { 
                                                                   (yyval.classLoopFor) = new LoopFor();
                                                                 }
    break;

  case 100:

/* Line 663 of lalr1.cc  */
#line 809 "GuavaParser.yy"
    { 
                                                                     variable_no_declarada((yysemantic_stack_[(9) - (3)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front());
                                                                   }
    break;

  case 101:

/* Line 663 of lalr1.cc  */
#line 812 "GuavaParser.yy"
    { 
                                                                           (yyval.classLoopFor) = new LoopFor();
                                                                         }
    break;

  case 102:

/* Line 663 of lalr1.cc  */
#line 820 "GuavaParser.yy"
    {
                            (yyval.classErrorLoopFor) = new ErrorLoopFor((yysemantic_stack_[(1) - (1)].classAsignacion));
                          }
    break;

  case 103:

/* Line 663 of lalr1.cc  */
#line 823 "GuavaParser.yy"
    {
                            (yyval.classErrorLoopFor) = new ErrorLoopFor((yysemantic_stack_[(1) - (1)].classExp));
                          }
    break;

  case 104:

/* Line 663 of lalr1.cc  */
#line 826 "GuavaParser.yy"
    {
                            (yyval.classErrorLoopFor) = new ErrorLoopFor();
                          }
    break;

  case 105:

/* Line 663 of lalr1.cc  */
#line 830 "GuavaParser.yy"
    { 
                                                 driver.tablaSimbolos.enterScope();   
                                                 identacion += "  ";
                                               }
    break;

  case 106:

/* Line 663 of lalr1.cc  */
#line 834 "GuavaParser.yy"
    { 
                                                             LoopWhile* result;
                                                             ErrorBoolExp* exp_bool = (yysemantic_stack_[(10) - (3)].classErrorBoolExp);
                                                             if (exp_bool->get_error()
                                                                 || exp_bool->get_tipo() == TypeError::Instance()
                                                                 || (yysemantic_stack_[(10) - (9)].classListaInstrucciones)->get_tipo() == TypeError::Instance()){
                                                                 result = new LoopWhile();
                                                                 std::string msg = mensaje_error_tipos("error","void");
                                                                 driver.error(yylloc,msg);
                                                             } 
                                                             else {
                                                                 result = new LoopWhile(exp_bool->exp,(yysemantic_stack_[(10) - (8)].classBloqueDeclare),(yysemantic_stack_[(10) - (9)].classListaInstrucciones));
                                                             }
                                                             result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                             (yyval.classLoopWhile) = result;
                                                             if (!error_state && driver.print_table) {
                                                                 std::cout << identacion << "while {\n"; 
                                                                 driver.tablaSimbolos.show(driver.tablaSimbolos.currentScope(),identacion+"  ");
                                                                 std::cout << identacion << "}\n ";
                                                                 driver.tablaSimbolos.exitScope();
                                                                 identacion.erase(0,2);
                                                             }
                                                           }
    break;

  case 107:

/* Line 663 of lalr1.cc  */
#line 857 "GuavaParser.yy"
    { 
                    driver.tablaSimbolos.enterScope();   
                    identacion += "  ";
                  }
    break;

  case 108:

/* Line 663 of lalr1.cc  */
#line 861 "GuavaParser.yy"
    { 
                                                                                   LoopWhile* result;
                                                                                   ErrorBoolExp* exp_bool = (yysemantic_stack_[(10) - (9)].classErrorBoolExp);
                                                                                   if (exp_bool->get_error()
                                                                                       || exp_bool->get_tipo() == TypeError::Instance()
                                                                                       || (yysemantic_stack_[(10) - (5)].classListaInstrucciones)->get_tipo() == TypeError::Instance()){
                                                                                       result = new LoopWhile();
                                                                                       std::string msg = mensaje_error_tipos("error","void");
                                                                                       driver.error(yylloc,msg);
                                                                                   } 
                                                                                   else {
                                                                                       result = new LoopWhile(exp_bool->exp,(yysemantic_stack_[(10) - (4)].classBloqueDeclare),(yysemantic_stack_[(10) - (5)].classListaInstrucciones));
                                                                                   }
                                                                                   result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                                   (yyval.classLoopWhile) = result;
                                                                                   if (!error_state && driver.print_table) {
                                                                                       std::cout << identacion << "while {\n";
                                                                                       driver.tablaSimbolos.show(driver.tablaSimbolos.currentScope(),identacion+"  ");
                                                                                       std::cout << identacion << "}\n ";
                                                                                       driver.tablaSimbolos.exitScope();
                                                                                       identacion.erase(0,2);
                                                                                   }
                                                                                 }
    break;

  case 109:

/* Line 663 of lalr1.cc  */
#line 887 "GuavaParser.yy"
    {    Exp* tmp = (yysemantic_stack_[(1) - (1)].classExp);
                            ErrorBoolExp* tmp1;
                            if ( (yysemantic_stack_[(1) - (1)].classExp) == 0 || (yysemantic_stack_[(1) - (1)].classExp)->get_tipo() != TypeBool::Instance()){
                                tmp1 = new ErrorBoolExp();
                                tmp1->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                (yyval.classErrorBoolExp) = tmp1;
                             } else {
                                tmp1 = new ErrorBoolExp((yysemantic_stack_[(1) - (1)].classExp));
                                tmp1->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                (yyval.classErrorBoolExp) = tmp1;
                             }
                            }
    break;

  case 110:

/* Line 663 of lalr1.cc  */
#line 899 "GuavaParser.yy"
    {
                              (yyval.classErrorBoolExp) = new ErrorBoolExp();
                            }
    break;

  case 111:

/* Line 663 of lalr1.cc  */
#line 903 "GuavaParser.yy"
    { 
                                          driver.tablaSimbolos.enterScope();   
                                          identacion += "  ";
                                        }
    break;

  case 112:

/* Line 663 of lalr1.cc  */
#line 907 "GuavaParser.yy"
    { 
                                                               ErrorBoolExp* err_exp = (yysemantic_stack_[(11) - (3)].classErrorBoolExp);
                                                               SelectorIf * result;
                                                               if (err_exp->get_error()
                                                                   || err_exp->get_tipo() == TypeError::Instance()
                                                                   || (yysemantic_stack_[(11) - (9)].classListaInstrucciones)->get_tipo() == TypeError::Instance()){
                                                                   result = new SelectorIf(); 
                                                                   std::string msg = mensaje_error_tipos("error","void");
                                                                   driver.error(yylloc,msg);
                                                               } 
                                                               else {
                                                                   result = new SelectorIf(err_exp->exp,(yysemantic_stack_[(11) - (8)].classBloqueDeclare),(yysemantic_stack_[(11) - (9)].classListaInstrucciones),(yysemantic_stack_[(11) - (11)].classLElseIf));
                                                               }
                                                               result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                               (yyval.classSelectorIf) = result;
                                                               driver.tablaSimbolos.exitScope();
                                                               identacion.erase(0,2);
                                                             }
    break;

  case 113:

/* Line 663 of lalr1.cc  */
#line 925 "GuavaParser.yy"
    { 
                                                               ErrorBoolExp* err_exp = (yysemantic_stack_[(7) - (3)].classErrorBoolExp);
                                                               SelectorIf * result;
                                                               if (err_exp->get_error()
                                                                   || err_exp->get_tipo() == TypeError::Instance()
                                                                   || (yysemantic_stack_[(7) - (6)].classInstruccion)->get_tipo() == TypeError::Instance()){
                                                                   result = new SelectorIf(); 
                                                                   std::string msg = mensaje_error_tipos("error","void");
                                                                   driver.error(yylloc,msg);
                                                               } 
                                                               else {
                                                                   result = new SelectorIf(err_exp->exp,(yysemantic_stack_[(7) - (6)].classInstruccion),0);
                                                               }
                                                               result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                               (yyval.classSelectorIf) = result;
                                                             }
    break;

  case 114:

/* Line 663 of lalr1.cc  */
#line 941 "GuavaParser.yy"
    { 
                                                                       ErrorBoolExp* err_exp = (yysemantic_stack_[(9) - (3)].classErrorBoolExp);
                                                                       SelectorIf * result;
                                                                       if (err_exp->get_error()
                                                                          || err_exp->get_tipo() == TypeError::Instance()
                                                                          ){
                                                                           result = new SelectorIf(); 
                                                                           std::string msg = mensaje_error_tipos("error","void");
                                                                           driver.error(yylloc,msg);
                                                                       } 
                                                                       else {
                                                                           result = new SelectorIf(err_exp->exp,(yysemantic_stack_[(9) - (6)].classInstruccion),(yysemantic_stack_[(9) - (8)].classInstruccion));
                                                                       }
                                                                       result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                       (yyval.classSelectorIf) = result;
                                                                     }
    break;

  case 115:

/* Line 663 of lalr1.cc  */
#line 959 "GuavaParser.yy"
    { 
                                                                      (yyval.classLElseIf) = new LElseIf(false);
                                                                    }
    break;

  case 116:

/* Line 663 of lalr1.cc  */
#line 962 "GuavaParser.yy"
    { 
                             driver.tablaSimbolos.enterScope();   
                           }
    break;

  case 117:

/* Line 663 of lalr1.cc  */
#line 965 "GuavaParser.yy"
    { 
                                                                      LElseIf* result; 
                                                                      if ( (yysemantic_stack_[(7) - (1)].classLElseIf)->get_tipo() == TypeError::Instance()
                                                                           || (yysemantic_stack_[(7) - (6)].classListaInstrucciones)->get_tipo() == TypeError::Instance() ){
                                                                          result = new LElseIf(true);
                                                                          std::string msg = mensaje_error_tipos("error","void");
                                                                          driver.error(yylloc,msg);
                                                                      } 
                                                                      else {
                                                                          result = new LElseIf((yysemantic_stack_[(7) - (5)].classBloqueDeclare),(yysemantic_stack_[(7) - (6)].classListaInstrucciones));
                                                                          result->lelseif = (yysemantic_stack_[(7) - (1)].classLElseIf);
                                                                      }
                                                                      result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                      (yyval.classLElseIf) = result;
                                                                      driver.tablaSimbolos.exitScope();
                                                                    }
    break;

  case 118:

/* Line 663 of lalr1.cc  */
#line 981 "GuavaParser.yy"
    { driver.tablaSimbolos.enterScope();
                   }
    break;

  case 119:

/* Line 663 of lalr1.cc  */
#line 983 "GuavaParser.yy"
    {
                                                                      LElseIf* result; 
                                                                      if ( 
                                                                           (yysemantic_stack_[(6) - (5)].classListaInstrucciones)->get_tipo() == TypeError::Instance() ){
                                                                          result = new LElseIf(true);
                                                                          std::string msg = mensaje_error_tipos("error","void");
                                                                          driver.error(yylloc,msg);
                                                                      } 
                                                                      else {
                                                                          result = new LElseIf((yysemantic_stack_[(6) - (4)].classBloqueDeclare),(yysemantic_stack_[(6) - (5)].classListaInstrucciones));
                                                                      }
                                                                      result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                      (yyval.classLElseIf) = result;
                                                                    }
    break;

  case 120:

/* Line 663 of lalr1.cc  */
#line 997 "GuavaParser.yy"
    { }
    break;

  case 121:

/* Line 663 of lalr1.cc  */
#line 1001 "GuavaParser.yy"
    { 
                                             driver.tablaSimbolos.enterScope();   
                                            }
    break;

  case 122:

/* Line 663 of lalr1.cc  */
#line 1004 "GuavaParser.yy"
    {
                                                                   LElseIf* result; 
                                                                   if ( 
                                                                         (yysemantic_stack_[(11) - (4)].classErrorBoolExp)->get_error()
                                                                        || (yysemantic_stack_[(11) - (4)].classErrorBoolExp)->get_tipo() == TypeError::Instance()
                                                                        || (yysemantic_stack_[(11) - (10)].classListaInstrucciones)->get_tipo() == TypeError::Instance()) {
                                                                       result = new LElseIf(true);
                                                                       std::string msg = mensaje_error_tipos("error","void");
                                                                       driver.error(yylloc,msg);
                                                                   } 
                                                                   else {
                                                                       result = new LElseIf((yysemantic_stack_[(11) - (4)].classErrorBoolExp)->exp,(yysemantic_stack_[(11) - (9)].classBloqueDeclare),(yysemantic_stack_[(11) - (10)].classListaInstrucciones));
                                                                   }
                                                                   result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                   (yyval.classLElseIf) = result;
                                                                   driver.tablaSimbolos.exitScope();
                                                                 }
    break;

  case 123:

/* Line 663 of lalr1.cc  */
#line 1021 "GuavaParser.yy"
    { 
                                                      driver.tablaSimbolos.enterScope();   
                                                    }
    break;

  case 124:

/* Line 663 of lalr1.cc  */
#line 1024 "GuavaParser.yy"
    {
                                                                   LElseIf* result; 
                                                                   if ( (yysemantic_stack_[(12) - (1)].classLElseIf)->get_tipo() == TypeError::Instance()
                                                                        || (yysemantic_stack_[(12) - (5)].classErrorBoolExp)->get_error()
                                                                        || (yysemantic_stack_[(12) - (5)].classErrorBoolExp)->get_tipo() == TypeError::Instance()
                                                                        || (yysemantic_stack_[(12) - (11)].classListaInstrucciones)->get_tipo() == TypeError::Instance()) {
                                                                       result = new LElseIf(true);
                                                                       std::string msg = mensaje_error_tipos("error","void");
                                                                       driver.error(yylloc,msg);
                                                                   } 
                                                                   else {
                                                                       result = new LElseIf((yysemantic_stack_[(12) - (5)].classErrorBoolExp)->exp,(yysemantic_stack_[(12) - (10)].classBloqueDeclare),(yysemantic_stack_[(12) - (11)].classListaInstrucciones),(yysemantic_stack_[(12) - (1)].classLElseIf));
                                                                   }
                                                                   result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                                   (yyval.classLElseIf) = result;
                                                                   driver.tablaSimbolos.exitScope();
                                                                 }
    break;

  case 125:

/* Line 663 of lalr1.cc  */
#line 1045 "GuavaParser.yy"
    {  ErrorBoolExp* tmp;
                      if ((yysemantic_stack_[(1) - (1)].classExp) == 0  || (yysemantic_stack_[(1) - (1)].classExp)->get_tipo() != TypeBool::Instance()){
                        tmp = new ErrorBoolExp();
                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                        (yyval.classErrorBoolExp) = tmp;
                      } else {
                        tmp = new ErrorBoolExp((yysemantic_stack_[(1) - (1)].classExp));
                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                        (yyval.classErrorBoolExp) = tmp;
                      }
                    }
    break;

  case 126:

/* Line 663 of lalr1.cc  */
#line 1056 "GuavaParser.yy"
    {
                      (yyval.classErrorBoolExp) = new ErrorBoolExp();
                    }
    break;

  case 127:

/* Line 663 of lalr1.cc  */
#line 1060 "GuavaParser.yy"
    { Symbol *id; 
                                                   LlamadaFuncion* result;
                                                   if ( (id = driver.tablaSimbolos.lookup((yysemantic_stack_[(4) - (1)].classIdentificador)->identificador,0)) == 0){
                                                        std::string msg ("Undefined function '");
                                                        msg += (yysemantic_stack_[(4) - (1)].classIdentificador)->identificador;
                                                        msg += "'";
                                                        driver.error(yylloc,msg);
                                                        error_state = 1;
                                                        (yyval.classExp) = new LlamadaFuncion();
                                                    }else {
                                                        TypeS* tipo = obtener_tipo_simbolo(id);
                                                        if (tipo != 0 && tipo->is_func()){
                                                            TypeFunction * func = (TypeFunction*) tipo;
                                                            result = new LlamadaFuncion((yysemantic_stack_[(4) - (1)].classIdentificador),(yysemantic_stack_[(4) - (3)].classLVaroValor));
                                                            TypeS* rango = tipo->get_tipo(); 
                                                            std::list<TypeS*>::iterator parametros = func->parametros.begin();
                                                            int expected = func->parametros.size();
                                                            int given = (yysemantic_stack_[(4) - (3)].classLVaroValor)->lvarovalor.size();
                                                            std::list<Exp*>::iterator lvarovalor = (yysemantic_stack_[(4) - (3)].classLVaroValor)->lvarovalor.begin();
                                                            Exp* tmp;
                                                            while (parametros != func->parametros.end()
                                                                   && lvarovalor != (yysemantic_stack_[(4) - (3)].classLVaroValor)->lvarovalor.end()
                                                                  ){
                                                                  tmp = *lvarovalor;
                                                                  if (tmp->get_tipo() != *parametros) {
                                                                    std::string msg = mensaje_error_tipos(tmp->get_tipo()->get_name(),(*parametros)->get_name());
                                                                    driver.error(yylloc,msg);
                                                                    result->tipo = TypeError::Instance();
                                                                    break;
                                                                  }
                                                                  ++parametros;
                                                                  ++lvarovalor;
                                                            }
                                                            if (lvarovalor != (yysemantic_stack_[(4) - (3)].classLVaroValor)->lvarovalor.end() && parametros != func->parametros.end()){
                                                                std::string msg ("Expected ");
                                                                msg += std::to_string(expected);
                                                                msg += " arguments, ";
                                                                msg += std::to_string(given);
                                                                msg += " provided.";
                                                                driver.error(yylloc,msg);
                                                                result->tipo = TypeError::Instance();
                                                            } else {
                                                                result->tipo = rango;
                                                            }
                                                            result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                            (yyval.classExp) = result;
                                                        }else{
                                                            std::string msg;
                                                            if (tipo == 0){
                                                                msg = mensaje_error_tipos("null","function");
                                                            } else {
                                                                msg = mensaje_error_tipos(tipo->get_name(),"function");
                                                            }
                                                            driver.error(yylloc,msg);
                                                            (yyval.classExp) = new LlamadaFuncion();
                                                        }
                                                    }

                                                 }
    break;

  case 128:

/* Line 663 of lalr1.cc  */
#line 1119 "GuavaParser.yy"
    {/*Llamado a una funcion con identificador erroneo*/
                                                 }
    break;

  case 129:

/* Line 663 of lalr1.cc  */
#line 1123 "GuavaParser.yy"
    { 
                            (yyval.classLVaroValor) = new LVaroValor(false); 
                          }
    break;

  case 130:

/* Line 663 of lalr1.cc  */
#line 1126 "GuavaParser.yy"
    { 
                           }
    break;

  case 131:

/* Line 663 of lalr1.cc  */
#line 1129 "GuavaParser.yy"
    { 
                                      (yysemantic_stack_[(3) - (1)].classLVaroValor)->append((yysemantic_stack_[(3) - (3)].classExp));
                                      if ((yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeError::Instance()){
                                        (yysemantic_stack_[(3) - (1)].classLVaroValor)->tipo = (yysemantic_stack_[(3) - (3)].classExp)->get_tipo();
                                      }
                                      (yyval.classLVaroValor) = (yysemantic_stack_[(3) - (1)].classLVaroValor);
                                    }
    break;

  case 132:

/* Line 663 of lalr1.cc  */
#line 1136 "GuavaParser.yy"
    {
                                      LVaroValor *tmp = new LVaroValor(false);
                                      if ( (yysemantic_stack_[(1) - (1)].classExp) != 0 && (yysemantic_stack_[(1) - (1)].classExp)->get_tipo() == TypeError::Instance()){
                                        tmp->tipo = (yysemantic_stack_[(1) - (1)].classExp)->get_tipo();
                                      }
                                      tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                      tmp->append((yysemantic_stack_[(1) - (1)].classExp));
                                      (yyval.classLVaroValor) = tmp; 
                                    }
    break;

  case 133:

/* Line 663 of lalr1.cc  */
#line 1145 "GuavaParser.yy"
    { (yyval.classLVaroValor) = new LVaroValor(true);
                                    }
    break;

  case 134:

/* Line 663 of lalr1.cc  */
#line 1147 "GuavaParser.yy"
    {
                                      LVaroValor *tmp = new LVaroValor(true);
                                      (yyval.classLVaroValor) = tmp;
                                    }
    break;

  case 135:

/* Line 663 of lalr1.cc  */
#line 1152 "GuavaParser.yy"
    { (yyval.classExp) = (yysemantic_stack_[(1) - (1)].classExp); }
    break;

  case 136:

/* Line 663 of lalr1.cc  */
#line 1153 "GuavaParser.yy"
    { (yyval.classExp) = (yysemantic_stack_[(1) - (1)].classExp); }
    break;

  case 137:

/* Line 663 of lalr1.cc  */
#line 1154 "GuavaParser.yy"
    { (yyval.classExp) = (yysemantic_stack_[(1) - (1)].classValor); }
    break;

  case 138:

/* Line 663 of lalr1.cc  */
#line 1155 "GuavaParser.yy"
    { (yyval.classExp) = (yysemantic_stack_[(1) - (1)].classExp); }
    break;

  case 139:

/* Line 663 of lalr1.cc  */
#line 1156 "GuavaParser.yy"
    { (yyval.classExp) = (yysemantic_stack_[(3) - (2)].classExp); }
    break;

  case 140:

/* Line 663 of lalr1.cc  */
#line 1157 "GuavaParser.yy"
    {  /*Supondremos que una llamada a una funcion es una expresion*/}
    break;

  case 141:

/* Line 663 of lalr1.cc  */
#line 1158 "GuavaParser.yy"
    {}
    break;

  case 142:

/* Line 663 of lalr1.cc  */
#line 1162 "GuavaParser.yy"
    { TypeS* tipo;
                         ExpID* result;
                         Symbol* id;
                         if ((id = variable_no_declarada((yysemantic_stack_[(1) - (1)].classIdentificador)->identificador,&driver,yylloc, tabla_actual.front()))  != 0) {

                            if((tipo = obtener_tipo_simbolo(id)) != 0) {;
                                result = new ExpID((yysemantic_stack_[(1) - (1)].classIdentificador));
                                result->tipo = tipo;
                                result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                (yyval.classExp) = result;
                            }
                            else {
                               std::string msg ("Type has not been declared or doesn't exists in current context");
                               driver.error(yylloc,msg);
                               result = new ExpID();
                               result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               (yyval.classExp) = result;
                            }

                          } else {
                          result = new ExpID();
                          result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                          (yyval.classExp) = result;
                          }
                       }
    break;

  case 143:

/* Line 663 of lalr1.cc  */
#line 1187 "GuavaParser.yy"
    { TypeS* tipo;
                                        ExpID* result;
                                        Symbol* id;
                                        // Caso en que la variable ha sido declarada
                                        if ((id = variable_no_declarada((yysemantic_stack_[(2) - (1)].classIdentificador)->identificador,&driver, yylloc, tabla_actual.front())) != 0) {
                                            tipo = obtener_tipo_simbolo(id);
                                            if (tipo != 0){
                                                result = new ExpID((yysemantic_stack_[(2) - (1)].classIdentificador), (yysemantic_stack_[(2) - (2)].classLCorchetesExp));
                                                result->set_line_column(yylloc.begin.line,yylloc.begin.column);

                                                if ((yysemantic_stack_[(2) - (2)].classLCorchetesExp)->get_tipo() == TypeInt::Instance() &&
                                                    tipo->is_array()) {
                                                    //Se asigna el tipo del arreglo a la variable.
                                                    result->tipo = tipo->get_tipo();
                                                }

                                                //Caso en el que el identificador NO es un arreglo
                                            
                                                else if (!tipo->is_array()){
                                                    std::string msg = mensaje_error_tipos("array",tipo->get_name());
                                                    driver.error(yylloc, msg);
                                                    result->tipo = TypeError::Instance();
                                                }

                                            //Caso en el que la estructura del arreglo no es de tipo integer

                                                else {
                                                    result->tipo = TypeError::Instance();
                                                }
                                                (yyval.classExp) = result;
                                            }
                                        } else{
                                            result = new ExpID();
                                            result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            (yyval.classExp) = result;
                                        }
                                      }
    break;

  case 144:

/* Line 663 of lalr1.cc  */
#line 1224 "GuavaParser.yy"
    { 
                                        Symbol * id;
                                        Identificador *prueba = (yysemantic_stack_[(2) - (1)].classIdentificador);
                                        ExpID* result;
                                        if ((id = variable_no_declarada(prueba->identificador,&driver,yylloc, tabla_actual.front())) != 0){
                                        //Caso en el que la variable es un record o union.
                                            if (!es_estructura_error(id->sym_catg, (yysemantic_stack_[(2) - (1)].classIdentificador)->identificador,&driver,yylloc)){
                                                std::list<Identificador*> tmp = (yysemantic_stack_[(2) - (2)].classLAccesoAtributos)->get_list();
                                                TypeS* tipo = verificar_acceso_atributos(id, tmp, &driver,yylloc);
                                                result = new ExpID((yysemantic_stack_[(2) - (1)].classIdentificador),(yysemantic_stack_[(2) - (2)].classLAccesoAtributos));
                                                result->tipo = tipo;
                                                result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                (yyval.classExp) = result;
                                            }
                                            else {
                                                result = new ExpID();
                                                result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                                (yyval.classExp) = result;
                                            }
                                        } else {
                                            result = new ExpID();
                                            result->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                            (yyval.classExp) = result;
                                        }
                                      }
    break;

  case 145:

/* Line 663 of lalr1.cc  */
#line 1251 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("AND"));
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeBool::Instance() &&
                                   (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeBool::Instance())
                               { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                               } 
                               else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeBool::Instance()) {
                                 std::string msg = mensaje_error_tipos("boolean",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               else {
                                 std::string msg = mensaje_error_tipos("boolean",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               (yyval.classExp) = tmp;
                             }
    break;

  case 146:

/* Line 663 of lalr1.cc  */
#line 1269 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("OR"));
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeBool::Instance() &&
                                   (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeBool::Instance())
                               { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                               } 
                               else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeBool::Instance()) {
                                 std::string msg = mensaje_error_tipos("boolean",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               else {
                                 std::string msg = mensaje_error_tipos("boolean",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               (yyval.classExp) = tmp;
                             }
    break;

  case 147:

/* Line 663 of lalr1.cc  */
#line 1287 "GuavaParser.yy"
    { ExpBin* tmp;
                               if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                   ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                    (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance())) {
                                 int cmpv = (yysemantic_stack_[(3) - (2)].subtok);
                                 switch(cmpv){
                                      case 1:
                                          tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string(">"));
                                          break;
                                      case 2:
                                          tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("<"));
                                          break;
                                      case 3:
                                          tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("<="));
                                          break;
                                      case 4:
                                          tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string(">="));
                                          break;
                                      case 5:
                                          tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("="));
                                          break;
                                      case 6:
                                          tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("!="));
                                          break;
                                 }
                                 tmp->tipo = TypeBool::Instance();
                                 tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               } 
                               else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                        ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() &&
                                         (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeReal::Instance()) ||
                                        ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance() &&
                                         (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance())) {
                                 std::string expected = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name()+"' or '"+(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name();
                                 std::string msg = mensaje_diff_operandos(std::string("<=>"),(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),expected);
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                                 tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               }
                               else if ( (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() && 
                                         (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeBool::Instance() &&
                                         (yysemantic_stack_[(3) - (2)].subtok) == 5
                                       ){
                                        tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("="));
                                        tmp->tipo = TypeBool::Instance();
                                        tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               }else {
                                tmp = new ExpBin();
                                 if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance() &&
                                     (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeReal::Instance()) {
                                     std::cout << "";
                                     std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                     driver.error(yylloc,msg);
                                 }
                                 else {
                                   std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                   driver.error(yylloc,msg);
                                 }
                                 tmp->tipo = TypeError::Instance();
                               }
                               (yyval.classExp) = tmp;

                             }
    break;

  case 148:

/* Line 663 of lalr1.cc  */
#line 1350 "GuavaParser.yy"
    { std::string * op = new std::string("NOT");
                               ExpUn* tmp = new ExpUn((yysemantic_stack_[(2) - (2)].classExp),op);
                               tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                               if ((yysemantic_stack_[(2) - (2)].classExp)->get_tipo() == TypeBool::Instance())
                               { tmp->tipo = (yysemantic_stack_[(2) - (2)].classExp)->get_tipo();
                               }
                               else {
                                 std::string msg = mensaje_error_tipos("boolean",(yysemantic_stack_[(2) - (2)].classExp)->get_tipo()->get_name());
                                 driver.error(yylloc,msg);
                                 tmp->tipo = TypeError::Instance();
                               }
                               (yyval.classExp) = tmp;
                             }
    break;

  case 149:

/* Line 663 of lalr1.cc  */
#line 1364 "GuavaParser.yy"
    { std::string * op = new std::string("-");
                                       ExpUn* tmp = new ExpUn((yysemantic_stack_[(2) - (2)].classExp),op);
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(2) - (2)].classExp)->get_tipo() == TypeInt::Instance() ||
                                           (yysemantic_stack_[(2) - (2)].classExp)->get_tipo() == TypeReal::Instance())
                                       { tmp->tipo = (yysemantic_stack_[(2) - (2)].classExp)->get_tipo();
                                       }
                                       else {
                                         std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(2) - (2)].classExp)->get_tipo()->get_name());
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 150:

/* Line 663 of lalr1.cc  */
#line 1378 "GuavaParser.yy"
    { 
                                       std::string * op = new std::string("++");
                                       ExpUn* tmp = new ExpUn((yysemantic_stack_[(2) - (1)].classExp),op);
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(2) - (1)].classExp)->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = (yysemantic_stack_[(2) - (1)].classExp)->get_tipo();
                                       }
                                       else {
                                         std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(2) - (1)].classExp)->get_tipo()->get_name());
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 151:

/* Line 663 of lalr1.cc  */
#line 1392 "GuavaParser.yy"
    { std::string * op = new std::string("--");
                                       ExpUn* tmp = new ExpUn((yysemantic_stack_[(2) - (1)].classExp),op);
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(2) - (1)].classExp)->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = (yysemantic_stack_[(2) - (1)].classExp)->get_tipo();
                                       }
                                       else {
                                         std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(2) - (1)].classExp)->get_tipo()->get_name());
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 152:

/* Line 663 of lalr1.cc  */
#line 1405 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("<=>"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                           ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                            (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = TypeInt::Instance();
                                        // El tipo de esta expresion es integer, recordar que UFO devuelve -1,0,1.
                                       } 
                                       else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeReal::Instance()) ||
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name()+"' or '"+(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("<=>"),(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),
                                                                                    (yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance() &&
                                             (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeReal::Instance()) {
                                           std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                         }
                                         else {
                                           std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 153:

/* Line 663 of lalr1.cc  */
#line 1438 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("+"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() && 
                                           ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                            (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                       } 
                                       else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeReal::Instance()) ||
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name()+"' or '"+(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("+"),(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),
                                                                                    (yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance() &&
                                             (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeReal::Instance()) {
                                             std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                             driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 154:

/* Line 663 of lalr1.cc  */
#line 1470 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("-"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                           ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                            (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                       } 
                                       else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeReal::Instance()) ||
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name()+"' or '"+(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("-"),(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),
                                                                                (yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance() &&
                                             (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 155:

/* Line 663 of lalr1.cc  */
#line 1502 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("*"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                           ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                            (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                       } 
                                       else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeReal::Instance()) ||
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name()+"' or '"+(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("*"),(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),
                                                                                    (yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance() &&
                                             (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 156:

/* Line 663 of lalr1.cc  */
#line 1534 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("/"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                           ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                            (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance()))
                                       { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                       } 
                                       else if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeReal::Instance()) ||
                                                ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance() &&
                                                 (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance())) {
                                         std::string expected = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name()+"' or '"+(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name();
                                         std::string msg = mensaje_diff_operandos(std::string("/"),
                                                                    (yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name(),(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name(),expected);
                                         driver.error(yylloc,msg);
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance() &&
                                             (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeReal::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 157:

/* Line 663 of lalr1.cc  */
#line 1566 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("DIV"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                           (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance()) {
                                            std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         else {
                                            std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                            driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 158:

/* Line 663 of lalr1.cc  */
#line 1585 "GuavaParser.yy"
    { ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("MOD"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() &&
                                           (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance())
                                       { tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                       }
                                       else {
                                         if ((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() != TypeInt::Instance()) {
                                             std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(3) - (1)].classExp)->get_tipo()->get_name());
                                             driver.error(yylloc,msg);
                                         }
                                         else {
                                             std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                             driver.error(yylloc,msg);
                                         }
                                         tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 159:

/* Line 663 of lalr1.cc  */
#line 1604 "GuavaParser.yy"
    { //El exponente sera integer, la base integer o real.
                                       ExpBin* tmp = new ExpBin((yysemantic_stack_[(3) - (1)].classExp),(yysemantic_stack_[(3) - (3)].classExp),std::string("**"));
                                       tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                       if ((yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == TypeInt::Instance()) {
                                           if((yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeInt::Instance() ||
                                              (yysemantic_stack_[(3) - (1)].classExp)->get_tipo() == TypeReal::Instance()) {
                                              tmp->tipo = (yysemantic_stack_[(3) - (1)].classExp)->get_tipo();
                                           }
                                           else {
                                               std::string msg = mensaje_error_tipos("integer' or 'real",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                               driver.error(yylloc,msg);
                                               tmp->tipo = TypeError::Instance();
                                           }
                                       }
                                       else {
                                           std::string msg = mensaje_error_tipos("integer",(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                           driver.error(yylloc,msg);
                                           tmp->tipo = TypeError::Instance();
                                       }
                                       (yyval.classExp) = tmp;
                                     }
    break;

  case 160:

/* Line 663 of lalr1.cc  */
#line 1626 "GuavaParser.yy"
    { 
                  Valor* v = new Bool((yysemantic_stack_[(1) - (1)].boolval),TypeBool::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  (yyval.classValor) = v;
                }
    break;

  case 161:

/* Line 663 of lalr1.cc  */
#line 1631 "GuavaParser.yy"
    { 
                  Valor* v = new String((yysemantic_stack_[(1) - (1)].strval),TypeString::Instance());
                  insertar_cadena_caracteres(*v->get_valor_str(),&driver, yylloc);
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  (yyval.classValor) = v;
                }
    break;

  case 162:

/* Line 663 of lalr1.cc  */
#line 1637 "GuavaParser.yy"
    { 
                  Valor* v = new Char((yysemantic_stack_[(1) - (1)].charval),TypeChar::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  (yyval.classValor) = v;
                }
    break;

  case 163:

/* Line 663 of lalr1.cc  */
#line 1642 "GuavaParser.yy"
    { 
                  Valor* v  = new Integer((yysemantic_stack_[(1) - (1)].intval),TypeInt::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  (yyval.classValor) = v;
                }
    break;

  case 164:

/* Line 663 of lalr1.cc  */
#line 1647 "GuavaParser.yy"
    { 
                  Valor* v = new Real((yysemantic_stack_[(1) - (1)].realval),TypeReal::Instance());
                  v->set_line_column(yylloc.begin.line,yylloc.begin.column);
                  (yyval.classValor) = v;
                }
    break;

  case 165:

/* Line 663 of lalr1.cc  */
#line 1652 "GuavaParser.yy"
    {
                  (yyval.classValor) = (yysemantic_stack_[(1) - (1)].classArreglo);
                }
    break;

  case 166:

/* Line 663 of lalr1.cc  */
#line 1657 "GuavaParser.yy"
    { 
                      (yyval.classTipo) = TypeReal::Instance();
                    }
    break;

  case 167:

/* Line 663 of lalr1.cc  */
#line 1660 "GuavaParser.yy"
    { 
                      (yyval.classTipo) = TypeInt::Instance();
                    }
    break;

  case 168:

/* Line 663 of lalr1.cc  */
#line 1663 "GuavaParser.yy"
    { 
                      (yyval.classTipo) = TypeBool::Instance();
                    }
    break;

  case 169:

/* Line 663 of lalr1.cc  */
#line 1666 "GuavaParser.yy"
    { 
                      (yyval.classTipo) = TypeChar::Instance();
                    }
    break;

  case 170:

/* Line 663 of lalr1.cc  */
#line 1669 "GuavaParser.yy"
    { 
                      (yyval.classTipo) = TypeString::Instance();
                    }
    break;

  case 171:

/* Line 663 of lalr1.cc  */
#line 1675 "GuavaParser.yy"
    {
                            Arreglo* tmp;
                            LArreglo *lr = (yysemantic_stack_[(3) - (2)].classLArreglo);
                            tmp = new Arreglo(lr);
                            tmp->tipo_primitivo = lr->get_tipo();
                            tmp->tipo_estructura = lr->get_tipoEstructura();
                            tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                            (yyval.classArreglo) = tmp;
                          }
    break;

  case 172:

/* Line 663 of lalr1.cc  */
#line 1686 "GuavaParser.yy"
    { 
                                  //Caso: Tipos no nulos
                                  std::string msg;
                                  if ((yysemantic_stack_[(3) - (1)].classLArreglo)->get_tipo() != 0 && (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() != 0) {
                                    //Caso: Tipos primitivos diferentes
                                    if ((yysemantic_stack_[(3) - (1)].classLArreglo)->get_tipo() != (yysemantic_stack_[(3) - (3)].classExp)->get_tipo()) {
                                      msg = mensaje_error_tipos((yysemantic_stack_[(3) - (1)].classLArreglo)->get_tipo()->get_name(),(yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->get_name());
                                    }
                                    //Caso: Tipos estructurales diferentes
                                    else if ((yysemantic_stack_[(3) - (3)].classExp)->get_tipo()->is_array()) {
                                        Arreglo* expArr = (Arreglo *) (yysemantic_stack_[(3) - (3)].classExp);
                                        if ((yysemantic_stack_[(3) - (1)].classLArreglo)->get_tipoEstructura() != expArr->get_tipoEstructura()) {
                                          msg = mensaje_error_tipos((yysemantic_stack_[(3) - (1)].classLArreglo)->get_tipoEstructura()->get_name(),expArr->get_tipoEstructura()->get_name());
                                        }
                                    }
                                    driver.error(yylloc,msg);
                                    (yysemantic_stack_[(3) - (1)].classLArreglo)->tipo_primitivo = TypeError::Instance();
                                  }
                                  //Caso: Tipos nulos
                                  else if ((yysemantic_stack_[(3) - (1)].classLArreglo)->get_tipo() == 0 && (yysemantic_stack_[(3) - (3)].classExp)->get_tipo() == 0) {
                                    msg = mensaje_error_tipos("null","null");
                                    driver.error(yylloc,msg);
                                    (yysemantic_stack_[(3) - (1)].classLArreglo)->tipo_primitivo = TypeError::Instance();
                                  }
                                  //Caso: Sin Errores
                                  else {
                                    (yysemantic_stack_[(3) - (1)].classLArreglo)->append((yysemantic_stack_[(3) - (3)].classExp));
                                  }
                                  (yyval.classLArreglo) = (yysemantic_stack_[(3) - (1)].classLArreglo);
                                }
    break;

  case 173:

/* Line 663 of lalr1.cc  */
#line 1716 "GuavaParser.yy"
    { 
                                  LArreglo *tmp = new LArreglo();
                                  tmp->tipo_primitivo = (yysemantic_stack_[(1) - (1)].classExp)->get_tipo();
                                  //Caso para arreglos anidados
                                  if((yysemantic_stack_[(1) - (1)].classExp)->get_tipo()->is_array() != 0) {
                                    Arreglo* expArr = (Arreglo *) (yysemantic_stack_[(1) - (1)].classExp);
                                    tmp->tipo_estructura = expArr->get_tipoEstructura();
                                  }
                                  //Caso para arreglos simples
                                  else {
                                    tmp->tipo_estructura = 0;
                                  }
                                  tmp->set_line_column(yylloc.begin.line,yylloc.begin.column);
                                  tmp->append((yysemantic_stack_[(1) - (1)].classExp));
                                  (yyval.classLArreglo) = tmp;
                                }
    break;

  case 174:

/* Line 663 of lalr1.cc  */
#line 1733 "GuavaParser.yy"
    { 
                                 (yysemantic_stack_[(3) - (1)].classLArreglo)->tipo_primitivo = TypeError::Instance();
                                 (yyval.classLArreglo) = (yysemantic_stack_[(3) - (1)].classLArreglo); 
                                }
    break;

  case 175:

/* Line 663 of lalr1.cc  */
#line 1737 "GuavaParser.yy"
    { LArreglo *tmp = new LArreglo(); 
                                  tmp->tipo_primitivo = TypeError::Instance();
                                }
    break;

  case 176:

/* Line 663 of lalr1.cc  */
#line 1742 "GuavaParser.yy"
    { 
                                      (yyval.classLAccesoAtributos) = new LAccesoAtributos((yysemantic_stack_[(2) - (2)].classIdentificador));
                                    }
    break;

  case 177:

/* Line 663 of lalr1.cc  */
#line 1745 "GuavaParser.yy"
    {
                                                        (yysemantic_stack_[(3) - (1)].classLAccesoAtributos)->append((yysemantic_stack_[(3) - (3)].classIdentificador));
                                                        (yyval.classLAccesoAtributos) = (yysemantic_stack_[(3) - (1)].classLAccesoAtributos);
                                                     }
    break;

  case 178:

/* Line 663 of lalr1.cc  */
#line 1749 "GuavaParser.yy"
    {
                                                                    (yysemantic_stack_[(4) - (1)].classLAccesoAtributos)->append((yysemantic_stack_[(4) - (3)].classIdentificador));
                                                                    (yyval.classLAccesoAtributos) = (yysemantic_stack_[(4) - (1)].classLAccesoAtributos);
                                                                   }
    break;

  case 179:

/* Line 663 of lalr1.cc  */
#line 1753 "GuavaParser.yy"
    {
                                                                     (yyval.classLAccesoAtributos) = new LAccesoAtributos((yysemantic_stack_[(3) - (2)].classIdentificador));
                                                                   }
    break;

  case 180:

/* Line 663 of lalr1.cc  */
#line 1757 "GuavaParser.yy"
    { std::string str =  std::string((yysemantic_stack_[(1) - (1)].strval));
                    Identificador* id = new Identificador(str);
                    id->line = yylloc.begin.line;
                    id->column = yylloc.begin.column;
                    (yyval.classIdentificador) = id;
                  }
    break;



/* Line 663 of lalr1.cc  */
#line 3065 "GuavaParser.cc"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  GuavaParser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int GuavaParser::yypact_ninf_ = -354;
  const short int
  GuavaParser::yypact_[] =
  {
      -354,     2,  -354,   -21,  -354,    -2,    23,   492,  -354,    -2,
    -354,  -354,    -8,  -354,  -354,  -354,    76,  -354,  -354,    64,
    -354,  -354,  1186,  -354,    18,    29,    43,    64,    64,   140,
      48,    54,    82,    68,     4,   107,   201,    62,    70,  -354,
      75,    88,   101,    97,  -354,  -354,  -354,   138,    13,  -354,
     152,   152,   138,    78,   119,   132,   169,   163,   169,  -354,
    -354,  -354,  -354,   138,   109,   152,   152,   138,   180,   113,
     180,   141,   204,  -354,   197,   165,   176,   211,  -354,   231,
    -354,   235,    51,   242,  -354,  1186,  1186,   178,  -354,   195,
     202,   203,   125,   241,   217,  -354,   241,  -354,  -354,  -354,
    -354,  -354,  -354,   -21,  -354,   263,   169,  -354,   255,  -354,
    -354,   273,  1135,  1153,  -354,  -354,  -354,  -354,   279,   282,
     144,   180,   180,   -21,  -354,   -21,   265,   103,  -354,  -354,
     -21,   267,  -354,  -354,  -354,  -354,   284,   285,   241,   241,
    -354,   655,  -354,   -21,  -354,   259,  -354,  -354,   -21,  -354,
    -354,   680,    34,   286,   288,   289,   295,   298,  -354,  -354,
     294,   297,    64,    64,  -354,   302,  -354,  -354,  -354,  -354,
    -354,  -354,  -354,  -354,   352,    19,   714,  -354,  -354,  -354,
     739,  -354,  -354,   230,   167,  -354,   261,   400,   409,  -354,
     301,  -354,  -354,  -354,  -354,  -354,   230,   230,   462,   471,
    -354,  1271,  -354,  -354,  -354,  -354,  -354,   137,   230,   230,
    -354,  -354,  -354,   481,  -354,  -354,  -354,   524,   167,    64,
     309,   306,  -354,   773,  -354,   798,  1271,   301,   310,   318,
    1271,   316,   317,   301,   315,  1271,   301,   323,  1271,   -21,
    1318,  -354,   301,  1271,    84,   143,  1180,   230,   230,   230,
     230,   230,   230,   230,   230,   230,  -354,  -354,   230,   230,
    1199,  1218,   301,  1271,   219,  1237,   324,   319,   534,    64,
    -354,  -354,  -354,   543,   230,   596,   363,   362,  -354,   605,
    -354,  -354,  -354,  1298,  1309,  1318,   281,   281,   264,   264,
     264,   264,   341,  1286,  -354,  -354,  -354,  -354,  -354,   309,
     223,  1254,   319,   301,  1271,  1271,   336,   216,   337,  1098,
     342,   832,   301,  1271,  -354,  -354,   309,   615,   615,   615,
    -354,     5,  -354,   370,    12,  -354,   343,  1271,   352,   344,
     346,   -21,  1150,  -354,   -21,   348,   347,   361,   369,  -354,
     360,  -354,   409,  -354,  -354,  -354,   857,  -354,   891,   364,
     -21,   -21,   -21,   378,  -354,  -354,  -354,  -354,  -354,    21,
    -354,   401,   916,   950,   975,   367,  -354,    27,  -354,  -354,
    -354,   400,   -21,   368,  -354,   377,  -354,   400,   -21,   415,
    1009,   382,  -354,   390,  -354,   422,  1034,  -354,   392,  -354,
     -21,  -354,  -354,   -21,  1068,  -354,  -354,  1093,  -354
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  GuavaParser::yydefact_[] =
  {
         3,     0,     2,     5,     1,     0,     0,     0,     4,     0,
      43,    45,     0,   167,   166,   169,     0,   168,   170,     0,
      44,    46,     0,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,     0,     0,    20,    21,    29,     0,     0,    27,
       0,     0,     0,     0,     0,     0,    61,     0,    61,    25,
      23,    18,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    16,     0,     0,     0,    47,     0,
      55,    62,     0,     0,    52,     0,     0,     0,     8,     0,
       0,     0,     0,    33,     0,    10,    31,    22,    30,    28,
      14,    12,    49,     5,    59,     0,     0,    67,     0,    63,
      57,     0,     0,     0,    11,    17,    15,    13,     0,     0,
       0,     0,     0,     5,    71,     5,     0,     0,    68,    64,
       5,     0,    26,    24,    37,    35,     0,     0,    34,    32,
      71,     0,    71,     5,    69,     0,    65,    71,     5,    38,
      36,     0,     0,     0,     0,     0,     0,     0,    82,    81,
       0,     0,     0,     0,    48,     0,    73,    74,    80,    85,
      86,    87,    88,    75,     0,     0,     0,    71,    70,    66,
       0,    71,    50,     0,     0,    83,     0,     0,     0,   107,
       0,   163,   161,   162,   164,   160,     0,     0,     0,     0,
     140,    95,   138,   136,   135,   137,   165,   142,     0,     0,
      78,    76,    72,     0,    84,    79,    77,     0,     0,     0,
     143,   144,    60,     0,    58,     0,    90,   134,     0,   130,
     132,     0,     0,   126,     0,   125,   110,     0,   109,     5,
     148,   149,   175,   173,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   150,   151,     0,     0,
       0,     0,    91,    89,     0,     0,     0,   176,     0,     0,
      56,    53,   128,     0,     0,     0,     0,     0,    71,     0,
     171,   141,   139,   152,   145,   146,   153,   154,   155,   156,
     157,   158,   159,   147,    93,    92,    41,    39,   127,   179,
       0,     0,   177,   133,   131,     0,   136,     0,   136,     0,
       0,     0,   174,   172,    42,    40,   178,     0,     0,     0,
     111,     0,   105,     0,   104,   102,     0,   103,   138,     0,
       0,     5,     0,   113,     5,     0,     0,     0,     0,    71,
       0,    71,     0,    98,   100,    96,     0,   114,     0,     0,
       5,     5,     5,   115,   106,   108,    71,    71,    71,     0,
     112,   120,     0,     0,     0,     0,   118,     0,    99,   101,
      97,     0,     5,     0,   116,     0,    71,     0,     5,     0,
       0,     0,    71,     0,   119,     0,     0,   121,     0,   117,
       5,   123,    71,     5,     0,    71,   122,     0,   124
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  GuavaParser::yypgoto_[] =
  {
      -354,  -354,  -354,  -354,  -102,  -354,   215,   -25,  -354,   -22,
    -354,   135,   -19,   -40,  -259,  -354,  -354,   434,  -354,  -354,
     435,  -354,  -354,  -354,  -354,  -354,  -354,   389,  -354,     1,
    -292,  -354,    -6,  -354,  -354,  -354,  -354,  -354,  -354,   -32,
    -354,  -354,  -354,   112,  -354,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,  -353,   -66,   239,  -354,   177,  -122,    15,  -354,
    -354,     3,  -354,  -354,  -354,   -16
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  GuavaParser::yydefgoto_[] =
  {
        -1,     1,     2,     3,     5,     6,    29,    30,    86,    31,
      85,    48,    69,    93,   220,     8,     9,    10,   103,   123,
      11,    58,   111,    56,   105,   130,   125,    80,    81,   141,
     165,   166,   167,   168,   169,   170,   352,   350,   351,   326,
     171,   334,   239,   237,   172,   331,   360,   378,   372,   361,
     390,   393,   234,   200,   228,   229,   235,   202,   203,   204,
     205,    32,   206,   244,   221,   207
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const short int GuavaParser::yytable_ninf_ = -143;
  const short int
  GuavaParser::yytable_[] =
  {
        25,   124,     4,    26,    40,    53,    33,    41,   299,    -6,
      19,    37,    38,    43,    71,   183,    49,   321,   375,   174,
     214,   140,  -142,   142,   381,   332,    49,     7,   147,   174,
      96,    70,    42,    76,    49,    49,    70,   183,    23,   365,
     340,   177,    22,   316,    87,   373,   181,    70,    91,    49,
      49,    70,   107,    12,   174,    23,    99,   333,   174,    82,
      54,    82,    72,   215,   216,    73,   109,   184,    23,    33,
      33,   366,   217,    34,   218,   173,   219,   374,   122,   108,
      23,   138,   139,    46,    35,   173,    23,    40,    40,   184,
      41,    41,   129,    24,    50,    51,    43,    43,    36,    52,
      44,   174,    46,   174,   144,    23,    45,    23,    55,   127,
     173,   146,    59,    47,   173,    42,    42,   -54,   -54,   -54,
      60,   -54,   -54,    65,    66,   175,   118,    61,    67,   179,
     119,   145,    63,   279,    77,   175,   185,   278,   280,    68,
      62,   151,    23,   176,    23,   136,   210,   211,   180,   137,
      13,    14,    15,    46,    17,    18,    23,   173,    72,   173,
     175,    88,    94,   -54,   175,    95,    27,    28,   227,    78,
     232,    23,   191,   192,   193,   194,   195,    64,   223,    13,
      14,    15,   225,    17,    18,    74,    75,   174,    79,   174,
     217,    39,   218,    97,   219,   328,   328,   328,   184,   281,
      89,    90,    57,   267,   196,    98,   197,   175,    23,   175,
     174,   -51,   -51,   -51,    72,   -51,   -51,   100,   121,    83,
     198,    23,   199,  -129,   174,    94,   174,    94,   101,   339,
     114,   190,   341,    92,    23,   191,   192,   193,   194,   195,
     174,   174,   174,   173,    72,   173,    72,   115,   356,   357,
     358,    72,    94,   302,   116,   117,   128,   -51,   174,    23,
     178,   102,   231,    23,   174,    23,   173,   196,   318,   197,
     376,   184,   174,   296,   184,   174,   382,   314,   184,   311,
     173,   104,   173,   198,   106,   199,   329,   330,   392,   306,
     308,   395,   110,   175,   120,   175,   173,   173,   173,   190,
     112,   113,    23,   191,   192,   193,   194,   195,   256,   257,
     258,   325,   325,   325,   173,   143,   175,   148,   -94,   126,
     173,   252,   253,   254,   255,   256,   257,   258,   173,   131,
     175,   173,   175,   134,   201,   196,   135,   197,   149,   150,
     346,   186,   348,   187,   188,   189,   175,   175,   175,   208,
     -94,   198,   209,   199,   212,   213,   184,   362,   363,   364,
     226,   230,   268,   269,   175,   238,   272,   273,   274,   275,
     175,   276,   217,   240,   241,   243,   246,   380,   175,   277,
     298,   175,   309,   386,   310,   260,   261,   258,   317,   319,
     263,   335,   322,   394,   265,   230,   397,   343,   359,   336,
     337,   233,   338,   342,    23,   191,   192,   193,   194,   195,
     236,   344,   347,    23,   191,   192,   193,   194,   195,   345,
     355,   367,   371,   377,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   379,   383,   292,   293,   196,   385,   197,
     387,   388,   391,    20,    21,   301,   196,    84,   197,     0,
     304,   305,   305,   198,   349,   199,   313,   266,     0,     0,
       0,     0,   198,   242,   199,     0,    23,   191,   192,   193,
     194,   195,   245,     0,     0,    23,   191,   192,   193,   194,
     195,     0,   262,     0,     0,    23,   191,   192,   193,   194,
     195,     0,     0,     0,   327,   327,   327,     0,     0,   196,
       0,   197,    13,    14,    15,    16,    17,    18,   196,     0,
     197,     0,     0,     0,     0,   198,     0,   199,   196,   238,
     197,     0,     0,     0,   198,   264,   199,     0,    23,   191,
     192,   193,   194,   195,   198,   300,   199,     0,    23,   191,
     192,   193,   194,   195,   303,     0,     0,    23,   191,   192,
     193,   194,   195,     0,     0,     0,     0,     0,     0,     0,
       0,   196,     0,   197,     0,     0,     0,     0,     0,     0,
       0,   196,     0,   197,     0,     0,     0,   198,     0,   199,
     196,     0,   197,     0,     0,     0,     0,   198,     0,   199,
       0,     0,     0,     0,     0,     0,   198,   307,   199,     0,
      23,   191,   192,   193,   194,   195,   312,     0,     0,    23,
     191,   192,   193,   194,   195,     0,   324,     0,     0,    23,
     191,   192,   193,   194,   195,     0,     0,     0,     0,     0,
       0,     0,     0,   196,     0,   197,     0,     0,     0,     0,
       0,     0,   196,     0,   197,     0,     0,     0,     0,   198,
       0,   199,   196,     0,   197,     0,   152,     0,   198,    23,
     199,     0,     0,     0,     0,     0,     0,     0,   198,     0,
     199,   153,     0,   154,     0,     0,   155,   156,   157,   158,
     159,   152,     0,     0,    23,     0,     0,   160,   161,     0,
       0,     0,     0,     0,     0,     0,   153,     0,   154,   162,
     163,   155,   156,   157,   158,   159,   164,     0,     0,     0,
       0,     0,   160,   161,     0,   152,     0,     0,    23,     0,
       0,     0,     0,     0,   162,   163,     0,     0,     0,     0,
     153,   182,   154,     0,     0,   155,   156,   157,   158,   159,
     152,     0,     0,    23,     0,     0,   160,   161,     0,     0,
       0,     0,     0,     0,     0,   153,     0,   154,   162,   163,
     155,   156,   157,   158,   159,   222,     0,     0,     0,     0,
       0,   160,   161,     0,   152,     0,     0,    23,     0,     0,
       0,     0,     0,   162,   163,     0,     0,     0,     0,   153,
     224,   154,     0,     0,   155,   156,   157,   158,   159,   152,
       0,     0,    23,     0,     0,   160,   161,     0,     0,     0,
       0,     0,     0,     0,   153,     0,   154,   162,   163,   155,
     156,   157,   158,   159,   270,     0,     0,     0,     0,     0,
     160,   161,     0,   152,     0,     0,    23,     0,     0,     0,
       0,     0,   162,   163,     0,     0,     0,     0,   153,   271,
     154,     0,     0,   155,   156,   157,   158,   159,   152,     0,
       0,    23,     0,     0,   160,   161,     0,     0,     0,     0,
       0,     0,     0,   153,     0,   154,   162,   163,   155,   156,
     157,   158,   159,   323,     0,     0,     0,     0,     0,   160,
     161,     0,   152,     0,     0,    23,     0,     0,     0,     0,
       0,   162,   163,     0,     0,     0,     0,   153,   353,   154,
       0,     0,   155,   156,   157,   158,   159,   152,     0,     0,
      23,     0,     0,   160,   161,     0,     0,     0,     0,     0,
       0,     0,   153,     0,   154,   162,   163,   155,   156,   157,
     158,   159,   354,     0,     0,     0,     0,     0,   160,   161,
       0,   152,     0,     0,    23,     0,     0,     0,     0,     0,
     162,   163,     0,     0,     0,     0,   153,   368,   154,     0,
       0,   155,   156,   157,   158,   159,   152,     0,     0,    23,
       0,     0,   160,   161,     0,     0,     0,     0,     0,     0,
       0,   153,     0,   154,   162,   163,   155,   156,   157,   158,
     159,   369,     0,     0,     0,     0,     0,   160,   161,     0,
     152,     0,     0,    23,     0,     0,     0,     0,     0,   162,
     163,     0,     0,     0,     0,   153,   370,   154,     0,     0,
     155,   156,   157,   158,   159,   152,     0,     0,    23,     0,
       0,   160,   161,     0,     0,     0,     0,     0,     0,     0,
     153,     0,   154,   162,   163,   155,   156,   157,   158,   159,
     384,     0,     0,     0,     0,     0,   160,   161,     0,   152,
       0,     0,    23,     0,     0,     0,     0,     0,   162,   163,
       0,     0,     0,     0,   153,   389,   154,     0,     0,   155,
     156,   157,   158,   159,   152,     0,     0,    23,     0,   152,
     160,   161,    23,     0,     0,     0,     0,     0,     0,   153,
       0,   154,   162,   163,   155,   156,   157,   158,   159,   396,
       0,   157,   158,   159,     0,   160,   161,     0,     0,     0,
     160,   161,     0,     0,     0,     0,     0,   162,   163,    23,
       0,     0,   162,   163,   398,    13,    14,    15,   320,    17,
      18,   152,     0,     0,    23,     0,     0,    23,     0,     0,
       0,    27,    28,    13,    14,    15,     0,    17,    18,     0,
       0,     0,     0,   157,   158,   159,     0,     0,     0,    27,
      28,     0,   160,   161,     0,     0,   132,     0,     0,     0,
      23,     0,     0,     0,   162,   163,    13,    14,    15,     0,
      17,    18,     0,     0,   133,     0,     0,     0,     0,     0,
       0,     0,    27,    28,   247,   248,   249,     0,   250,   251,
     252,   253,   254,   255,   256,   257,   258,     0,   259,     0,
       0,     0,     0,   247,   248,   249,   282,   250,   251,   252,
     253,   254,   255,   256,   257,   258,     0,   259,     0,     0,
       0,     0,   247,   248,   249,   294,   250,   251,   252,   253,
     254,   255,   256,   257,   258,     0,   259,     0,     0,     0,
       0,   247,   248,   249,   295,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,   259,     0,     0,   247,   248,
     249,   297,   250,   251,   252,   253,   254,   255,   256,   257,
     258,     0,   259,     0,     0,   247,   248,   249,   315,   250,
     251,   252,   253,   254,   255,   256,   257,   258,     0,   259,
     247,   248,   249,     0,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   248,   249,     0,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   249,     0,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   250,   251,   252,   253,
     254,   255,   256,   257,   258
  };

  /* YYCHECK.  */
  const short int
  GuavaParser::yycheck_[] =
  {
        16,   103,     0,    19,    29,     1,    22,    29,   267,    30,
       7,    27,    28,    29,     1,     3,    32,   309,   371,   141,
       1,   123,     3,   125,   377,    20,    42,    29,   130,   151,
      70,    47,    29,    52,    50,    51,    52,     3,     4,    18,
     332,   143,    50,   302,    63,    18,   148,    63,    67,    65,
      66,    67,     1,    30,   176,     4,    72,    52,   180,    56,
      56,    58,    49,    44,    45,    52,    82,    55,     4,    85,
      86,    50,    53,    55,    55,   141,    57,    50,    94,    28,
       4,   121,   122,     1,    55,   151,     4,   112,   113,    55,
     112,   113,   108,    17,    26,    27,   112,   113,    55,    31,
      52,   223,     1,   225,     1,     4,    52,     4,     1,   106,
     176,   127,    50,    31,   180,   112,   113,    10,    11,    12,
      50,    14,    15,    26,    27,   141,     1,    52,    31,   145,
       5,    28,    31,    49,    56,   151,   152,   239,    54,     1,
      52,   140,     4,   142,     4,     1,   162,   163,   147,     5,
      10,    11,    12,     1,    14,    15,     4,   223,    49,   225,
     176,    52,    49,    56,   180,    52,    26,    27,     1,    50,
     186,     4,     5,     6,     7,     8,     9,    42,   177,    10,
      11,    12,   181,    14,    15,    50,    51,   309,    56,   311,
      53,    51,    55,    52,    57,   317,   318,   319,    55,    56,
      65,    66,     1,   219,    37,     1,    39,   223,     4,   225,
     332,    10,    11,    12,    49,    14,    15,    52,     1,    56,
      53,     4,    55,    56,   346,    49,   348,    49,    52,   331,
      52,     1,   334,    53,     4,     5,     6,     7,     8,     9,
     362,   363,   364,   309,    49,   311,    49,    52,   350,   351,
     352,    49,    49,   269,    52,    52,     1,    56,   380,     4,
       1,    50,     1,     4,   386,     4,   332,    37,    52,    39,
     372,    55,   394,    54,    55,   397,   378,    54,    55,   278,
     346,    50,   348,    53,    49,    55,   318,   319,   390,   274,
     275,   393,    50,   309,    53,   311,   362,   363,   364,     1,
      85,    86,     4,     5,     6,     7,     8,     9,    44,    45,
      46,   317,   318,   319,   380,    50,   332,    50,    20,    56,
     386,    40,    41,    42,    43,    44,    45,    46,   394,    56,
     346,   397,   348,    54,   157,    37,    54,    39,    54,    54,
     339,    55,   341,    55,    55,    50,   362,   363,   364,    55,
      52,    53,    55,    55,    52,     3,    55,   356,   357,   358,
     183,   184,    53,    57,   380,   188,    56,    49,    52,    52,
     386,    56,    53,   196,   197,   198,   199,   376,   394,    56,
      56,   397,    19,   382,    22,   208,   209,    46,    52,    52,
     213,    21,    50,   392,   217,   218,   395,    50,    20,    56,
      56,     1,    56,    55,     4,     5,     6,     7,     8,     9,
       1,    50,    52,     4,     5,     6,     7,     8,     9,    50,
      56,    20,    55,    55,   247,   248,   249,   250,   251,   252,
     253,   254,   255,    56,    19,   258,   259,    37,    56,    39,
      50,    19,    50,     9,     9,   268,    37,    58,    39,    -1,
     273,   274,   275,    53,   342,    55,   279,   218,    -1,    -1,
      -1,    -1,    53,     1,    55,    -1,     4,     5,     6,     7,
       8,     9,     1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    -1,     1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    -1,    -1,    -1,   317,   318,   319,    -1,    -1,    37,
      -1,    39,    10,    11,    12,    13,    14,    15,    37,    -1,
      39,    -1,    -1,    -1,    -1,    53,    -1,    55,    37,   342,
      39,    -1,    -1,    -1,    53,     1,    55,    -1,     4,     5,
       6,     7,     8,     9,    53,     1,    55,    -1,     4,     5,
       6,     7,     8,     9,     1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    39,    -1,    -1,    -1,    53,    -1,    55,
      37,    -1,    39,    -1,    -1,    -1,    -1,    53,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    53,     1,    55,    -1,
       4,     5,     6,     7,     8,     9,     1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    -1,     1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39,    -1,    -1,    -1,    -1,    53,
      -1,    55,    37,    -1,    39,    -1,     1,    -1,    53,     4,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      55,    16,    -1,    18,    -1,    -1,    21,    22,    23,    24,
      25,     1,    -1,    -1,     4,    -1,    -1,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    44,
      45,    21,    22,    23,    24,    25,    51,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,     1,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      16,    51,    18,    -1,    -1,    21,    22,    23,    24,    25,
       1,    -1,    -1,     4,    -1,    -1,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    44,    45,
      21,    22,    23,    24,    25,    51,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,     1,    -1,    -1,     4,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    16,
      51,    18,    -1,    -1,    21,    22,    23,    24,    25,     1,
      -1,    -1,     4,    -1,    -1,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    18,    44,    45,    21,
      22,    23,    24,    25,    51,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,     1,    -1,    -1,     4,    -1,    -1,    -1,
      -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    16,    51,
      18,    -1,    -1,    21,    22,    23,    24,    25,     1,    -1,
      -1,     4,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    18,    44,    45,    21,    22,
      23,    24,    25,    51,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,     1,    -1,    -1,     4,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    16,    51,    18,
      -1,    -1,    21,    22,    23,    24,    25,     1,    -1,    -1,
       4,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    44,    45,    21,    22,    23,
      24,    25,    51,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,     1,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    -1,    -1,    16,    51,    18,    -1,
      -1,    21,    22,    23,    24,    25,     1,    -1,    -1,     4,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    -1,    18,    44,    45,    21,    22,    23,    24,
      25,    51,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,
       1,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    16,    51,    18,    -1,    -1,
      21,    22,    23,    24,    25,     1,    -1,    -1,     4,    -1,
      -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    -1,    18,    44,    45,    21,    22,    23,    24,    25,
      51,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,     1,
      -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    16,    51,    18,    -1,    -1,    21,
      22,    23,    24,    25,     1,    -1,    -1,     4,    -1,     1,
      32,    33,     4,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    18,    44,    45,    21,    22,    23,    24,    25,    51,
      -1,    23,    24,    25,    -1,    32,    33,    -1,    -1,    -1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    44,    45,     4,
      -1,    -1,    44,    45,    51,    10,    11,    12,    50,    14,
      15,     1,    -1,    -1,     4,    -1,    -1,     4,    -1,    -1,
      -1,    26,    27,    10,    11,    12,    -1,    14,    15,    -1,
      -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,    26,
      27,    -1,    32,    33,    -1,    -1,    51,    -1,    -1,    -1,
       4,    -1,    -1,    -1,    44,    45,    10,    11,    12,    -1,
      14,    15,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    34,    35,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    48,    -1,
      -1,    -1,    -1,    34,    35,    36,    56,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    48,    -1,    -1,
      -1,    -1,    34,    35,    36,    56,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    34,    35,    36,    56,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    -1,    -1,    34,    35,
      36,    54,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    -1,    -1,    34,    35,    36,    54,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      34,    35,    36,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    35,    36,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    38,    39,    40,    41,
      42,    43,    44,    45,    46
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  GuavaParser::yystos_[] =
  {
         0,    59,    60,    61,     0,    62,    63,    29,    73,    74,
      75,    78,    30,    10,    11,    12,    13,    14,    15,   119,
      75,    78,    50,     4,    17,   123,   123,    26,    27,    64,
      65,    67,   119,   123,    55,    55,    55,   123,   123,    51,
      65,    67,   119,   123,    52,    52,     1,    31,    69,   123,
      26,    27,    31,     1,    56,     1,    81,     1,    79,    50,
      50,    52,    52,    31,    69,    26,    27,    31,     1,    70,
     123,     1,    49,    52,    69,    69,    70,    56,    50,    56,
      85,    86,   119,    56,    85,    68,    66,    70,    52,    69,
      69,    70,    53,    71,    49,    52,    71,    52,     1,   123,
      52,    52,    50,    76,    50,    82,    49,     1,    28,   123,
      50,    80,    64,    64,    52,    52,    52,    52,     1,     5,
      53,     1,   123,    77,    62,    84,    56,   119,     1,   123,
      83,    56,    51,    51,    54,    54,     1,     5,    71,    71,
      62,    87,    62,    50,     1,    28,   123,    62,    50,    54,
      54,    87,     1,    16,    18,    21,    22,    23,    24,    25,
      32,    33,    44,    45,    51,    88,    89,    90,    91,    92,
      93,    98,   102,   111,   115,   123,    87,    62,     1,   123,
      87,    62,    51,     3,    55,   123,    55,    55,    55,    50,
       1,     5,     6,     7,     8,     9,    37,    39,    53,    55,
     111,   114,   115,   116,   117,   118,   120,   123,    55,    55,
     123,   123,    52,     3,     1,    44,    45,    53,    55,    57,
      72,   122,    51,    87,    51,    87,   114,     1,   112,   113,
     114,     1,   123,     1,   110,   114,     1,   101,   114,   100,
     114,   114,     1,   114,   121,     1,   114,    34,    35,    36,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    48,
     114,   114,     1,   114,     1,   114,   112,   123,    53,    57,
      51,    51,    56,    49,    52,    52,    56,    56,    62,    49,
      54,    56,    56,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,    56,    56,    54,    54,    56,    72,
       1,   114,   123,     1,   114,   114,   116,     1,   116,    19,
      22,    87,     1,   114,    54,    54,    72,    52,    52,    52,
      50,    88,    50,    51,     1,    90,    97,   114,   115,    97,
      97,   103,    20,    52,    99,    21,    56,    56,    56,    62,
      88,    62,    55,    50,    50,    50,    87,    52,    87,   101,
      95,    96,    94,    51,    51,    56,    62,    62,    62,    20,
     104,   107,    87,    87,    87,    18,    50,    20,    51,    51,
      51,    55,   106,    18,    50,   110,    62,    55,   105,    56,
      87,   110,    62,    19,    51,    56,    87,    50,    19,    51,
     108,    50,    62,   109,    87,    62,    51,    87,    51
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  GuavaParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    43,    45,
      42,    47,   293,   294,   295,   296,   297,   298,   299,    44,
     123,   125,    59,    91,    93,    40,    41,    46
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  GuavaParser::yyr1_[] =
  {
         0,    58,    59,    61,    60,    62,    63,    62,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    66,    65,    68,    67,    69,    69,    69,
      69,    70,    70,    70,    70,    71,    71,    71,    71,    72,
      72,    72,    72,    73,    73,    74,    74,    76,    75,    77,
      75,    79,    80,    78,    81,    82,    78,    83,    78,    84,
      78,    85,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    87,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    89,    89,    89,    90,
      90,    90,    91,    91,    92,    92,    94,    93,    95,    93,
      96,    93,    97,    97,    97,    99,    98,   100,    98,   101,
     101,   103,   102,   102,   102,   104,   105,   104,   106,   104,
     104,   108,   107,   109,   107,   110,   110,   111,   111,   112,
     112,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   115,   115,   115,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   120,   121,   121,   121,   121,   122,   122,   122,   122,
     123
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  GuavaParser::yyr2_[] =
  {
         0,     2,     1,     0,     3,     0,     0,     5,     4,     3,
       4,     5,     4,     5,     4,     5,     3,     5,     3,     3,
       2,     2,     4,     0,     6,     0,     6,     1,     3,     1,
       3,     2,     4,     2,     4,     3,     4,     3,     4,     3,
       4,     3,     4,     1,     2,     1,     2,     0,    10,     0,
      11,     0,     0,    12,     0,     0,    12,     0,    11,     0,
      11,     0,     1,     2,     3,     4,     5,     2,     3,     4,
       5,     0,     3,     2,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     3,
       3,     3,     4,     4,     1,     2,     0,    13,     0,    13,
       0,    13,     1,     1,     1,     0,    10,     0,    10,     1,
       1,     0,    11,     7,     9,     0,     0,     7,     0,     6,
       1,     0,    11,     0,    12,     1,     1,     4,     4,     0,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     2,     2,     3,     3,     3,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     1,     2,     3,     4,     3,
       1
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const GuavaParser::yytname_[] =
  {
    "\"end of block\"", "error", "$undefined", "ASSIGN", "\"identifier\"",
  "\"integer value\"", "\"string\"", "\"character\"", "\"real value\"",
  "\"boolean value\"", "TYPE_INTEGER", "TYPE_REAL", "TYPE_CHAR",
  "TYPE_VOID", "TYPE_BOOLEAN", "TYPE_STRING", "\"for loop\"",
  "\"main function\"", "\"if\"", "\"then\"", "\"else\"", "\"while loop\"",
  "\"do clause\"", "\"return statement\"", "\"break statement\"",
  "\"continue statement\"", "\"record\"", "\"union\"", "\"reference\"",
  "\"function\"", "\"declare statement\"", "\"array\"",
  "\"print statement\"", "\"read statement\"", "\"<=> operator\"",
  "\"and operator\"", "\"or operator\"", "\"not operator\"",
  "\"+ operator\"", "\"- operator\"", "\"* operator\"", "\"/ operator\"",
  "\"div operator\"", "\"mod operator\"", "\"++ operator\"",
  "\"-- operator\"", "\"** operator\"", "\"unary - operator\"",
  "COMPARISON", "','", "'{'", "'}'", "';'", "'['", "']'", "'('", "')'",
  "'.'", "$accept", "program", "bloqueprincipal", "$@1", "bloquedeclare",
  "$@2", "lvariables", "union", "$@3", "record", "$@4", "lvar",
  "lvararreglo", "lcorchetes", "lcorchetesExp", "lfunciones",
  "lfunciones1", "funcionmain", "$@5", "$@6", "funcion", "$@7", "$@8",
  "$@9", "$@10", "$@11", "$@12", "lparam", "lparam2", "listainstrucciones",
  "instruccion", "instruccion1", "asignacion", "entradasalida", "retorno",
  "loopfor", "$@13", "$@14", "$@15", "errorloopfor", "loopwhile", "$@16",
  "$@17", "errorloopwhile", "selectorif", "$@18", "lelseif", "$@19",
  "$@20", "lelseif1", "$@21", "$@22", "errorif", "llamadafuncion",
  "lvarovalor", "lvarovalor2", "exp", "expID", "expBool", "expAritmetica",
  "valor", "tipo", "arreglo", "larreglo", "lAccesoAtributos",
  "identificador", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const GuavaParser::rhs_number_type
  GuavaParser::yyrhs_[] =
  {
        59,     0,    -1,    60,    -1,    -1,    61,    62,    73,    -1,
      -1,    -1,    63,    30,    50,    64,    51,    -1,    64,   119,
      69,    52,    -1,   119,    69,    52,    -1,   119,    31,    70,
      52,    -1,    64,   119,    31,    70,    52,    -1,   123,    31,
      70,    52,    -1,    64,   123,    31,    70,    52,    -1,   123,
      27,    69,    52,    -1,    64,   123,    27,    69,    52,    -1,
     123,    26,    69,    -1,    64,   123,    26,    69,    52,    -1,
      64,    65,    52,    -1,    64,    67,    52,    -1,    65,    52,
      -1,    67,    52,    -1,   119,    69,     1,    52,    -1,    -1,
      27,   123,    50,    66,    64,    51,    -1,    -1,    26,   123,
      50,    68,    64,    51,    -1,   123,    -1,    69,    49,   123,
      -1,     1,    -1,    69,    49,     1,    -1,   123,    71,    -1,
      70,    49,   123,    71,    -1,     1,    71,    -1,    70,    49,
       1,    71,    -1,    53,     5,    54,    -1,    71,    53,     5,
      54,    -1,    53,     1,    54,    -1,    71,    53,     1,    54,
      -1,    53,   114,    54,    -1,    72,    53,   114,    54,    -1,
      53,     1,    54,    -1,    72,    53,     1,    54,    -1,    75,
      -1,    74,    75,    -1,    78,    -1,    74,    78,    -1,    -1,
      29,    13,    17,    55,    56,    50,    76,    62,    87,    51,
      -1,    -1,    29,    13,    17,    55,     1,    56,    50,    77,
      62,    87,    51,    -1,    -1,    -1,    29,   119,   123,    55,
      79,    85,    80,    56,    50,    62,    87,    51,    -1,    -1,
      -1,    29,    13,   123,    55,    81,    85,    82,    56,    50,
      62,    87,    51,    -1,    -1,    29,   119,   123,    55,     1,
      56,    50,    83,    62,    87,    51,    -1,    -1,    29,    13,
     123,    55,     1,    56,    50,    84,    62,    87,    51,    -1,
      -1,    86,    -1,   119,   123,    -1,   119,    28,   123,    -1,
      86,    49,   119,   123,    -1,    86,    49,   119,    28,   123,
      -1,   119,     1,    -1,   119,    28,     1,    -1,    86,    49,
     119,     1,    -1,    86,    49,   119,    28,     1,    -1,    -1,
      87,    88,    52,    -1,    87,    89,    -1,    90,    -1,   111,
      -1,    45,   123,    -1,   123,    45,    -1,    44,   123,    -1,
     123,    44,    -1,    91,    -1,    25,    -1,    24,    -1,     1,
     123,    -1,   123,     1,    -1,    92,    -1,    93,    -1,    98,
      -1,   102,    -1,   115,     3,   114,    -1,     1,     3,   114,
      -1,   115,     3,     1,    -1,    33,    55,   114,    56,    -1,
      32,    55,   114,    56,    -1,    23,    -1,    23,   114,    -1,
      -1,    16,    55,   123,    52,   116,    52,    97,    56,    50,
      94,    62,    87,    51,    -1,    -1,    16,    55,     1,    52,
     116,    52,    97,    56,    50,    95,    62,    87,    51,    -1,
      -1,    16,    55,   123,    52,     1,    52,    97,    56,    50,
      96,    62,    87,    51,    -1,    90,    -1,   114,    -1,     1,
      -1,    -1,    21,    55,   101,    56,    22,    50,    99,    62,
      87,    51,    -1,    -1,    22,    50,   100,    62,    87,    51,
      21,    55,   101,    56,    -1,   114,    -1,     1,    -1,    -1,
      18,    55,   110,    56,    19,    50,   103,    62,    87,    51,
     104,    -1,    18,    55,   110,    56,    19,    88,    52,    -1,
      18,    55,   110,    56,    19,    88,    20,    88,    52,    -1,
      -1,    -1,   107,    20,    50,   105,    62,    87,    51,    -1,
      -1,    20,    50,   106,    62,    87,    51,    -1,   107,    -1,
      -1,    20,    18,    55,   110,    56,    19,    50,   108,    62,
      87,    51,    -1,    -1,   107,    20,    18,    55,   110,    56,
      19,    50,   109,    62,    87,    51,    -1,   114,    -1,     1,
      -1,   123,    55,   112,    56,    -1,     1,    55,   112,    56,
      -1,    -1,   113,    -1,   113,    49,   114,    -1,   114,    -1,
     113,    49,     1,    -1,     1,    -1,   117,    -1,   116,    -1,
     118,    -1,   115,    -1,    55,   114,    56,    -1,   111,    -1,
      55,     1,    56,    -1,   123,    -1,   123,    72,    -1,   123,
     122,    -1,   114,    35,   114,    -1,   114,    36,   114,    -1,
     114,    48,   114,    -1,    37,   114,    -1,    39,   114,    -1,
     114,    44,    -1,   114,    45,    -1,   114,    34,   114,    -1,
     114,    38,   114,    -1,   114,    39,   114,    -1,   114,    40,
     114,    -1,   114,    41,   114,    -1,   114,    42,   114,    -1,
     114,    43,   114,    -1,   114,    46,   114,    -1,     9,    -1,
       6,    -1,     7,    -1,     5,    -1,     8,    -1,   120,    -1,
      11,    -1,    10,    -1,    14,    -1,    12,    -1,    15,    -1,
      53,   121,    54,    -1,   121,    49,   114,    -1,   114,    -1,
     121,    49,     1,    -1,     1,    -1,    57,   123,    -1,   122,
      57,   123,    -1,   122,    57,   123,    72,    -1,    57,   123,
      72,    -1,     4,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  GuavaParser::yyprhs_[] =
  {
         0,     0,     3,     5,     6,    10,    11,    12,    18,    23,
      27,    32,    38,    43,    49,    54,    60,    64,    70,    74,
      78,    81,    84,    89,    90,    97,    98,   105,   107,   111,
     113,   117,   120,   125,   128,   133,   137,   142,   146,   151,
     155,   160,   164,   169,   171,   174,   176,   179,   180,   191,
     192,   204,   205,   206,   219,   220,   221,   234,   235,   247,
     248,   260,   261,   263,   266,   270,   275,   281,   284,   288,
     293,   299,   300,   304,   307,   309,   311,   314,   317,   320,
     323,   325,   327,   329,   332,   335,   337,   339,   341,   343,
     347,   351,   355,   360,   365,   367,   370,   371,   385,   386,
     400,   401,   415,   417,   419,   421,   422,   433,   434,   445,
     447,   449,   450,   462,   470,   480,   481,   482,   490,   491,
     498,   500,   501,   513,   514,   527,   529,   531,   536,   541,
     542,   544,   548,   550,   554,   556,   558,   560,   562,   564,
     568,   570,   574,   576,   579,   582,   586,   590,   594,   597,
     600,   603,   606,   610,   614,   618,   622,   626,   630,   634,
     638,   640,   642,   644,   646,   648,   650,   652,   654,   656,
     658,   660,   664,   668,   670,   674,   676,   679,   683,   688,
     692
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  GuavaParser::yyrline_[] =
  {
         0,   153,   153,   156,   156,   171,   173,   173,   178,   183,
     187,   191,   197,   202,   208,   213,   219,   224,   231,   236,
     241,   244,   248,   253,   253,   269,   269,   284,   290,   297,
     301,   303,   307,   311,   315,   322,   328,   333,   336,   340,
     353,   362,   367,   373,   375,   381,   383,   389,   389,   417,
     417,   426,   429,   426,   460,   463,   460,   487,   487,   494,
     494,   500,   504,   507,   514,   521,   527,   533,   534,   535,
     536,   539,   542,   554,   567,   569,   571,   596,   621,   646,
     671,   673,   678,   685,   688,   691,   696,   698,   700,   703,
     727,   730,   735,   744,   754,   757,   766,   766,   804,   804,
     809,   809,   820,   823,   826,   830,   830,   857,   857,   887,
     899,   903,   903,   925,   941,   959,   962,   962,   981,   981,
     997,  1001,  1001,  1021,  1021,  1045,  1056,  1060,  1119,  1123,
    1126,  1129,  1136,  1145,  1147,  1152,  1153,  1154,  1155,  1156,
    1157,  1158,  1162,  1187,  1224,  1251,  1269,  1287,  1350,  1364,
    1378,  1392,  1405,  1438,  1470,  1502,  1534,  1566,  1585,  1604,
    1626,  1631,  1637,  1642,  1647,  1652,  1657,  1660,  1663,  1666,
    1669,  1675,  1686,  1716,  1733,  1737,  1742,  1745,  1749,  1753,
    1757
  };

  // Print the state stack on the debug stream.
  void
  GuavaParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  GuavaParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  GuavaParser::token_number_type
  GuavaParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      55,    56,    40,    38,    49,    39,    57,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    42,    43,    44,    45,    46,    47,    48
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int GuavaParser::yyeof_ = 0;
  const int GuavaParser::yylast_ = 1364;
  const int GuavaParser::yynnts_ = 66;
  const int GuavaParser::yyempty_ = -2;
  const int GuavaParser::yyfinal_ = 4;
  const int GuavaParser::yyterror_ = 1;
  const int GuavaParser::yyerrcode_ = 256;
  const int GuavaParser::yyntokens_ = 58;

  const unsigned int GuavaParser::yyuser_token_number_max_ = 299;
  const GuavaParser::token_number_type GuavaParser::yyundef_token_ = 2;


} // yy

/* Line 1108 of lalr1.cc  */
#line 4112 "GuavaParser.cc"

/* Line 1109 of lalr1.cc  */
#line 1765 "GuavaParser.yy"


void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  if(!error_state)
    error_state = 1;

  driver.error (l, m);
}

