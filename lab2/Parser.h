#pragma once
#include <vector>
#include <set>
#include <string>
#include <map>

#include "get_Number.h"

std::vector<std::vector<double>> A;
std::vector<double> b;

void compute_matrix(std::string function) {
	std::string cur;
	std::vector<std::string> split;
	std::vector<char> signs;
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
}

std::vector<std::string> split(std::vector<char>& signs, const std::string function) {
	std::string ch = "";
	std::string cur;
	std::vector<std::string> spl;
	for (int i = 0; i < function.size(); i++) {
		if (function[i] == 32 && function[i + 1] != 32) {
			continue;
		}
		if (function[i] == '+' || function[i] == '-') {
			signs.push_back(function[i]);
			if (ch == " ") {
				cur.pop_back();
			}
			spl.push_back(cur);
			cur = "";
			continue;
		}
		cur += function[i];
		ch = function[i];

		if (i == function.size() - 1) {
			spl.push_back(cur);
			cur = "";
			ch = "";
		}
	}
	return spl;
}

void get_vars(std::string s, std::set<std::string>& vars) {
	std::string ch = "";
	std::string var = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[0] < '0' || s[0] >'9') {
			while (s[i] != 42 && i < s.size()) {
				var += s[i];
				i++;
			}
			vars.insert(var);
			var = "";
			ch = "";
		}
		if (ch == "*") {
			while (s[i] != 42 && i < s.size()) {
				var += s[i];
				i++;
			}
			vars.insert(var);
			var = "";
			ch = "";
		}

		ch = s[i];
	}
}

std::vector<std::string> Parser(std::string function) {
	std::vector<char> signs;

	std::vector<std::string> spl = split(signs, function);
	std::string ch = "";
	std::set<std::string> vars;
	for (std::string s : spl) {
		get_vars(s, vars);
	}

	std::vector<std::string> variables;
	for (std::string s : vars) {
		variables.push_back(s);
	}

	std::vector<std::string> grad;
	for (int i = 0; i < variables.size(); i++) {
		std::vector<std::string> parts_grad_part;
		std::string grad_part = "";
		std::string var = variables[i];
		for (std::string s : spl) {
			std::vector<int> variables_cnt(variables.size());
			std::string cur = "";
			std::string darivative = "";
			bool flag = false;
			for (int j = 0; j < s.size(); j++) {
					while (s[j] != 42 && j < s.size()) {
						cur += s[j];
						j++;
					}
					if (cur == var) {
						variables_cnt[i]++;
						if (!flag) {
							int l = j;
							j = (j >= var.size() + 1) ? j - var.size() - 1 : 0;
							std::string left = s.substr(0, j);
							std::string right = (j + var.size() + 1 > s.size()) ? s.substr(j + var.size()) : s.substr(j + var.size() + 1);
							darivative += left;
							darivative += right;
							flag = true;
							j = (l >= var.size() + 1) ? j + var.size() + 1 : j + l;
						}
					}
					cur = "";
			}

			std::pair<double, int> n = get_number(s, variables_cnt[i]);
			std::pair<std::string, int> num;
			num.first = toString(n.first);
			num.second = n.second;
			std::string r = (darivative != "") ? darivative.substr(num.second) : "";
			std::string gr = num.first + ((num.second == 0) ? "*" : "") + r;
			if (gr[gr.size() - 1] == '*')
				gr.pop_back();
			parts_grad_part.push_back(gr);
		}
		int sn = 0;
		for (std::string gr : parts_grad_part) {
			if (gr == "0") {
				sn++;
				continue;
			}
			grad_part += gr + ((sn != signs.size()) ? signs[sn] : '+');
			sn++;
		}
		grad_part.pop_back();
		grad.push_back(grad_part);
	}

	return grad;
}

std::vector<int> get_indexes(std::string part, std::map<std::string, double> x) {
	std::set<std::string> vars;
	get_vars(part, vars);
	std::vector<int> res;
	int i = 0;
	for (std::pair<std::string, double> p : x) {
		if (vars.find(p.first) != vars.end()) {
			res.push_back(i);
		}
		i++;
	}
	return res;
}

std::vector<std::vector<double>> get_A(std::string function, std::map<std::string, double> x) {
	std::vector<char> signs;
	std::vector<std::string> spl = split(signs, function);
	std::vector<std::vector<double>> A(x.size(), std::vector<double>(x.size()));
	
	for (std::string s : spl) {
		std::vector<int> indexes = get_indexes(s, x);
		if (indexes.size() == 1) {
			A[indexes[0]][indexes[0]] = get_number(s, 1).first;
		}
		else {
			A[indexes[0]][indexes[1]] = get_number(s, 2).first;
			A[indexes[1]][indexes[0]] = get_number(s, 2).first;
		}
		
	}
	return A;
}