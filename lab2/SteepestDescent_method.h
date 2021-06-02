#pragma once
#include "Compute_gradient.h"
#include "Parser.h"
#include <iostream>
#include <vector>
#include <map>
#include "../lab1/Golden_ratio_method.h" 

struct SteepestDescent_mathod {

	double operator()(const std::string& func) {
		std::map<std::string, double> x;
		double eps = 1e-7;
		double f = compute_function(func, x);
		while (true) {
			std::vector <double> grad = compute_gradient(Parser(func), x);
			if (norm(grad) < eps)
			{
				return compute_function(func, x);
			}
			std::map<std::string, std::string> nx = newx(func, x);
			std::string fi = substitute(func, nx);
			Golden_ratio_method grm;
			double alpha = grm(func, -1, 1, eps);
			std::map<std::string, double> alp;
			alp["x"] = alpha;
			x = compute_x(nx, alp);
		}
	}

private:
	std::map<std::string, std::string> newx(std::string function, std::map<std::string, double> x) {
		std::map<std::string, std::string> nx;
		int i = 0;
		for (std::pair<std::string, double> s : x) {
			std::string r = toString(s.second) + "-" + "x" + "*" + toString(compute_gradient(Parser(function), x)[i]);
			i++;
			nx[s.first] = r;
		}
		return nx;
	}

	std::map<std::string, double> compute_x(std::map<std::string, std::string> x, std::map<std::string, double> alpha) {
		std::map < std::string, double> res;
		for (std::pair<std::string, std::string> s : x) {
			res[s.first] = compute_function(s.second, alpha);
		}
		return res;
	}
};
