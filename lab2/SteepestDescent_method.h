#pragma once

#include "Compute_gradient.h"
#include "Parser.h"
#include <iostream>
#include <vector>
#include <map>

template<typename Minimum>
struct SteepestDescent_method {

    long double operator()(const std::string &func) {
        std::map<std::string, long double> x;
        double eps = 0.001;
        double eps1 = 1e-7;
        x["x"] = 4;
        x["y"] = 5;
        int iter = 0;
        long double f = compute_function(func, x);
        while (true) {
            std::vector<long double> grad = compute_gradient(Parser(func), x);
            if (norm(grad) < eps ) {
                return compute_function(func, x);
            }
            std::map<std::string, std::string> nx = newx(func, x);
            std::string fi = bringing_similar(substitute(func, nx), x);
            long double alpha = Minimum()(fi, -2048, 2048, eps1);
            std::map<std::string, long double> alp;
            alp["x"] = alpha;
            auto xk =  matrix_sum(x, negate(const_multiply(alpha, grad)));
            auto diff = compute_function(func, x) - compute_function(func, xk);
            if (std::abs(alpha) < eps || std::abs(diff) < eps){
                return compute_function(func, xk);
            }
            x = xk;
            iter++;

        }
    }

private:
    std::map<std::string, std::string> newx(std::string function, std::map<std::string, long double> x) {
        std::map<std::string, std::string> nx;
        int i = 0;
        auto grad = compute_gradient(Parser(function), x);
        for (std::pair<std::string, double> s : x) {
            std::string r = toString(s.second);
            long double gr = grad[i] ;
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
    compute_x(std::map<std::string, std::string> x, std::map<std::string, long double> alpha) {
        std::map<std::string, long double> res;
        for (std::pair<std::string, std::string> s : x) {
            res[s.first] = compute_function(s.second, alpha);
        }
        return res;
    }
};
