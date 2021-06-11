#pragma once

#include "Compute_gradient.h"
#include "Parser.h"
#include <iostream>
#include <vector>
#include <map>

template<typename Minimum>
struct SteepestDescent_method {

    long double operator()(const std::string &func, long double eps) {
        std::map<std::string, long double> x;
        double eps1 = 1e-9;
        x["x"] = 0;
        x["y"] = 0;
        int iter = 0;
        long double alpha;
        while (true) {
            std::vector<long double> grad = compute_gradient(Parser(func), x);
            if (norm(grad) <= eps) {
                break;
            }
            std::map<std::string, std::string> nx = newx(func, x);
            std::string fi = bringing_similar(substitute(func, nx), x);
            alpha = Minimum()(fi, 0, INT32_MAX, eps1);
            std::map<std::string, long double> alp;
            alp["x"] = alpha;
            grad = const_divide(norm(grad), grad);
            x = matrix_sum(x, const_multiply(alpha,negate(grad)));
            iter++;
        }
        std::cout << iter << "\n";
        return compute_function(func, x);
    }

private:
    std::map<std::string, std::string> newx(const std::string& function, std::map<std::string, long double> x) {
        std::map<std::string, std::string> nx;
        int i = 0;
        auto grad = compute_gradient(Parser(function), x);
        grad = const_divide(norm(grad), grad);
        for (auto & s : x) {
            std::string r = toString(s.second);
            long double gr = grad[i];
            if (gr > 0) {
                r += "-";
            } else {
                gr *= -1;
                r += "+";
            }
            r += toString(gr) + "*" + "x";
            i++;
            nx[s.first] = r;
        }
        return nx;
    }

    std::map<std::string, long double>
    compute_x(const std::map<std::string, std::string>& x, std::map<std::string, long double> alpha) {
        std::map<std::string, long double> res;
        for (auto & s : x) {
            res[s.first] = compute_function(s.second, alpha);
        }
        return res;
    }
};
