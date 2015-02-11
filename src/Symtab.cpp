/* Name: Zachary Shore
 * Date: 2014-11-11
 * Edit: 2014-11-11
 */
#include "Symtab.h"

namespace spyceless
{

void Symtab::insert(Identifier* id)
{
   _table[id->name()] = id;
}

Identifier* Symtab::find(std::string name) const
{
   auto it = _table.find(name);
   if( it != _table.end() )
      return it->second;

   return nullptr;
}

void Symtab::clear()
{
   for(auto id : _table)
      delete id.second;
   _table.clear();
}

};
