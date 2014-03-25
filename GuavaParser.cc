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
#line 74 "GuavaParser.yy"

# include "GuavaDriver.hh"



/* Line 285 of lalr1.cc  */
#line 59 "GuavaParser.cc"


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
#line 155 "GuavaParser.cc"

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
#line 18 "GuavaParser.yy"
{
  yylloc.begin.filename = yylloc.end.filename = &driver.file;
}

/* Line 538 of lalr1.cc  */
#line 351 "GuavaParser.cc"

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
#line 136 "GuavaParser.yy"
    { //*$$ = Program(*$1); 
                         }
    break;

  case 3:

/* Line 663 of lalr1.cc  */
#line 140 "GuavaParser.yy"
    { 
                   driver.tablaSimbolos.enterScope(); 
                 }
    break;

  case 4:

/* Line 663 of lalr1.cc  */
#line 143 "GuavaParser.yy"
    { //*$$ = BloquePrincipal(*$2, *$3); 
                                            }
    break;

  case 5:

/* Line 663 of lalr1.cc  */
#line 147 "GuavaParser.yy"
    { //*$$ = BloqueDeclare(); 
                                            }
    break;

  case 6:

/* Line 663 of lalr1.cc  */
#line 149 "GuavaParser.yy"
    { //*$$ = BloqueDeclare(*$3); 
                                            }
    break;

  case 7:

/* Line 663 of lalr1.cc  */
#line 153 "GuavaParser.yy"
    { //Tipo tipo = *$1; 
                                                    //LVar lvar = *$3; 
                                                    
                                                  }
    break;

  case 8:

/* Line 663 of lalr1.cc  */
#line 157 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, *$3, 0); 
                                                    }
    break;

  case 9:

/* Line 663 of lalr1.cc  */
#line 159 "GuavaParser.yy"
    {}
    break;

  case 10:

/* Line 663 of lalr1.cc  */
#line 160 "GuavaParser.yy"
    {}
    break;

  case 11:

/* Line 663 of lalr1.cc  */
#line 161 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, *$3, 0); 
                                                    }
    break;

  case 12:

/* Line 663 of lalr1.cc  */
#line 163 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, *$3, $5); 
                                                    }
    break;

  case 13:

/* Line 663 of lalr1.cc  */
#line 165 "GuavaParser.yy"
    {}
    break;

  case 14:

/* Line 663 of lalr1.cc  */
#line 166 "GuavaParser.yy"
    {}
    break;

  case 15:

/* Line 663 of lalr1.cc  */
#line 167 "GuavaParser.yy"
    {}
    break;

  case 16:

/* Line 663 of lalr1.cc  */
#line 168 "GuavaParser.yy"
    {}
    break;

  case 17:

/* Line 663 of lalr1.cc  */
#line 169 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, $3); 
                                                   }
    break;

  case 18:

/* Line 663 of lalr1.cc  */
#line 171 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, $3); 
                                                   }
    break;

  case 19:

/* Line 663 of lalr1.cc  */
#line 173 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, 0); 
                                                   }
    break;

  case 20:

/* Line 663 of lalr1.cc  */
#line 175 "GuavaParser.yy"
    { //*$$ = LVariables(*$1, 0); 
                                                   }
    break;

  case 21:

/* Line 663 of lalr1.cc  */
#line 179 "GuavaParser.yy"
    { //*$$ = Union(Identificador(std::string($2)), $4); 
                                   }
    break;

  case 22:

/* Line 663 of lalr1.cc  */
#line 182 "GuavaParser.yy"
    { //*$$ = Record(Identificador(std::string($2)), $4); 
                                     }
    break;

  case 23:

/* Line 663 of lalr1.cc  */
#line 185 "GuavaParser.yy"
    { //LVar tmp = LVar(Identificador(std::string($1)), 0); 
                     //$$ = &tmp;
                   }
    break;

  case 24:

/* Line 663 of lalr1.cc  */
#line 188 "GuavaParser.yy"
    { //LVar tmp = LVar(Identificador(std::string($1)), $3); 
                     //$$ = &tmp;
                   }
    break;

  case 25:

/* Line 663 of lalr1.cc  */
#line 193 "GuavaParser.yy"
    { //*$$ = LVarArreglo(Identificador(std::string($1)), $2, 0); 
                                           }
    break;

  case 26:

/* Line 663 of lalr1.cc  */
#line 195 "GuavaParser.yy"
    { //*$$ = LVarArreglo(Identificador(std::string($1)), $2, $4); 
                                           }
    break;

  case 27:

/* Line 663 of lalr1.cc  */
#line 198 "GuavaParser.yy"
    { LCorchetes tmp =  LCorchetes(*(yysemantic_stack_[(3) - (2)].classExp),0); 
                                      (yyval.classLCorchetes) = &tmp;
                                    }
    break;

  case 28:

/* Line 663 of lalr1.cc  */
#line 201 "GuavaParser.yy"
    { LCorchetes tmp = LCorchetes(*(yysemantic_stack_[(4) - (2)].classExp),(yysemantic_stack_[(4) - (4)].classLCorchetes));
                                      (yyval.classLCorchetes) = &tmp;
                                    }
    break;

  case 29:

/* Line 663 of lalr1.cc  */
#line 205 "GuavaParser.yy"
    { //*$$ = LFunciones(*$1,0);  
                               }
    break;

  case 30:

/* Line 663 of lalr1.cc  */
#line 207 "GuavaParser.yy"
    { //*$$ = LFunciones(*$1,$2); 
                               }
    break;

  case 31:

/* Line 663 of lalr1.cc  */
#line 210 "GuavaParser.yy"
    { driver.tablaSimbolos.enterScope();   
                                                 }
    break;

  case 32:

/* Line 663 of lalr1.cc  */
#line 212 "GuavaParser.yy"
    { /*Tipo v = Tipo(std::string("void"));
                                                                                            LParam lp = LParam();
                                                                                            *$$ = Funcion(v,Identificador(std::string("main")),lp,*$8,*$9,0); 
                                                                                            driver.tablaSimbolos.exitScope(); */
                                                                                          }
    break;

  case 33:

/* Line 663 of lalr1.cc  */
#line 219 "GuavaParser.yy"
    { driver.tablaSimbolos.enterScope();   
                                             }
    break;

  case 34:

/* Line 663 of lalr1.cc  */
#line 221 "GuavaParser.yy"
    { /**$$ = Funcion(*$2,Identificador(std::string($3))
                                                                                                                 ,*$5,*$9,*$10,*$12); 
                                                                                                   driver.tablaSimbolos.exitScope();*/
                                                                                                  }
    break;

  case 35:

/* Line 663 of lalr1.cc  */
#line 225 "GuavaParser.yy"
    { 
                                                    driver.tablaSimbolos.enterScope();   
                                                  }
    break;

  case 36:

/* Line 663 of lalr1.cc  */
#line 228 "GuavaParser.yy"
    { /*Tipo v = Tipo(std::string("void"));
                                                                                                    *$$ = Funcion(v,Identificador(std::string($3)),*$5,*$9,*$10,0);
                                                                                                    driver.tablaSimbolos.exitScope();*/
                                                                                                  }
    break;

  case 37:

/* Line 663 of lalr1.cc  */
#line 234 "GuavaParser.yy"
    { //*$$ = LParam(); 
                            }
    break;

  case 38:

/* Line 663 of lalr1.cc  */
#line 236 "GuavaParser.yy"
    { //$$ = $1; 
                                }
    break;

  case 39:

/* Line 663 of lalr1.cc  */
#line 239 "GuavaParser.yy"
    { //*$$ = LParam(*$1,Identificador(std::string($2)), LParam());  
                                }
    break;

  case 40:

/* Line 663 of lalr1.cc  */
#line 241 "GuavaParser.yy"
    { //*$$ = LParam(*$1,Identificador(std::string($2)),*$4);
                                }
    break;

  case 41:

/* Line 663 of lalr1.cc  */
#line 245 "GuavaParser.yy"
    { //*$$ = ListaInstrucciones(); 
                                                        }
    break;

  case 42:

/* Line 663 of lalr1.cc  */
#line 247 "GuavaParser.yy"
    { //*$$ = ListaInstrucciones($1,$3); 
                                                        }
    break;

  case 43:

/* Line 663 of lalr1.cc  */
#line 249 "GuavaParser.yy"
    { //*$$ = ListaInstrucciones($1,$2); 
                                                        }
    break;

  case 44:

/* Line 663 of lalr1.cc  */
#line 253 "GuavaParser.yy"
    { 
                            }
    break;

  case 45:

/* Line 663 of lalr1.cc  */
#line 255 "GuavaParser.yy"
    { 
                            }
    break;

  case 46:

/* Line 663 of lalr1.cc  */
#line 257 "GuavaParser.yy"
    { PlusMinus tmp = PlusMinus(Identificador(std::string((yysemantic_stack_[(2) - (2)].strval))), 0); 
                              //$$ = &tmp; 
                            }
    break;

  case 47:

/* Line 663 of lalr1.cc  */
#line 260 "GuavaParser.yy"
    { PlusMinus tmp = PlusMinus(Identificador(std::string((yysemantic_stack_[(2) - (1)].strval))), 1); 
                              //$$ = &tmp;
                            }
    break;

  case 48:

/* Line 663 of lalr1.cc  */
#line 263 "GuavaParser.yy"
    { PlusMinus tmp = PlusMinus(Identificador(std::string((yysemantic_stack_[(2) - (2)].strval))), 2); 
                              (yyval.classInstruccion) = &tmp;
                            }
    break;

  case 49:

/* Line 663 of lalr1.cc  */
#line 266 "GuavaParser.yy"
    { PlusMinus tmp = PlusMinus(Identificador(std::string((yysemantic_stack_[(2) - (1)].strval))), 3); 
                              (yyval.classInstruccion) = &tmp;
                            }
    break;

  case 50:

/* Line 663 of lalr1.cc  */
#line 269 "GuavaParser.yy"
    { 
                            }
    break;

  case 51:

/* Line 663 of lalr1.cc  */
#line 272 "GuavaParser.yy"
    { 
                             }
    break;

  case 52:

/* Line 663 of lalr1.cc  */
#line 274 "GuavaParser.yy"
    { 
                             }
    break;

  case 53:

/* Line 663 of lalr1.cc  */
#line 276 "GuavaParser.yy"
    { 
                             }
    break;

  case 54:

/* Line 663 of lalr1.cc  */
#line 280 "GuavaParser.yy"
    { /*Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,$3);*/
                                     }
    break;

  case 55:

/* Line 663 of lalr1.cc  */
#line 283 "GuavaParser.yy"
    { /*Identificador id = Identificador(std::string($1));
                                       *$$ = Asignacion(id,*$2,$4);*/
                                     }
    break;

  case 56:

/* Line 663 of lalr1.cc  */
#line 286 "GuavaParser.yy"
    { /*Identificador id1 = Identificador(std::string($1));
                                       Identificador id2 = Identificador(std::string($3));
                                       *$$ = Asignacion(id1,id2,$5);*/
                                     }
    break;

  case 57:

/* Line 663 of lalr1.cc  */
#line 292 "GuavaParser.yy"
    { //*$$ = EntradaSalida(0, *$3); 
                                       }
    break;

  case 58:

/* Line 663 of lalr1.cc  */
#line 294 "GuavaParser.yy"
    { //*$$ = EntradaSalida(1, *$3); 
                                         }
    break;

  case 59:

/* Line 663 of lalr1.cc  */
#line 298 "GuavaParser.yy"
    { 
                                                     driver.tablaSimbolos.enterScope();   
                                                   }
    break;

  case 60:

/* Line 663 of lalr1.cc  */
#line 301 "GuavaParser.yy"
    { /*Identificador id = Identificador(std::string($3));
                                                                                          *$$ = LoopFor(id,$5,*$7,*$11,*$12); 
                                                                                          driver.tablaSimbolos.exitScope();*/
                                                                                        }
    break;

  case 61:

/* Line 663 of lalr1.cc  */
#line 305 "GuavaParser.yy"
    { 
                                              driver.tablaSimbolos.enterScope();   
                                            }
    break;

  case 62:

/* Line 663 of lalr1.cc  */
#line 308 "GuavaParser.yy"
    { /*Identificador id = Identificador(std::string($3));
                                                                                          *$$ = LoopFor(id,$5,$7,*$11,*$12);
                                                                                          driver.tablaSimbolos.exitScope();*/
                                                                                        }
    break;

  case 63:

/* Line 663 of lalr1.cc  */
#line 314 "GuavaParser.yy"
    { 
                                      driver.tablaSimbolos.enterScope();   
                                    }
    break;

  case 64:

/* Line 663 of lalr1.cc  */
#line 317 "GuavaParser.yy"
    { /**$$ = LoopWhile($3,*$8,*$9); 
                                                                           driver.tablaSimbolos.exitScope();*/
                                                                         }
    break;

  case 65:

/* Line 663 of lalr1.cc  */
#line 320 "GuavaParser.yy"
    { 
                   driver.tablaSimbolos.enterScope();   
                 }
    break;

  case 66:

/* Line 663 of lalr1.cc  */
#line 323 "GuavaParser.yy"
    { /**$$ = LoopWhile($9,*$4,*$5); 
                                                                           driver.tablaSimbolos.exitScope();*/
                                                                         }
    break;

  case 67:

/* Line 663 of lalr1.cc  */
#line 328 "GuavaParser.yy"
    { 
                                      driver.tablaSimbolos.enterScope();   
                                    }
    break;

  case 68:

/* Line 663 of lalr1.cc  */
#line 331 "GuavaParser.yy"
    { /**$$ = SelectorIf($3,$8,$9,$11);
                                                                                   driver.tablaSimbolos.exitScope();*/
                                                                                 }
    break;

  case 69:

/* Line 663 of lalr1.cc  */
#line 334 "GuavaParser.yy"
    { //*$$ = SelectorIf($3,$6,0); 
                                                                                 }
    break;

  case 70:

/* Line 663 of lalr1.cc  */
#line 336 "GuavaParser.yy"
    { //*$$ = SelectorIf($3,$6,$8); 
                                                                                 }
    break;

  case 71:

/* Line 663 of lalr1.cc  */
#line 340 "GuavaParser.yy"
    { //*$$ = LElseIf(); 
                                                                                   }
    break;

  case 72:

/* Line 663 of lalr1.cc  */
#line 342 "GuavaParser.yy"
    { 
                                        driver.tablaSimbolos.enterScope();   
                                      }
    break;

  case 73:

/* Line 663 of lalr1.cc  */
#line 345 "GuavaParser.yy"
    { /**$$ = LElseIf($4,*$9,*$10,$12);
                                                                                     driver.tablaSimbolos.exitScope();*/
                                                                                   }
    break;

  case 74:

/* Line 663 of lalr1.cc  */
#line 348 "GuavaParser.yy"
    { 
                    driver.tablaSimbolos.enterScope();   
                  }
    break;

  case 75:

/* Line 663 of lalr1.cc  */
#line 351 "GuavaParser.yy"
    { /**$$ = LElseIf(*$4,*$5); 
                                                                                      driver.tablaSimbolos.exitScope();*/
                                                                                    }
    break;

  case 76:

/* Line 663 of lalr1.cc  */
#line 356 "GuavaParser.yy"
    { //*$$ = LlamadaFuncion(Identificador(std::string($1)),*$3); 
                                      }
    break;

  case 77:

/* Line 663 of lalr1.cc  */
#line 360 "GuavaParser.yy"
    { LVaroValor tmp= LVaroValor();
                            (yyval.classLVaroValor) = &tmp;
                          }
    break;

  case 78:

/* Line 663 of lalr1.cc  */
#line 363 "GuavaParser.yy"
    { 
                          }
    break;

  case 79:

/* Line 663 of lalr1.cc  */
#line 366 "GuavaParser.yy"
    { Exp e = (yysemantic_stack_[(3) - (1)].classExp);
                                       LVaroValor tmp = LVaroValor(&e,(yysemantic_stack_[(3) - (3)].classLVaroValor));
                                       (yyval.classLVaroValor) = &tmp; 
                                     }
    break;

  case 80:

/* Line 663 of lalr1.cc  */
#line 370 "GuavaParser.yy"
    { Exp e = (yysemantic_stack_[(1) - (1)].classExp);
                                       LVaroValor tmp = LVaroValor(&e);
                                       (yyval.classLVaroValor) = &tmp; 
                                     }
    break;

  case 81:

/* Line 663 of lalr1.cc  */
#line 376 "GuavaParser.yy"
    {  
                  }
    break;

  case 82:

/* Line 663 of lalr1.cc  */
#line 378 "GuavaParser.yy"
    {  
                  }
    break;

  case 83:

/* Line 663 of lalr1.cc  */
#line 380 "GuavaParser.yy"
    {  
                  }
    break;

  case 84:

/* Line 663 of lalr1.cc  */
#line 382 "GuavaParser.yy"
    { 
                  }
    break;

  case 85:

/* Line 663 of lalr1.cc  */
#line 384 "GuavaParser.yy"
    { 
                  }
    break;

  case 86:

/* Line 663 of lalr1.cc  */
#line 388 "GuavaParser.yy"
    { 
                               ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("and"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 87:

/* Line 663 of lalr1.cc  */
#line 392 "GuavaParser.yy"
    { 
                               ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("or"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 88:

/* Line 663 of lalr1.cc  */
#line 396 "GuavaParser.yy"
    { int cmpv = (yysemantic_stack_[(3) - (2)].subtok);
                               ExpBin eb;
                               switch(cmpv){
                                    case 1:
                                        eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string(">"));
                                        (yyval.classExpBin) = &eb;
                                        break;
                                    case 2:
                                        eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("<"));
                                        (yyval.classExpBin) = &eb;
                                        break;
                                    case 3:
                                        eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("<="));
                                        (yyval.classExpBin) = &eb;
                                        break;
                                    case 4:
                                        eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string(">="));
                                        (yyval.classExpBin) = &eb;
                                        break;
                                    case 5:
                                        eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("="));
                                        (yyval.classExpBin) = &eb;
                                        break;
                                    case 6:
                                        eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("!="));
                                        (yyval.classExpBin) = &eb;
                                        break;
                               }
                             }
    break;

  case 89:

/* Line 663 of lalr1.cc  */
#line 425 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("<=>"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 90:

/* Line 663 of lalr1.cc  */
#line 428 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("+"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 91:

/* Line 663 of lalr1.cc  */
#line 431 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("-"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 92:

/* Line 663 of lalr1.cc  */
#line 434 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("*"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 93:

/* Line 663 of lalr1.cc  */
#line 437 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("/"));
                               (yyval.classExpBin) = &eb;
                             }
    break;

  case 94:

/* Line 663 of lalr1.cc  */
#line 440 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("div"));
                               (yyval.classExpBin) = &eb; 
                             }
    break;

  case 95:

/* Line 663 of lalr1.cc  */
#line 443 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("mod"));
                               (yyval.classExpBin) = &eb; 
                             }
    break;

  case 96:

/* Line 663 of lalr1.cc  */
#line 446 "GuavaParser.yy"
    { ExpBin eb = ExpBin(*(yysemantic_stack_[(3) - (1)].classExp),*(yysemantic_stack_[(3) - (3)].classExp),std::string("**"));
                               (yyval.classExpBin) = &eb; 
                             }
    break;

  case 97:

/* Line 663 of lalr1.cc  */
#line 449 "GuavaParser.yy"
    {	Exp id1 = Identificador(std::string((yysemantic_stack_[(3) - (1)].strval))); /* Es necesario considerar el caso ID.ID.ID... */ 
                                Exp id2 = Identificador(std::string((yysemantic_stack_[(3) - (3)].strval)));
                                ExpBin eb = ExpBin(id1,id2,std::string("."));
                             	(yyval.classExpBin) = &eb;
                             }
    break;

  case 98:

/* Line 663 of lalr1.cc  */
#line 456 "GuavaParser.yy"
    { std::string str = std::string("not");
                               ExpUn tmp = ExpUn(*(yysemantic_stack_[(2) - (2)].classExp), &str);
                               (yyval.classExpUn) = &tmp; 
                             }
    break;

  case 99:

/* Line 663 of lalr1.cc  */
#line 460 "GuavaParser.yy"
    { std::string str = std::string("-");
                               ExpUn tmp = ExpUn(*(yysemantic_stack_[(2) - (2)].classExp), &str);
                               (yyval.classExpUn) = &tmp; 
                             }
    break;

  case 100:

/* Line 663 of lalr1.cc  */
#line 464 "GuavaParser.yy"
    { std::string str = std::string("++sufijo");
                               ExpUn tmp = ExpUn(*(yysemantic_stack_[(2) - (1)].classExp), &str);
                               (yyval.classExpUn) = &tmp; 
                             }
    break;

  case 101:

/* Line 663 of lalr1.cc  */
#line 468 "GuavaParser.yy"
    { std::string str = std::string("--sufijo");
                               ExpUn tmp = ExpUn(*(yysemantic_stack_[(2) - (1)].classExp), &str);
                               (yyval.classExpUn) = &tmp;
                             }
    break;

  case 102:

/* Line 663 of lalr1.cc  */
#line 472 "GuavaParser.yy"
    { std::string str = std::string("++prefijo");
                              ExpUn tmp = ExpUn(*(yysemantic_stack_[(2) - (2)].classExp), &str);
                              (yyval.classExpUn) = &tmp; 
                            }
    break;

  case 103:

/* Line 663 of lalr1.cc  */
#line 476 "GuavaParser.yy"
    { 
                               std::string str = std::string("--prefijo");
                               Exp e = *(yysemantic_stack_[(2) - (2)].classExp);
                               ExpUn tmp = ExpUn(e, &str);
                               (yyval.classExpUn) = &tmp; 
                             }
    break;

  case 104:

/* Line 663 of lalr1.cc  */
#line 482 "GuavaParser.yy"
    { Exp id = Identificador(std::string((yysemantic_stack_[(2) - (1)].strval)));
                               ExpUn tmp = ExpUn(id, (yysemantic_stack_[(2) - (2)].classLCorchetes));
                               (yyval.classExpUn) = &tmp;
                             }
    break;

  case 105:

/* Line 663 of lalr1.cc  */
#line 487 "GuavaParser.yy"
    { Valor tmp = Bool((yysemantic_stack_[(1) - (1)].boolval));
                  (yyval.classValor) = &tmp;
                }
    break;

  case 106:

/* Line 663 of lalr1.cc  */
#line 490 "GuavaParser.yy"
    { Valor tmp = String((yysemantic_stack_[(1) - (1)].strval));
                  (yyval.classValor) = &tmp;
                }
    break;

  case 107:

/* Line 663 of lalr1.cc  */
#line 493 "GuavaParser.yy"
    { Valor tmp = Char((yysemantic_stack_[(1) - (1)].charval));
                  (yyval.classValor) = &tmp;
                }
    break;

  case 108:

/* Line 663 of lalr1.cc  */
#line 496 "GuavaParser.yy"
    { Integer tmp;
                  tmp = Integer((yysemantic_stack_[(1) - (1)].intval));
                  (yyval.classValor) = &tmp;
                }
    break;

  case 109:

/* Line 663 of lalr1.cc  */
#line 500 "GuavaParser.yy"
    { Valor tmp = Real((yysemantic_stack_[(1) - (1)].realval));
                  (yyval.classValor) = &tmp;
                }
    break;

  case 110:

/* Line 663 of lalr1.cc  */
#line 503 "GuavaParser.yy"
    {
                  (yyval.classValor) = (yysemantic_stack_[(1) - (1)].classArreglo);
                }
    break;

  case 111:

/* Line 663 of lalr1.cc  */
#line 508 "GuavaParser.yy"
    { Tipo tmp = Tipo(std::string("real"));
                      (yyval.classTipo) = &tmp;
                    }
    break;

  case 112:

/* Line 663 of lalr1.cc  */
#line 511 "GuavaParser.yy"
    { Tipo tmp = Tipo(std::string("integer"));
                      (yyval.classTipo) = &tmp;
                    }
    break;

  case 113:

/* Line 663 of lalr1.cc  */
#line 514 "GuavaParser.yy"
    { Tipo tmp = Tipo(std::string("boolean"));
                      (yyval.classTipo) = &tmp;
                    }
    break;

  case 114:

/* Line 663 of lalr1.cc  */
#line 517 "GuavaParser.yy"
    { Tipo tmp = Tipo(std::string("character"));
                      (yyval.classTipo) = &tmp;
                    }
    break;

  case 115:

/* Line 663 of lalr1.cc  */
#line 520 "GuavaParser.yy"
    { Tipo tmp = Tipo(std::string("string"));
                      (yyval.classTipo) = &tmp;
                    }
    break;

  case 116:

/* Line 663 of lalr1.cc  */
#line 525 "GuavaParser.yy"
    {
                            Arreglo tmp;
                            LArreglo *lr = (yysemantic_stack_[(3) - (2)].classLArreglo);
                            tmp = Arreglo(lr);
                            (yyval.classArreglo) = &tmp; 
                          }
    break;

  case 117:

/* Line 663 of lalr1.cc  */
#line 534 "GuavaParser.yy"
    { 
                                  Exp e = *(yysemantic_stack_[(3) - (1)].classExp);
                                  LArreglo *l = (yysemantic_stack_[(3) - (3)].classLArreglo);
                                  LArreglo tmp = LArreglo(e,l); 
                                  (yyval.classLArreglo) = &tmp;
                                }
    break;

  case 118:

/* Line 663 of lalr1.cc  */
#line 540 "GuavaParser.yy"
    { 
                                  LArreglo tmp = LArreglo(*(yysemantic_stack_[(1) - (1)].classExp),0);
                                  (yyval.classLArreglo) = &tmp;
                                 
                                }
    break;



/* Line 663 of lalr1.cc  */
#line 1525 "GuavaParser.cc"
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
  const short int GuavaParser::yypact_ninf_ = -212;
  const short int
  GuavaParser::yypact_[] =
  {
      -212,    12,  -212,   -15,  -212,   -30,    15,   114,    26,  -212,
    -212,    15,    49,  -212,  -212,  -212,  -212,  -212,    53,    61,
     -22,    11,    16,     4,    -1,    64,  -212,    68,    68,    39,
      40,  -212,   114,   114,    44,    68,    87,    42,    51,    72,
      75,    62,    82,   114,   114,  -212,  -212,    68,    83,    63,
      86,   114,   170,    67,   170,   114,   114,    88,    93,  -212,
     114,   148,    97,   114,  -212,   104,  -212,   158,   116,   110,
    -212,  -212,  -212,  -212,  -212,   -48,  -212,  -212,  -212,  -212,
    -212,   148,   148,   148,   148,   148,   148,   317,  -212,  -212,
    -212,  -212,    87,  -212,   118,   122,  -212,   126,   173,  -212,
     442,  -212,    65,    65,   333,   125,   209,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,  -212,  -212,   148,
      63,  -212,  -212,   170,   -15,  -212,  -212,   148,  -212,  -212,
     410,   422,   433,   442,    58,    58,   100,   100,   100,   100,
     140,  -212,   -15,  -212,    76,   -15,  -212,    76,    24,   134,
     135,   136,   143,   141,   142,   191,   194,   149,   154,    76,
    -212,  -212,  -212,  -212,  -212,  -212,    76,   156,   148,  -212,
    -212,   148,   203,   205,   210,   148,   148,  -212,   148,   148,
    -212,  -212,  -212,    76,  -212,   190,  -212,   397,   159,  -212,
     347,   213,   148,   167,   227,   245,   -15,   165,   168,  -212,
     148,  -212,   148,   148,   397,   148,   201,   204,    76,  -212,
    -212,   361,  -212,   397,   379,    41,   176,   177,   178,   164,
    -212,   211,  -212,   208,  -212,     7,   180,   263,   -15,    -3,
     -15,   182,   228,   205,   184,   189,    76,  -212,    76,   148,
     213,  -212,  -212,   197,   207,   281,   -15,   -15,   220,  -212,
    -212,    76,    76,   -16,  -212,   225,   226,   186,  -212,  -212,
    -212,   148,   -15,   299,    76,   239,   243,   229,  -212,  -212,
     -15,    76,   244,   220,  -212
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  GuavaParser::yydefact_[] =
  {
         3,     0,     2,     5,     1,     0,     0,     0,     0,     4,
      29,     0,     0,   112,   111,   114,   113,   115,     0,     0,
       0,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,     6,    19,    20,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    18,     0,     0,     0,
       0,    10,    37,     0,    37,    15,    13,     0,     0,    24,
       8,     0,    25,    11,     9,     0,    38,     0,     0,     0,
      16,    14,    22,    21,     7,    84,   108,   106,   107,   109,
     105,     0,     0,     0,     0,     0,     0,     0,    81,    82,
      83,   110,     0,    12,     0,    39,    31,     0,     0,   104,
      98,    99,   103,   102,   118,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,   100,     0,
      27,    26,    35,     0,     5,    33,    97,     0,   116,    85,
      88,    89,    86,    87,    90,    91,    92,    93,    95,    94,
      96,    28,     5,    40,    41,     5,   117,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      44,    50,    51,    52,    53,    45,    41,     0,     0,    47,
      49,    77,     0,     0,     0,     0,     0,    65,    77,    77,
      46,    48,    32,    41,    43,     0,    36,    54,     0,    78,
      80,     0,     0,     0,     0,     0,     5,     0,     0,    42,
       0,    76,     0,     0,    55,     0,     0,     0,    41,    58,
      57,     0,    79,    56,     0,     0,     0,     0,     0,     0,
      67,    69,    63,     0,    34,    84,     0,     0,     5,     0,
       5,     0,     0,   104,     0,     0,    41,    70,    41,     0,
      97,    59,    61,     0,     0,     0,     5,     5,    71,    64,
      66,    41,    41,     0,    68,     0,     0,     0,    74,    60,
      62,     0,     5,     0,    41,     0,     0,     0,    75,    72,
       5,    41,     0,    71,    73
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  GuavaParser::yypgoto_[] =
  {
      -212,  -212,  -212,  -212,  -111,   179,  -212,  -212,   -21,   185,
     -64,   248,  -212,  -212,  -212,  -212,  -212,   206,   172,   -88,
    -211,  -212,    77,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,    38,  -212,  -212,  -212,   -96,   111,   -61,  -212,
    -212,  -212,     9,  -212,   187
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  GuavaParser::yydefgoto_[] =
  {
        -1,     1,     2,     3,     6,    20,    21,    22,    37,    50,
      62,     9,    10,   124,    11,   145,   142,    65,    66,   157,
     158,   159,   160,   161,   162,   246,   247,   163,   230,   196,
     164,   228,   254,   270,   262,   165,   188,   189,   190,    88,
      89,    90,    23,    91,   105
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char GuavaParser::yytable_ninf_ = -1;
  const short int
  GuavaParser::yytable_[] =
  {
        87,   148,   257,    38,   221,    61,    41,    42,    34,    98,
     168,    99,     4,   144,    48,     5,    39,    25,   237,     7,
     100,   101,   102,   103,   104,   106,    59,   168,    31,   153,
     154,   147,    35,   258,   166,    36,    13,    14,    15,    24,
      16,    17,   155,   156,     8,   148,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   141,    29,   140,   167,
      61,    67,    32,    67,   232,    30,   104,    33,    40,   169,
     170,   184,    34,   153,   154,    27,    28,    61,   185,   171,
     148,   172,   197,   198,   173,   208,   155,   156,    43,    44,
     220,    49,   149,    51,   150,   199,    47,   151,   152,   113,
     114,   115,   116,   117,   118,   119,    52,   187,   153,   154,
      -1,    -1,   119,    55,   194,   195,    61,   236,    12,   238,
     217,   155,   156,    68,    13,    14,    15,    53,    16,    17,
      54,   204,    67,    56,    60,   251,   252,    63,    72,   211,
      18,    19,   213,    73,   214,   117,   118,   119,   243,    92,
     244,   264,    75,    76,    77,    78,    79,    80,   227,   271,
      94,   233,    95,   255,   256,    96,    97,   122,   225,    76,
      77,    78,    79,    80,   123,   125,   266,   126,   245,   128,
      13,    14,    15,   272,    16,    17,    81,   119,    82,   174,
     175,   176,   177,    83,    84,   180,   178,   179,   181,   182,
     263,    85,    81,    86,    82,   183,   186,   191,   192,    83,
      84,    45,    46,   200,   193,   201,   203,    85,   205,    86,
     215,   209,    57,    58,   210,   222,   216,   223,   224,   231,
      64,   229,   240,   241,    70,    71,   234,   239,   242,    74,
     253,   261,    93,   107,   108,   109,   110,   248,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   249,   267,    26,
      69,   107,   108,   109,   110,   129,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   259,   260,   121,   269,   107,
     108,   109,   110,   206,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   268,   273,   143,   226,   107,   108,   109,
     110,   207,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   274,     0,   212,   146,   107,   108,   109,   110,   235,
     111,   112,   113,   114,   115,   116,   117,   118,   119,     0,
       0,     0,     0,   107,   108,   109,   110,   250,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     0,     0,     0,
       0,   107,   108,   109,   110,   265,   111,   112,   113,   114,
     115,   116,   117,   118,   119,     0,     0,   107,   108,   109,
     110,   120,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   107,   108,   109,   110,   127,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   107,   108,   109,   110,   202,
     111,   112,   113,   114,   115,   116,   117,   118,   119,     0,
       0,     0,   218,   107,   108,   109,   110,     0,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     0,     0,     0,
     219,   107,   108,   109,   110,     0,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   108,   109,   110,     0,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   109,   110,
       0,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     110,     0,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   111,   112,   113,   114,   115,   116,   117,   118,   119
  };

  /* YYCHECK.  */
  const short int
  GuavaParser::yycheck_[] =
  {
        61,     4,    18,     4,   215,    53,    27,    28,     4,    57,
       3,    75,     0,   124,    35,    30,    17,     8,   229,    49,
      81,    82,    83,    84,    85,    86,    47,     3,    50,    32,
      33,   142,    28,    49,   145,    31,    10,    11,    12,    13,
      14,    15,    45,    46,    29,     4,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   120,     4,   119,   147,
      53,    52,    51,    54,    57,     4,   127,    51,     4,    45,
      46,   159,     4,    32,    33,    26,    27,    53,   166,    55,
       4,    57,   178,   179,   148,   196,    45,    46,    49,    49,
      49,     4,    16,    51,    18,   183,    52,    21,    22,    41,
      42,    43,    44,    45,    46,    47,    55,   168,    32,    33,
      45,    46,    47,    51,   175,   176,    53,   228,     4,   230,
     208,    45,    46,    56,    10,    11,    12,    55,    14,    15,
      55,   192,   123,    51,    51,   246,   247,    51,    50,   200,
      26,    27,   203,    50,   205,    45,    46,    47,   236,    52,
     238,   262,     4,     5,     6,     7,     8,     9,   219,   270,
      56,   225,     4,   251,   252,    49,    56,    49,     4,     5,
       6,     7,     8,     9,    52,    49,   264,     4,   239,    54,
      10,    11,    12,   271,    14,    15,    38,    47,    40,    55,
      55,    55,    49,    45,    46,     4,    55,    55,     4,    50,
     261,    53,    38,    55,    40,    51,    50,     4,     3,    45,
      46,    32,    33,    23,     4,    56,     3,    53,    51,    55,
      19,    56,    43,    44,    56,    49,    22,    50,    50,    21,
      51,    20,     4,    49,    55,    56,    56,    55,    49,    60,
      20,    55,    63,    34,    35,    36,    37,    50,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    50,    19,    11,
      54,    34,    35,    36,    37,    56,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    50,    50,    92,    49,    34,
      35,    36,    37,    56,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    50,    50,   123,   219,    34,    35,    36,
      37,    56,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   273,    -1,   202,   127,    34,    35,    36,    37,    56,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    56,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    56,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    34,    35,    36,
      37,    54,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    34,    35,    36,    37,    52,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    34,    35,    36,    37,    52,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    51,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      51,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    39,    40,    41,    42,    43,    44,    45,    46,    47
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  GuavaParser::yystos_[] =
  {
         0,    59,    60,    61,     0,    30,    62,    49,    29,    69,
      70,    72,     4,    10,    11,    12,    14,    15,    26,    27,
      63,    64,    65,   100,    13,   100,    69,    26,    27,     4,
       4,    50,    51,    51,     4,    28,    31,    66,     4,    17,
       4,    66,    66,    49,    49,    63,    63,    52,    66,     4,
      67,    51,    55,    55,    55,    51,    51,    63,    63,    66,
      51,    53,    68,    51,    63,    75,    76,   100,    56,    75,
      63,    63,    50,    50,    63,     4,     5,     6,     7,     8,
       9,    38,    40,    45,    46,    53,    55,    96,    97,    98,
      99,   101,    52,    63,    56,     4,    49,    56,    57,    68,
      96,    96,    96,    96,    96,   102,    96,    34,    35,    36,
      37,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      54,    67,    49,    52,    71,    49,     4,    52,    54,    56,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    68,    74,    76,    62,    73,   102,    62,     4,    16,
      18,    21,    22,    32,    33,    45,    46,    77,    78,    79,
      80,    81,    82,    85,    88,    93,    62,    77,     3,    45,
      46,    55,    57,    68,    55,    55,    55,    49,    55,    55,
       4,     4,    50,    51,    77,    77,    50,    96,    94,    95,
      96,     4,     3,     4,    96,    96,    87,    94,    94,    77,
      23,    56,    52,     3,    96,    51,    56,    56,    62,    56,
      56,    96,    95,    96,    96,    19,    22,    77,    51,    51,
      49,    78,    49,    50,    50,     4,    80,    96,    89,    20,
      86,    21,    57,    68,    56,    56,    62,    78,    62,    55,
       4,    49,    49,    77,    77,    96,    83,    84,    50,    50,
      56,    62,    62,    20,    90,    77,    77,    18,    49,    50,
      50,    55,    92,    96,    62,    56,    77,    19,    50,    49,
      91,    62,    77,    50,    90
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,    43,
      45,    42,    47,   294,   295,   296,   297,   298,   299,   123,
     125,    59,    44,    91,    93,    40,    41,    46
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  GuavaParser::yyr1_[] =
  {
         0,    58,    59,    61,    60,    62,    62,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    71,    70,    73,    72,    74,    72,    75,    75,    76,
      76,    77,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    79,    80,    80,    80,    81,    81,    83,
      82,    84,    82,    86,    85,    87,    85,    89,    88,    88,
      88,    90,    91,    90,    92,    90,    93,    94,    94,    95,
      95,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    99,    99,    99,    99,    99,
      99,   100,   100,   100,   100,   100,   101,   102,   102
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  GuavaParser::yyr2_[] =
  {
         0,     2,     1,     0,     3,     0,     4,     5,     4,     4,
       3,     4,     5,     4,     5,     4,     5,     3,     3,     2,
       2,     5,     5,     1,     3,     2,     4,     3,     4,     1,
       2,     0,    10,     0,    14,     0,    11,     0,     1,     2,
       4,     0,     3,     2,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     3,     4,     5,     4,     4,     0,
      13,     0,    13,     0,    10,     0,    10,     0,    11,     6,
       8,     0,     0,    12,     0,     6,     4,     0,     1,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const GuavaParser::yytname_[] =
  {
    "END", "error", "$undefined", "ASSIGN", "ID", "INTEGER", "STRING",
  "CHAR", "REAL", "BOOL", "TYPE_INTEGER", "TYPE_REAL", "TYPE_CHAR",
  "TYPE_VOID", "TYPE_BOOLEAN", "TYPE_STRING", "FOR", "MAIN", "IF", "THEN",
  "ELSE", "WHILE", "DO", "RETURN", "BREAK", "CONTINUE", "RECORD", "UNION",
  "VAR", "FUNCTION", "DECLARE", "ARRAY", "PRINT", "READ", "COMPARISON",
  "UFO", "AND", "OR", "NOT", "'+'", "'-'", "'*'", "'/'", "MOD", "DIV",
  "MINUSMINUS", "PLUSPLUS", "POW", "UMINUS", "'{'", "'}'", "';'", "','",
  "'['", "']'", "'('", "')'", "'.'", "$accept", "program",
  "bloqueprincipal", "$@1", "bloquedeclare", "lvariables", "union",
  "record", "lvar", "lvararreglo", "lcorchetes", "lfunciones",
  "funcionmain", "$@2", "funcion", "$@3", "$@4", "lparam", "lparam2",
  "listainstrucciones", "instruccion", "instruccion1", "asignacion",
  "entradasalida", "loopfor", "$@5", "$@6", "loopwhile", "$@7", "$@8",
  "selectorif", "$@9", "lelseif", "$@10", "$@11", "llamadafuncion",
  "lvarovalor", "lvarovalor2", "exp", "expbin", "expun", "valor", "tipo",
  "arreglo", "larreglo", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const GuavaParser::rhs_number_type
  GuavaParser::yyrhs_[] =
  {
        59,     0,    -1,    60,    -1,    -1,    61,    62,    69,    -1,
      -1,    30,    49,    63,    50,    -1,   100,    28,    66,    51,
      63,    -1,   100,    28,    66,    51,    -1,   100,    66,    51,
      63,    -1,   100,    66,    51,    -1,   100,    31,    67,    51,
      -1,   100,    31,    67,    51,    63,    -1,     4,    27,    66,
      51,    -1,     4,    27,    66,    51,    63,    -1,     4,    26,
      66,    51,    -1,     4,    26,    66,    51,    63,    -1,    64,
      51,    63,    -1,    65,    51,    63,    -1,    64,    51,    -1,
      65,    51,    -1,    27,     4,    49,    63,    50,    -1,    26,
       4,    49,    63,    50,    -1,     4,    -1,     4,    52,    66,
      -1,     4,    68,    -1,     4,    68,    52,    67,    -1,    53,
      96,    54,    -1,    53,    96,    54,    68,    -1,    70,    -1,
      72,    69,    -1,    -1,    29,    13,    17,    55,    56,    49,
      71,    62,    77,    50,    -1,    -1,    29,   100,     4,    55,
      75,    56,    49,    73,    62,    77,    23,    96,    51,    50,
      -1,    -1,    29,    13,     4,    55,    75,    56,    49,    74,
      62,    77,    50,    -1,    -1,    76,    -1,   100,     4,    -1,
     100,     4,    52,    76,    -1,    -1,    78,    51,    77,    -1,
      79,    77,    -1,    80,    -1,    93,    -1,    45,     4,    -1,
       4,    45,    -1,    46,     4,    -1,     4,    46,    -1,    81,
      -1,    82,    -1,    85,    -1,    88,    -1,     4,     3,    96,
      -1,     4,    68,     3,    96,    -1,     4,    57,     4,     3,
      96,    -1,    33,    55,    94,    56,    -1,    32,    55,    94,
      56,    -1,    -1,    16,    55,     4,    51,    96,    51,    80,
      56,    49,    83,    62,    77,    50,    -1,    -1,    16,    55,
       4,    51,    96,    51,    96,    56,    49,    84,    62,    77,
      50,    -1,    -1,    21,    55,    96,    56,    22,    49,    86,
      62,    77,    50,    -1,    -1,    22,    49,    87,    62,    77,
      50,    21,    55,    96,    56,    -1,    -1,    18,    55,    96,
      56,    19,    49,    89,    62,    77,    50,    90,    -1,    18,
      55,    96,    56,    19,    78,    -1,    18,    55,    96,    56,
      19,    78,    20,    78,    -1,    -1,    -1,    20,    18,    55,
      96,    56,    19,    49,    91,    62,    77,    50,    90,    -1,
      -1,    20,    49,    92,    62,    77,    50,    -1,     4,    55,
      94,    56,    -1,    -1,    95,    -1,    96,    52,    95,    -1,
      96,    -1,    97,    -1,    98,    -1,    99,    -1,     4,    -1,
      55,    96,    56,    -1,    96,    36,    96,    -1,    96,    37,
      96,    -1,    96,    34,    96,    -1,    96,    35,    96,    -1,
      96,    39,    96,    -1,    96,    40,    96,    -1,    96,    41,
      96,    -1,    96,    42,    96,    -1,    96,    44,    96,    -1,
      96,    43,    96,    -1,    96,    47,    96,    -1,     4,    57,
       4,    -1,    38,    96,    -1,    40,    96,    -1,    96,    46,
      -1,    96,    45,    -1,    46,    96,    -1,    45,    96,    -1,
       4,    68,    -1,     9,    -1,     6,    -1,     7,    -1,     5,
      -1,     8,    -1,   101,    -1,    11,    -1,    10,    -1,    14,
      -1,    12,    -1,    15,    -1,    53,   102,    54,    -1,    96,
      52,   102,    -1,    96,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  GuavaParser::yyprhs_[] =
  {
         0,     0,     3,     5,     6,    10,    11,    16,    22,    27,
      32,    36,    41,    47,    52,    58,    63,    69,    73,    77,
      80,    83,    89,    95,    97,   101,   104,   109,   113,   118,
     120,   123,   124,   135,   136,   151,   152,   164,   165,   167,
     170,   175,   176,   180,   183,   185,   187,   190,   193,   196,
     199,   201,   203,   205,   207,   211,   216,   222,   227,   232,
     233,   247,   248,   262,   263,   274,   275,   286,   287,   299,
     306,   315,   316,   317,   330,   331,   338,   343,   344,   346,
     350,   352,   354,   356,   358,   360,   364,   368,   372,   376,
     380,   384,   388,   392,   396,   400,   404,   408,   412,   415,
     418,   421,   424,   427,   430,   433,   435,   437,   439,   441,
     443,   445,   447,   449,   451,   453,   455,   459,   463
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  GuavaParser::yyrline_[] =
  {
         0,   136,   136,   140,   140,   147,   149,   153,   157,   159,
     160,   161,   163,   165,   166,   167,   168,   169,   171,   173,
     175,   179,   182,   185,   188,   193,   195,   198,   201,   205,
     207,   210,   210,   219,   219,   225,   225,   234,   236,   239,
     241,   245,   247,   249,   253,   255,   257,   260,   263,   266,
     269,   272,   274,   276,   280,   283,   286,   292,   294,   298,
     298,   305,   305,   314,   314,   320,   320,   328,   328,   334,
     336,   340,   342,   342,   348,   348,   355,   360,   363,   366,
     370,   376,   378,   380,   382,   384,   388,   392,   396,   425,
     428,   431,   434,   437,   440,   443,   446,   449,   456,   460,
     464,   468,   472,   476,   482,   487,   490,   493,   496,   500,
     503,   508,   511,   514,   517,   520,   525,   534,   540
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
      55,    56,    41,    39,    52,    40,    57,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    51,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
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
      35,    36,    37,    38,    43,    44,    45,    46,    47,    48
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int GuavaParser::yyeof_ = 0;
  const int GuavaParser::yylast_ = 489;
  const int GuavaParser::yynnts_ = 45;
  const int GuavaParser::yyempty_ = -2;
  const int GuavaParser::yyfinal_ = 4;
  const int GuavaParser::yyterror_ = 1;
  const int GuavaParser::yyerrcode_ = 256;
  const int GuavaParser::yyntokens_ = 58;

  const unsigned int GuavaParser::yyuser_token_number_max_ = 299;
  const GuavaParser::token_number_type GuavaParser::yyundef_token_ = 2;


} // yy

/* Line 1108 of lalr1.cc  */
#line 2295 "GuavaParser.cc"

/* Line 1109 of lalr1.cc  */
#line 547 "GuavaParser.yy"


void yy::GuavaParser::error (const yy::GuavaParser::location_type& l, const std::string& m)
{
  driver.error (l, m);
}

