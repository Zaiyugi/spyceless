/* Name: Zachary Shore
 * Date: 2014-11-11
 * Edit: 2014-11-11
 */
#include "Program.h"

namespace spyceless
{

Program::~Program()
{
   delete _body;
   delete _functions;
}

void Program::eval()
{
   try
   {
      if( _body )
         _body->eval();
   } catch(std::exception& e) {
      handle_exception(e);
      _errcode = 1;
   }

}

void Program::init()
{
   _functions = new FunctionTable;
   _body = new Block();
}

void Program::addFunction(Function* func)
{
   _functions->insert(func);
}

void Program::addStatement(Statement* loc)
{
   if( _body )
      _body->addStatement(loc);
}

Symtab* Program::getGlobalSymtab() const
{
   return _body->getCurrentInstance();
}

FunctionTable* Program::getFunctionTable() const
{
   return _functions;
}

Block* Program::getBlockPointer() const
{
   return _body;
}

const std::string Program::name() const
{
   return _name;
}

const int Program::errcode() const
{
   return _errcode;
}

void Program::handle_exception(std::exception& e) const
{
   std::string loc = _name;

   //loc += ":" + std::to_string(_body[ndx]->lineno()) + ": error";
   loc += ": error";

   std::string msg = loc + ": " + std::string(e.what()) + "\n";

   std::cout << msg << std::endl;
}

};
