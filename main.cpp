#include <iostream>
#include <cstdio>
#include <stack>

#include "Exceptions.h"
#include "Program.h"
#include "Block.h"

extern FILE* yyin;
extern int yyparse();
extern spyceless::Program* program;
extern std::stack<spyceless::Block*> current_block;

bool from_cmdline = false;
FILE* script;

void cleanup()
{
   delete program;

   if( from_cmdline )
	   fclose(script);
}

int main(int argc, char** argv)
{
   std::string prog_name("console");
   if(argc == 2)
	{
      prog_name = std::string(argv[1]);
	   script = fopen(argv[1], "r");
      yyin = script;
      from_cmdline = true;
	}

   program = new spyceless::Program(prog_name);
   current_block.push(program->getBlockPointer());

   std::cout << "# ------------------------ #" << std::endl;
   int errcode = 1;
   if ( yyparse() ) {
      std::cout << std::endl;

      cleanup();

      return errcode;
   } else {

      try
      {
         program->eval();
      } catch(std::exception& e) {
      }

      errcode = program->errcode();
      cleanup();

      std::cout << std::endl;
      std::cout << "\t accepted" << std::endl;
      std::cout << "# ------------------------ #" << std::endl << std::endl;
   }

   return errcode;
}
