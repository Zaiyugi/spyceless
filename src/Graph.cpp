#include "Graph.h"

/* -- Public Methods -- */

void Graph::buildTable()
{
   int ndx = 1;
   int level = 0;

   table[ast] = ndx;

   #ifdef DEBUG
   std::cout << "level: " << level << std::endl;
   #endif

   if(ast->getLeft())
      build(ast->getLeft(), ++ndx, level);
   if(ast->getRight())
      build(ast->getRight(), ++ndx, level);
}

void Graph::debug()
{
   for_each(table.begin(), table.end(), [](std::pair<Ast*, int> val) {
      std::cout << "map[" << val.first << "] = " << val.second << std::endl;
   });
}

void Graph::print(std::string path)
{
   std::string filename = path + std::to_string(id) + ".gv";
   std::ofstream ofs(filename.c_str(), std::ofstream::out);
   ofs << "digraph G {" << std::endl;

   for_each(table.begin(), table.end(), [&ofs, this](std::pair<Ast*, int> val) {
      if( (val.first)->getNodetype() == "K" )
      {
         switchToDiamond(ofs, std::string("#0077AA"));
         ofs << "\t" << val.second << " [label=\"" << (val.first)->eval()() << "\"];" << std::endl;
      } else if( (val.first)->getNodetype() == "M") {
         switchToBox(ofs, std::string("#AA0077"));
         ofs << "\t" << val.second << " [label=\"" << "-" << "\"];" << std::endl;
      } else {
         switchToEllipse(ofs, std::string("#77AA00"));
         ofs << "\t" << val.second << " [label=\"" << (val.first)->getNodetype() << "\"];" << std::endl;
      }
   });  

   if(ast->getLeft())
   {
      ofs << "\t\"" << table[ast] << "\"" << " -> ";
      traverse(ast->getLeft(), ofs);
   }

   if(ast->getRight())
   {
      ofs << "\t\"" << table[ast] << "\"" << " -> ";
      traverse(ast->getRight(), ofs);
   }

   ofs << "}" << std::endl;

   ofs.close();
}

/* -- Private Methods -- */

void Graph::build(Ast* a, int &ndx, int level)
{
   ++level;

   #ifdef DEBUG
   for(int i = 0; i < level; ++i) std::cout << "  ";
   std::cout << "level: " << level << std::endl;
   #endif

   table[a] = ndx;
   if(a->getLeft())
   {
      build(a->getLeft(), ++ndx, level);
   }

   if(a->getRight())
   {
      build(a->getRight(), ++ndx, level);
   }
}

void Graph::traverse(Ast* a, std::ofstream& ofs)
{
   ofs << "\"" << table[a] << "\"" << ";" << std::endl;

   if(a->getLeft())
   {
      ofs << "\t\"" << table[a] << "\"" << " -> ";
      traverse(a->getLeft(), ofs);
   }

   if(a->getRight())
   {
      ofs << "\t\"" << table[a] << "\"" << " -> ";
      traverse(a->getRight(), ofs);
   }

}

void Graph::switchToBox(std::ofstream& ofs, std::string color)
{
   ofs << "\tnode [";
   ofs << "shape=polygon,";
   ofs << "sides=4,";
   ofs << "style=filled,";
   ofs << "fillcolor=\"" << color << "\"";
   ofs << "]; " << std::endl;
}

void Graph::switchToEllipse(std::ofstream& ofs, std::string color)
{
   ofs << "\tnode [";
   ofs << "shape=ellipse,";
   ofs << "style=filled,";
   ofs << "fillcolor=\"" << color << "\"";
   ofs << "]; " << std::endl;
}

void Graph::switchToDiamond(std::ofstream& ofs, std::string color)
{
   ofs << "\tnode [";
   ofs << "shape=polygon,";
   ofs << "sides=3,";
   ofs << "style=filled,";
   ofs << "fillcolor=\"" << color << "\"";
   ofs << "]; " << std::endl;
}
