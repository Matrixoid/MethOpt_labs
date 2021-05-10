#include <iostream>
#include "Parser.h"
#include "Compute_gradient.h"

int main()
{
	std::cout.precision(15);

	std::vector<std::string> gradient = Parser("113.37 * x1*x2*x1*x1+ x1*x1 + x2");
	std::map<std::string, double> x;
	x["x1"] = 5;
	x["x2"] = 1;
	std::vector<double> r = compute_gradient(gradient, x);
	for (double a : r) {
		std::cout << a << std::endl;
	}
}