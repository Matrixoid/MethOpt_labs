#include <iostream>
#include "Parser.h"
#include "Compute_gradient.h"
#include "GradientDescent_method.h"

int main()
{
	std::cout.precision(15);
	std::string f = "-13.7 * x * x - 2 * y - 15 * x - 67";
	std::map<std::string, double> x;
	x["x"] = 1;
	x["y"] = -3;
	double s = compute_function(f, x);
	std::cout << s;
}