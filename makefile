LEX    = flex++

lexer: 	lex.yy.cc
	g++ $^ -o $@

lex.yy.cc: GuavaLexer.l
		flex++ $<

clean: 
	rm lex.yy.cc lexer 