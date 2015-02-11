/* Name: Zachary Shore
 * Date: 2014-11-11
 * Edit: 2014-11-24
 */
#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <cstdlib>
#include <string>
#include <vector>
#include <stack>

#include "Exceptions.h"

#include "Symtab.h"
#include "Function.h"
#include "Block.h"

namespace spyceless
{

class Block;
class Function;
class Statement;
class FunctionTable;

class Program
{
   public:
      Program() : _name(""), _errcode(0) {}

      Program(std::string name) : _name(name), _errcode(0) { init(); }

      ~Program();

      void eval();
      void init();

      void addFunction(Function* func);
      void addStatement(Statement* loc);

      Symtab* getGlobalSymtab() const;
      FunctionTable* getFunctionTable() const;
      Block* getBlockPointer() const;
      const std::string name() const;
      const int errcode() const;

   private:
      void handle_exception(std::exception& e) const;

      std::string _name;
      int _errcode;

      FunctionTable* _functions;
      Block* _body;

};

};

#endif
