#pragma once

#include <algorithm>
#include <vector>
#include "functions.h"

#define function func2
double a = -1;
double b = 1;

double extr(double a, double b, double eps) {
	double res = a;
	double min = 1000000;
	for (double i = a; i < b; i += eps) {
		double f = function(res);
		if (f <= min) {
			res = i;
			min = f;
		}
	}
	return function(res);
}