/* Name: Zachary Shore
 *	Date: 2014-10-30
 */
#include <Number.h>

/* Math Ops */
const Number Number::operator+(const Number& n) const
{
	return Number( _value + n.get(), _type );
}

const Number Number::operator-(const Number& n) const
{
	return Number( _value - n.get(), _type );
}

const Number operator-(const Number& n)
{
	return Number( -n.get(), n.type() );
}

const Number Number::operator*(const Number& n) const
{
	return Number( _value * n.get(), _type );
}

const Number Number::operator/(const Number& n) const
{
	double val = _value / n.get();
	std::string datatype("double");
	if(n.type() == "int" && _type == "int")
	{
		datatype = "int";
		if(n() < 0 || _value < 0)
			val = std::ceil(val);
		else
			val = std::floor(val);
	}

	return Number( val, datatype );
}

const Number Number::operator^(const Number& n) const
{
	return Number( std::pow( _value, n.get() ), _type );
}

const Number Number::operator%(const Number& n) const
{
	return Number();
}

/* Boolean Ops */
const bool Number::operator<(const Number& n) const
{
	return _value < n.get();
}

const bool Number::operator<=(const Number& n) const
{
	return _value <= n.get();
}

const bool Number::operator>(const Number& n) const
{
	return _value > n.get();
}

const bool Number::operator>=(const Number& n) const
{
	return _value >= n.get();
}

const bool Number::operator!=(const Number& n) const
{
	return _value != n.get();
}

const bool Number::operator==(const Number& n) const
{
	return _value == n.get();
}

/* Getter/Setter functions */
const double Number::operator()() const
{ return _value; }

const std::string Number::type() const
{ return _type; }

void Number::set(double val)
{ _value = val; }

const double Number::get() const
{ return _value; }

