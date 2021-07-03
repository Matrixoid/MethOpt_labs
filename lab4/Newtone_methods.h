#pragma once

#include <string>
#include <vector>
#include "../lab2/Parser.h"
#include "../lab2/Compute_gradient.h"
#include "../lab3/Gauss_method.h"

long double eps2 = 1e-9;

long double matrix_multiply(std::vector<long double> x1, std::vector<long double> x2) {
    long double res = 0;
    for (int i = 0; i < x1.size(); i++) {
        res += x1[i] * x2[i];
    }
    return res;
}

std::vector<long double> matrix_sub(std::vector<double> x1, std::vector<double> x2) {
    std::vector<long double> res;
    res.reserve(x1.size());
    for (int i = 0; i < x1.size(); i++) {
        res.push_back(x1[i] - x2[i]);
    }
    return res;
}

long double norm(const std::map<std::string, long double> &x_) {
    long double res = 0;
    for (auto &x1: x_) {
        res += x1.second * x1.second;
    }
    return sqrt(res);
}


std::vector<long double> solve(const std::string &filename, const std::vector<long double> &f1) {
    test_directory = "conditions/";
    test_matrix = filename;
    test_matrix_size = "size";
    test_f = "f.txt";
    std::ofstream ofile("conditions/" + test_f);
    x.clear();
    b.clear();
    ofile.precision(10);
    for (long double i : f1) {
        ofile << i << "\n";
        b.push_back(i);
    }
    ofile.close();
    std::ifstream File("conditions/" + filename);
    profile(File, f1.size());
    File.close();
    return Gauss();
}

struct Newtone_methods {

    static long double test_function(std::map<std::string, long double> &x_) {
        auto x1 = x_["x1"];
        auto x2 = x_["x2"];
        return std::cos(x1 +3.14) + x2*x2;
    }

    static std::vector<long double> gradient_function(std::map<std::string, long double> &x_) {
        auto x1 = x_["x1"], x2 = x_["x2"];
        return {-std::sin(x1 +3.14), 2*x2};
    }

    static std::vector<std::vector<long double>> gessian_function(std::map<std::string, long double> &x_) {
        auto x1 = x_["x1"], x2 = x_["x2"];
        return {{-std::cos(x1 +3.14),    0},
                {0, 2}};
    }

    static long double f(long double var, std::vector<long double> p_k, std::map<std::string, long double> x_k) {
        std::map<std::string, long double> new_x;
        for (int i = 0; i < p_k.size(); ++i) {
            new_x["x" + std::to_string(i + 1)] = x_k["x" + std::to_string(i + 1)] + var * p_k[i];
        }
        return test_function(new_x);
    }

    static long double Newtone(std::map<std::string, long double> curX, int & iteration) {
        std::map<std::string, long double> prevX;
        long double diff = 1000;
        iteration = 0;
        std::vector<long double> p;
        while (diff > eps2) {
            iteration++;
            prevX = curX;
            make_gessian_matrix("matrix.txt", prevX);
            p = solve("matrix.txt", const_multiply(-1, gradient_function(prevX)));
            curX = matrix_sum(prevX, p);
            diff = norm(matrix_sub(curX, prevX));
            if (norm(p) < eps1) {
                break;
            }
        }
        return test_function(curX);
    };

    static long double Linear_Newtone(std::map<std::string, long double> x_1,int & iteration) {
        std::vector<long double> p;
        long double diff = 1000;
        iteration = 0;
        auto x_2 = x_1;
        while (diff > eps2) {
            iteration++;
            x_1 = x_2;
            make_gessian_matrix("matrix.txt", x_1);
            p = solve("matrix.txt", const_multiply(-1, gradient_function(x_1)));
            Golden_ratio_method grt;
            auto alpha = grt(f, 0, INT32_MAX, p, x_1);
            x_2 = matrix_sum(x_1, const_multiply(alpha, p));
            diff = norm(matrix_sub(x_1, x_2));
            if (norm(p) < eps1) {
                break;
            }
        }
        return test_function(x_2);
    }

    static long double DecentDirection_Newtone(std::map<std::string, long double> x0, int & iteration) {

        std::vector<long double> p_k = const_multiply(-1, gradient_function(x0));

        Golden_ratio_method grt;
        auto alpha = grt(f, 0, INT32_MAX, p_k, x0);

        auto x_k = matrix_sum(x0, const_multiply(alpha, p_k));

        long double diff = norm(matrix_sub(x0, x_k));
        iteration = 0;

        while (diff > eps2) {
            iteration++;
            auto grad = gradient_function(x_k);
            auto r_grad = const_multiply(-1, grad);// -grad(x_k);
            make_gessian_matrix("matrix.txt", x_k);
            p_k = solve("matrix.txt", r_grad);
            if (matrix_multiply(p_k, grad) > 0) {
                p_k = r_grad;
            }
            alpha = grt(f, 0, INT32_MAX, p_k, x_k);
            auto x_n = matrix_sum(x_k, const_multiply(alpha, p_k));
            diff = norm(matrix_sub(x_n, x_k));
            x_k = x_n;
        }
        //std::cout << iteration << "\n";
        return test_function(x_k);
    }

private:
    static void make_gessian_matrix(const std::string &filename,
                                    std::map<std::string, long double> &currentX) {
        auto gessian = gessian_function(currentX);
        std::ofstream File("conditions/" + filename);
        for (auto &i : gessian) {
            for (long double j : i) {
                File << j << " ";
            }
            File << std::endl;
        }
        File.close();

    }

    struct Golden_ratio_method {
        long double operator()(
                const std::function<long double(long double, std::vector<long double>,
                                                std::map<std::string, long double>)> &func,
                long double a, long double b_,
                const std::vector<long double> &p_k, const std::map<std::string, long double> &x_k) {
            long double t = (sqrt(5) - 1) / 2;

            long double x1 = a + (1 - t) * (b_ - a);
            long double x2 = a + t * (b_ - a);

            long double f1 = func(x1, p_k, x_k);
            long double f2 = func(x2, p_k, x_k);
            long double eps_n = (b_ - a) / 2;

            while (eps_n > eps) {
                if (f1 - f2 <= eps) {
                    b_ = x2;
                    x2 = x1;
                    f2 = f1;
                    x1 = a + (1 - t) * (b_ - a);
                    f1 = func(x1, p_k, x_k);
                } else {
                    a = x1;
                    x1 = x2;
                    f1 = f2;
                    x2 = a + t * (b_ - a);
                    f2 = func(x2, p_k, x_k);
                }
                eps_n *= t;
            }
            return (a + b_) / 2;
        }
    };
};
