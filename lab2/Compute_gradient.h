#pragma once
#include <vector>
#include <map>
#include <string>

#include "get_Number.h"

double compute_function(std::string function, std::map<std::string, double> x) {
	std::string cur;
	std::vector<std::string> split;
	std::string ch = "";
	for (int i = 0; i < function.size(); i++) {
		if (function[i] == 32 && function[i + 1] != 32) {
			continue;
		}
		if (function[i] == '+') {
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
	for (std::string s : split) {
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
		res += temp_res;
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