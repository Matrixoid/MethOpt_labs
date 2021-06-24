#pragma once

#include "Compute_gradient.h"
#include "Parser.h"
#include <iostream>
#include <vector>
#include <map>

template<typename Minimum>
struct SteepestDescent_method {

    //Если функция задается строкой, переменные x1,x2...
    long double operator()(const std::string &func, long double eps, std::map<std::string, long double> &x) {
        double eps1 = 1e-9;
        std::map<std::string, long double> x1;
        int iter = 0;
        long double alpha;
        long double res;
        res = compute_function(func, x);
        std::vector<long double> grad;
        while (true) {
            grad = compute_gradient(Parser(func), x);
            if (norm(grad) <= eps) {
                break;
            }
            std::map<std::string, std::string> nx = newx(grad, func, x);
            std::map<std::string, long double> alp;
            alp["x"] = 1;
            std::string fi = bringing_similar(substitute(func, nx), alp);
            alpha = 0;
            auto res1 = Minimum()(fi, eps1, INT32_MAX, eps1, alpha);
            alp["x"] = alpha;
            if (std::abs(res - res1) < eps1) {
                x = compute_x(nx, alp);
                break;
            }
            iter++;
            x = compute_x(nx, alp);
            res = res1;
        }
        std::cout << iter << "\n";
        return res;
    }

    //Если функция имеет вид f(x) = 1/2Ax и задается матрицей A, где A[i][j] = 0, переменные x1,x2...
    long double operator()(std::vector<std::vector<long double>> &A, const std::string &func, long double eps,
                           std::map<std::string, long double> &x) {
        double eps1 = 1e-9;
        std::map<std::string, long double> x1;
        int iter = 0;
        long double alpha;
        long double res;
        res = compute(x, A);
        std::vector<long double> grad;
        while (true) {
            grad = make_grad(x, A);
            if (norm(grad) <= eps) {
                break;
            }
            std::map<std::string, std::string> nx = newx(grad, func, x);
            std::map<std::string, long double> alp;
            alp["x"] = 1;
            std::string fi = bringing_similar(substitute(func, nx), alp);
            alpha = 0;
            auto res1 = Minimum()(fi, eps1, INT32_MAX, eps1, alpha);
            alp["x"] = alpha;
            if (std::abs(res - res1) < eps1) {
                x = compute_x(nx, alp);
                break;
            }
            iter++;
            x = compute_x(nx, alp);
            res = res1;
        }
        std::cout << iter << "\n";
        return res;
    }

private:
    std::map<std::string, std::string>
    newx(std::vector<long double> grad, const std::string &function, std::map<std::string, long double> x) {
        std::map<std::string, std::string> nx;
        for (auto &s : x) {
            std::string r = toString(s.second);
            int i = std::atoi(s.first.substr(1).c_str()) - 1;
            long double gr = grad[i];
            if (gr > 0) {
                r += "-";
            } else {
                gr *= -1;
                r += "+";
            }
            r += toString(gr) + "*" + "x";
            nx[s.first] = r;
        }
        return nx;
    }

    std::map<std::string, long double>
    compute_x(const std::map<std::string, std::string> &x, std::map<std::string, long double> alpha) {
        std::map<std::string, long double> res;
        for (auto &s : x) {
            res[s.first] = compute_function(s.second, alpha);
        }
        return res;
    }
};
