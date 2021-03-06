#pragma once

#include <iostream>
#include <map>
#include "Compute_gradient.h"
#include "Parser.h"
#include "Output.h"
#include <vector>

struct ConjugateGradient_method {
    //Если функция задается строкой, переменные x1,x2...
    long double operator()(const std::string &function, long double eps, std::map<std::string, long double> &x) {
        std::vector<long double> grad = compute_gradient(Parser(function), x);
        std::vector<std::vector<long double>> A = get_A(function, x);
        std::vector<long double> p = negate(grad);
        int iter = 0;
        while (norm(grad) > eps) {
            std::vector<long double> Ap = matrix_multiply(A, p);
            long double alpha = (norm(grad) * norm(grad)) / (scalar_multiply(Ap, p));
            x = matrix_sum(x, const_multiply(alpha, p));
            std::vector<long double> newgrad = matrix_sum(grad, const_multiply(alpha, Ap));
            long double beta = (norm(newgrad) * norm(newgrad)) / (norm(grad) * norm(grad));
            p = matrix_sum(const_multiply(beta, p), negate(newgrad));
            grad = newgrad;
            iter++;
        }
        std::cout << iter << "\n";
        return compute_function(function, x);
    }

    //Если функция имеет вид f(x) = 1/2Ax и задается матрицей A, где A[i][j] = 0, переменные x1,x2...
    long double
    operator()(const std::vector<std::vector<long double>> &A, long double eps, std::map<std::string, long double> &x) {
        std::vector<long double> grad = make_grad(x, A);
        std::vector<long double> p = negate(grad);
        int iter = 0;
        while (norm(grad) > eps) {
            std::vector<long double> Ap = matrix_multiply(A, p);
            long double alpha = (norm(grad) * norm(grad)) / (scalar_multiply(Ap, p));
            x = matrix_sum(x, const_multiply(alpha, p));
            std::vector<long double> newgrad = matrix_sum(grad, const_multiply(alpha, Ap));
            long double beta = (norm(newgrad) * norm(newgrad)) / (norm(grad) * norm(grad));
            p = matrix_sum(const_multiply(beta, p), negate(newgrad));
            grad = newgrad;
            iter++;
        }
        std::cout << iter << "\n";
        return compute(x, A);
    }

};