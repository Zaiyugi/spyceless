sPyceless Interpreter
=====================

Build Instructions
-------------------
| Command         | Use |
| --------------- | --- |
| **make clean**  | Wipe the slate |
| **make**        | Build everything |
| **make phase1** | Run Phase 1 testsuite |
| **make phase2** | Run Phase 2 testsuite |
| **make vegas**  | Run Vegas mode |

Project Description
--------------------
This project is a command-line interpreter for sPyceless. sPyceless is a derivative of Python. However, instead of defining blocks by indentation, an **end** keyword has been added. **if** and **while** statements end their blocks with the **end** keyword.

Directory Structure
--------------------
| Directory | Description |
| --------- | ----------- |
| include   | All header files |
| src       | All source files for headers |
| build     | Storage for object files during compilation |
| phase_one | Scripts testing Phase 1 functionality |
| phase_two | Scripts testing Phase 2 functionality |
| vegas     | Scripts for Vegas mode |

Classes
========

Block
------
Block contains a list of statements and stack of Symtab*. Block takes the place of the Function and Program pseudo-blocks from Phase 1. With the Block class, we can now easily create multiple scope levels and check Identifiers against them. 

Literal
--------
Stores primitive datatypes. Consists of two std::strings, one for type information and the other for data. So when performing an operation on two Literals, you use the type information to determine how to perform the operation. Exceptions throw by Literal methods will be handled by the Statement class. Typecasting works both Numeric to String and vise-versa

Identifier
-----------
Associated a std::string name with a Literal. Variables are created using this class.

Ast
----
Node classes used in building parse trees for expressions. Almost all operations on expr in parse.y have a corresponding Ast class. Parse trees are stored inside Statements to be evaluated later. 

Statement
----------
Each line of code is translated into a Statement of some kind. This is how functions and the program is represented in memory. All Statements keep a pointer to the Program they are defined in, while some also keep a pointer to the Function they are defined in. When a Statement is evaluated, it evaluates whatever parse tree is associated with it. There are two Statements to make special note of:

#### FunctionCall
Statement defining a function call. This doesn't keep a parse tree, only a function name as a std::string and a Program* ptr. This Statement discards the return value for the function.

#### ReturnStatement
Statement defining a function's return statement. Once a return value is generated, it is placed in within the function's storage space and the function is signalled to begin returning through its blocks.

Function
---------
Represents a function in memory. A Function contains a Block, a ParameterList and storage for a return value. 

#### eval()
eval takes a list of Literals as an argument. These are used to match against the parameter list. When eval is called, the function requests its block to initialize a new instance of itself. The function then matches parameter names to the Literals passed into eval. These are stored into the block's new instance's Symtab before executing the block's statements.

Program
--------
Represents the complete program in memory. Similar to a Function, a Program now stores a Block along with its FunctionTable. eval() simply calls the block's eval()

Symtab
-------
Symbol Table class. Really just a wrapper for a std::map, mapping std::strings to Identifier* pointers.

FunctionTable
--------------
Function Table class. Also just a wrapper for a std::map, mapping std::strings to Function* pointers.

Exceptions.h
-------------
Contains all exceptions used by the various classes for signalling errors. Each inherits from std::exception

Features
==========

Strings
--------
Strings and some String operations are supported. Strings are defined as a sequence bounded by double quotes on either end and any set of characters between (except for double quotes). (Note: control characters currently don't work, so use their phyiscal equivalents)

#### Define
##### Input
   x = "cat"
   print x

##### Output
   cat

#### Append
##### Input
   x = "cat"
   x = x + "dog"

##### Output
   catdog

#### Multi-Append
##### Input
   x = "cat"
   x = x * 3 OR x = 3 * x

##### Output
   catcatcat

#### Control Character hack
##### Input
   print "cat
   dog
   fish"

##### Output
   cat
   dog
   fish

Typecasting
------------
You can typecast from any type to another.

Example 1:
##### Input
   x = 3.4
   print int(x)
   
##### Output
   3

Example 2:
##### Input
   x = 3
   print double(x)

##### Output
   3.00000

Example 3:
##### Input
   x = 1
   print "There is " + str(x) + " cat"

##### Output
   There is 1 cat

Functions
----------   
For features related to functions, it's best to look at the testsuite/phase_two examples

Errors
-------
Exceptions have been added for more useful error handling (hopefully).

Example:
##### Input
   x = "cat" + 3

##### Output
   console:1: error: invalid operands of types 'string' and 'int' to operator '+'

Scope levels
-------------
Operators have been added to explicitly specify scope. Use (::) to specify global scope and (var) for local scope. With Blocks, multiple scopes beyond just local and global are now supported. (var) references the current block. (::) is still global scope. When checking scope on an identifier, we first check local, and then start floating upward til we hit global. If it's not found along the way, the identifier is created.

Example:
##### Input
   def foo():
      ::x = 3.14
      var x = 15

      print x
   end

   foo()
   print x

##### Output
   15
   3.14

Phase 2 Features: testsuite/phase_two
======================================

Loops!
-------
While statements can be used for looping blocks. Check out the test_loops.py example

println and print
------------------
print has been changed to only print the expression with no newline added. Use println to print with a trailing newline

`__debug__`
------------
A debugging directive has been added. Call it with `__debug__` on a single line. This will print the symtab of the currently executing block along with the function table.

File Input
-----------
Input can be read from a file. Use "<id> = open(<filename>)" to open <filename> and create file stream <id> to open. Read by calling "read(<id>)". Each successive call to read will advance the file stream. Close with "close(<id>)"
Example:

   test = open("cat_data")
   x = read(test)
   print read(test)
   close(test)

eval(*expr*)
-------------
Use eval with an expression to turn that expression into a Identifier name. This can be used to approximate lists. Scope operators will also work with eval. If a non-string Literal is passed to eval, it will be reinterpreted as a string Example:

##### Input
   i = 0
   while i < 5:
      name = "x"+str(i)
      ::eval(name) = i
      i = i + 1
   end

   __debug__

##### Output
   @ -- Symtab -- @
     x0 --> 0
     x1 --> 1
     x2 --> 2
     x3 --> 3
     x4 --> 4
   @ ------------ @
   ...

Accepting/Failing
------------------
Currently, a syntactically correct program (one that follows the grammar) is accepted. While exceptions are thrown and handled for errors, default values are used to make up for missing data. This may, and probably will, lead to incorrect output. A buggy program will say accepted, as it may correct under the grammar, but have no output due to runtime errors.

