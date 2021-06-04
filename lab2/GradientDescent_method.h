#pragma once

#include <map>
#include <vector>
#include <iostream>
#include "Compute_gradient.h"
#include "Parser.h"

struct GradientDescent_method {
    long double operator()(const std::string &function) {
        long double eps = 1e-8, alpha = 120;
        std::map<std::string, long double> x;
        std::vector<std::string> parsed = Parser(function);
        x["x"] = 1;
        x["y"] = -5;
        long double f = compute_function(function, x);
        while (true) {
            std::vector<long double> gradient = compute_gradient(parsed, x);

            if (norm(gradient) <= eps) {
                std::map<std::string,long double> min = x;//точка минимума
                f = compute_function(function, x);//значение в точке минимума
                return f;
            }
            while (true) {
                std::map<std::string, long double> y;
                gradient = compute_gradient(parsed, x);
                int i = 0;
                for (const auto &p : x) {
                    std::cout << gradient[i] <<" ";
                    y[p.first] = x[p.first] - alpha * gradient[i];
                    i++;
                }
                std::cout<<"\n";
                long double f2 = compute_function(function, y);
                if (f2 < f) {
                    x = y;
                    f = f2;
                    break;
                } else {
                    alpha /= 2;
                }

            }
        }

    }
};
