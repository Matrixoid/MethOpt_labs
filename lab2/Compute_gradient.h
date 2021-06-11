#pragma once

#include <vector>
#include <map>
#include <string>
#include <cmath>

#include "get_Number.h"

long double norm(const std::vector<long double> &grad) {
    long double res = 0;
    for (long double i : grad)
        res += i * i;
    res = sqrt(res);
    return res;
}

long double compute_function(std::string function, std::map<std::string, long double> x) {
    std::string cur;
    std::vector<char> signs;
    signs.push_back('+');
    std::vector<std::string> split;
    std::string ch;
    for (int i = 0; i < function.size(); i++) {
        if (function[i] == ' ') {
            continue;
        }
        if (function[i] == '+' || function[i] == '-') {
            signs.push_back(function[i]);
            if (ch == " ") {
                cur.pop_back();
            }
            split.push_back(cur);
            cur = "";
            continue;
        }
        cur += function[i];
        ch = function[i];

        if (i == function.size() - 1) {
            split.push_back(cur);
            cur = "";
            ch = "";
        }
    }

    double res = 0;
    int sn = 0;
    for (std::string s : split) {
        if (s.empty())
            res--;
        double temp_res = get_number(s, 1).first;
        for (int i = 0; i < s.size(); i++) {
            std::string var;
            if (s[0] < '0' || s[0] > '9') {
                while (s[i] != 42 && i < s.size()) {
                    var += s[i];
                    i++;
                }
                temp_res *= x[var];
                var = "";
                ch = "";
            }
            if (ch == "*") {
                while (s[i] != 42 && i < s.size()) {
                    var += s[i];
                    i++;
                }
                temp_res *= x[var];
                var = "";
            }
            ch = s[i];
        }
        if (signs[sn] == '+') {
            res += temp_res;
        } else {
            res -= temp_res;
        }
        sn++;
    }
    return res;
}

std::vector<long double> compute_gradient(const std::vector<std::string> &gradient, const std::map<std::string, long double>& x) {
    std::vector<long double> result;
    result.reserve(gradient.size());
    for (const std::string &g : gradient) {
        result.push_back(compute_function(g, x));
    }
    return result;
}

std::vector<long double> negate(const std::vector<long double> &grad) {
    std::vector<long double> res = grad;
    for (auto &re : res)
        re *= -1;
    return res;
}

std::vector<long double> matrix_multiply(std::vector<std::vector<long double>> A, std::vector<long double> p) {
    std::vector<long double> res;
    for (auto &i : A) {
        double sum = 0;
        for (int j = 0; j < i.size(); j++) {
            sum += i[j] * p[j];
        }
        res.push_back(sum);
    }
    return res;
}

std::vector<long double> matrix_multiply(const std::vector<std::vector<long double>>& A, std::map<std::string, double> x) {
    std::vector<long double> res;
    for (auto &i : A) {
        double sum = 0;
        auto it = x.begin();
        for (long double j : i) {
            sum += j * it->second;
            it++;
        }
        res.push_back(sum);
    }
    return res;
}

std::vector<double> matrix_sum(std::map<std::string, double> x1, std::map<std::string, double> x2) {
    std::vector<double> res;
    auto it1 = x1.begin();
    auto it2 = x2.begin();
    for (int i = 0; i < x1.size(); i++) {
        res.push_back(it1->second + it2->second);
        it1++;
        it2++;
    }
    return res;
}

std::map<std::string, long double> matrix_sum(const std::map<std::string, long double>& x1, std::vector<long double> x2) {
    std::map<std::string, long double> res;
    int i = 0;
    for (const auto &s : x1) {
        res[s.first] = s.second + x2[i];
        i++;
    }
    return res;
}

std::vector<long double> matrix_sum(std::vector<long double> x1, std::vector<long double> x2) {
    std::vector<long double> res;
    res.reserve(x1.size());
    for (int i = 0; i < x1.size(); i++) {
        res.push_back(x1[i] + x2[i]);
    }
    return res;
}

std::vector<long double> matrix_sub(std::map<std::string, long double> x1, std::map<std::string, long  double> x2) {
    std::vector<long double> res;
    auto it1 = x1.begin();
    auto it2 = x2.begin();
    for (int i = 0; i < x1.size(); i++) {
        res.push_back(it1->second - it2->second);
        it1++;
        it2++;
    }
    return res;
}

std::vector<long double> matrix_sub(std::vector<long double> x1, std::vector<long double> x2) {
    std::vector<long double> res;
    res.reserve(x1.size());
    for (int i = 0; i < x1.size(); i++) {
        res.push_back(x1[i] - x2[i]);
    }
    return res;
}

std::vector<long double> const_multiply(long double constant, const std::vector<long double>& p) {
    std::vector<long double> res;
    res.reserve(p.size());
    for (long double i : p) {
        res.push_back(constant * i);
    }
    return res;
}
std::vector<long double> const_divide(long double constant, const std::vector<long double>& p) {
    std::vector<long double> res;
    res.reserve(p.size());
    for (long double i : p) {
        res.push_back(i/constant);
    }
    return res;
}

double scalar_multiply(std::vector<long double> p1, std::vector<long double> p2) {
    double res = 0;
    for (int i = 0; i < p1.size(); i++) {
        res += p1[i] * p2[i];
    }
    return res;
}