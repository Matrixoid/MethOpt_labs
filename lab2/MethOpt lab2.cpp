#include <iostream>
#include "Parser.h"
#include "Compute_gradient.h"
#include "GradientDescent_method.h"
#include "ConjugateGradients_method.h"

int main()
{
	std::cout.precision(15);
	std::string f = "x * x + 2 * x * y + y * y - 5";
	std::map<std::string, double> x;
	ConjugateGradient_method cgm;
	std::cout << cgm(f);
	/*double s = compute_function(f, x);
	std::cout << s;*/
}