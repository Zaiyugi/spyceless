%{
#include <iostream>
#include <cstdio>
#include <stack>
#include <map>

#include "Identifier.h"
#include "Literal.h"
#include "Symtab.h"
#include "Ast.h"

#include "Statement.h"
#include "Function.h"
#include "Program.h"
#include "Block.h"
#include "ExpressionList.h"
#include "ParameterList.h"

using namespace spyceless;

extern FILE* yyin;

extern int yylex();
extern int lineno;

void yyerror(const char * msg);

Symtab* symtab;
Program* program;

Function* current_function;
ParameterList* parameters;
ExpressionList* expr_list;

std::stack<Block*> current_block;
std::stack<Statement*> current_statement;

%}
%error-verbose

%union
{
   char* id;
   int i_val;
   double f_val;
   spyceless::Ast* ast;
}

%type<id> start funcdef prototype
%type<id> id_list opt_parm_list 
%type<id> if_block else_block loop_condition
%type<id> stmt selection loop line
%type<ast> expr

%token ASSIGN
%token PRINT
%token PRINTLN
%token<id> IDENT 
%token<id> STRING 
%token<i_val> NUMBER
%token<f_val> FLOAT
%token LPAREN RPAREN
%token DEBUG EVAL
%token OPEN
%token CLOSE
%token READ
%token DEF
%token COLON
%token DIRECTIVE
%token SHEBANG
%token VAR
%token STR_TYPE
%token INT_TYPE
%token DOUBLE_TYPE
%token COMMA
%token IF WHILE
%token END
%token ELSE
%token RETURN

%left  LOGIC_AND LOGIC_OR
%left  LESS LESSEQ GREAT GREATEQ EQ NOTEQ
%left  PLUS MINUS
%left  MULT DIV MOD
%right EXPON

%%

start 
   : funcdef start
      {
         $$ = 0;
      }

   | line start
      { $$ = 0; }

   | selection start
      { $$ = 0; }

   | error
      {
         yyerrok;
         //yyclearin;
      }

   | 
      { $$ = 0; }

   ;

funcdef
   : prototype stmt END
      {
         //std::cout << "add function to program" << std::endl;
         program->addFunction(current_function);
         current_function = nullptr;
         current_block.pop();
      }

   ;

prototype
   : DEF IDENT LPAREN id_list RPAREN COLON
      {
         //std::cout << "create function" << std::endl;
         std::string name($2);
         current_function = new Function(name, program->getBlockPointer());
         current_function->setParameters(parameters);

         current_block.push(current_function->getBlockPointer());
         parameters = nullptr;
         delete [] $2;
      }

   ;

id_list
   : id_list COMMA IDENT
      {
         std::string name($3);
         if( parameters )
            parameters->add(name);
         delete [] $3;
      }

   | IDENT
      {
         std::string name($1);
         parameters = new ParameterList;
         parameters->add(name);
         delete [] $1;
      }

   |
      {
         parameters = new ParameterList;
      }

   ;

opt_parm_list
   : opt_parm_list COMMA expr
      {
         if( expr_list )
            expr_list->add($3);
      }

   | expr
      {
         expr_list = new ExpressionList;
         expr_list->add($1);
      }

   |
      {
         expr_list = new ExpressionList;
      }

   ;

stmt
   : line stmt
      { $$ = 0; }

   | selection stmt
      { $$ = 0; }

   | loop stmt
      { $$ = 0; }

   |
      { $$ = 0; }

   ;

selection 
   : if_block stmt END
      {
         current_statement.pop();
         current_block.pop();
      }

   | if_block stmt else_block stmt END
      {
         current_statement.pop();
         current_block.pop();
      }

   ;

if_block
   : IF expr COLON
      {
         Statement* loc = new IfStatement(lineno, $2, current_block.top());

         current_statement.push(loc);
         current_block.top()->addStatement(loc);
         current_block.push( dynamic_cast<IfStatement*>(loc)->getIfBranch() );
      }

   ;

else_block
   : ELSE COLON
      {
         Statement* loc = current_statement.top();
         if( loc->type() == IF_STATEMENT )
         {
            current_block.pop();
            current_block.push( dynamic_cast<IfStatement*>(loc)->getElseBranch() );
         }
      }

   ;

loop
   : loop_condition stmt END
      {
         current_block.pop();
      }

   ;

loop_condition
   : WHILE expr COLON
      {
         Statement* loc = new WhileStatement(lineno, $2, current_block.top());

         current_block.top()->addStatement(loc);
         current_block.push( dynamic_cast<WhileStatement*>(loc)->getLoopBlock() );
      }

   ;

line
   : IDENT ASSIGN expr
      {
         std::string name($1);
         Statement* loc = new Assignment(name, lineno, $3, current_block.top());
         current_block.top()->addStatement(loc);
         delete [] $1;
      }

   | COLON COLON IDENT ASSIGN expr
      {
         std::string name($3);
         Statement* loc = new GlobalAssignment(name, lineno, $5, program->getBlockPointer());
         current_block.top()->addStatement(loc);
         delete [] $3;
      }

   | VAR IDENT ASSIGN expr
      {
         std::string name($2);
         Statement* loc = new LocalAssignment(name, lineno, $4, current_block.top());
         current_block.top()->addStatement(loc);
         delete [] $2;
      }

   | IDENT LPAREN opt_parm_list RPAREN
      {
         std::string name($1);
         Statement* loc = new FunctionCall(name, lineno, current_block.top(), program, expr_list);
         current_block.top()->addStatement(loc);
         expr_list = nullptr;
         delete [] $1;
      }

   | IDENT ASSIGN OPEN LPAREN expr RPAREN
      {
         std::string name($1);
         Statement* loc = new OpenFileStatement(name, lineno, $5, current_block.top());
         current_block.top()->addStatement(loc);
         delete [] $1;
      }

   | CLOSE LPAREN expr RPAREN
      {
         Statement* loc = new CloseFileStatement(lineno, $3, current_block.top());
         current_block.top()->addStatement(loc);
      }

   | READ LPAREN expr RPAREN
      {
         Statement* loc = new ReadFileStatement(lineno, $3, current_block.top());
         current_block.top()->addStatement(loc);
      }

   | PRINT expr
      {
         Statement* loc = new PrintStatement(lineno, $2, current_block.top());
         current_block.top()->addStatement(loc);
      }

   | PRINTLN expr
      {
         Statement* loc = new PrintLineStatement(lineno, $2, current_block.top());
         current_block.top()->addStatement(loc);
      }

   | RETURN expr
      {
         Statement* loc = new ReturnStatement(lineno, $2, current_block.top(), current_function);
         current_block.top()->addStatement(loc);
      }

   | DEBUG
      {
         //std::cout << "print: " << lineno << std::endl;
         Statement* loc = new DebugStatement(lineno, current_block.top(), program);
         current_block.top()->addStatement(loc);
      }

   | COLON COLON EVAL LPAREN expr RPAREN ASSIGN expr
      {
         Statement* loc = new GlobalEvalStatement(lineno, $5, $8, program->getBlockPointer());
         current_block.top()->addStatement(loc);
      }

   | VAR EVAL LPAREN expr RPAREN ASSIGN expr
      {
         Statement* loc = new LocalEvalStatement(lineno, $4, $7, current_block.top());
         current_block.top()->addStatement(loc);
      }

   | EVAL LPAREN expr RPAREN ASSIGN expr
      {
         Statement* loc = new EvalStatement(lineno, $3, $6, current_block.top());
         current_block.top()->addStatement(loc);
      }

   ;

expr
   : expr PLUS expr
      { $$ = new AstAdd($1, $3); }

   | expr MINUS expr
      { $$ = new AstSub($1, $3); }

   | expr MULT expr
      { $$ = new AstMult($1, $3); }

   | expr EXPON expr
      { $$ = new AstExpo($1, $3); }

   | expr DIV expr
      { $$ = new AstDiv($1, $3); }

   | expr MOD expr
      { $$ = new AstModulo($1, $3); }

   | expr LESS expr
      { $$ = new AstLT($1, $3); }

   | expr LESSEQ expr
      { $$ = new AstLTE($1, $3); }

   | expr GREAT expr
      { $$ = new AstGT($1, $3); }

   | expr GREATEQ expr
      { $$ = new AstGTE($1, $3); }

   | expr NOTEQ expr
      { $$ = new AstNEQ($1, $3); }

   | expr EQ expr
      { $$ = new AstEQ($1, $3); }

   | expr LOGIC_AND expr
      { $$ = new AstAnd($1, $3); }

   | expr LOGIC_OR expr
      { $$ = new AstOr($1, $3); }

   | MINUS expr
      { $$ = new AstNegate($2); }

   | NUMBER
      {
         //std::cout << "Creating new integer " << std::endl;
         $$ = new AstLiteral(spyceless::Literal($1, spyceless::INTEGER) );
      }

   | FLOAT
      {
         //std::cout << "Creating new double " << std::endl;
         $$ = new AstLiteral(spyceless::Literal($1, spyceless::DOUBLE) );
      }

   | STRING
      {
         //std::cout << "Creating new string " << std::endl;
         $$ = new AstLiteral(spyceless::Literal($1, spyceless::STRING) );
         delete [] $1;
      }

   | INT_TYPE LPAREN expr RPAREN
      {
         $$ = new AstCastToInt($3);
      }

   | DOUBLE_TYPE LPAREN expr RPAREN
      {
         $$ = new AstCastToDouble($3);
      }

   | STR_TYPE LPAREN expr RPAREN
      {
         $$ = new AstCastToString($3);
      }

   | IDENT
      {
         std::string name($1);
         $$ = new AstIdentifier(name, current_block.top());
         delete [] $1;
      }

   | COLON COLON IDENT
      {
         std::string name($3);
         $$ = new AstIdentifier(name, program->getBlockPointer());
         delete [] $3;
      }

   | IDENT LPAREN opt_parm_list RPAREN
      {
         std::string name($1);
         $$ = new AstFunctionCall(name, program, expr_list);
         expr_list = nullptr;
         delete [] $1;
      }

   | EVAL LPAREN expr RPAREN
      {
         $$ = new AstEvalIdentifier($3, current_block.top());
      }

   | COLON COLON EVAL LPAREN expr RPAREN
      {
         $$ = new AstEvalIdentifier($5, program->getBlockPointer());
      }

   | READ LPAREN expr RPAREN
      {
         $$ = new AstReadFile($3, current_block.top());
      }

   | LPAREN expr RPAREN
      { $$ = $2; }

   ;

%%

void yyerror(const char * msg)
{
   std::cout 
      << "Error: line " << lineno 
      << "\n  >>>  " << msg << std::endl;
}

