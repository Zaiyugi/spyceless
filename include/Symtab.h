/* Name: Zachary Shore
 * Date: 2014-11-11
 * Edit: 2014-11-11
 */
#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include <cstdlib>
#include <string>
#include <map>

#include "Identifier.h"

namespace spyceless
{

class Symtab
{
   private:
      std::map<std::string, Identifier*> _table;

   public:
      Symtab() {}

      Symtab(const Symtab& st) : _table(st._table) {}

      Symtab(Symtab&& st) 
         : _table( std::move(st._table) )
      {}

      ~Symtab()
      {
         for(auto id : _table)
            delete id.second;
         _table.clear();
      }

      void insert(Identifier* id);
      Identifier* find(std::string name) const;
      void clear();

      // Some voodoo
      auto begin() -> decltype( _table.begin() ) const
      { return _table.begin(); }

      // More voodoo
      auto end() -> decltype( _table.end() ) const
      { return _table.end(); }
};

};

#endif
