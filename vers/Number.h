/* Name: Zachary Shore
 *	Date: 2014-10-30
 */
#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <cstdlib>
#include <string>
#include <cmath>

static const double TOL = 1e-8;

class Number
{
	public:
		Number() : _type("double"), _value(0) {}
		Number(double x, std::string t) : _type(t), _value(x) {}

		Number(const Number& n) : 
			_type( n.type() ), 
			_value( n() )
		{}

		Number(Number&& n) : 
			_type( std::move(n.type()) ), 
			_value( n() )
		{}

		const Number operator+(const Number& n) const;
		const Number operator-(const Number& n) const;
		friend const Number operator-(const Number& n);
		const Number operator*(const Number& n) const;
		const Number operator/(const Number& n) const;
		const Number operator%(const Number& n) const;
		const Number operator^(const Number& n) const;

		const bool operator<(const Number& n) const;
		const bool operator<=(const Number& n) const;
		const bool operator>(const Number& n) const;
		const bool operator>=(const Number& n) const;
		
		const bool operator!=(const Number& n) const;
		const bool operator==(const Number& n) const;
		
		const double operator()() const;
		const std::string type() const;
		void set(double val);
		const double get() const;

	private:
		std::string _type;
		double _value;
};

#endif
