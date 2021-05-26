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
	//std::string f = return_function(_A, _B, _C, x);
	std::string f1 = "x + x + x * x + y + y * y + y * x + x * y + y * y";
	f1 = bringing_similar(f1, x);
	std::cout << f1 << "\n";
}