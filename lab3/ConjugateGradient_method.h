#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "tests.h"

std::vector<long double> di;
std::vector<long double> al;
std::vector<long double> au;
std::vector<long long> ja;
std::vector<long long> ia;
std::vector<long double> f;
std::vector<long double> x;
long double eps = 1e-10;

struct Comp {
	bool operator()(std::pair<long double, int> a, std::pair<long double, int> b) {
		return a.second < b.second;
	}
};

void sparse(std::ifstream& input_file, long long n) {
	di.clear();
	ia.clear();
	al.clear();
	au.clear();

	ia.push_back(1);
	std::vector <std::pair<long double, long long>> au_temp;
	std::vector<long long> helper(n);

	for (long long i = 0; i < n; i++) {
		bool flagl = false;
		long long l = 0;
		for (long long j = 0; j < n; j++) {
			long double elem;
			input_file >> elem;
			if (i == j) {
				di.push_back(elem);
			}
			else if (i > j) {
				if (elem != 0)
					flagl = true;
				if (flagl) {
					if (elem != 0) {
						l++;
						al.push_back(elem);
						ja.push_back(j + 1);
					}
				}
			}
			else {
				if (elem != 0) {
					helper[j] = helper[j] != 0 ? helper[j] : i + 1;
				}
			}
		}
		ia.push_back(ia[ia.size() - 1] + l);
	}
	input_file.close();

	input_file.open(test_directory + test_matrix);
	for (long long i = 0; i < n; i++) {
		for (long long j = 0; j < n; ++j) {
			long double elem;
			input_file >> elem;
			if (j > i) {
				if (helper[j] <= i + 1 && helper[j] != 0) {
						au_temp.emplace_back(elem, j);
				}
			}
		}
	}

	input_file.close();
	std::stable_sort(au_temp.begin(), au_temp.end(), Comp());

	for (std::pair<long double, long long> u : au_temp) {
		if(u.first != 0)
			au.push_back(u.first);
	}
}

long double get_element(long long i, long long j) {
	if (i == j) {
		return di[i - 1];
	}
	else if (i > j) {
		long long cnt = ia[i] - ia[i - 1];
		long long l = 0;
		long long a = 0;
		for (long long k = ia[i - 1] - 1; a <= cnt; k++) {
			l++;
			a++;
			
			if (l == cnt || ja[k] == j) {
				break;
			}
		}
		if (l >= cnt) {
			return 0;
		}
		else {
			return al[ia[i - 1] - 1 + l];
		}
	}
	else {
		long long cnt = ia[j] - ia[j - 1];
		long long l = 0;
		long long a = 0;
		for (long long k = ia[j - 1] - 1; a <= cnt; k++) {
			l++;
			a++;
			if (l == cnt || ja[k] == i) {
				break;
			}
		}

		if (l >= cnt) {
			return 0;
		}
		else {
			return au[ia[j - 1] - 1 + l];
		}

	}
}

long double norm(std::vector<long double> x) {
	long double res = 0;
	for (long double i : x) {
		res += i * i;
	}
	res = sqrt(res);
	return res;
}

std::vector<long double> matrix_multiply(std::vector<long double> x) {
	std::vector<long double> res;
	for (long long i = 1; i <= di.size(); i++) {
		long double sum = 0;
		for (long long j = 1; j <= di.size(); j++) {
			sum += get_element(i, j) * x[j - 1];
		}
		res.push_back(sum);
	}
	return res;
}

std::vector<long double> matrix_sum(std::vector<long double> f1, std::vector<long double> f2) {
	std::vector<long double> res;
	for (long long i = 1; i <= di.size(); i++) {
		res.push_back(f1[i - 1] + f2[i - 1]);
	}
	return res;
}

std::vector<long double> matrix_sub(std::vector<long double> f1, std::vector<long double> f2) {
	std::vector<long double> res;
	for (long long i = 1; i <= di.size(); i++) {
		res.push_back(f1[i - 1] - f2[i - 1]);
	}
	return res;
}

long double scalar_multiply(std::vector<long double> x1, std::vector<long double> x2) {
	long double sum = 0;
	for (long long i = 1; i <= di.size(); i++) {
		sum += x1[i - 1] * x2[i - 1];
	}
	return sum;
}

std::vector<long double> const_multiply(long double c, std::vector<long double> x) {
	std::vector<long double> res;
	for (long long i = 1; i <= di.size(); i++) {
		res.push_back(c * x[i - 1]);
	}
	return res;
}

void ConjugateGradient_method() {

	std::vector<long double> curX;
	for (long long i = 1; i <= di.size(); i++) {
		curX.push_back(0);
	}
	std::vector<long double> newX = curX;

	std::vector<long double> curR;
	curR = matrix_sub(f, matrix_multiply(curX));
	std::vector<long double> newR = curR;

	std::vector<long double> curZ = curR;
	std::vector<long double> newZ = curZ;

	long long maxK = 10000;
	long double a;
	long double b;
	
	for (long long i = 0; i < maxK; i++) {
		a = scalar_multiply(curR, curR) / scalar_multiply(matrix_multiply(curZ), curZ);
		newX = matrix_sum(curX, const_multiply(a, curZ));
		newR = matrix_sub(curR, const_multiply(a, matrix_multiply(curZ)));
		b = scalar_multiply(newR, newR) / scalar_multiply(curR, curR);
		newZ = matrix_sum(curR, const_multiply(b, curZ));
		curX = newX;
		curZ = newZ;
		curR = newR;
		if ((norm(newR) / norm(f)) < eps) {
			break;
		}
	}

	x = newX;
	x = newX;

}