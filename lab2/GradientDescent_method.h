#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Compute_gradient.h"
#include "Parser.h"

struct GradientDescent_method {

    //Если функция задается строкой, переменные x1,x2...
    long double operator()(std::string & function, long double eps, std::map<std::string, long double> &x) {
        double alpha = 10;
        std::map<std::string, long double> newx;
        int it = 0;
        auto f = compute_function(function, x);
        while (true) {
            std::vector<long double> gradient = compute_gradient(Parser(function), x);
            long double len = norm(gradient);
            if (len < eps) {
                break;
            }
            while (true) {
                for (const auto &p : x) {
                    int i = std::atoi(p.first.substr(1).c_str()) - 1;
                    newx[p.first] = x[p.first] - alpha * gradient[i];
                }
                long double f2 = compute_function(function, newx);
                if (f2 <= f) {
                    f = f2;
                    break;
                }
                alpha /= 2;
            }
            x = newx;
            alpha = 10;
            it++;
        }
        std::cout << it << "\n";
        return f;
    }
    //Если функция имеет вид f(x) = 1/2Ax и задается матрицей A, где A[i][j] = 0, переменные x1,x2...
    long double operator()(std::vector<std::vector<long double>>& A, long double eps, std::map<std::string, long double> &x) {
        double alpha = 10;
        std::map<std::string, long double> newx;
        int it = 0;
        auto f = compute(x,A);
        while (true) {
            std::vector<long double> gradient = make_grad(x,A);
            long double len = norm(gradient);
            if (len < eps) {
                break;
            }
            while (true) {
                for (const auto &p : x) {
                    int i = std::atoi(p.first.substr(1).c_str()) - 1;
                    newx[p.first] = x[p.first] - alpha * gradient[i];
                }
                long double f2 = compute(newx, A);
                if (f2 <= f) {
                    f = f2;
                    break;
                }
                alpha /= 2;
            }
            x = newx;
            alpha = 10;
            it++;
        }
        std::cout << it << "\n";
        return compute(x,A);
    }
};
