/* Name: Zachary Shore
 * Date: 2014-12-02
 * Edit: 2014-12-02
 */
#ifndef __PARAMETERLIST_H__
#define __PARAMETERLIST_H__

#include <cstdlib>
#include <string>
#include <vector>

namespace spyceless
{

class ParameterList
{
   public:
      ParameterList() {}

      ~ParameterList() {}

      void add(std::string name);

      size_t size() const;

      std::string operator[](const int ndx) const;

   private:
      std::vector<std::string> _param;
};

};

#endif
