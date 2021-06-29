#pragma once

#include <filesystem>
#include <cmath>
#include <fstream>
#include <random>
std::vector<long double> operator*(const std::vector<std::vector<long double>> &a, const std::vector<long double> &b) {
    std::vector<long double> answer(a.size());
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            answer[i] += a[i][j] * b[j];
        }
    }
    return answer;

}



void make_matrix(int seed, bool inverse, int n, const std::string &dir) {
    std::vector <std::vector<long double>> A;
    A.reserve(n);
    for (int i = 0; i < n; ++i) {
        A.emplace_back(n);
    }
    long double sum = 0;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> range(n/2, n);
    std::vector<int> profile(n);
    for (int i = 0; i < n; ++i) {
        profile[i] = range(gen);
    }
    int inv = -1;
    if (!inverse){
        inv = 1;
    }
    std::uniform_int_distribution<int> n_range(1, 4);
    std::uniform_int_distribution<int> n1_range(0, 4);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((j > profile[i] && j < i) || (i > profile[j] && i < j)) {

                A[i][j] = n1_range(gen) *inv;
            }
            if (i == profile[j] || j == profile[i]) {
                A[i][j] = n_range(gen) * inv;
            }
            sum += A[i][j];

        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] == 0 != A[j][i] ==0){
                A[i][j] = -4;
                A[j][i] = -4;
            }
        }

    }

    for (int i = 0; i < n; ++i) {
        A[i][i] = -sum;
        if (i == 0) {
            A[i][i] += 1;
        }
    }
    std::ofstream out_file(dir + "/matrix");
    std::vector<long double> x_(n);
    for (int i = 0; i < n; ++i) {
        x_[i] = i + 1;
    }
    std::vector<long double> f = A * x_;
    out_file.precision(20);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out_file << A[i][j] << " ";
        }
        out_file << std::endl;
    }
    std::ofstream f_file(dir + "/f");
    f_file.precision(20);
    for (int i = 0; i < n; ++i) {
        f_file << f[i] << std::endl;
    }
    std::ofstream x_file(dir  + "/x");
    for (int i = 0; i < n; ++i) {
        x_file << i + 1 << std::endl;
    }
    std::ofstream size_file(dir +  "/size");
    size_file << n;
    x_file.close();
    f_file.close();
    out_file.close();
    size_file.close();

}
