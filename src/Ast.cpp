#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "Ast.h"

namespace spyceless
{

/* Math Ops */
const Literal AstAdd::eval() const
{
   return _left->eval() + _right->eval();
}

const Literal AstSub::eval() const
{
   return _left->eval() - _right->eval();
}

const Literal AstMult::eval() const
{
   return _left->eval() * _right->eval();
}

const Literal AstDiv::eval() const
{
   return _left->eval() / _right->eval();
}

const Literal AstExpo::eval() const
{
   return _left->eval() ^ _right->eval();
}

const Literal AstModulo::eval() const
{
   return _left->eval() % _right->eval();
}

const Literal AstNegate::eval() const
{
   return -_left->eval();
}

/* Typecasting */
const Literal AstCastToInt::eval() const
{
   Literal val = _left->eval().castToInt();
   return val;
}

const Literal AstCastToDouble::eval() const
{
   Literal val = _left->eval().castToDouble();
   return val;
}

const Literal AstCastToString::eval() const
{
   Literal val = _left->eval().castToString();
   return val;
}

/* Boolean Ops */
const Literal AstLT::eval() const
{
   if(_left->eval() < _right->eval())
      return var_true;

   return var_false;
}

const Literal AstLTE::eval() const
{
   if(_left->eval() <= _right->eval())
      return var_true;

   return var_false;
}

const Literal AstGT::eval() const
{
   if(_left->eval() > _right->eval())
      return var_true;

   return var_false;
}

const Literal AstGTE::eval() const
{
   if(_left->eval() >= _right->eval())
      return var_true;

   return var_false;
}

const Literal AstNEQ::eval() const
{
   if(_left->eval() != _right->eval())
      return var_true;

   return var_false;
}

const Literal AstEQ::eval() const
{
   if(_left->eval() == _right->eval())
      return var_true;

   return var_false;
}

const Literal AstAnd::eval() const
{
   if(_left->eval() == TRUE_LITERAL && _right->eval() == TRUE_LITERAL)
      return var_true;

   return var_false;
}

const Literal AstOr::eval() const
{
   if(_left->eval() == TRUE_LITERAL || _right->eval() == TRUE_LITERAL)
      return var_true;

   return var_false;
}

/* Identifiers */
const Literal AstIdentifier::eval() const
{
   Identifier* id = _block->checkScope(_name);
   if( id )
   {
      if( id->type() == "file" )
         return Literal(id->name(), STRING);
      else
         return id->get();
   } else {
      throw UnknownIdentifier(_name.c_str());
   }

   return INVALID_LITERAL;
}

/* Function Calls */
AstFunctionCall::~AstFunctionCall()
{
   if( _exprList )
      delete _exprList;
}

const Literal AstFunctionCall::eval() const
{
   FunctionTable* func_tab = _prog->getFunctionTable();
   Function* func = func_tab->find(_name);

   if( func )
   {
      std::vector<Literal> vals;
      vals.resize(_exprList->size());
      for(int i = 0; i < _exprList->size(); ++i)
         vals[i] = (*_exprList)[i]->eval();

      func->eval(vals);
      return func->getReturnValue();
   } else {
      throw InvalidFunctionName(_name.c_str());
   }

   return Literal();
}

/* EvalIdentifier */
const Literal AstEvalIdentifier::eval() const
{
   Literal val = _left->eval();
   std::string name = val.get();

   Identifier* id = _block->checkScope(name);
   if( id )
      return id->get();
   else
      throw UnknownIdentifier(name.c_str());

   return INVALID_LITERAL;
}

/* Read File */
const Literal AstReadFile::eval() const
{
   Literal val = _left->eval();
   std::string name = val.get();

   Identifier* id = _block->checkScope(name);
   if( id )
   {
      if( id->type() == "file" )
      {
         std::string temp;
         dynamic_cast<FileIdentifier*>(id)->_ifs >> temp;
         return Literal(temp, STRING);
      } else {
         throw InvalidUnaryOperation(name.c_str(), "read");
      }
   } else {
      throw UnknownFileHandle(name.c_str());
   }

   return INVALID_LITERAL;
}

};

