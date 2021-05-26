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

std::vector<std::string> split_by_mul(std::string part) {
	std::string ch = "";
	std::string cur;
	std::vector<std::string> spl;
	for (int i = 0; i < part.size(); i++) {
		if (part[i] == 32 && part[i + 1] != 32) {
			continue;
		}
		if (part[i] == '*') {
			if (ch == " ") {
				cur.pop_back();
			}
			spl.push_back(cur);
			cur = "";
			continue;
		}
		cur += part[i];
		ch = part[i];

		if (i == part.size() - 1) {
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
	//std::vector<std::string> spl = split_by_mul(part);

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
			A[indexes[0]][indexes[0]] = get_number(s, 2).first;
		}
		else {
			A[indexes[0]][indexes[1]] = get_number(s, 1).first;
			A[indexes[1]][indexes[0]] = get_number(s, 1).first;
		}
		
	}
	return A;
}

std::string bringing_similar(std::string function, std::map<std::string, double> x) {
	std::string res = "";

	std::map<std::string, int> x_to_num;
	std::map<int, std::string> num_to_x;
	int i = 0;
	for (std::pair<std::string, double> p : x) {
		x_to_num[p.first] = i;
		num_to_x[i] = p.first;
		i++;
	}
	std::vector<std::vector<double>> _A(x.size(), std::vector<double>(x.size()));
	std::vector<double> _B(x.size());
	double _C = 0;

	std::vector<char> signs;
	std::vector<std::string> spl = split(signs, function);
	for (std::string s : spl) {
		std::vector<std::string> spl1 = split_by_mul(s);
		if (spl1.size() == 3) {
			if (spl1[1] > spl1[2]) {
				std::swap(spl1[1], spl1[2]);
			}
			_A[x_to_num[spl1[1]]][x_to_num[spl1[2]]] += get_number(spl1[0], 1).first;
		}
		else if (spl1.size() == 1) {
			_B[x_to_num[spl1[1]]] += get_number(spl1[0], 1).first;
		}
		else {
			_C += get_number(spl1[0], 1).first;
		}
	}

	for (int i = 0; i < x.size(); i++) {
		for (int j = i; j < x.size(); j++) {
			res += (_A[i][j] != 0) ? ((_A[i][j] != 1) ? toString(_A[i][j] / 2) + "*" : "") + num_to_x[i] + "*" + num_to_x[j] + "+" : "";
		}
	}

	for (int i = 0; i < x.size(); i++) {
		res += (_B[i] != 0) ? ((_B[i] != 1) ? toString(_B[i]) + "*" : "") + num_to_x[i] + "+" : "";
	}

	if (_C != 0) {
		res += toString(_C);
	}
	else {
		res.erase(res.size() - 1);
	}

	return res;

}

std::string return_function(std::vector<std::vector<double>> A, std::vector<double> B, double C, std::map<std::string, double> x) {
	std::string res = "";
	
	int i = 0;
	int j = 0;
	for (std::pair<std::string, double> p1 : x) {
		for (std::pair<std::string, double> p2 : x) {
			res += (A[i][j] != 0) ? ((A[i][j] / 2 != 1) ? toString(A[i][j] / 2) + "*" : "") + p1.first + "*" + p2.first + "+" : "";
			j++;
		}
		j = 0;
		i++;
	}

	i = 0;
	for (std::pair<std::string, double> p : x) {
		res += (B[i] != 0) ? ((B[i] != 1) ? toString(B[i]) + "*" : "") + p.first + "+" : "";
	}

	if (C != 0) {
		res += toString(C);
	}
	else {
		res.erase(res.size() - 1);
	}

	return bringing_similar(res, x);
}