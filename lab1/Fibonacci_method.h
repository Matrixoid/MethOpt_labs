#pragma once

#include "All_inclusive.h"

struct Fibonacci_method {

    double operator()(double a, double b, double eps) {

        computation_fib();

        int n = 0;
        int k = 0;
        double eps_n = (b - a) / eps;
        while (eps_n > fib[n]) {
            n++;
        }
        double x1 = a + ((double) fib[n - 2] / fib[n]) * (b - a);
        double x2 = a + ((double) fib[n - 1] / fib[n]) * (b - a);
        double f1 = function(x1);
        double f2 = function(x2);

        while (k != n - 3) {
            if (f1 > f2) {
                a = x1;
                x1 = x2;
                f1 = f2;
                x2 = a + ((double) fib[n - k - 2] / fib[n - k - 1]) * (b - a);
                f2 = function(x2);
            } else {
                b = x2;
                x2 = x1;
                f2 = f1;
                x1 = a + ((double) fib[n - k - 3] / fib[n - k - 1]) * (b - a);
                f1 = function(x1);
            }
            k++;
        }

        double x = (x1 + x2) / 2;
        double f = function(x);
        return f;
    }

    double operator()(std::string func, double a, double b, double eps, long double &x) {
        computation_fib();
        int n = 0;
        int k = 0;
        double eps_n = (b - a) / eps;
        while (eps_n > fib[n]) {
            n++;
        }
        std::map<std::string, long double> x1;
        std::map<std::string, long double> x2;
        x1["x"] = a + ((double) fib[n - 2] / fib[n]) * (b - a);
        x2["x"] = a + ((double) fib[n - 1] / fib[n]) * (b - a);
        double f1 = compute_function(func, x1);
        double f2 = compute_function(func, x2);

        while (k != n - 3) {
            if (f1 > f2) {
                a = x1["x"];
                x1 = x2;
                f1 = f2;
                x2["x"] = a + ((double) fib[n - k - 2] / fib[n - k - 1]) * (b - a);
                f2 = compute_function(func, x2);
            } else {
                b = x2["x"];
                x2 = x1;
                f2 = f1;
                x1["x"] = a + ((double) fib[n - k - 3] / fib[n - k - 1]) * (b - a);
                f1 =  compute_function(func, x1);
            }
            k++;
        }

        x = (x1["x"] + x2["x"]) / 2;
        x1["x"] = x;
        return compute_function(func, x1);
    }

private:
    int n = 45;
    std::vector<long long> fib;

    void computation_fib() {
        fib.resize(90);
        fib[0] = 1;
        fib[1] = 1;
        for (int i = 2; i < 90; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
    }

};
