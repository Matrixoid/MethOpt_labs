#pragma once

#include "All_inclusive.h"

struct Dychotomy_method {
	double operator()(double a, double b, double eps) {
		double d = eps;
		double x1, x2, f1, f2;
		while ((b - a) / 2 > eps) {
			x1 = (a + b - d) / 2;
			x2 = (a + b + d) / 2;
			f1 = function(x1);
			f2 = function(x2);
			if (f1 <= f2)
				b = x2;
			else
				a = x1;
		}

		double x = (a + b) / 2;
		double f = function(x);
		return f;
	}
};