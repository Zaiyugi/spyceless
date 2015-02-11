#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "Ast.h"

/* Math Ops */
const Number AstAdd::eval() const
{
	return _left->eval() + _right->eval();
}

const Number AstSub::eval() const
{
	return _left->eval() - _right->eval();
}

const Number AstMult::eval() const
{
	return _left->eval() * _right->eval();
}

const Number AstDiv::eval() const
{
	return _left->eval() / _right->eval();
}

const Number AstExpo::eval() const
{
	return _left->eval() ^ _right->eval();
}

const Number AstModulo::eval() const
{
	return _left->eval() % _right->eval();
}

const Number AstNegate::eval() const
{
	return -_left->eval();
}

/* Boolean Ops */
const Number AstLT::eval() const
{
	Number ret(0, "int");
	if(_left->eval() < _right->eval())
		ret.set(1);

	return ret;
}

const Number AstLTE::eval() const
{
	Number ret(0, "int");
	if(_left->eval() <= _right->eval())
		ret.set(1);

	return ret;
}

const Number AstGT::eval() const
{
	Number ret(0, "int");
	if(_left->eval() > _right->eval())
		ret.set(1);

	return ret;
}

const Number AstGTE::eval() const
{
	Number ret(0, "int");
	if(_left->eval() >= _right->eval())
		ret.set(1);

	return ret;
}

const Number AstNEQ::eval() const
{
	Number ret(0, "int");
	if(_left->eval() != _right->eval())
		ret.set(1);

	return ret;
}

const Number AstEQ::eval() const
{
	Number ret(0, "int");
	if(_left->eval() == _right->eval())
		ret.set(1);

	return ret;
}

