/* Name: Zachary Shore
 * Date: 2014-12-02
 * Edit: 2014-12-02
 */
#ifndef __EXPRESSIONLIST_H__
#define __EXPRESSIONLIST_H__

#include <cstdlib>
#include <string>
#include <vector>

#include "Ast.h"

namespace spyceless
{

class Ast;

class ExpressionList
{
   public:
      ExpressionList() {}

      ~ExpressionList();

      void add(Ast* name);

      size_t size() const;

      Ast* operator[](const int ndx) const;

   private:
      std::vector<Ast*> _expr;
};

};

#endif
