#pragma once

#include "matrix_generator_1.h"

//NOTE: запуск генератора  make_Gilbert_matrix(n, "GilbertTests/test_for_n");,
// где n - размерность матрицы, директория должна быть создана ранее
void make_Gilbert_matrix(int n, const std::string &dir) {
    std::vector<std::vector<long double>> A;
    A.reserve(n);
    for (int i = 0; i < n; ++i) {
        A.emplace_back(n);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            A[i - 1][j - 1] = 1 / (long double) (i + j - 1);
        }
    }
    std::vector<long double> x_(n);
    for (int i = 0; i < n; ++i) {
        x_[i] = i + 1;
    }
    std::ofstream out_file(dir + "/matrix");
    out_file << n << std::endl;
    std::vector<long double> f = A * x_;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out_file << A[i][j] << " ";
        }
        out_file  << std::endl;
    }
    std::ofstream f_file(dir + "/f");
    for (int i = 0; i < n; ++i) {
        f_file << f[i] << std::endl;
    }
    f_file.close();
    out_file.close();
}