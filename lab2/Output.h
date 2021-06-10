#pragma once
#include <vector>
#include <iostream>
#include <map>


void output(std::vector<std::vector<long double>>& A) {
	for (auto & i : A) {
		for (double j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}

void output(const std::vector<long double>& p) {
	for (double i : p) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void output(const std::map<std::string,long double>& x) {
	for (const auto& p : x) {
		std::cout << "{ " << p.first << ", " << p.second << " } ";
	}
	std::cout << std::endl;
}
void output(const std::map<std::string,std::string>& x) {
    for (const auto& p : x) {
        std::cout << "{ " << p.first << ", " << p.second << " } ";
    }
    std::cout << std::endl;
}

void output(double a) {
	std::cout << a << std::endl;
}

void output(const std::vector<std::pair<char, std::string>>& p) {
	for (const std::pair<char, std::string>& l : p) {
		std::cout << "{ " << l.first << ", " << l.second << " } ";
	}
	std::cout << std::endl;
}

void output(const std::vector<char>& signs) {
	for (int i = 0; i < signs.size(); i++) {
		std::cout << (char)signs[i] << " ";
	}
	std::cout << std::endl;
}

void output(std::vector<std::string> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << "\n";
	}
	std::cout << std::endl;
}