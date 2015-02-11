.SUFFIXES: .cpp .y .l .o .h

CCC = clang++
LEX = flex
YACC = bison
CFLAGS = -Wall -std=c++0x 
LEXFLAGS = -Wno-unused

ROOT_DIR = .

OBJ_DIR = build
SRC_DIR = src
INC_DIR = include

INCLUDE := \
	-I. \
	-I./$(INC_DIR) \

OFILES = \
	Exceptions.o Literal.o Identifier.o \
	Block.o ParameterList.o ExpressionList.o \
	Function.o Program.o Statement.o Ast.o Symtab.o \

OBJS = $(patsubst %, $(OBJ_DIR)/%, $(OFILES)) main.o lex.yy.o parse.tab.o

all: spyceless

objs: $(OBJS)

test: spyceless
	python runtests.py

phase1: spyceless
	python runtests.py testsuite/phase_one

phase2: spyceless
	python runtests.py testsuite/phase_two

vegas: spyceless
	python runtests.py testsuite/vegas

report: testsuite/* ./spyceless
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --legend --output-directory report
	echo Coverage report in report/index.html

spyceless: $(OBJS)
	$(CCC) $(CFLAGS) -o spyceless $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CCC) $< $(CFLAGS) -g $(INCLUDE) -c -o $@

main.o: main.cpp
	$(CCC) $(CFLAGS) $(INCLUDE) -c main.cpp

parse.tab.c: parse.y
	$(YACC) -vtd parse.y

parse.tab.o: parse.tab.c
	$(CCC) $(CFLAGS) -g $(INCLUDE) -c parse.tab.c

lex.yy.c: scan.l parse.tab.o
	$(LEX) scan.l

lex.yy.o: lex.yy.c
	$(CCC) $(CFLAGS) $(INCLUDE) $(LEXFLAGS) -c lex.yy.c
	
clean:
	rm -f spyceless *.o $(OBJ_DIR)/*.o parse.tab.c lex.yy.c
	rm -f parse.tab.h
	rm -f graph.gv graph.png
	rm -f *.gcda *.gcno *.bb *.bbg *.da *.gcov
	rm -rf report cov.info
