#pragma once

#include "All_inclusive.h"
#include "../lab2/Compute_gradient.h"

struct Golden_ratio_method {
    double operator()(double a, double b, double eps) {
        double t = (sqrt(5) - 1) / 2;

        double x1 = a + (1 - t) * (b - a);
        double x2 = a + t * (b - a);

        double f1 = func2(x1);
        double f2 = func2(x2);
        double eps_n = (b - a) / 2;

        while (eps_n > eps) {
            if (f1 - f2 <= eps) {
                b = x2;
                x2 = x1;
                f2 = f1;
                x1 = a + (1 - t) * (b - a);
                f1 = func2(x1);
            } else {
                a = x1;
                x1 = x2;
                f1 = f2;
                x2 = a + t * (b - a);
                f2 = func2(x2);
            }
            eps_n *= t;
        }

        double x = (a + b) / 2;
        double f = func2(x);
        return f;
    }

    double operator()(std::string func, double a, double b, double eps,  long double &x) {
        double t = (sqrt(5) - 1) / 2;
        std::map<std::string, long double> x1;
        std::map<std::string, long double> x2;
        x1["x"] = a + (1 - t) * (b - a);
        x2["x"] = a + t * (b - a);

        long double f1 = compute_function(func, x1);
        long double f2 = compute_function(func, x2);
        double eps_n = (b - a) / 2;

        while (eps_n > eps) {
            if (f1 - f2 <= eps) {
                b = x2["x"];
                x2 = x1;
                f2 = f1;
                x1["x"] = a + (1 - t) * (b - a);
                f1 = compute_function(func, x1);
            } else {
                a = x1["x"];
                x1 = x2;
                f1 = f2;
                x2["x"] = a + t * (b - a);
                f2 = compute_function(func, x2);
            }
            eps_n *= t;
        }
        x1["x"] = (a + b) / 2;
        x = (a + b) / 2;
        return compute_function(func, x1);
    }
};