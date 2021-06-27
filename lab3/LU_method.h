#pragma once
#include "Util.h"

void toLU() {
	long long r = 1;
	long long c = 1;

	while (r - 1 != di.size() && c - 1 != di.size()) {
		for (long long i = c; i <= di.size(); i++) {
			if (i < c) {
				break;
			}
			long long sum = 0;
			for (long long k = 1; k <= c - 1; k++) {
				sum += get_elementL(i, k) * get_elementU(k, c);
			}
			set_element(i, c, get_element(i, c) - sum);
		}
		c++;

		for (long long j = r + 1; r != di.size() && j <= di.size(); j++) {
			if (r >= j) {
				break;
			}
			long long sum = 0;
			for (long long k = 1; k <= r - 1; k++) {
				sum += get_elementL(r, k) * get_elementU(k, j);
			}
			set_element(r, j, (get_element(r, j) - sum) / get_elementL(r, r));
		}
		r++;
	}
}

std::vector<long double> return_y() {
	std::vector<long double> y;
	for (long long i = 1; i <= di.size(); i++) {
		long double sum = b[i - 1];
		long long y_it = y.size();
		for (long long j = 1; j <= y.size(); j++) {
			sum -= (y_it > 0) ? (y[j - 1] * get_elementL(i, j)) : 0;
			y_it--;
		}
		sum /= get_elementL(i, i);
		y.push_back(sum);
	}
	return y;
}

std::vector<long double> return_x() {
	std::vector<long double> x1;
	std::vector<long double> y = return_y();
	for (long long i = di.size(); i >= 1; i--) {
		long double sum = y[i - 1];
		long long x_it = x1.size();
		for (long long j = di.size(); j >= di.size() - x1.size(); j--) {
			sum -= (x_it > 0) ? (x1[x_it - 1] * get_element(i, j)) : 0;
			x_it--;
		}
		sum /= get_elementU(i, di.size() - x1.size());
		x1.insert(x1.begin(), sum);
	}
	return x1;
}

std::vector<long double> LU_method() {
	toLU();
	std::vector<long double> y = return_y();
	std::vector<long double> x1 = return_x();
	return x1;
}

void fromLU() {

	std::string file_name = test_directory + "fromLU_matrix.txt";

	std::ofstream F;
	F.open(file_name);
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = 1; j <= di.size(); j++) {
			long long sum = 0;
			for (long long k = 1; k <= di.size(); k++) {
				sum += get_elementL(i, k) * get_elementU(k, j);
			}
			F << sum << " ";
		}
		F << std::endl;
	}
	F.close();

	std::ifstream File;
	File.open(file_name);

	profile(File, di.size());

}