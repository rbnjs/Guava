CC=g++

OBJ=Types.o Symbol.o GuavaSymTable.o GuavaQuads.o GuavaTemplates.o GuavaDescriptor.o GetReg.o GrafoBloques.o GuavaTree.o GuavaDriver.o GuavaParser.o GuavaLexer.o Guava.o

LFLAGS=-std=c++11 -g -o guava

CFLAGS=-g -c -std=c++11


all: guava

guava:  $(OBJ) 	

	$(CC) $(LFLAGS) $(OBJ) 

GuavaDriver.o: GuavaDriver.cc GuavaDriver.hh GuavaTree.hh GuavaParser.hh 

	$(CC) $(CFLAGS) GuavaDriver.cc

GuavaParser.o: GuavaParser.cc GuavaParser.hh GuavaTree.hh GuavaDriver.hh

	$(CC) $(CFLAGS) GuavaParser.cc 

GuavaParser.cc GuavaParser.hh: GuavaParser.yy

	bison -r state --defines=GuavaParser.hh -o GuavaParser.cc GuavaParser.yy

GuavaLexer.o: GuavaLexer.cc GuavaParser.hh GuavaDriver.hh

	$(CC) $(CFLAGS) GuavaLexer.cc

GuavaLexer.cc: GuavaLexer.l

	flex -o GuavaLexer.cc GuavaLexer.l

GuavaSymTable.o: GuavaSymTable.cc GuavaSymTable.hh Symbol.hh

	$(CC) $(CFLAGS) GuavaSymTable.cc

Symbol.o: Symbol.cc Symbol.hh Types.hh

	$(CC) $(CFLAGS) Symbol.cc

Types.o: Types.cc Types.hh

	$(CC) $(CFLAGS) Types.cc

GuavaTree.o: GuavaTree.cc GuavaTree.hh GrafoBloques.hh

	$(CC) $(CFLAGS) GuavaTree.cc

Guava.o: Guava.cc

	$(CC) $(CFLAGS) Guava.cc

GuavaDescriptor.o: GuavaDescriptor.hh GuavaQuads.hh

	$(CC) $(CFLAGS) GuavaDescriptor.cc

GuavaQuads.o: GuavaQuads.hh GuavaQuads.cc GuavaSymTable.hh

	$(CC) $(CFLAGS) GuavaQuads.cc 

GrafoBloques.o: GrafoBloques.hh GrafoBloques.cc GuavaQuads.hh

	$(CC)  $(CFLAGS) -I /usr/include/boost GrafoBloques.cc 

GetReg.o: GetReg.hh GetReg.cc GuavaQuads.hh

	$(CC) $(CFLAGS) GetReg.cc

GuavaTemplates.o: GuavaTemplates.cc GuavaTemplates.hh Symbol.hh GuavaDescriptor.hh

	$(CC) $(CFLAGS) GuavaTemplates.cc

.PHONY: clean doc

clean:

	-rm *.o GuavaParser.hh GuavaParser.cc *.output location.hh position.hh stack.hh guava GuavaLexer.cc

doc:

	doxygen Documentacion/config

