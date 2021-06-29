#pragma once
#include <string>
#include <vector>
#include "Util.h"
#include "../../MethOpt lab 2/MethOpt lab 2/Compute_gradient.h"
#include "../../MethOpt lab 2/MethOpt lab 2/get_Number.h"
#include "../../MethOpt lab 2/MethOpt lab 2/Parser.h"
#include "../../MethOpt lab1/MethOpt lab1/Combined_Brent_method.h"

double eps = 1e-7;

struct Broyden_Fletcher_Sheno_method {

	std::vector<long double> operator()(std::string func) {
		std::map<std::string, long double> curX = initial_approximation(2, { 0, 0 });
		std::vector<std::vector<long double>> curG = return_identity_matrix(curX.size());
		std::vector<long double> grad = compute_gradient(Parser(func), curX);
		std::vector<long double> curW = const_multiply(-1, grad);
		std::vector<long double> curP = curW;
		long double alpha = 1;
		std::map<std::string, std::string> nx = newx(curP, curX);
		std::map<std::string, long double> alp;
		alp["x"] = 1;
		std::string fi = bringing_similar(substitute(func, nx), alp);
		Combined_Brent_method cbm;
		alpha = cbm(fi, 0, 10, eps);
		
		std::map<std::string, long double> newX = matrix_sum(curX, const_multiply(alpha, curP));
		std::map<std::string, long double> deltaX = matrix_sub(newX, curX);
		curX = newX;

		while (true) {
			std::vector<long double> newW = const_multiply(-1, compute_gradient(Parser(func), curX));
			std::vector<long double> deltaW = matrix_sub(newW, curW);
			std::vector<long double> Gw = matrix_multiply(curG, curW);
			std::vector<long double> vectorX = return_vector(deltaX);
			long double xw = scalar_multiply(vectorX, deltaW);
			long double k = scalar_multiply(Gw, curW);
			std::vector<long double> r = matrix_sub(matrix_div(Gw, k), matrix_div(vectorX, xw));

			std::vector<std::vector<long double>> first_term = curG;
			std::vector<std::vector<long double>> second_term = matrix_div(matrix_transpode_multiply(vectorX), xw);
			std::vector<std::vector<long double>> third_term = matrix_div(matrix_transpode_multiply(Gw), k);
			std::vector<std::vector<long double>> fouth_term = const_multiply(k, matrix_transpode_multiply(deltaW));

			std::vector<std::vector<long double>> newG = matrix_sum(matrix_sub(matrix_sub(first_term, second_term), third_term), fouth_term);

			std::vector<long double> newP = matrix_multiply(newG, newW);
			nx = newx(newP, curX);
			alp["x"] = 1;
			std::string fi = bringing_similar(substitute(func, nx), alp);
			Combined_Brent_method cbm;
			alpha = cbm(fi, 0, 10, eps);

			std::map<std::string, long double> newX = matrix_sub(curX, const_multiply(alpha, newP));
			deltaX = matrix_sub(newX, curX);

			curW = newW;
			curX = newX;
			curG = newG;
			curP = newP;

			if (norm(return_vector(deltaX)) < eps) {
				return return_vector(deltaX);
			}

		}
	}

};