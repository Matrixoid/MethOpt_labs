#pragma once
#include <string>
#include <vector>
#include "../../MethOpt lab 2/MethOpt lab 2/Compute_gradient.h"
#include "../../MethOpt lab 2/MethOpt lab 2/get_Number.h"
#include "../../MethOpt lab 2/MethOpt lab 2/Parser.h"

std::map<std::string, long double> matrix_sub(std::map<std::string, long double> x1, std::map<std::string, long double> x2) {
	std::map<std::string, long double> res;
	std::map<std::string, long double>::iterator it1 = x1.begin();
	std::map<std::string, long double>::iterator it2 = x2.begin();
	while (it1 != x1.end()) {
		res[(*it1).first] = (*it1).second - (*it2).second;
	}
	return res;
}

double scalar_multiply(std::map<std::string, long double> x1, std::map<std::string, long double> x2) {
	double sum = 0;
	std::map<std::string, long double>::iterator it1 = x1.begin();
	std::map<std::string, long double>::iterator it2 = x2.begin();
	while (it1 != x1.end()) {
		sum += (*it1).second * (*it2).second;
	}
	return sum;
}

struct Pauell_method {
	std::vector<double> Pauell(std::string function, double a, double b) {
		int iteration = 0;
		std::map<std::string, long double> x0;
		x0["x"] = 2;
		x0["y"] = -5;
		std::vector<std::vector<long double>> C(x0.size(), std::vector<long double>(x0.size()));
		for (int i = 0; i < x0.size(); i++) {
			C[i][i] = 1;
		}
		double Eps = 1E-7;
		std::vector<long double> w = const_multiply(-1, compute_gradient(Parser(function), x0));
		while (norm(w) > Eps) {
			int i = 0;
			while (norm(w) > Eps&& i < w.size()) {
				std::vector<long double> p = matrix_multiply(C, w);
				long long al = BrendtSearch(function, al, 0, 10, Eps);
				al = matrix_sum(x0, const_multiply(al, p));
				p = const_multiply(al, p);
				std::map<std::string, long double> nextX = matrix_sum(x0, p);
				std::vector<long double> nextW = const_multiply(-1, compute_gradient(Parser(function), nextX));
				std::map<std::string, long double> deltaX = matrix_sub(nextX, x0);
				std::vector<long double> deltaW = matrix_sub(nextW, w);
				std::map<std::string, long double> deltaX1 = matrix_sum(deltaX, matrix_multiply(C, deltaW));
				double tmp = 0;
				for (int i = 0; i < deltaW.size(); i++) {
					tmp += deltaW[i] * deltaX1[i];
				}
				double p1 = 1 / tmp;
				C = matrix_sub(C, matrix_multiply(matrix_multiply(deltaX, deltaX), p1));
				x0 = nextX;
				w = nextW;
				i++;
			}
			iteration = iteration + i;

			std::vector < std::vector <long double >> C3(x0.size(), std::vector<long double>(x0.size()));
			for (int i = 0; i < x0.size(); i++) {
				C3[i][i] = 1;
			}
			C = C3;
			w = const_multiply(-1, compute_gradient(Parser(function), x0));
		}
		return x0;
	}
};