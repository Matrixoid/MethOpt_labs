#pragma once
#include <vector>
#include <iostream>
#include <map>


void output(std::vector<std::vector<double>> A) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void output(std::vector<double> p) {

	for (int i = 0; i < p.size(); i++) {
		std::cout << p[i] << " ";
	}
	std::cout << std::endl;
}

void output(std::map<std::string, double> x) {
	for (std::pair<std::string, double> p : x) {
		std::cout << "{ " << p.first << ", " << p.second << " }";
	}
	std::cout << std::endl;
}

void output(double a) {
	std::cout << a << std::endl;
}