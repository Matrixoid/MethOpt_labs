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