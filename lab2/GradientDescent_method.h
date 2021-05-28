#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Compute_gradient.h"
#include "Parser.h"

struct GradientDescent_method {
	double operator()(const std::string& function) {
		double eps = 1e-8, alpha = 512;
		std::map<std::string, double> x;
		x["x"] = 1;
		x["y"] = 5;
		double f = compute_function(function, x);
		while (true) {
			std::vector<double> gradient = compute_gradient(Parser(function), x);
			if (norm(gradient) < eps) {
				std::map<std::string, double> min = x;//точка минимума
				f = compute_function(function, x);//значение в точке минимума
				return f;
			}
			while (true) {
				std::map<std::string, double> y;
				gradient = compute_gradient(Parser(function), x);
				int i = 0;
				for (const auto& p : x) {
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
