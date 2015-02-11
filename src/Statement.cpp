/* Name: Zachary Shore
 * Date: 2014-11-10
 * Edit: 2014-12-01
 */
#include <algorithm>
#include "Statement.h"

namespace spyceless
{

/* Base Classes */

Statement::~Statement()
{
   if( _rvalue )
      delete _rvalue;
}

void Statement::eval()
{
   std::cout << "Evaluating from Statement base class..." << std::endl;
}

const std::string Statement::type() const
{
   return _type;
}

const int Statement::lineno() const
{
   return _lineno;
}

void Statement::handle_exception(std::exception& e)
{
   std::string loc;

   loc += ":" + std::to_string(_lineno) + ": error";

   std::string msg = loc + ": " + std::string(e.what()) + "\n";

   std::cout << msg << std::endl;
}

/* -- Derived Classes -- */

/* PrintStatement */
void PrintStatement::eval()
{
   try
   {
      std::cout << _rvalue->eval().get();
   } catch(std::exception& e) {
      handle_exception(e);
   }
}

/* PrintLineStatement */
void PrintLineStatement::eval()
{
   try
   {
      std::cout << _rvalue->eval().get() << std::endl;
   } catch(std::exception& e) {
      handle_exception(e);
   }
}
/* DebugStatement */
void DebugStatement::eval()
{
   Symtab* symtab = _block->getCurrentInstance();
   auto iter = symtab->begin();

   std::cout << std::endl << "  @ -- Symtab -- @\n";
   for(; iter != symtab->end(); ++iter)
   {
      std::string name = iter->first;
      Identifier* value = iter->second;
      std::cout << "    " << name << " --> " << value->get().get() << std::endl;
   }
   std::cout << "  @ ------------ @\n";

   FunctionTable* functab = _prog->getFunctionTable();
   std::cout << std::endl << "  @ -- Function Table -- @\n";
   auto func_iter = functab->begin();

   for(; func_iter != functab->end(); ++func_iter)
   {
      std::string name = func_iter->first;
      ParameterList* params = func_iter->second->getParameters();

      std::cout << "    " << name << "(";
      int size = params->size();
      for(int i = 0; i < size; ++i)
      {
         if( i == size-1 )
            std::cout << (*params)[i];
         else
            std::cout << (*params)[i] << ", ";
      }
      std::cout << ")" << std::endl;
   }
   std::cout << "  @ -------------------- @\n";

}

/* ReturnStatement */
void ReturnStatement::eval()
{
   Literal val;
   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);
   }

   try
   {
      _function->setReturnValue(val);
   } catch(std::exception& e) {
   }

}

/* IfStatement */
IfStatement::~IfStatement()
{
   delete if_branch;
   delete else_branch;
}

void IfStatement::eval()
{
   Literal val = _rvalue->eval();
   if( val == TRUE_LITERAL )
   {
      if_branch->eval();
   } else {
      else_branch->eval();
   } 

}

void IfStatement::hasElse()
{ has_else = true; }

Block* IfStatement::getIfBranch() const
{ return if_branch; }

Block* IfStatement::getElseBranch() const
{ return else_branch; }

void IfStatement::init(Block* parent)
{
   if_branch = new Block(parent);
   else_branch = new Block(parent);
}

/* WhileStatement */
WhileStatement::~WhileStatement()
{
   delete loop_block;
}

void WhileStatement::eval()
{
   Literal val = _rvalue->eval();
   while( val == TRUE_LITERAL )
   {
      loop_block->eval();
      if( loop_block->parent()->returning() )
      {
         break;
      }

      val = _rvalue->eval();
   }
}

Block* WhileStatement::getLoopBlock() const
{ return loop_block; }

void WhileStatement::init(Block* parent)
{
   loop_block = new Block(parent);
}

/* FunctionCall */
FunctionCall::~FunctionCall()
{
   if( _exprList )
      delete _exprList;
}

void FunctionCall::eval()
{
   FunctionTable* func_tab = _prog->getFunctionTable();
   Function* func = func_tab->find(_lvalue);

   if( func )
   {
      std::vector<Literal> vals;
      vals.resize(_exprList->size());
      for(int i = 0; i < _exprList->size(); ++i)
         vals[i] = (*_exprList)[i]->eval();

      func->eval(vals);
   } else {
      throw InvalidFunctionName(_lvalue.c_str());
   }
}

/* Assignment */
void Assignment::eval()
{
   Literal val;
   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);

      val = Literal(0.0, "double");
   }

   Identifier* id = _block->checkScope(_lvalue);
   if( id )
      id->set(val);
   else {
      Symtab* symtab = _block->getCurrentInstance();
      symtab->insert( new VariableIdentifier(_lvalue, val) );
   }

}

/* GlobalAssignment */
void GlobalAssignment::eval()
{
   Literal val;
   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);

      val = Literal(0.0, "double");
   }

   Identifier* id = _block->checkScope(_lvalue);
   if( id )
      id->set(val);
   else {
      Symtab* symtab = _block->getCurrentInstance();
      symtab->insert( new VariableIdentifier(_lvalue, val) );
   }

}

/* LocalAssignment */
void LocalAssignment::eval()
{
   Literal val;
   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);
      val = Literal(0.0, "double");
   }

   Symtab* symtab = _block->getCurrentInstance();
   Identifier* id = symtab->find(_lvalue);
   if( id )
      id->set(val);
   else
      symtab->insert( new VariableIdentifier(_lvalue, val) );
}

/* EvalStatement */
EvalStatement::~EvalStatement()
{
   delete _lvalue;
}

void EvalStatement::eval()
{
   Literal val = _lvalue->eval();
   std::string name = val.get();

   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);
      val = Literal(0.0, "double");
   }

   Identifier* id = _block->checkScope(name);
   if( id )
      id->set(val);
   else {
      Symtab* symtab = _block->getCurrentInstance();
      symtab->insert( new VariableIdentifier(name, val) );
   }
}

/* GlobalEvalStatement */
void GlobalEvalStatement::eval()
{
   Literal val = _lvalue->eval();
   std::string name = val.get();

   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);
      val = Literal(0.0, "double");
   }

   Identifier* id = _block->checkScope(name);
   if( id )
      id->set(val);
   else {
      Symtab* symtab = _block->getCurrentInstance();
      symtab->insert( new VariableIdentifier(name, val) );
   }
}

/* LocalEvalStatement */
void LocalEvalStatement::eval()
{
   Literal val = _lvalue->eval();
   std::string name = val.get();

   try
   {
      val = _rvalue->eval();
   } catch(std::exception& e) {
      handle_exception(e);
      val = Literal(0.0, "double");
   }

   Symtab* symtab = _block->getCurrentInstance();
   Identifier* id = symtab->find(name);
   if( id )
      id->set(val);
   else
      symtab->insert( new VariableIdentifier(name, val) );
}

/* OpenFileStatement */
void OpenFileStatement::eval()
{
   Identifier* id = _block->checkScope(_name);
   if( id )
      if( id->type() == "file" )
         dynamic_cast<FileIdentifier*>(id)->close();

   Literal val = _rvalue->eval();
   if( id )
   {
      delete id;
      id = new FileIdentifier(_name, Literal(val.get(), STRING));
   } else {
      Symtab* symtab = _block->getCurrentInstance();
      symtab->insert( new FileIdentifier(_name, Literal(val.get(), STRING)) );
   }

}

/* CloseFileStatement */
void CloseFileStatement::eval()
{
   Literal val = _rvalue->eval();
   Identifier* id = _block->checkScope(val.get());

   if( id )
   {
      if( id->type() == "file" )
         dynamic_cast<FileIdentifier*>(id)->close();
      else
         throw InvalidUnaryOperation(id->type().c_str(), "close");
   }

}

/* ReadFileStatement */
void ReadFileStatement::eval()
{
   Literal val = _rvalue->eval();
   Identifier* id = _block->checkScope(val.get());

   if( id )
   {
      if( id->type() == "type" )
      {
         std::string temp;
         dynamic_cast<FileIdentifier*>(id)->_ifs >> temp;
      } else {
         throw InvalidUnaryOperation(id->type().c_str(), "read");
      }
   }

}

};
