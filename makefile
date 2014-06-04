all: guava

guava: Types.o Symbol.o GuavaSymTable.o GuavaTree.o globals.o GuavaDriver.o GuavaParser.o GuavaLexer.o Guava.o

	g++ -std=c++11 -g -o guava Types.o Symbol.o GuavaSymTable.o GuavaTree.o GuavaDriver.o GuavaParser.o GuavaLexer.o Guava.o

GuavaDriver.o: GuavaDriver.cc GuavaDriver.hh GuavaTree.hh GuavaParser.hh

	g++ -g -c  -std=c++11 GuavaDriver.cc

GuavaParser.o: GuavaParser.cc GuavaParser.hh GuavaTree.hh GuavaDriver.hh

	g++ -g -c -std=c++11 GuavaParser.cc 

GuavaParser.cc GuavaParser.hh: GuavaParser.yy

	bison -r state --defines=GuavaParser.hh -o GuavaParser.cc GuavaParser.yy

GuavaLexer.o: GuavaLexer.cc GuavaParser.hh GuavaDriver.hh

	g++ -g -c -std=c++11 GuavaLexer.cc

GuavaLexer.cc: GuavaLexer.l

	flex -o GuavaLexer.cc GuavaLexer.l

GuavaSymTable.o: GuavaSymTable.cc GuavaSymTable.hh Symbol.hh GuavaTree.hh

	g++ -g -c -std=c++11 GuavaSymTable.cc

Symbol.o: Symbol.cc Symbol.hh Types.hh

	g++ -g -c -std=c++11 Symbol.cc

Types.o: Types.cc Types.hh

	g++ -g -c -std=c++11 Types.cc

GuavaTree.o: GuavaTree.cc GuavaTree.hh GuavaSymTable.hh

	g++ -g -c -std=c++11 GuavaTree.cc

Guava.o: Guava.cc

	g++ -g -c -std=c++11 Guava.cc

globals.o: globals.cc globals.hh GuavaParser.hh

	g++ -g -c -std=c++11 globals.cc

.PHONY: clean

clean:

	-rm *.o GuavaParser.hh GuavaParser.cc *.output location.hh position.hh stack.hh guava GuavaLexer.cc


