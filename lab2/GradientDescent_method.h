#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Compute_gradient.h"
#include "Parser.h"

struct GradientDescent_method {
	double operator()(std::string function) {
		double yeps = 1e-8, alpha = 512;
		std::map<std::string, double> x;
		x["x"] = 1;
		x["y"] = 5;
		double f = compute_function(function, x);
		while (true) {
			std::vector<double> gradient = compute_gradient(Parser(function), x);
			if (norm(gradient) < yeps) {
				std::map<std::string, double>x_ = x;
				f = compute_function(function, x);
				return f;
			}

			while (true) {
				std::map<std::string, double> y;
				gradient = compute_gradient(Parser(function), x);
				int i = 0;
				for (std::pair<std::string, double> p : x) {
					y[p.first] = x[p.first] - alpha * gradient[i];
					i++;
				}
				double f2 = compute_function(function, y);
				if (f2 < f)
				{
					x = y;
					f = f2;
					break;
				}
				else
				{
					alpha /= 2;
				}
			}
		}
	}
};