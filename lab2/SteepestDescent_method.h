#pragma once
#include "Compute_gradient.h"
#include "Parser.h"
#include <iostream>
#include <vector>
#include <map>
#include "../../MethOpt lab1/MethOpt lab1/Golden_ratio_method.h" 

struct SteepestDescent_mathod {

	double operator()(std::string function) {
		std::map<std::string, double> x;
		double yeps = 1e-7;
		double f = compute_function(function, x);
	step2:
		std::vector <double> grad = compute_gradient(Parser(function), x);
		if (norm(grad) < yeps)
		{
			return compute_function(function, x);
		}
		std::string fi = substitute(function, matrix_sub(x, const_multiply(alpha, grad));
		double fix = compute_function(fi, x);
		alpha = findalpha();
		x = matrix_sub(const_multiply(alpha, grad));
		f = compute_function(function, x);
		goto step2;
	}

};
