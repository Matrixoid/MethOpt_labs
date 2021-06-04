#pragma once
#include <iostream>
#include <map>
#include "Compute_gradient.h"
#include "Parser.h"
#include "Output.h"
#include <vector>

struct ConjugateGradient_method {

	double operator()(const std::string& function) {
		std::map<std::string,long double> x;
		x["x"] = 4;
		x["y"] = 19;
	//	std::cout << "x:" << std::endl;
	//	output(x);
		std::map<std::string,long double> newx = x;
		//std::cout << "newx:" << std::endl;
	//	output(newx);
		std::vector<std::vector<long double>> A = get_A(function, x);
	//	std::cout << "A:" << std::endl;
	//	output(A);
		std::vector<long double> grad = compute_gradient(Parser(function), x);
		//std::cout << "grad:" << std::endl;
	//	output(grad);
		std::vector<long double> p = negate(grad);
	//	std::cout << "p:" << std::endl;
	//	output(p);
		
		double eps = 1e-7;
		while (true) {
			x = newx;
            std::vector<long double> Ap = matrix_multiply(A, p);
		//	std::cout << "x:" << std::endl;
		//	output(x);
			double alpha = (norm(grad) * norm(grad)) / (scalar_multiply(Ap, p));
		//	std::cout << "alpha:" << std::endl;
		//	output(alpha);
			newx = matrix_sum(x, const_multiply(alpha, p));
		//	std::cout << "newx:" << std::endl;
		//	output(newx);
			
			
			std::vector<long double> newgrad = matrix_sum(grad, const_multiply(alpha, Ap));
		//	std::cout << "newgrad:" << std::endl;
		//	output(newgrad);
			long double beta = (norm(newgrad) * norm(newgrad)) / (norm(grad) * norm(grad));
		//	std::cout << "beta:" << std::endl;
		//	output(beta);
			p = matrix_sub(const_multiply(beta, p), newgrad);
		//	std::cout << "p:" << std::endl;
		//	output(p);
			grad = newgrad;
		//	std::cout << "grad:" << std::endl;
		//	output(grad);
		//	std::cout << norm(p);
			if (norm(p) < eps || norm(matrix_sub(newx, x)) < eps) {
				return compute_function(function, newx);
			}
		}
	}

};