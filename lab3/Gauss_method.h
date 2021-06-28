#pragma once
#include "Util.h"

void multiply_string(long long i, long double m) {
	for (long long j = 1; j <= di.size(); j++) {
		if (belongs_to_the_profile(i, j)) {
			set_element(i, j, get_element(i, j) * m);
		}
	}
	b[i - 1] *= m;
}

void subtract_strings(long long i, long long j) {
	for (long long k = 1; k <= di.size(); k++) {
		set_element(j, k, get_element(j, k) - get_element(i, k));
		/*if(get_element(j, k) - get_element(i, k) < eps)
			set_element(j, k, 0);*/
	}

	b[j - 1] -= b[i - 1];
}

void return_x(long long i) {
	long double sum = b[i - 1];
	long long x_it = x.size();
	for (long long j = di.size(); j >= di.size() - x.size(); j--) {
		sum -= (x_it > 0) ? (x[x_it - 1] * get_element(i, j)) : 0;
		x_it--;
	}
	sum /= get_element(i, di.size() - x.size());
	x.insert(x.begin(), sum);
}

long long number_of_nonzero_elements() {
	long long cnt = 0;
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = 1; j <= di.size(); j++) {
			if (get_element(i, j) == 0) {
				cnt++;
			}
		}
	}
	return cnt;
}

void dense_matrix_transforms() {

	std::string file_name = test_directory + "dense_matrix.txt";

	std::ofstream File;
	File.open(file_name);

	std::vector<long long> i_trans;
	for (long long i = 1; i <= di.size(); i++) {
		i_trans.push_back(i);
	}

	for (long long j = 1; j <= di.size(); j++) {
		long double max = -1000000000;
		long long max_i = 0;
		for (long long i = j; i <= di.size(); i++) {
			if (get_element(i_trans[i - 1], j) > max) {
				max = get_element(i, j);
				max_i = i;
			}
		}
		std::swap(i_trans[j - 1], i_trans[max_i - 1]);
		std::swap(b[j - 1], b[max_i - 1]);
	}

	for (long long i : i_trans) {
		for (long long j = 1; j <= di.size(); j++) {
			File << get_element(i, j) << " ";
		}
		File << std::endl;
	}

	std::ifstream F;
	F.open(file_name);
	profile(F, di.size());
}

std::vector<long double> Gauss() {
    x.clear();

	if (number_of_nonzero_elements() * 100 / (di.size() * di.size()) > 65L) {
		dense_matrix_transforms();
	}

	// Прямой ход
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = i + 1; j <= di.size(); j++) {
			if (belongs_to_the_profile(j, i) && get_element(j,i)!= 0) {
				multiply_string(j, get_element(i, i) / get_element(j, i));
				subtract_strings(i, j);
			}
		}
	}

	// Обратный ход
	for (int i = di.size(); i >= 1; i--) {
		return_x(i);
	}

	return x;
}