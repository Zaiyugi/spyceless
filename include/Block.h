/* Name: Zachary Shore
 * Date: 2014-11-24
 * Edit: 2014-11-24
 */
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <cstdlib>
#include <string>
#include <vector>
#include <stack>

#include "Statement.h"
#include "Symtab.h"
#include "Identifier.h"

namespace spyceless
{

class Statement;

class Block
{
   public:
      Block() : _parent(nullptr), _returning(false) {}
      Block(Block* parent) : _parent(parent), _returning(false) {}

      ~Block();

      void eval();

      void execute();
      void initialize();
      void cleanup();

      void addStatement(Statement* loc);
      Identifier* checkScope(std::string name) const;

      Symtab* getCurrentInstance() const;
      Statement* getStatement(const int ndx) const;
      Block* parent() const;

      bool returning() const;
      void setReturning(bool flag);

   private:
      Block* _parent;

      std::vector<Statement*> _body;
      std::stack<Symtab*> _instances;

      bool _returning;
};

};

#endif
