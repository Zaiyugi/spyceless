/* Name: Zachary Shore
 * Date: 2014-11-10
 * Edit: 2014-11-28
 */
#ifndef __STATEMENT_H__
#define __STATEMENT_H__

#include <cstdlib>
#include <string>
#include <exception>

#include "ExpressionList.h"
#include "Identifier.h"
#include "Block.h"
#include "Function.h"
#include "Program.h"
#include "Literal.h"
#include "Ast.h"

namespace spyceless
{

class Ast;
class Function;
class Program;
class Block;

class Statement
{
   public:
      Statement()
         : _type("void"), _lineno(-1), _raw_line("something should go here"),
         _rvalue(nullptr), _block(nullptr) {}

      Statement(std::string type) 
         : _type(type), _lineno(-1), _raw_line("something should go here"),
         _rvalue(nullptr), _block(nullptr) {}

      Statement(std::string type, int no, std::string line, Ast* tree, Block* b)
         : _type(type), _lineno(no), _raw_line(line),
         _rvalue(tree), _block(b) {}

      Statement(const Statement& id) : 
         _type( id._type ),
         _lineno( id._lineno ),
         _raw_line( id._raw_line ),
         _rvalue( id._rvalue ),
         _block( id._block )
      {}

      Statement(Statement&& id) : 
         _type( std::move(id._type) ),
         _lineno( id._lineno ),
         _raw_line( std::move(id._raw_line) ),
         _rvalue( id._rvalue ),
         _block( id._block )
      {
         id._rvalue = nullptr;
         id._block = nullptr;
      }

      virtual ~Statement();

      virtual void eval();

      const std::string type() const;
      const int lineno() const;

   protected:
      void handle_exception(std::exception& e);

      std::string _type;
      int _lineno;
      std::string _raw_line;

      Ast* _rvalue;

      Block* _block;
};

static const Statement INVALID_STATEMENT("invalid");
static const std::string RETURN_STATEMENT("return");
static const std::string IF_STATEMENT("if");
static const std::string FOR_STATEMENT("for");

class PrintStatement : public Statement
{
   public:
      PrintStatement() : Statement("print") {}
      PrintStatement(int no, Ast* rv, Block* b)
         : Statement("print", no, "yippee", rv, b) {}

      ~PrintStatement() {}

      void eval();
};

class PrintLineStatement : public Statement
{
   public:
      PrintLineStatement() : Statement("print") {}
      PrintLineStatement(int no, Ast* rv, Block* b)
         : Statement("print", no, "kai-yea", rv, b) {}

      ~PrintLineStatement() {}

      void eval();
};

class DebugStatement : public Statement
{
   public:
      DebugStatement() : Statement("debug") {}
      DebugStatement(int no, Block* b, Program* p)
         : Statement("debug", no, "timey-wimey", nullptr, b), _prog(p) {}

      ~DebugStatement() {}

      void eval();

   private:
      Program* _prog;

};

class ReturnStatement : public Statement
{
   public:
      ReturnStatement() : Statement("return") {}
      ReturnStatement(int no, Ast* rv, Block* b, Function* f)
         : Statement("return", no, "yahoo", rv, b), _function(f) {}

      ~ReturnStatement() {}

      void eval();

   private:
      Function* _function;
};

class IfStatement : public Statement
{
   public:
      IfStatement() : Statement("if") {}
      IfStatement(int no, Ast* cond, Block* b = nullptr)
         : Statement("if", no, "allonsy", cond, b), has_else(false) { init(b); }

      ~IfStatement();

      void eval();
      void hasElse();

      Block* getIfBranch() const;
      Block* getElseBranch() const;

   private:
      void init(Block* parent);

      Block* if_branch;
      Block* else_branch;

      bool has_else;
};

class WhileStatement : public Statement
{
   public:
      WhileStatement() : Statement("while") {}
      WhileStatement(int no, Ast* cond, Block* b = nullptr)
         : Statement("while", no, "groundhogs", cond, b) { init(b); }

      ~WhileStatement();

      void eval();

      Block* getLoopBlock() const;

   private:
      void init(Block* parent);

      Block* loop_block;
};

class FunctionCall : public Statement
{
   public:
      FunctionCall() : Statement("function_call") {}

      FunctionCall(std::string lv, int no, Block* b, Program* p, ExpressionList* e)
         : Statement("function_call", no, "geronimo", nullptr, b), 
         _lvalue(lv), _prog(p), _exprList(e) {}

      ~FunctionCall();

      void eval();

   private:
      std::string _lvalue;
      Program* _prog;
      ExpressionList* _exprList;

};

class Assignment : public Statement
{
   public:
      Assignment() : Statement("assign") {}
      Assignment(std::string type) : Statement(type) {}

      Assignment(std::string id, int no, Ast* rv, Block* b)
         : Statement("assign", no, "yoohoo", rv, b), _lvalue(id) {}

      virtual ~Assignment() {}

      virtual void eval();

   protected:
      std::string _lvalue;

};

class GlobalAssignment : public Assignment
{
   public:
      GlobalAssignment() : Assignment("global_assign") {}
      GlobalAssignment(std::string id, int no, Ast* rv, Block* b)
         : Assignment(id, no, rv, b) {}

      ~GlobalAssignment() {}

      void eval();

};

class LocalAssignment : public Assignment
{
   public:
      LocalAssignment() : Assignment("local_assign") {}
      LocalAssignment(std::string id, int no, Ast* rv, Block* b)
         : Assignment(id, no, rv, b) {}

      ~LocalAssignment() {}

      void eval();

};

class EvalStatement : public Statement
{
   public:
      EvalStatement() : Statement("eval") {}
      EvalStatement(int no, Ast* lv, Ast* rv, Block* b)
         : Statement("eval", no, "alley-oop", rv, b), _lvalue(lv) {}

      virtual ~EvalStatement();

      virtual void eval();

   protected:
      Ast* _lvalue;
};

class GlobalEvalStatement : public EvalStatement
{
   public:
      GlobalEvalStatement() : EvalStatement() {}
      GlobalEvalStatement(int no, Ast* lv, Ast* rv, Block* b)
         : EvalStatement(no, lv, rv, b) {}

      ~GlobalEvalStatement() {}

      void eval();
};

class LocalEvalStatement : public EvalStatement
{
   public:
      LocalEvalStatement() : EvalStatement() {}
      LocalEvalStatement(int no, Ast* lv, Ast* rv, Block* b)
         : EvalStatement(no, lv, rv, b) {}

      ~LocalEvalStatement() {}

      void eval();
};

class OpenFileStatement : public Statement
{
   public:
      OpenFileStatement() : Statement("open_file") {}
      OpenFileStatement(std::string name, int no, Ast* rv, Block* b)
         : Statement("open_file", no, "open-sesame", rv, b), _name(name) {}

      void eval();

   private:
      std::string _name;
};

class CloseFileStatement : public Statement
{
   public:
      CloseFileStatement() : Statement("open_file") {}
      CloseFileStatement(int no, Ast* rv, Block* b)
         : Statement("close_file", no, "close-up-shop", rv, b) {}

      void eval();
};

class ReadFileStatement : public Statement
{
   public:
      ReadFileStatement() : Statement("open_file") {}
      ReadFileStatement(int no, Ast* rv, Block* b)
         : Statement("read_file", no, "jiiiii", rv, b) {}

      void eval();
};

};

#endif
