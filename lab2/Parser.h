#pragma once

#include <utility>
#include <vector>
#include <set>
#include <string>
#include <map>

#include "get_Number.h"
#include "Output.h"

std::vector<std::string> split(std::vector<char> &signs, const std::string &function) {
    std::string ch;
    std::string cur;
    std::vector<std::string> spl;
    if(function[0] != '+' && function[0] != '-') {
        signs.push_back('+');
    }
    for (int i = 0; i < function.size(); i++) {
        if (function[i] == ' ') {
            continue;
        }
        if (function[i] == '+' || function[i] == '-') {
            signs.push_back(function[i]);
            if (ch == " ") {
                cur.pop_back();
            }
            if (!cur.empty())
                spl.push_back(cur);
            cur = "";
            continue;
        }
        cur += function[i];
        ch = function[i];

        if (i == function.size() - 1) {
            spl.push_back(cur);
            cur = "";
            ch = "";
        }
    }
    return spl;
}

std::vector<std::string> split_by_mul(std::string part) {
    std::vector<std::string> spl;
    long double num = get_number(part, 1).first;
    if (num == 1) {
        spl.emplace_back("1");
    }
    std::string ch;
    std::string cur;
    for (int i = 0; i < part.size(); i++) {
        if (part[i] == 32 && part[i + 1] != 32) {
            continue;
        }
        if (part[i] == '*') {
            if (ch == " ") {
                cur.pop_back();
            }
            spl.push_back(cur);
            cur = "";
            continue;
        }
        cur += part[i];
        ch = part[i];

        if (i == part.size() - 1) {
            spl.push_back(cur);
            cur = "";
            ch = "";
        }
    }
    return spl;
}

void get_vars(std::string s, std::set<std::string> &vars) {
    std::string ch;
    std::string var;
    for (int i = 0; i < s.size(); i++) {
        if (s[0] < '0' || s[0] > '9') {
            while (s[i] != 42 && i < s.size()) {
                var += s[i];
                i++;
            }
            vars.insert(var);
            var = "";
            ch = "";
        }
        if (ch == "*") {
            while (s[i] != 42 && i < s.size()) {
                var += s[i];
                i++;
            }
            vars.insert(var);
            var = "";
        }
        ch = s[i];
    }
}

std::vector<std::string> Parser(const std::string &function) {
    std::vector<char> signs;
    std::vector<std::string> spl = split(signs, function);
    std::string ch;
    std::set<std::string> vars;
    for (const std::string &s : spl) {
        get_vars(s, vars);
    }

    std::vector<std::string> variables;
    variables.reserve(vars.size());
    for (const std::string &s : vars) {
        variables.push_back(s);
    }

    std::vector<std::string> grad;
    for (int i = 0; i < variables.size(); i++) {
        std::vector<std::string> parts_grad_part;
        std::string grad_part;
        std::string var = variables[i];
        for (std::string s : spl) {
            std::vector<int> variables_cnt(variables.size());
            std::string cur;
            std::string darivative;
            bool flag = false;
            for (int j = 0; j < s.size(); j++) {
                while (s[j] != 42 && j < s.size()) {
                    cur += s[j];
                    j++;
                }
                if (cur == var) {
                    variables_cnt[i]++;
                    if (!flag) {
                        int l = j;
                        j = (j >= var.size() + 1) ? j - var.size() - 1 : 0;
                        std::string left = s.substr(0, j);
                        std::string right = (j + var.size() + 1 > s.size()) ? s.substr(j + var.size()) : s.substr(
                                j + var.size() + 1);
                        darivative += left;
                        darivative += right;
                        flag = true;
                        j = (l >= var.size() + 1) ? j + var.size() + 1 : j + l;
                    }
                }
                cur = "";
            }

            std::pair<double, int> n = get_number(s, variables_cnt[i]);
            std::pair<std::string, int> num;
            num.first = toString(n.first);
            num.second = n.second;
            std::string r = (!darivative.empty()) ? darivative.substr(num.second) : "";//gradient
            std::string gr = num.first + ((num.second == 0) ? "*" : "") + r;
            if (gr[gr.size() - 1] == '*')
                gr.pop_back();
            parts_grad_part.push_back(gr);
        }
        int sn = 0;
        for (const std::string &gr : parts_grad_part) {
            if (gr == "0") {
                sn++;
                continue;
            }
            grad_part += signs[sn] + gr;
            sn++;
        }
        if (grad_part[0] == '+'){
            grad_part = grad_part.substr(1);
        }
        grad.push_back(grad_part);
    }

    return grad;
}

char get_sign(std::vector<char> signs, std::vector<std::string> vec, int i) {
    if (signs.size() != vec.size()) {
        if (i == 0)
            return '+';
        else
            return signs[i - 1];
    } else {
        return signs[i];
    }
}

std::string bringing_similar(const std::string &function, const std::map<std::string, long  double> &x) {
    std::string res;

    std::map<std::string, int> x_to_num;
    std::map<int, std::string> num_to_x;
    int k = 0;
    for (const auto &p : x) {
        x_to_num[p.first] = k;
        num_to_x[k] = p.first;
        k++;
    }
    std::vector<std::vector<double>> A(x.size(), std::vector<double>(x.size()));
    std::vector<double> B(x.size());
    double C = 0;

    std::vector<char> signs;
    std::vector<std::string> spl = split(signs, function);
    for (int k = 0; k < spl.size(); k++) {
        std::vector<std::string> spl1 = split_by_mul(spl[k]);
        int c = (get_sign(signs, spl, k) == '-') ? -1 : 1;
        if (spl1.size() == 3) {
            if (spl1[1] > spl1[2]) {
                std::swap(spl1[1], spl1[2]);
            }
            A[x_to_num[spl1[1]]][x_to_num[spl1[2]]] += c * get_number(spl1[0], 1).first;
        } else if (spl1.size() == 2) {
            B[x_to_num[spl1[1]]] += c * get_number(spl1[0], 1).first;
        } else {
            C += c * get_number(spl1[0], 1).first;
        }
    }

    for (int i = 0; i < x.size(); i++) {
        for (int j = i; j < x.size(); j++) {
            if (A[i][j] == 0) {
                continue;
            } else if (A[i][j] == 1) {
                res += num_to_x[i] + "*" + num_to_x[j] + "+";
            } else if (A[i][j] == -1) {
                if (!res.empty())
                    res.erase(res.size() - 1);
                res += "-" + num_to_x[i] + "*" + num_to_x[j] + "+";
            } else if (A[i][j] > 0 && A[i][j] != 1) {
                res += toString(A[i][j]) + "*" + num_to_x[i] + "*" + num_to_x[j] + "+";
            } else {
                if (!res.empty())
                    res.erase(res.size() - 1);
                res += toString(A[i][j]) + "*" + num_to_x[i] + "*" + num_to_x[j] + "+";
            }
        }
    }

    for (int i = 0; i < x.size(); i++) {
        if (B[i] == 0) {
            continue;
        } else if (B[i] == 1) {
            res += num_to_x[i] + "+";
        } else if (B[i] == -1) {
            if (!res.empty())
                res.erase(res.size() - 1);
            res += "-" + num_to_x[i] + "+";
        } else if (B[i] > 0 && B[i] != 1) {
            res += toString(B[i]) + "*" + num_to_x[i] + "+";
        } else {
            if (!res.empty())
                res.erase(res.size() - 1);
            res += toString(B[i]) + "*" + num_to_x[i] + "+";
        }
    }

    if (C > 0) {
        res += toString(C);
    } else {
        res.erase(res.size() - 1);
        if (C < 0) {
            res += toString(C);
        }
    }

    return res;

}

std::string
return_function(std::vector<std::vector<double>> A, std::vector<double> B, double C, std::map<std::string, double> x) {
    std::string res;

    int i = 0;
    int j = 0;
    for (const auto &p1 : x) {
        for (const auto &p2 : x) {
            res += (A[i][j] != 0) ? ((A[i][j] / 2 != 1) ? toString(A[i][j] / 2) + "*" : "") + p1.first + "*" +
                                    p2.first + "+" : "";
            j++;
        }
        j = 0;
        i++;
    }

    i = 0;
    for (const auto &p : x) {
        res += (B[i] != 0) ? ((B[i] != 1) ? toString(B[i]) + "*" : "") + p.first + "+" : "";
    }

    if (C != 0) {
        res += toString(C);
    } else {
        res.erase(res.size() - 1);
    }

//    return bringing_similar(res, x);
}

std::vector<int> get_indexes(std::string part, const std::map<std::string, long double> &x) {
    std::vector<std::string> spl = split_by_mul(part);
    spl.erase(spl.begin(), spl.begin() + 1);
    std::map<std::string, int> x_to_num;
    int i = 0;
    for (auto &p : x) {
        x_to_num[p.first] = i;
        i++;
    }

    std::vector<int> res;

    for (const std::string &s : spl) {
        if (x.find(s) != x.end()) {
            res.push_back(x_to_num[s]);
        }
    }
    return res;
}

std::vector<std::vector<long double>> get_A(const std::string &function, const std::map<std::string, long double> &x) {
    std::string func = bringing_similar(function, x);
    std::vector<char> signs;
    std::vector<std::string> spl = split(signs, func);
    std::vector<std::vector<long double>> A(x.size(), std::vector<long double>(x.size()));

    for (const std::string &s : spl) {
        std::vector<int> indexes = get_indexes(s, x);
        if (indexes.size() == 2) {
            if (indexes[0] == indexes[1]) {
                A[indexes[0]][indexes[0]] = get_number(s, 2).first;
            } else {
                A[indexes[0]][indexes[1]] = get_number(s, 1).first;
                A[indexes[1]][indexes[0]] = get_number(s, 1).first;
            }
        }
    }
    return A;
}

//std::vector<double> get_B(const std::string &function, const std::map<std::string, double> &x) {
//    std::string func = bringing_similar(function, x);
//    std::vector<char> signs;
//    std::vector<std::string> spl = split(signs, func);
//    std::vector<double> B(x.size());
//
//    for (const std::string &s : spl) {
//        std::vector<int> indexes = get_indexes(s, x);
//        if (indexes.size() == 1) {
//            B[indexes[0]] = get_number(s, 1).first;
//        }
//    }
//    return B;
//}
//
//double get_C(const std::string &function, std::map<std::string, double> x) {
//    std::string func = bringing_similar(function, x);
//    std::vector<char> signs;
//    std::vector<std::string> spl = split(signs, func);
//    double C;
//    for (const std::string &s : spl) {
//        std::vector<int> indexes = get_indexes(s, x);
//        if (indexes.size() == 0) {
//            C = get_number(s, 1).first;
//        }
//    }
//    return C;
//}

//void get_matrixes(const std::string &function, std::map<std::string, double> x, std::vector<std::vector<double>> &A,
//                  std::vector<double> &B, double &C) {
//    std::string func = bringing_similar(function, x);
//    std::vector<char> signs;
//    std::vector<std::string> spl = split(signs, func);
//    A.resize(x.size(), std::vector<double>(x.size()));
//    B.resize(x.size());
//
//    for (const std::string &s : spl) {
//        std::vector<int> indexes = get_indexes(s, x);
//        if (indexes.size() == 2) {
//            if (indexes[0] == indexes[1]) {
//                A[indexes[0]][indexes[0]] = get_number(s, 2).first;
//            } else {
//                A[indexes[0]][indexes[1]] = get_number(s, 1).first;
//                A[indexes[1]][indexes[0]] = get_number(s, 1).first;
//            }
//        } else if (indexes.size() == 1) {
//            B[indexes[0]] = get_number(s, 1).first;
//        } else {
//            C = get_number(s, 1).first;
//        }
//    }
//}

std::vector<std::pair<char, std::string>> conformity(std::vector<char> signs, std::vector<std::string> spl) {
    std::vector<std::pair<char, std::string>> res;

    if (signs.size() == spl.size()) {
        for (int i = 0; i < signs.size(); i++) {
            res.push_back(std::make_pair(signs[i], spl[i]));
        }
    } else {
        res.push_back(std::make_pair('+', spl[0]));
        for (int j = 1; j < spl.size(); j++) {
            res.push_back(std::make_pair(signs[j - 1], spl[j]));
        }
    }

    return res;
}

std::string function_recovery(std::vector<std::pair<char, std::string>> p) {
    std::string res;
    if (p.size() == 0) {
        return res;
    }

    if (p[0].first == '-') {
        res += '-';
    }
    res += p[0].second;

    for (int i = 1; i < p.size(); i++) {
        res += p[i].first + p[i].second;
    }

    return res;
}

std::string multiply_strings(const std::string &s1, const std::string &s2) {
    std::string res;
    std::vector<char> signs1;
    std::vector<std::string> spl1 = split(signs1, s1);
    std::vector<std::pair<char, std::string>> con1 = conformity(signs1, spl1);
    std::vector<char> signs2;
    std::vector<std::string> spl2 = split(signs2, s2);
    std::vector<std::pair<char, std::string>> con2 = conformity(signs2, spl2);

    std::vector<std::pair<char, std::string>> preres;

    for (std::pair<char, std::string> c1 : con1) {
        for (std::pair<char, std::string> c2 : con2) {
            std::pair<char, std::string> p;
            std::pair<char, std::string> c1_temp = c1;
            std::pair<char, std::string> c2_temp = c2;
            if (c1.first != c2.first) {
                p.first = '-';
            } else {
                p.first = '+';
            }
            p.second += toString(get_number(c1.second, 1).first * get_number(c2.second, 1).first) + "*";
            c1_temp.second = remove_number(c1_temp.second);
            c2_temp.second = remove_number(c2_temp.second);
            if (!c1_temp.second.empty() && c2_temp.second.empty()) {
                p.second += c1_temp.second;
            } else if (c1_temp.second.empty() && !c2_temp.second.empty()) {
                p.second += c2_temp.second;
            } else if (!c1_temp.second.empty() && !c2_temp.second.empty()) {
                p.second += c1_temp.second + "*" + c2_temp.second;
            } else {
                p.second.erase(p.second.size() - 1);
            }
            preres.push_back(p);

        }
    }
    res = function_recovery(preres);
    return res;
}

std::string substitute(std::string function, std::map<std::string, std::string> x) {
    std::vector<char> signs;
    std::vector<std::string> spl = split(signs, function);
    std::vector<std::pair<char, std::string>> con = conformity(signs, spl);
    for (int i = 0; i < con.size(); i++) {
        std::string tmp = con[i].second;
        std::vector<std::string> splm = split_by_mul(tmp);
        std::string temp_res = splm[0];
        for (int j = 1; j < splm.size(); j++) {
            temp_res = multiply_strings(temp_res, x[splm[j]]);
        }
        con[i].second = temp_res;
    }
    return function_recovery(con);
}