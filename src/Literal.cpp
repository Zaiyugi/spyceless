/* Name: Zachary Shore
 * Date: 2014-10-30
 * Edit: 2014-11-06
 */
#include <iostream>
#include <Literal.h>

namespace spyceless
{

/* Math Ops */
const Literal Literal::operator+(const Literal& n) const
{
   //std::cout << "Types: " << _type << " " << n.type() << std::endl;

   if( isNumeric() && n.isNumeric() )
   {
      if( isInteger() && n.isInteger() )
      {
         int val = getInteger() + n.getInteger();
         return Literal(val, INTEGER);
      } else {
         double val = getDouble() + n.getDouble();
         return Literal(val, DOUBLE);
      }
   } else if( _type == n.type() ) {
      std::string data = _value + n.get();
      return Literal(data, _type);

   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "+");
   }

   return INVALID_LITERAL;
}

const Literal Literal::operator-(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      if( isInteger() && n.isInteger() )
      {
         int val = getInteger() - n.getInteger();
         return Literal(val, INTEGER);
      } else {
         double val = getDouble() - n.getDouble();
         return Literal(val, DOUBLE);
      }
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "-");
   }

   return INVALID_LITERAL;
}

const Literal operator-(const Literal& n)
{
   if( n.isDouble() )
   {
      double val = -n.getDouble();
      return Literal(val, n.type());

   } else if( n.isInteger() ) {
      int val = -n.getInteger();
      return Literal(val, n.type());

   } else {
      throw InvalidUnaryOperation(n.type().c_str(), "-");
   }

   return INVALID_LITERAL;
}

const Literal Literal::operator*(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      if( isInteger() && n.isInteger() )
      {
         int val = getInteger() * n.getInteger();
         return Literal(val, INTEGER);
      } else {
         double val = getDouble() * n.getDouble();
         return Literal(val, DOUBLE);
      }

   } else if( isString() && n.isInteger() ) {
      std::string data;
      nCopyConcat( data, n.getInteger() );
      return Literal( data, _type );

   } else if( isInteger() && n.isString() ) {
      std::string data;
      n.nCopyConcat( data, getInteger() );
      return Literal( data, n.type() );

   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "*");
   }

   return INVALID_LITERAL;
}

const Literal Literal::operator/(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      double val = getDouble() / n.getDouble();
      std::string datatype("double");

      if( n.getDouble() == 0 )
         throw DivisionByZero();

      if( n.isInteger() || isInteger() )
      {
         datatype = "int";
         if(n.getInteger() < 0 || getInteger() < 0)
            val = std::ceil(val);
         else
            val = std::floor(val);

         return Literal( static_cast<int>(val), datatype );
      }

      return Literal( val, datatype );

   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "/");
   }

   return INVALID_LITERAL;
}

const Literal Literal::operator^(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      if( isInteger() && n.isInteger() )
      {
         int val = std::pow( getInteger(), n.getInteger() );
         return Literal(val, INTEGER);
      } else {
         double val = std::pow( getDouble(), n.getDouble() );
         return Literal(val, DOUBLE);
      }
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "**");
   }

   return INVALID_LITERAL;
}

const Literal Literal::operator%(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      if( isInteger() && n.isInteger() )
      {
         int val = getInteger() % n.getInteger();
         return Literal(val, INTEGER);
      } else {
         double val = std::fmod( getDouble(), n.getDouble() );
         return Literal(val, DOUBLE);
      }
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "%");
   }

   return INVALID_LITERAL;
}

/* Boolean Ops */
const bool Literal::operator<(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      return getDouble() < n.getDouble();
   } else if( _type == n.type() ) {
      return _value < n.get();
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "<");
   }

   return false;
}

const bool Literal::operator<=(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      return getDouble() <= n.getDouble();
   } else if( _type == n.type() ) {
      return _value <= n.get();
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "<=");
   }

   return false;
}

const bool Literal::operator>(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      return getDouble() > n.getDouble();
   } else if( _type == n.type() ) {
      return _value > n.get();
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), ">");
   }

   return false;
}

const bool Literal::operator>=(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      return getDouble() >= n.getDouble();
   } else if( _type == n.type() ) {
      return _value >= n.get();
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), ">=");
   }

   return false;
}

const bool Literal::operator!=(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      return getDouble() != n.getDouble();
   } else if( _type == n.type() ) {
      return _value != n.get();
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "!=");
   }

   return false;
}

const bool Literal::operator==(const Literal& n) const
{
   if( isNumeric() && n.isNumeric() )
   {
      return getDouble() == n.getDouble();
   } else if( _type == n.type() ) {
      return _value == n.get();
   } else {
      throw InvalidBinaryOperation(_type.c_str(), n.type().c_str(), "==");
   }

   return false;
}

/* Helper Functions */
bool Literal::isNumeric() const
{
   return (_type == INTEGER || _type == DOUBLE);
}

bool Literal::isInteger() const
{
   return (_type == INTEGER);
}

bool Literal::isDouble() const
{
   return (_type == DOUBLE);
}

bool Literal::isString() const
{
   return (_type == STRING);
}

void Literal::nCopyConcat(std::string& data, int copies) const
{
   data = _value;
   copies--;
   for(int i = 0; i < copies; ++i)
      data += _value;
}

void Literal::invalid_operation(std::string t1, std::string t2, std::string op) const
{
   std::cerr << "Error: Invalid operands";

   std::cerr << " \'" << t1 << "\' ";
   if(!t2.empty())
      std::cerr << "and \'" << t2 << "\' ";

   std::cerr << "to operator \'" << op << "\'" << std::endl;
}

/* Assignment */
const Literal Literal::operator=(const Literal& v)
{
   _value = v.get();
   _type = v.type();
   return *this;
}

/* Get operator */
const std::string Literal::operator()() const
{
   return _value;
}

/* Indexing */
const std::string Literal::operator[](const int& ndx) const
{
   return std::string();
}

/* Typecasting */
void Literal::toInt()
{
   if( isDouble() || isString() )
   {
      size_t pos = _value.find_first_of(".");
      if(pos < _value.size())
         _value.erase(pos, _value.npos);
   }

   _type = INTEGER;

}

void Literal::toDouble()
{
   _type = DOUBLE;
}

void Literal::toString()
{
   _type = STRING;
}

const Literal Literal::castToInt() const
{
   Literal val(*this);
   val.set(this->getInteger());
   val.toInt();
   return val;
}

const Literal Literal::castToDouble() const
{
   Literal val(*this);
   val.set(this->getDouble());
   val.toDouble();
   return val;
}

const Literal Literal::castToString() const
{
   Literal val(*this);
   val.toString();
   return val;
}

/* Getter/Setter functions */
const std::string Literal::type() const
{
   return _type;
}

void Literal::set(double val)
{
   _value = std::to_string(val);
}

void Literal::set(std::string val)
{
   _value = val;
}

const std::string Literal::get() const
{
   return _value;
}

const double Literal::getDouble() const
{
   return std::stof(_value);
}

const int Literal::getInteger() const
{
   return std::stoi(_value);
}

/* Protected Raw */
const std::string Literal::raw_type() const
{ return _type; }

const std::string Literal::raw_value() const
{ return _value; }

};
