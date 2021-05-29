#include <iostream>
#include "Parser.h"
#include "Compute_gradient.h"
#include "GradientDescent_method.h"
#include "ConjugateGradients_method.h"

int main()
{
	std::cout.precision(15);
	std::map<std::string, double> x;
	x["x"] = 0;
	x["y"] = 0;
	std::vector<std::vector<double>> _A = { {2, 2}, {2, 2} };
	std::vector<double> _B = { 0, 0 };
	double _C = 0;
	ConjugateGradient_method cgm;
	std::string func = "x * x - 2 * x + 125 + y * y - 2 * y";
	std::cout << cgm(func);
}