#include <iostream>
#include "Parser.h"
#include "Compute_gradient.h"
#include "GradientDescent_method.h"
#include "ConjugateGradients_method.h"

int main()
{
	std::cout.precision(15);
	std::string f = "x * x + 2 * x * y + y * y";
	std::vector<char> signs;
	std::vector<std::string> spl = split(signs, f);
	/*for (int i = 0; i < spl.size(); i++) {
		std::vector<std::string> spl1 = split_by_mul(spl[i]);
		for (std::string s : spl1) {
			std::cout << s << " ";
		}
	}*/
	std::map<std::string, double> x;
	ConjugateGradient_method cgm;
	std::cout << cgm(f);
	/*double s = compute_function(f, x);
	std::cout << s;*/
}