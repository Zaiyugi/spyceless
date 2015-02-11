/* Name: Zachary Shore
 * Date: 2014-11-11
 * Edit: 2014-11-11
 */
#include "Function.h"

namespace spyceless
{

/* Function */
Function::~Function()
{
   delete _body;
   if( _param )
      delete _param;
}

void Function::init(Block* parent)
{
   _body = new Block(parent);
}

void Function::eval(std::vector<Literal>& vals)
{
   if( _body )
   {
      if( vals.size() != _param->size() )
      {
         throw FunctionParameterMismatch(_name.c_str(), _param->size(), vals.size());
      }

      _body->initialize();
      Symtab* symtab = _body->getCurrentInstance();
      for(int i = 0; i < vals.size(); ++i)
      {
         symtab->insert( new VariableIdentifier((*_param)[i], vals[i]) );
      }

      _body->execute();
      _body->cleanup();

      _body->setReturning(false);
      _body->parent()->setReturning(false);
   }
}

void Function::addStatement(Statement* loc)
{
   _body->addStatement(loc);
}

void Function::setParameters(ParameterList* param)
{
   _param = param;
}

Symtab* Function::getCurrentInstance() const
{
   return _body->getCurrentInstance();
}

Block* Function::getBlockPointer() const
{
   return _body;
}

ParameterList* Function::getParameters() const
{
   return _param;
}

Literal Function::getReturnValue() const
{ return _returnValue; }

void Function::setReturnValue(Literal& ret)
{ _returnValue = ret; }

const std::string Function::name() const
{
   return _name;
}

void Function::handle_exception(std::exception& e, int ndx) const
{
   std::string loc = ":" + std::to_string(_body->getStatement(ndx)->lineno()) 
      + ": error in function \'" + _name + "\'";

   std::string msg = loc + ": " + std::string(e.what()) + "\n";

   std::cout << msg << std::endl;
}

/* FunctionTable */
void FunctionTable::insert(Function* func)
{
   _table[func->name()] = func;
}

Function* FunctionTable::find(std::string name) const
{
   auto it = _table.find(name);
   if( it != _table.end() )
      return it->second;

   return nullptr;
}

void FunctionTable::clear()
{
   for(auto func : _table)
      delete func.second;
   _table.clear();
}

};
