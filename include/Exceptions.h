/* Name: Zachary Shore
 * Date: 2014-11-04
 * Edit: 2014-11-04
 */
#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <string>
#include <sstream>
#include <exception>

namespace spyceless
{

void handle_exception(std::exception& e, int lineno, std::string _prog, std::string _func);

class InvalidBinaryOperation : public std::exception
{
   public:
      InvalidBinaryOperation() : _type1(nullptr), _type2(nullptr), _op(nullptr)  {}
      InvalidBinaryOperation(const char* t1, const char* t2, const char* op)
         : _type1(t1), _type2(t2), _op(op) {}

      ~InvalidBinaryOperation() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_type1, *_type2, *_op;
};

class InvalidUnaryOperation : public std::exception
{
   public:
      InvalidUnaryOperation() : _type1(nullptr), _op(nullptr)  {}
      InvalidUnaryOperation(const char* t1, const char* op)
         : _type1(t1), _op(op) {}

      ~InvalidUnaryOperation() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_type1, *_op;
};

class UnknownIdentifier : public std::exception
{
   public:
      UnknownIdentifier() : _name(nullptr) {}
      UnknownIdentifier(const char* n)
         : _name(n) {}

      ~UnknownIdentifier() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_name;
};

class UnknownFileHandle : public std::exception
{
   public:
      UnknownFileHandle() : _name(nullptr) {}
      UnknownFileHandle(const char* n)
         : _name(n) {}

      ~UnknownFileHandle() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_name;
};

class InvalidFunctionName : public std::exception
{
   public:
      InvalidFunctionName() : _name(nullptr) {}
      InvalidFunctionName(const char* n)
         : _name(n) {}

      ~InvalidFunctionName() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_name;
};

class InvalidAssignmentScope : public std::exception
{
   public:
      InvalidAssignmentScope() : _name(nullptr) {}
      InvalidAssignmentScope(const char* n) : _name(n) {}

      ~InvalidAssignmentScope() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_name;
};

class InvalidTypecast : public std::exception
{
   public:
      InvalidTypecast() : _fromType(nullptr), _toType(nullptr) {}
      InvalidTypecast(const char* ft, const char* tt) : _fromType(ft), _toType(tt) {}

      ~InvalidTypecast() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_fromType, *_toType;
};

class DivisionByZero : public std::exception
{
   public:
      DivisionByZero() {}

      ~DivisionByZero() noexcept {}

      const char* what() const noexcept;

};

class FunctionParameterMismatch : public std::exception
{
   public:
      FunctionParameterMismatch() : _name(nullptr), _params(0), _exprs(0) {}
      FunctionParameterMismatch(const char* n, size_t p, size_t e)
         : _name(n), _params(p), _exprs(e) {}

      ~FunctionParameterMismatch() noexcept {}

      const char* what() const noexcept;

   private:
      const char *_name;
      size_t _params, _exprs;
};

};

#endif
