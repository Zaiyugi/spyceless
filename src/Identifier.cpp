/* Name: Zachary Shore
 * Date: 2014-11-10
 * Edit: 2014-11-10
 */
#include "Identifier.h"

namespace spyceless
{

/* Base Identifier */
const std::string Identifier::name() const
{
   return _name;
}

const std::string Identifier::type() const
{
   return std::string("base");
}

const size_t Identifier::size() const
{
   return 0;
}

const Literal Identifier::get(size_t ndx) const
{
   return INVALID_LITERAL;
}

/* Variable Identifier */
const size_t VariableIdentifier::size() const
{
   return 1;
}

const std::string VariableIdentifier::type() const
{
   return std::string("variable");
}

const Literal VariableIdentifier::get(size_t ndx) const
{
   return _data;
}

void VariableIdentifier::set(Literal& val)
{
   _data = val;
}

/* File Identifier */
FileIdentifier::~FileIdentifier()
{
   if( _ifs.is_open() )
      _ifs.close();
}

const std::string FileIdentifier::type() const
{
   return std::string("file");
}

void FileIdentifier::open()
{
   _ifs.open(_data.get().c_str(), std::ifstream::in);
}

void FileIdentifier::close()
{
   _ifs.close();
}

};

