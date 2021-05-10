#pragma once

#include <cmath>

double func1(double x) {
	return x * x + exp(-0.35 * x);
}

double func2(double x) {
	return x * x * x * x - 1.5 * atan(x);
}

double func3(double x) {
	return x * sin(x) + 2 * cos(x);
}

double func4(double x) {
	return x - log(x); 
}

double func5(double x) {
	return 10 * x * log(x) - x * x / 2;
}

double func6(double x) {
	return -5 * x * x * x * x * x + 4 * x * x * x * x - 12 * x * x * x + 11 * x * x - 2 * x + 1;
}

double func7(double x) {
	return log10(x - 2) * log10(x - 2) + log10(10 - x) * log10(10 - x) - pow(x, 0.2);
}

double func8(double x) {
	return 3 * x * sin(0.75 * x) + exp(-2 * x);
}

double func9(double x) {
	return exp(3 * x) + 5 * exp(-2 * x);
}

double func10(double x) {
	return 0.2 * x * log10(x) + (x - 2.3) * (x - 2.3);
}

double func11(double x) {
	return 24 * x - 25 * x * x + 35 * x * x * x / 3 - 5 * x * x * x * x / 2 + x * x * x * x * x / 5;
}

double func12(double x) {
	const double PI = 3.141592653589793238463;
	return x * x + x * sin(PI * x);
}

double func13(double x) {
	const double PI = 3.141592653589793238463;
	return x * x + x * x * sin(PI * x);
}
