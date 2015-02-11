/* Name: Zachary Shore
 * Date: 2014-12-02
 * Edit: 2014-12-02
 */
#include "ExpressionList.h" 

namespace spyceless
{

ExpressionList::~ExpressionList()
{
   for(auto entry : _expr)
      delete entry;
}

void ExpressionList::add(Ast* expr)
{
   _expr.push_back(expr);
}

size_t ExpressionList::size() const
{
   return _expr.size();
}

Ast* ExpressionList::operator[](const int ndx) const
{
   return _expr[ndx];
}

};
