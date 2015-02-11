%{
#include <iostream>
#include <cstring>
#include <cmath>

#include "Ast.h"
#include "parse.tab.h"

int lineno = 0;

%}

letter      [a-zA-Z]
ident       (_|{letter})(_|{letter}|{digit})*
digit       [0-9]
digits      [0-9]+
float       {digits}"."{digits}

%%


"#"[^!]([^\n])*  { ; }

"**"       { return EXPON; }
"="        { return ASSIGN; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"*"        { return MULT; }
"/"        { return DIV; }
"%"        { return MOD; }
"("        { return LPAREN; }
")"        { return RPAREN; }
"@"        { return DIRECTIVE; }
"#!"       { return SHEBANG; }


\"[^\"]*\" {
              int len = std::strlen(yytext)-2;
              yylval.id = new char[len+1];
              std::strncpy(yylval.id, yytext+1, len);
              yylval.id[len] = '\0';
              return STRING;
           }

":"        { return COLON; }
","        { return COMMA; }
"<"        { return LESS; }
">"        { return GREAT; }
"<="       { return LESSEQ; }
">="       { return GREATEQ; }
"=="       { return EQ; }
"!="       { return NOTEQ; }
"and"      { return LOGIC_AND; }
"or"       { return LOGIC_OR; }
"if"       { return IF; }
"else"     { return ELSE; }
"def"      { return DEF; }
"print"    { return PRINT; }
"println"  { return PRINTLN; }
"end"      { return END; }
"return"   { return RETURN; }
"while"    { return WHILE; }

"eval"      { return EVAL; }
"open"      { return OPEN; }
"close"     { return CLOSE; }
"read"      { return READ; }
"__debug__" { return DEBUG; }

"var"         { return VAR; }
"str"         { return STR_TYPE; }
"int"         { return INT_TYPE; }
"double"      { return DOUBLE_TYPE; }

{ident}    {
              yylval.id = new char[std::strlen(yytext)+1];
              std::strcpy(yylval.id, yytext);
              yylval.id[std::strlen(yytext)] = '\0';
              return IDENT;
           }

{float}    {
              yylval.f_val = std::atof(yytext);
              return FLOAT;
           }

{digits}   {
              yylval.i_val = std::atoi(yytext);
              return NUMBER;
           }

"\n"       { lineno++; }
.          { ; }

%% // LCOV_EXCL_START
int yywrap() {
  yylex_destroy();
  return 1;
}
// LCOV_EXCL_STOP
