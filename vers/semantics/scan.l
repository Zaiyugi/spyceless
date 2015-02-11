%option nodefault yylineno
%{
  extern void yyerror(const char *s);
  extern void yyerror(const char *s, const char ch);
#include "Ast.h"
#include "parse.tab.h"
%}

%%
"+"		{ return PLUS; }
"-"		{ return MINUS; }
"*"		{ return MULT; }
"/"		{ return DIV; }
"**"		{ return EXPO; }
"("		{ return LPAREN; }
")"		{ return RPAREN; }

(0|[1-9][0-9]*)("."[0-9]*)?	{
		yylval.d = atof(yytext);
		return NUMBER;
	}

\n			{ return EOL; }
"//".*  
[ \t]		{ } // ignore white space
.			{ yyerror("Mystery character ", yytext[0]); }
%%
int yywrap() {
  yylex_destroy();
  return 1;
}
