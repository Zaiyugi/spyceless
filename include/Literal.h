/* Name: Zachary Shore
 * Date: 2014-10-30
 * Edit: 2014-11-04
 */
#ifndef __LITERAL_H__
#define __LITERAL_H__

#include <cstdlib>
#include <cmath>
#include <string>

#include "Exceptions.h"

namespace spyceless
{

static const double TOL = 1e-8;
static const std::string DOUBLE("double");
static const std::string INTEGER("int");
static const std::string STRING("string");

class Literal
{
   public:
      Literal() : _type("double"), _value("0") {}

      Literal(std::string x, std::string t) : _type(t), _value(x) {}

      Literal(int x, std::string t) : _type(t), _value(std::to_string(x)) {}

      Literal(double x, std::string t) : _type(t), _value(std::to_string(x)) {}

      Literal(char* x, std::string t) : _type(t), _value(x) {}

      Literal(const Literal& n) :
         _type( n.raw_type() ), 
         _value( n.raw_value() )
      {
         //std::cout << "Copy" << std::endl;
      }

      Literal(Literal&& n) : 
         _type( std::move(n.raw_type()) ), 
         _value( std::move(n.raw_value()) )
      {
         //std::cout << "Move" << std::endl;
      }

      const Literal operator+(const Literal& n) const;
      const Literal operator-(const Literal& n) const;
      friend const Literal operator-(const Literal& n);
      const Literal operator*(const Literal& n) const;
      const Literal operator/(const Literal& n) const;
      const Literal operator%(const Literal& n) const;
      const Literal operator^(const Literal& n) const;

      const bool operator<(const Literal& n) const;
      const bool operator<=(const Literal& n) const;
      const bool operator>(const Literal& n) const;
      const bool operator>=(const Literal& n) const;
      
      const bool operator!=(const Literal& n) const;
      const bool operator==(const Literal& n) const;

      const Literal operator=(const Literal& v);
   
      const std::string operator[](const int& ndx) const;

      const std::string operator()() const;

      const std::string type() const;
      const std::string get() const;
      const double getDouble() const;
      const int getInteger() const;

      void toInt();
      void toDouble();
      void toString();

      const Literal castToInt() const;
      const Literal castToDouble() const;
      const Literal castToString() const;

      void set(double val);
      void set(std::string val);

   protected:
      bool isNumeric() const;
      bool isInteger() const;
      bool isDouble() const;
      bool isString() const;

      const std::string raw_type() const;
      const std::string raw_value() const;

      void nCopyConcat(std::string& data, int copies) const;

      void invalid_operation(std::string t1, std::string t2, std::string op) const;

      std::string _type;
      std::string _value;
};

static const Literal INVALID_LITERAL(-1, "invalid");
static const Literal TRUE_LITERAL(1, "int");
static const Literal FALSE_LITERAL(0, "int");

};

#endif
