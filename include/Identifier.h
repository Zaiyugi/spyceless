/* Name: Zachary Shore
 * Date: 2014-11-06
 * Edit: 2014-11-10
 */
#ifndef __IDENTIFIER_H__
#define __IDENTIFIER_H__

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <string>
#include <cmath>

#include "Literal.h"

namespace spyceless
{

class Identifier
{
   public:
      Identifier() : _name() {}

      Identifier(std::string str) : _name(str) {}

      Identifier(const Identifier& id) : 
         _name( id._name ) 
      {}

      Identifier(Identifier&& id) : 
         _name( std::move(id._name) )
      {}

      virtual ~Identifier() {}

      const std::string name() const;

      virtual const size_t size() const;
      virtual const std::string type() const;
      virtual const Literal get(size_t ndx = 0) const;
      virtual void set(Literal& val) {}

   protected:
      std::string _name;
};

static const Identifier INVALID_IDENT("invalid");

class VariableIdentifier : public Identifier
{
   public:
      VariableIdentifier() : Identifier(""), _data(INVALID_LITERAL) {}

      VariableIdentifier(std::string str, Literal datum) : 
         Identifier(str), _data(datum) {}

      virtual ~VariableIdentifier() {}

      const size_t size() const;
      virtual const std::string type() const;
      virtual const Literal get(size_t ndx = 0) const;
      void set(Literal& val);

   protected:
      Literal _data;

};

class FileIdentifier : public VariableIdentifier
{
   public:
      FileIdentifier() : VariableIdentifier() {}

      FileIdentifier(std::string str, Literal file) : VariableIdentifier(str, file) { open(); }

      ~FileIdentifier();

      const std::string type() const;
      void open();
      void close();

      std::ifstream _ifs;
};

};

#endif
