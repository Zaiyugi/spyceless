//  Declarations for an AST calculator
//  From "flex & bison", fb3-1, by John Levine
//  Adapted by Brian Malloy
#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <iostream>
#include "Number.h"

extern void yyerror(const char*);
extern void yyerror(const char*, const char);

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

      virtual const Number eval() const = 0;

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

		const Number eval() const;
};

class AstSub : public AstNode
{
	public:
		AstSub() : AstNode("-", nullptr, nullptr) {}
		AstSub(Ast* l, Ast* r) : AstNode("-", l, r) {}

		const Number eval() const;
};

class AstMult : public AstNode
{
	public:
		AstMult() : AstNode("*", nullptr, nullptr) {}
		AstMult(Ast* l, Ast* r) : AstNode("*", l, r) {}

		const Number eval() const;
};

class AstDiv : public AstNode
{
	public:
		AstDiv() : AstNode("/", nullptr, nullptr) {}
		AstDiv(Ast* l, Ast* r) : AstNode("/", l, r) {}

		const Number eval() const;
};

class AstExpo : public AstNode
{
	public:
		AstExpo() : AstNode("**", nullptr, nullptr) {}
		AstExpo(Ast* l, Ast* r) : AstNode("**", l, r) {}

		const Number eval() const;
};

class AstModulo : public AstNode
{
	public:
		AstModulo() : AstNode("%", nullptr, nullptr) {}
		AstModulo(Ast* l, Ast* r) : AstNode("%", l, r) {}

		const Number eval() const;
};

class AstNegate : public AstNode
{
	public:
		AstNegate() : AstNode("-", nullptr, nullptr) {}
		AstNegate(Ast* l) : AstNode("-", l, nullptr) {}

		const Number eval() const;
};

/* Boolean Ops */
class AstLT : public AstNode
{
	public:
		AstLT() : AstNode("<", nullptr, nullptr) {}
		AstLT(Ast* l, Ast* r) : AstNode("<", l, r) {}

		const Number eval() const;
};

class AstLTE : public AstNode
{
	public:
		AstLTE() : AstNode("<=", nullptr, nullptr) {}
		AstLTE(Ast* l, Ast* r) : AstNode("<=", l, r) {}

		const Number eval() const;
};

class AstGT : public AstNode
{
	public:
		AstGT() : AstNode(">", nullptr, nullptr) {}
		AstGT(Ast* l, Ast* r) : AstNode(">", l, r) {}

		const Number eval() const;
};

class AstGTE : public AstNode
{
	public:
		AstGTE() : AstNode(">=", nullptr, nullptr) {}
		AstGTE(Ast* l, Ast* r) : AstNode(">=", l, r) {}

		const Number eval() const;
};

class AstNEQ : public AstNode
{
	public:
		AstNEQ() : AstNode("!=", nullptr, nullptr) {}
		AstNEQ(Ast* l, Ast* r) : AstNode("!=", l, r) {}

		const Number eval() const;
};

class AstEQ : public AstNode
{
	public:
		AstEQ() : AstNode("==", nullptr, nullptr) {}
		AstEQ(Ast* l, Ast* r) : AstNode("==", l, r) {}

		const Number eval() const;
};

/* Number */
class AstNumber : public Ast
{
	public:
		AstNumber() : Ast("K"), number() {}
		AstNumber(Number* n) : Ast("K"), number(n) {}

		~AstNumber() { delete number; }

		const Number eval() const
		{ return *number; }

	private:
		Number* number;

};

#endif
