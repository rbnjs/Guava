CC=clang++

all: guava

guava:  Generator.o Types.o Symbol.o GuavaSymTable.o GuavaQuads.o GrafoBloques.o GuavaTree.o GuavaDriver.o GuavaParser.o GuavaLexer.o Guava.o

	$(CC) -std=c++11 -g -o guava Types.o Symbol.o GuavaSymTable.o GuavaQuads.o GrafoBloques.o GuavaTree.o GuavaDriver.o GuavaParser.o GuavaLexer.o Guava.o

GuavaDriver.o: GuavaDriver.cc GuavaDriver.hh GuavaTree.hh GuavaParser.hh Generator.hh

	$(CC) -g -c  -std=c++11 GuavaDriver.cc

GuavaParser.o: GuavaParser.cc GuavaParser.hh GuavaTree.hh GuavaDriver.hh

	$(CC) -g -c -std=c++11 GuavaParser.cc 

GuavaParser.cc GuavaParser.hh: GuavaParser.yy

	bison -r state --defines=GuavaParser.hh -o GuavaParser.cc GuavaParser.yy

GuavaLexer.o: GuavaLexer.cc GuavaParser.hh GuavaDriver.hh

	$(CC) -g -c -std=c++11 GuavaLexer.cc

GuavaLexer.cc: GuavaLexer.l

	flex -o GuavaLexer.cc GuavaLexer.l

GuavaSymTable.o: GuavaSymTable.cc GuavaSymTable.hh Symbol.hh

	$(CC) -g -c -std=c++11 GuavaSymTable.cc

Symbol.o: Symbol.cc Symbol.hh Types.hh

	$(CC) -g -c -std=c++11 Symbol.cc

Types.o: Types.cc Types.hh

	$(CC) -g -c -std=c++11 Types.cc

GuavaTree.o: GuavaTree.cc GuavaTree.hh GrafoBloques.hh

	$(CC) -g -c -std=c++11 GuavaTree.cc

Guava.o: Guava.cc

	$(CC) -g -c -std=c++11 Guava.cc

Generator.o: Generator.hh

	$(CC) -g -c -std=c++11 Generator.hh

GuavaQuads.o: GuavaQuads.hh GuavaQuads.cc GuavaSymTable.hh

	$(CC) -g -c -std=c++11 GuavaQuads.cc 

GrafoBloques.o: GrafoBloques.hh GrafoBloques.cc GuavaQuads.hh

	$(CC)  -g -c -std=c++11 -I /usr/include/boost GrafoBloques.cc 

.PHONY: clean

clean:

	-rm *.o GuavaParser.hh GuavaParser.cc *.output *.gch location.hh position.hh stack.hh guava GuavaLexer.cc


