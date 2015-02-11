/* Name: Zachary Shore
 * Date: 2014-11-24
 * Edit: 2014-11-24
 */
#include "Block.h"

namespace spyceless
{

/* Block */
Block::~Block()
{
   for(auto it : _body)
      delete it;
}

void Block::eval()
{
   initialize();
   execute();
   cleanup();
}

void Block::execute()
{
   for(size_t i = 0; i < _body.size(); ++i)
   {
      _body[i]->eval();

      if( _body[i]->type() == RETURN_STATEMENT || returning() )
      {
         _parent->setReturning(true);
         _returning = false;
         break;
      }
   }

}

void Block::initialize()
{
   _instances.push(new Symtab());
}

void Block::cleanup()
{
   Symtab* symtab = _instances.top();
   _instances.pop();
   delete symtab;
}

Identifier* Block::checkScope(std::string name) const
{
   Identifier* id = _instances.top()->find(name);
   if( id )
      return id;

   Block* cur = _parent;
   while( cur )
   {
      Symtab* instance = cur->getCurrentInstance();
      id = instance->find(name);
      if( id )
         break;
      cur = cur->parent();
   }

   return id;
}

void Block::addStatement(Statement* loc)
{
   _body.push_back(loc);
}

Symtab* Block::getCurrentInstance() const
{
   return _instances.top();
}

Statement* Block::getStatement(const int ndx) const
{
   return _body[ndx];
}

Block* Block::parent() const
{
   return _parent;
}

bool Block::returning() const
{ return _returning; }

void Block::setReturning(bool flag)
{ _returning = flag; }

};
