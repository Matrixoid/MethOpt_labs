#pragma once
#include <iostream>
#include <map>
#include "Compute_gradient.h"
#include "Parser.h"
#include <vector>

struct ConjugateGradient_method {

	double operator()(std::string function) {
		std::map<std::string, double> x;
		std::map<std::string, double> newx;
		std::vector<double> grad = compute_gradient(Parser(function), x);
		std::vector <double>p = negate(grad);
		
		double eps = 1e-7;
		while (true) {
			if (norm(p) < eps || norm(matrix_sub(newx, x)) < eps)
			{
				return compute_function(function, x);
			}

			std::vector<double> apk = matrix_multiply(A, p);
			double alpha = norm(grad) * norm(grad) / (scalar_multiply(matrix_multiply(A, p), p));
			int i = 0;
			x = newx;
			newx = matrix_sum(x, const_multiply(alpha, p));
			
			std::vector<double> newgrad = matrix_sum(grad, const_multiply(alpha, matrix_multiply(A, p)));
			double beta = (norm(newgrad) * norm(newgrad)) / (norm(grad) * norm(grad));
			p = matrix_sub(const_multiply(beta, p), newgrad);
			grad = newgrad;
		}
	}

};