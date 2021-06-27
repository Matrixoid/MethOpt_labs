#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "LU_method.h"
#include "Gauss_method.h"

int main()
{
	std::ifstream File;
	File.open("test2\\input.txt");

	std::ifstream ms;
	ms.open("test2\\matrix_size.txt");

	long long n;
	ms >> n;

	profile(File, n);

	File.open("test2\\b.txt");
	for (long long i = 0; i < n; i++) {
		long double b_i;
		File >> b_i;
		b.push_back(b_i);
	}
	File.close();

	for (double d : di) {
		std::cout << d << " ";
	}
	std::cout << std::endl;

	for (int i : ia) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for (double l : al) {
		std::cout << l << " ";
	}
	std::cout << std::endl;
	
	for (double u : au) {
		std::cout << u << " ";
	}
	std::cout << std::endl << std::endl;

	std::vector<long double> ans1 = LU_method();
	std::vector<long double> ans2 = Gauss();

	std::ofstream Fans1;
	Fans1.open("test2\\LU_x.txt");
	std::ofstream Fans2;
	Fans2.open("test2\\Gauss_x.txt");

	output_x(Fans1, ans1);
	output_x(Fans2, ans2);
}
