/* Name: Zachary Shore
 * Date: 2014-12-02
 * Edit: 2014-12-02
 */
#include "ParameterList.h" 

namespace spyceless
{

void ParameterList::add(std::string name)
{
   _param.push_back(name);
}

size_t ParameterList::size() const
{
   return _param.size();
}

std::string ParameterList::operator[](const int ndx) const
{
   return _param[ndx];
}

};
