/* Name: Zachary Shore
 * Date: 2014-11-03
 */
#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <iostream>

#include "Exceptions.h"

#include "Literal.h"
#include "ExpressionList.h"
#include "Identifier.h"
#include "Symtab.h"

#include "Block.h"
#include "Function.h"
#include "Program.h"

extern void yyerror(const char*);
extern void yyerror(const char*, const char);

namespace spyceless
{

class Ast;

class Ast
{
   public:
      Ast(std::string n) : _nodetype(n) {}
      virtual ~Ast() {}

      std::string getNodetype() const { return _nodetype; }

      virtual Ast* getLeft() const
      {
         // throw std::string("No Left");
         return nullptr;
      }

      virtual Ast* getRight() const
      {
         // throw std::string("No Right");
         return nullptr;
      }

      virtual const Literal eval() const = 0;

   private:
      std::string _nodetype;
};

class AstNode : public Ast
{
   public:
      AstNode() : Ast(""), _left(nullptr), _right(nullptr) {}
      AstNode(std::string n, Ast* l, Ast* r) :
         Ast(n), _left(l), _right(r)
         {}

      ~AstNode()
      {
         delete _left;
         delete _right;
      }

      Ast* getLeft() const  { return _left; }
      Ast* getRight() const { return _right; }

   protected:
      Ast *_left;
      Ast *_right;
};

/* Math Ops */
class AstAdd : public AstNode
{
   public:
      AstAdd() : AstNode("+", nullptr, nullptr) {}
      AstAdd(Ast* l, Ast* r) : AstNode("+", l, r) {}

      const Literal eval() const;
};

class AstSub : public AstNode
{
   public:
      AstSub() : AstNode("-", nullptr, nullptr) {}
      AstSub(Ast* l, Ast* r) : AstNode("-", l, r) {}

      const Literal eval() const;
};

class AstMult : public AstNode
{
   public:
      AstMult() : AstNode("*", nullptr, nullptr) {}
      AstMult(Ast* l, Ast* r) : AstNode("*", l, r) {}

      const Literal eval() const;
};

class AstDiv : public AstNode
{
   public:
      AstDiv() : AstNode("/", nullptr, nullptr) {}
      AstDiv(Ast* l, Ast* r) : AstNode("/", l, r) {}

      const Literal eval() const;
};

class AstExpo : public AstNode
{
   public:
      AstExpo() : AstNode("**", nullptr, nullptr) {}
      AstExpo(Ast* l, Ast* r) : AstNode("**", l, r) {}

      const Literal eval() const;
};

class AstModulo : public AstNode
{
   public:
      AstModulo() : AstNode("%", nullptr, nullptr) {}
      AstModulo(Ast* l, Ast* r) : AstNode("%", l, r) {}

      const Literal eval() const;
};

class AstNegate : public AstNode
{
   public:
      AstNegate() : AstNode("-", nullptr, nullptr) {}
      AstNegate(Ast* l) : AstNode("-", l, nullptr) {}

      const Literal eval() const;
};

/* Typecasting */
class AstCastToInt : public AstNode
{
   public:
      AstCastToInt() : AstNode("Cast->Int", nullptr, nullptr) {}
      AstCastToInt(Ast* l) : AstNode("Cast->Int", l, nullptr) {}

      const Literal eval() const;
};

class AstCastToDouble : public AstNode
{
   public:
      AstCastToDouble() : AstNode("Cast->Double", nullptr, nullptr) {}
      AstCastToDouble(Ast* l) : AstNode("Cast->Double", l, nullptr) {}

      const Literal eval() const;
};

class AstCastToString : public AstNode
{
   public:
      AstCastToString() : AstNode("Cast->String", nullptr, nullptr) {}
      AstCastToString(Ast* l) : AstNode("Cast->String", l, nullptr) {}

      const Literal eval() const;
};

/* Boolean Ops */
class AstBoolean : public AstNode
{
   public:
      AstBoolean()
         : AstNode("bool", nullptr, nullptr),
         var_true(TRUE_LITERAL), var_false(FALSE_LITERAL) {}

      AstBoolean(std::string n, Ast* l, Ast* r)
         : AstNode(n, l, r),
         var_true(TRUE_LITERAL), var_false(FALSE_LITERAL) {}

   protected:
      Literal var_true;
      Literal var_false;
};

class AstLT : public AstBoolean
{
   public:
      AstLT() : AstBoolean("<", nullptr, nullptr) {}
      AstLT(Ast* l, Ast* r) : AstBoolean("<", l, r) {}

      const Literal eval() const;
};

class AstLTE : public AstBoolean
{
   public:
      AstLTE() : AstBoolean("<=", nullptr, nullptr) {}
      AstLTE(Ast* l, Ast* r) : AstBoolean("<=", l, r) {}

      const Literal eval() const;
};

class AstGT : public AstBoolean
{
   public:
      AstGT() : AstBoolean(">", nullptr, nullptr) {}
      AstGT(Ast* l, Ast* r) : AstBoolean(">", l, r) {}

      const Literal eval() const;
};

class AstGTE : public AstBoolean
{
   public:
      AstGTE() : AstBoolean(">=", nullptr, nullptr) {}
      AstGTE(Ast* l, Ast* r) : AstBoolean(">=", l, r) {}

      const Literal eval() const;
};

class AstNEQ : public AstBoolean
{
   public:
      AstNEQ() : AstBoolean("!=", nullptr, nullptr) {}
      AstNEQ(Ast* l, Ast* r) : AstBoolean("!=", l, r) {}

      const Literal eval() const;
};

class AstEQ : public AstBoolean
{
   public:
      AstEQ() : AstBoolean("==", nullptr, nullptr) {}
      AstEQ(Ast* l, Ast* r) : AstBoolean("==", l, r) {}

      const Literal eval() const;
};

class AstAnd : public AstBoolean
{
   public:
      AstAnd() : AstBoolean("and", nullptr, nullptr) {}
      AstAnd(Ast* l, Ast* r) : AstBoolean("and", l, r) {}

      const Literal eval() const;
};

class AstOr : public AstBoolean
{
   public:
      AstOr() : AstBoolean("or", nullptr, nullptr) {}
      AstOr(Ast* l, Ast* r) : AstBoolean("<or", l, r) {}

      const Literal eval() const;
};

/* Literal */
class AstLiteral : public Ast
{
   public:
      AstLiteral() : Ast("K"), _value() {}
      AstLiteral(Literal n) : Ast("K"), _value(n) {}

      const Literal eval() const
      { return _value; }

   private:
      Literal _value;

};

class Program;
class Block;
class ExpressionList;

/* Identifiers */
class AstIdentifier : public Ast
{
   public:
      AstIdentifier() : Ast("Ident"), _name("invalid"), _block(nullptr) {}
      AstIdentifier(std::string n, Block* b)
         : Ast("Ident"), _name(n), _block(b) {}

      virtual const Literal eval() const;

   protected:
      std::string _name;
      Block* _block;
};

/* Function Calls */
class AstFunctionCall : public Ast
{
   public:
      AstFunctionCall() : Ast("FC") {}
      AstFunctionCall(std::string n, Program* p, ExpressionList* e)
         : Ast("FC"), _name(n), _prog(p), _exprList(e)  {}

      ~AstFunctionCall();

      const Literal eval() const;

   private:
      std::string _name;
      Program* _prog;
      ExpressionList* _exprList;
};

/* EvalIdentifier */
class AstEvalIdentifier : public AstNode
{
   public:
      AstEvalIdentifier() : AstNode("eval", nullptr, nullptr), _block(nullptr) {}
      AstEvalIdentifier(Ast* l, Block* b) : AstNode("eval", l, nullptr), _block(b) {}

      virtual const Literal eval() const;

   protected:
      Block* _block;
};

/* Read File */
class AstReadFile : public AstNode
{
   public:
      AstReadFile() : AstNode("open_file", nullptr, nullptr), _block(nullptr) {}
      AstReadFile(Ast* l, Block* b) : AstNode("open_file", l, nullptr), _block(b) {}

      const Literal eval() const;

   private:
      Block* _block;
};

};

#endif
