#pragma once
#include <vector>
#include <map>
#include <string>
#include "../../MethOpt lab 2/MethOpt lab 2/get_Number.h"

std::vector<std::vector<long double>> return_identity_matrix(long long size) {
	std::vector<std::vector<long double>> I(size, std::vector<long double>(size));
	for (long long i = 0; i < size; i++)
		I[i][i] = 1;
	return I;
}

std::map < std::string, long double> initial_approximation(long long size, std::initializer_list<long double> list) {
	std::map<std::string, long double> res;
	std::initializer_list<long double>::iterator it = list.begin();
	for (int i = 1; i <= size; i++) {
		std::string var = "x" + toString(i);
		res[var] = *it;
		it++;
	}
	return res;
}

std::map<std::string, std::string> newx(std::vector<long double> p, std::map<std::string, long double> x) {
	std::map<std::string, std::string> nx;
	for (auto& s : x) {
		std::string r = toString(s.second);
		int i = std::atoi(s.first.substr(1).c_str()) - 1;
		long double gr = p[i];
		if (gr > 0) {
			r += "+";
		}
		else {
			gr *= -1;
			r += "-";
		}
		r += toString(gr) + "*" + "x";
		nx[s.first] = r;
	}
	return nx;
}

std::map<std::string, long double> matrix_sub(std::map<std::string, long double> x1, std::map<std::string, long  double> x2) {
	std::map<std::string, long double> res;
	auto it1 = x1.begin();
	auto it2 = x2.begin();
	for (int i = 0; i < x1.size(); i++) {
		res[(*it1).first] = (*it1).second - (*it2).second;
		it1++;
		it2++;
	}
	return res;
}

std::map<std::string, long double> matrix_sub(std::map<std::string, long double> x1, std::vector<long  double> x2) {
	std::map<std::string, long double> res;
	auto it1 = x1.begin();
	for (int i = 0; i < x1.size(); i++) {
		res[(*it1).first] = (*it1).second - x2[i];
		it1++;
	}
	return res;
}

std::vector<long double> matrix_div(std::vector<long double> p, long double k) {
	std::vector<long double> res;
	for (int i = 0; i < p.size(); i++) {
		res.push_back(p[i] / k);
	}
	return res;
}

std::vector<std::vector<long double>> matrix_div(std::vector<std::vector<long double>> G, long double k) {
	std::vector<std::vector<long double>> res = G;
	for (int i = 0; i < G.size(); i++) {
		for (int j = 0; j < G[i].size(); j++) {
			res[i][j] /= k;
		}
	}
	return res;
}

std::vector<long double> return_vector(std::map<std::string, long double> x) {
	std::vector<long double> res;
	for (auto a : x) {
		res.push_back(a.second);
	}
	return res;
}

std::vector<std::vector<long double>> matrix_transpode_multiply(std::vector<long double> x) {
	std::vector<std::vector<long double>> res(x.size(), std::vector<long double>(x.size()));
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x.size(); j++) {
			res[i][j] = x[i] * x[j];
		}
	}
	return res;
}

std::vector<std::vector<long double>> const_multiply(long double k, std::vector<std::vector<long double>> G) {
	std::vector<std::vector<long double>> res = G;
	for (int i = 0; i < G.size(); i++) {
		for (int j = 0; j < G[i].size(); j++) {
			res[i][j] *= k;
		}
	}
	return res;
}

std::vector<std::vector<long double>> matrix_sub(std::vector<std::vector<long double>> A, std::vector<std::vector<long double>> B) {
	std::vector<std::vector<long double>> res = A;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			res[i][j] -= B[i][j];
		}
	}
	return res;
}

std::vector<std::vector<long double>> matrix_sum(std::vector<std::vector<long double>> A, std::vector<std::vector<long double>> B) {
	std::vector<std::vector<long double>> res = A;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			res[i][j] += B[i][j];
		}
	}
	return res;
}