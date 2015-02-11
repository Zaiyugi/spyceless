#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <tuple>
#include <map>

#include "Ast.h"

class Graph
{
   public:
      Graph() : ast(nullptr), id(0) {}
      Graph(Ast* a, int x) : ast(a), id(x) {}

      ~Graph() {}

      void set(Ast *a, int x)
      {
         ast = a;
         id = x;
         table.clear();
      }

      void buildTable();
      void debug();
      void print(std::string path);

   private:
      void build(Ast* a, int &ndx, int level);
      void traverse(Ast* a, std::ofstream& ofs);

      void switchToDiamond(std::ofstream& ofs, std::string color);
      void switchToEllipse(std::ofstream& ofs, std::string color);
      void switchToBox(std::ofstream& ofs, std::string color);

      Ast *ast;
      int id;

      std::map<Ast*, int> table;
};

#endif
