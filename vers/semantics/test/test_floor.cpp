#include <iostream>
#include <cmath>

int main(void)
{
	int x, y;
	std::cin >> x >> y;

	std::cout << "x/y: " << x/y << std::endl;

	double a, b;
	std::cin >> a >> b;

	double val = a/b;
	if(a < 0 || b < 0)
		val = std::ceil(val);
	else
		val = std::floor(val);

	std::cout << "floored a/b: " << val << std::endl;

	std::cout << "double/int: " << a/x << std::endl;
	std::cout << "int/double: " << x/a << std::endl;
}
