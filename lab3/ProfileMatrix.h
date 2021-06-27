#pragma once
#include <vector>
#include <fstream>
#include "tests.h";

std::vector<long double> di;
std::vector<long long> ia;
std::vector<long double> al;
std::vector<long double> au;
std::vector<long double> b;
std::vector<long double> x;

double long eps = 1e-10;

struct Comp {
	bool operator()(std::pair<long double, int> a, std::pair<long double, int> b) {
		return a.second < b.second;
	}
};

void profile(std::ifstream& input_file, long long n) {
	
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
					l++;
					al.push_back(elem);
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
		au.push_back(u.first);
	}
}