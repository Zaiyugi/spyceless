CCC = clang++
LEX = flex
YACC = bison
CFLAGS = -Wall -std=c++0x
LEXFLAGS = -Wno-unused

#Add debugging code to compilation
#DEBUG = -DDEBUG
DEBUG = 

OBJS = main.o Ast.o Graph.o Number.o parse.tab.o lex.yy.o

run: $(OBJS)
	$(CCC) $(CFLAGS) -o run $(OBJS)

main.o: main.cpp parse.y scan.l parse.tab.c lex.yy.c
	$(CCC) $(CFLAGS) -c main.cpp

parse.tab.c: parse.y Ast.h
	$(YACC) -dg parse.y

Ast.o: Ast.cpp Ast.h
	$(CCC) $(CFLAGS) -c Ast.cpp

Number.o: Number.cpp Number.h
	$(CCC) $(CFLAGS) -c Number.cpp

Graph.o: Graph.cpp Graph.h
	$(CCC) $(CFLAGS) $(DEBUG) -c Graph.cpp

parse.tab.o: parse.tab.c
	$(CCC) $(CFLAGS) -c parse.tab.c

lex.yy.c: scan.l parse.tab.o
	$(LEX) scan.l

lex.yy.o: lex.yy.c
	$(CCC) $(CFLAGS) $(LEXFLAGS) -c lex.yy.c
	
clean:
	rm -f run *.o parse.dot parse.tab.c lex.yy.c
	rm -f parse.tab.h
