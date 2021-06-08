#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Compute_gradient.h"
#include "Parser.h"

struct GradientDescent_method {
	double operator()(const std::string& function) {
		double eps = 1e-4;
		double alpha = 1;
		std::map<std::string, double> x;
		x["x"] = 0;
		x["x"] = 0;
		std::map<std::string, double> newx;
		int it = 0;
		while (true) {
			std::vector<double> gradient = compute_gradient(Parser(function), x);
			double len = norm(gradient);

			if (len < eps) {
				break;
			}

			int i = 0;
			for (const auto& p : x) {
				newx[p.first] = x[p.first] - alpha * gradient[i];
				i++;
			}
			double f = compute_function(function, x);
			double f2 = compute_function(function, newx);
			if (f < f2) {
				alpha /= 2;
			}
			newx = x;
			it++;
		}
		return compute_function(function, x);
	}
};
