//  Source code for "flex & bison", by John Levine
//  Declarations for an AST calculator fb3-1
//  Adapted by Brian Malloy
%{
#include <iostream>
#include "Ast.h"
#include "Graph.h"
	extern int yylex();
	void yyerror(const char *s) { std::cout << s << std::endl; }
	void yyerror(const char *s, const char ch) {
		std::cout << s << ch << std::endl;
	}

	Graph G;
	int gCnt = 1;
%}

%union {
  Ast* ast;
  double d;
}

%token EOL
%token <d> NUMBER
%type <ast> line expr 
%left PLUS MINUS
%left MULT DIV
%right EXPO
%left LPAREN RPAREN

%%

line
		: line expr EOL {
				std::cout << "= " << $2->eval()() << std::endl;

				G.set($2, gCnt);
				G.buildTable();
				G.print("graphs/ast_graph");

				delete $2;
				++gCnt;

				std::cout << "> ";
			}
		| { ; }
		;

expr	:	expr PLUS expr			{ $$ = new AstAdd($1,$3); }
		|	expr MINUS expr		{ $$ = new AstSub($1,$3);}
		|	expr MULT expr			{ $$ = new AstMult($1,$3); }
		|	expr DIV expr			{ $$ = new AstDiv($1,$3); }
		|	expr EXPO expr			{ $$ = new AstExpo($1,$3); }
		|	LPAREN expr RPAREN 	{ $$ = $2; }
		|	MINUS expr				{ $$ = new AstNegate($2); }
		|	NUMBER					{ $$ = new AstNumber(new Number($1, "double")); }
		;

%%
