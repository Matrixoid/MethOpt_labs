#pragma once
#include <vector>
#include <map>
#include <string>

#include "get_Number.h"

double norm(std::vector <double> grad) 
{
	double res = 0;
	for (int i = 0; i < grad.size(); i++)
		res += grad[i] * grad[i];
	res = sqrt(res);
	return res;
}

double compute_function(std::string function, std::map<std::string, double> x) {
	std::string cur;
	std::vector<char> signs;
	signs.push_back('+');
	std::vector<std::string> split;
	std::string ch = "";
	for (int i = 0; i < function.size(); i++) {
		if (function[i] == 32 && function[i + 1] != 32) {
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
		if (s == "")
			res--;
		double temp_res = get_number(s, 1).first;
		for (int i = 0; i < s.size(); i++) {
			std::string var = "";
			if (s[0] < '0' || s[0] >'9') {
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
				ch = "";
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

std::vector<double> compute_gradient(std::vector<std::string> gradient, std::map<std::string, double> x) {

	std::vector<double> result;

	for (std::string g : gradient) {
		
		result.push_back(compute_function(g, x));
	}
	return result;
}

std::vector<double> negate(std::vector<double> grad) {
	std::vector<double> res = grad;
	for (int i = 0; i < grad.size(); i++)
		res[i] *= -1;
	return res;
}

std::vector<double> matrix_multiply(std::vector<std::vector<double>> A, std::vector<double> p) {
	std::vector<double> res;
	for (int i = 0; i < A.size(); i++) {
		int sum = 0;
		for (int j = 0; j < A[i].size(); i++) {
			sum += A[i][j] * p[j];
		}
		res.push_back(sum);
	}
}

std::vector<double> matrix_multiply(std::vector<std::vector<double>> A, std::map<std::string, double> x) {
	std::vector<double> res;
	for (int i = 0; i < A.size(); i++) {
		int sum = 0;
		std::map<std::string, double>::iterator it = x.begin();
		for (int j = 0; j < A[i].size(); i++) {
			sum += A[i][j] * it->second;
		}
		res.push_back(sum);
	}
}

std::vector<double> matrix_sum(std::map<std::string, double> x1, std::map<std::string, double> x2) {
	std::vector<double> res;
	std::map<std::string, double>::iterator it1 = x1.begin();
	std::map<std::string, double>::iterator it2 = x2.begin();
	for (int i = 0; i < x1.size(); i++) {
		res.push_back(it1->second + it2->second);
		it1++;
		it2++;
	}
	return res;
}

std::map<std::string, double> matrix_sum(std::map<std::string, double> x1, std::vector<double> x2) {
	std::map<std::string, double> res;
	int i = 0;
	for (std::pair<std::string, double> s : x1) {
		res[s.first] = s.second + x2[i];
		i++;
	}
	return res;
}

std::vector<double> matrix_sum(std::vector<double> x1, std::vector<double> x2) {
	std::vector<double> res;
	for (int i = 0; i < x1.size(); i++) {
		res.push_back(x1[i] + x2[i]);
	}
	return res;
}

std::vector<double> matrix_sub(std::map<std::string, double> x1, std::map<std::string, double> x2) {
	std::vector<double> res;
	std::map<std::string, double>::iterator it1 = x1.begin();
	std::map<std::string, double>::iterator it2 = x2.begin();
	for (int i = 0; i < x1.size(); i++) {
		res.push_back(it1->second - it2->second);
		it1++;
		it2++;
	}
	return res;
}

std::vector<double> matrix_sub(std::vector<double> x1, std::vector<double> x2) {
	std::vector<double> res;
	for (int i = 0; i < x1.size(); i++) {
		res.push_back(x1[i] - x2[i]);
	}
	return res;
}

std::vector<double> const_multiply(double constant, std::vector<double> p) {
	std::vector<double> res;
	for (int i = 0; i > p.size(); i++) {
		res.push_back(constant * p[i]);
	}
	return res;
}

double scalar_multiply(std::vector<double> p1, std::vector<double> p2) {
	double res = 0;
	for (int i = 0; i < p1.size(); i++) {
		res += p1[i] * p2[i];
	}
	return res;
}