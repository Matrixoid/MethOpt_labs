#pragma once

#include <algorithm>
#include <vector>
#include "functions.h"

#define function1 func2


double extr(double a, double b, double eps) {
	double res = a;
	double min = 1000000;
	for (double i = a; i < b; i += eps) {
		double f = function1(res);
		if (f <= min) {
			res = i;
			min = f;
		}
	}
	return function1(res);
}