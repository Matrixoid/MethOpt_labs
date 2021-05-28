#pragma once
#include <vector>
#include <iostream>
#include <map>


void output(const std::vector<std::vector<double>>& A) {
	for (auto & i : A) {
		for (double j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}

void output(const std::vector<double>& p) {
	for (double i : p) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void output(const std::map<std::string, double>& x) {
	for (const auto& p : x) {
		std::cout << "{ " << p.first << ", " << p.second << " }";
	}
	std::cout << std::endl;
}

void output(double a) {
	std::cout << a << std::endl;
}