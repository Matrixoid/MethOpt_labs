#pragma once
#include <string>
#include <vector>
#include "../../MethOpt lab 2/MethOpt lab 2/Compute_gradient.h"
#include "../../MethOpt lab 2/MethOpt lab 2/get_Number.h"
#include "../../MethOpt lab 2/MethOpt lab 2/Parser.h"
#include "../../MethOpt lab1/MethOpt lab1/Combined_Brent_method.h"
#include "Pauell_method.h"

struct Broyden_Fletcher_Sheno_method {
	std::vector<double> Broyden_Fletcher_Sheno(std::string function, double a, double b) {
		std::map<std::string, long double> x0;
		x0["x"] = 2;
		x0["y"] = -5;
		std::vector < std::vector <long double>> C(x0.size(), std::vector<long double>(x0.size()));
		for (int i = 0; i < x0.size(); i++) {
			C[i][i] = 1;
		}
		double Eps = 1E-7;
		int iteration = 0;
		std::vector<long double> grad = compute_gradient(Parser(function), x0);
		while (norm(grad) > Eps) {

			int i = 0;
			while (norm(grad) > Eps&& i < x0.size()) {
				std::vector<long double> p = const_multiply(-1, matrix_multiply(C, grad));
				a = matrix_sum(x0, const_multiply(a, p));
				Combined_Brent_method cbm;
				a = cbm(function, a, 0, 10, Eps);
				p = const_multiply(a, p);
				std::map<std::string, long double> nextX = matrix_sum(x0, p);
				std::vector<long double> nextGrad = compute_gradient(Parser(function), nextX);
				std::map<std::string, long double> newX = matrix_sub(nextX, x0);
				std::vector<long double> newGrad = matrix_sub(nextGrad, grad);
				double tmp = 0;
				for (int i = 0; i < newX.size(); i++) {
					tmp += newX[i] * newGrad[i];
				}
				double p1 = 1 / tmp;


				std::vector<std::vector<double>> nextC;
				std::vector<std::vector<double>> C1(C.size(), std::vector<double>(C.size()));
				for (int i = 0; i < C.size(); i++) {
					C1[i][i] = 1;
				}
				nextC = matrix_sub(C1, matrix_multiply(matrix_multiply(newX, newGrad), p1));
				nextC = matrix_multiply(nextC, C);
				std::vector<std::vector<double>> C2(C.size(), std::vector<double>(C.size()));
				for (int i = 0; i < C.size(); i++) {
					C2[i][i] = 1;
				}
				C2 = matrix_sub(C2,
					matrix_multiply(matrix_multiply(newGrad, newX), p1));
				nextC = matrix_multiply(nextC, C2);
				nextC = matrix_sum(nextC, matrix_multiply(matrix_multiply(newX, newX), p1));
				C = nextC;
				x0 = nextX;
				grad = nextGrad;
				i++;
			}
			iteration = iteration + i;
			std::vector<std::vector<double>> C3(x0.size(), std::vector<double>(x0.size()));
			for (int i = 0; i < x0.size(); i++) {
				C3[i][i] = 1;
			}
			C = C3;
			grad = compute_gradient(Parser(function), x0);
		}
		return x0;
	}
};