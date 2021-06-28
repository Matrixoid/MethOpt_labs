#pragma once
#include <string>
#include <vector>
#include "../../MethOpt lab 2/MethOpt lab 2/GradientDescent_method.h"
#include "../../MethOpt lab 2/MethOpt lab 2/Parser.h"
#include "../../MethOpt lab 2/MethOpt lab 2/Compute_gradient.h"

double eps = 1e-7;

double norm(const std::vector<double>& grad) {
	double res = 0;
	for (double i : grad)
		res += i * i;
	res = sqrt(res);
	return res;
}

std::vector<double> matrix_sum(std::vector<double> x1, std::vector<double> x2) {
	std::vector<double> res;
	res.reserve(x1.size());
	for (int i = 0; i < x1.size(); i++) {
		res.push_back(x1[i] + x2[i]);
	}
	return res;
}

std::map<std::string, long double> matrix_sum(const std::map<std::string, long double>& x1, std::vector<long double> x2) {
	std::map<std::string, long double> res;
	int i = 0;
	for (const auto& s : x1) {
		res[s.first] = s.second + x2[i];
		i++;
	}
	return res;
}

std::vector<double> matrix_sub(std::vector<double> x1, std::vector<double> x2) {
	std::vector<double> res;
	res.reserve(x1.size());
	for (int i = 0; i < x1.size(); i++) {
		res.push_back(x1[i] - x2[i]);
	}
	return res;
}

long double compute_function(std::string function, std::map<std::string, long double> x) {
	std::string cur;
	std::vector<char> signs;
	signs.push_back('+');
	std::vector<std::string> split;
	std::string ch;
	for (int i = 0; i < function.size(); i++) {
		if (function[i] == ' ') {
			continue;
		}
		if (function[i] == '+' || function[i] == '-') {
			signs.push_back(function[i]);
			if (ch == " ") {
				cur.pop_back();
			}
			split.push_back(cur);
			cur = "";
			continue;
		}
		cur += function[i];
		ch = function[i];

		if (i == function.size() - 1) {
			split.push_back(cur);
			cur = "";
			ch = "";
		}
	}

	double res = 0;
	int sn = 0;
	for (std::string s : split) {
		if (s.empty())
			res--;
		long double temp_res = get_number(s, 1).first;
		for (int i = 0; i < s.size(); i++) {
			std::string var;
			if (s[0] < '0' || s[0] > '9') {
				while (s[i] != 42 && i < s.size()) {
					var += s[i];
					i++;
				}
				temp_res *= x[var];
				var = "";
				ch = "";
			}
			if (ch == "*") {
				while (s[i] != 42 && i < s.size()) {
					var += s[i];
					i++;
				}
				temp_res *= x[var];
				var = "";
			}
			ch = s[i];
		}
		if (signs[sn] == '+') {
			res += temp_res;
		}
		else {
			res -= temp_res;
		}
		sn++;
	}
	return res;
}
long double compute_function(std::string function, std::map<std::string, long double> x) {
	std::string cur;
	std::vector<char> signs;
	signs.push_back('+');
	std::vector<std::string> split;
	std::string ch;
	for (int i = 0; i < function.size(); i++) {
		if (function[i] == ' ') {
			continue;
		}
		if (function[i] == '+' || function[i] == '-') {
			signs.push_back(function[i]);
			if (ch == " ") {
				cur.pop_back();
			}
			split.push_back(cur);
			cur = "";
			continue;
		}
		cur += function[i];
		ch = function[i];

		if (i == function.size() - 1) {
			split.push_back(cur);
			cur = "";
			ch = "";
		}
	}

	double res = 0;
	int sn = 0;
	for (std::string s : split) {
		if (s.empty())
			res--;
		long double temp_res = get_number(s, 1).first;
		for (int i = 0; i < s.size(); i++) {
			std::string var;
			if (s[0] < '0' || s[0] > '9') {
				while (s[i] != 42 && i < s.size()) {
					var += s[i];
					i++;
				}
				temp_res *= x[var];
				var = "";
				ch = "";
			}
			if (ch == "*") {
				while (s[i] != 42 && i < s.size()) {
					var += s[i];
					i++;
				}
				temp_res *= x[var];
				var = "";
			}
			ch = s[i];
		}
		if (signs[sn] == '+') {
			res += temp_res;
		}
		else {
			res -= temp_res;
		}
		sn++;
	}
	return res;
}


std::vector<long> matrix_multiply(std::vector<std::vector<long long>> A, std::vector<long long> p) {
	std::vector<long> res;
	for (auto& i : A) {
		double sum = 0;
		for (int j = 0; j < i.size(); j++) {
			sum += i[j] * p[j];
		}
		res.push_back(sum);
	}
	return res;
}

struct Newtone_methods {
	double Newtone()(std::string funct, double a, double b) {
		std::map<std::string, double> x0;
		x0["x"] = 0;
		x0["y"] = 0;
		std::map<std::string, double> curX = x0;
		double diff = 1000;
		int iteration = 0;
		while (diff > eps) {
			iteration++;
			std::map<std::string, double> prevX = curX;
			//результат градиентного метода
			GradientDescent_method gdm;
			std::vector<double> p = gdm(gessian(function), multiply(compute_gradient(Parser(function), prevX), -1), epsilon);
			curX = matrix_sum(prevX, p);
			diff = norm(matrix_sub(curX, prevX));
		}

		return compute_function(function, curX);
	};

	double Linear_Newtone() {
		std::map<std::string, double> x0;
		x0["x"] = 0;
		x0["y"] = 0;
		std::map<std::string, double> prevX = x0;
		std::vector<double> p = gdm(gessian(function), matrix_multiply(compute_gradient(Parser(function), prevX), -1), epsilon);

		std::vector<double> curX = matrix_sum(prevX, p);
		double diff = norm(matrix_sub(curX, prevX));
		while (diff > eps&& norm(p) > eps) {
			prevX = curX;
			std::vector<double> p = gdm(gessian(function), matrix_multiply(compute_gradient(Parser(function), prevX), -1), epsilon);//результат градиентного метода

			std::vector<double> fPrevX = prevX;
			std::vector<double> fP = p;

			double a = 1;
			a = matrix_sum(finalPrevX, matrix_multiply(finalP, a));
			a = BrentSearch(function, a, -111, 111, eps);

			curX = matrix_sum(prevX, matrix_multiply(p, a));
			diff = norm(matrix_sub(curX, prevX))
		}

		return curX;
	}

	double DecentDirection_Newtone() {
		std::vector<double> d0 = matrix_multiply(compute_gradient(Parser(function), x0), -1);
		double a0 = 1;
		a0 = matrix_sum(x0, multiply(d0, a0))
			a0 = BrentSearch(function, a, -111, 111, epsilon);
		std::vector<double> nextX = matrix_sum(x0, matrix_multiply(d0, alpha0));
		double diff = norm(matrix_sub(nextX, x0));

		while (diff > epsilon) {
			std::vector<double> prevX = nextX;
			std::vector<double> grad = compute_gradient(Parser(function), prevX);
			std::vector<double> antiGrad = matrix_multiply(grad, -1);
			std::vector<double> p = gdm(gessian(prevX), antiGrad, epsilon);

			std::vector<double> direction(0);
			double result = 0;
			for (int i = 0; i < p.size(); i++) {
				result += p[i] * gradient[i];
			}
			if (result >= 0)
				direction = antiGrad;
			else
				direction = p;

			double a = 1;
			a = matrix_sum(prevX, matrix_multiply(direction, a));
			a = BrentSearch(function, a, -111, 111, epsilon);
			nextX = matrix_sum(prevX, matrix_multiply(direction, a));

			diff = norm(matrix_sub(nextX, prevX));
		}

		return nextX;
	}
}
