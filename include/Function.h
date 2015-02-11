/* Name: Zachary Shore
 * Date: 2014-11-11
 * Edit: 2014-11-24
 */
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <cstdlib>
#include <string>
#include <vector>
#include <map>

#include "Exceptions.h"

#include "Block.h"
#include "Symtab.h"
#include "ParameterList.h"
#include "ExpressionList.h"

namespace spyceless
{

class Block;
class Statement;
class ExpressionList;

class Function
{
   public:
      Function() : _name(""), _body(nullptr) {}

      Function(std::string name, Block* parent = nullptr)
         : _name(name), _returnValue() { init(parent); }

      ~Function();

      void eval(std::vector<Literal>& vals);

      void addStatement(Statement* loc);
      void setParameters(ParameterList* param);

      Symtab* getCurrentInstance() const;
      Block* getBlockPointer() const;
      ParameterList* getParameters() const;

      Literal getReturnValue() const;
      void setReturnValue(Literal& ret);

      const std::string name() const;

   private:
      void init(Block* parent);
      void handle_exception(std::exception& e, int ndx) const;

      std::string _name;
      ParameterList* _param;

      Block* _body;

      Literal _returnValue;
};

class FunctionTable
{  
   private:
      std::map<std::string, Function*> _table;
 
   public:
      FunctionTable() {}

      FunctionTable(const FunctionTable& st) : _table(st._table) {}

      FunctionTable(FunctionTable&& st) 
         : _table( std::move(st._table) )
      {}
      
      ~FunctionTable()
      {
         for(auto id : _table)
            delete id.second;
         _table.clear();
      }
      
      void insert(Function* func);
      Function* find(std::string name) const;

      void clear();
  
      auto begin() -> decltype( _table.begin() ) const
      { return _table.begin(); }
  
      auto end() -> decltype( _table.end() ) const
      { return _table.end(); }
};

};

#endif
