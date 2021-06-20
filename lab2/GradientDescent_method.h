#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Compute_gradient.h"
#include "Parser.h"

struct GradientDescent_method {
    long double operator()(const std::string &function, long double eps) {
        double alpha = 10;
        std::map<std::string, long double> x;
        x["x"] = 0;
        x["y"] = 0;
        std::map<std::string, long double> newx;
        int it = 0;
        while (true) {
            std::vector<long double> gradient = compute_gradient(Parser(function), x);
            long double len = norm(gradient);
            if (len < eps) {
                break;
            }
            while (true) {
                int i = 0;
                for (const auto &p : x) {
                    newx[p.first] = x[p.first] - alpha * gradient[i];
                    i++;
                }
                long double f = compute_function(function, x);
                long double f2 = compute_function(function, newx);
                if (f2 <= f) {
                    break;
                }
                alpha /= 2;
            }
            x = newx;
            alpha = 10;
            it++;
        }
        std::cout << it << "\n";
        return compute_function(function, x);
    }
};
