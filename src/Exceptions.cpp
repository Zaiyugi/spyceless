/* Name: Zachary Shore
 * Date: 2014-11-04
 * Edit: 2014-11-04
 */
#include "Exceptions.h"

namespace spyceless
{

const char* InvalidBinaryOperation::what() const noexcept
{
   std::string output;

   output += "invalid operands of types \'" 
      + std::string(_type1) + "\' and \'" + std::string(_type2) 
      + "\' to operation \'" + std::string(_op) + "\'";

   return output.c_str();
}

const char* InvalidUnaryOperation::what() const noexcept
{
   std::string output;

   output += "invalid operand of type \'" 
      + std::string(_type1) + "\' to operation \'" + std::string(_op) + "\'";

   return output.c_str();
}

const char* UnknownIdentifier::what() const noexcept
{
   std::string output;

   output += "identifier \'" + std::string(_name)
      + "\' not found";

   return output.c_str();
}

const char* UnknownFileHandle::what() const noexcept
{
   std::string output;

   output += "file handle \'" + std::string(_name)
      + "\' not found";

   return output.c_str();
}

const char* InvalidFunctionName::what() const noexcept
{
   std::string output;

   output += "function \'" + std::string(_name)
      + "\' has not been defined";

   return output.c_str();
}

const char* InvalidAssignmentScope::what() const noexcept
{
   std::string output;

   output += "\'" + std::string(_name) + "\' declared local in global scope";

   return output.c_str();
}

const char* InvalidTypecast::what() const noexcept
{
   std::string output;

   output += "invalid cast from \'" + std::string(_fromType) + "\' to \'" + std::string(_toType) + "\'";

   return output.c_str();
}

const char* DivisionByZero::what() const noexcept
{
   std::string output;
   output += "floating point exception: division by zero";
   return output.c_str();
}

const char* FunctionParameterMismatch::what() const noexcept
{
   std::string output;

   output += "function " + std::string(_name) + " takes " + std::to_string(_params) + " arguments; ";
   output += std::to_string(_exprs) + " provided";

   return output.c_str();
}

};
