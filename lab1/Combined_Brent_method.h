#pragma once

#include "All_inclusive.h"

struct Combined_Brent_method {
    double operator()(double a, double b, double eps) {
        double t = (3 - sqrt(5)) / 2;
        double x, w, v, u;
        x = w = v = a + t * (b - a);
        double d_cur, d_prev;
        d_cur = d_prev = b - a;
        double g;
        double f = function(x);
        double fw = f, fv = f;

        while (true) {

            if (std::max(x - a, b - x) < eps) {
                f = function(x);
                return f;
            }

            g = d_prev / 2;
            d_prev = d_cur;

            double a_1 = (fw - f) / (w - x);
            double a_2 = ((fv - f) / (v - x) - a_1) / (v - x);
            u = (w + x - a_1 / a_2) / 2;

            if ((w == x) || (x == v) || (w == v) || !(u >= a && u <= b) || (std::abs(u - x) >= g / 2)) {
                if (x < (a + b) / 2) {
                    u = x + (1 - t) * (b - x);
                    d_prev = b - x;
                } else {
                    u = a + (1 - t) * (x - a);
                    d_prev = x - a;
                }
            }
            d_cur = std::abs(u - x);
            double fu = function(u);
            if (fu > f) {
                if (u < x)
                    a = u;
                else
                    b = u;
                if (fu <= fw || w == x) {
                    v = w;
                    w = u;
                    fv = fw;
                    fw = fu;
                } else {
                    if (fu <= fv || v == x || v == w) {
                        v = u;
                        fv = fu;
                    }
                }
            } else {
                if (u < x)
                    b = x;
                else
                    a = x;
                v = w;
                w = x;
                x = u;
                fv = fw;
                fw = f;
                f = fu;
            }
        }
    }

    double operator()(std::string func, double a, double b, double eps, long double &x) {
        std::map<std::string, long double> x_;//Просто какой-то массив, с помощью которого я вычисляю функцию
        double t = (3 - sqrt(5)) / 2;
        double w, v, u;
        x = w = v = a + t * (b - a);
        double d_cur, d_prev;
        d_cur = d_prev = b - a;
        double g;
        x_["x"] = x;
        double f = compute_function(func, x_);
        double fw = f, fv = f;

        while (true) {

            if (std::max(x - a, b - x) < eps) {
                x_["x"] = x;
                return compute_function(func, x_);
            }

            g = d_prev / 2;
            d_prev = d_cur;

            double a_1 = (fw - f) / (w - x);
            double a_2 = ((fv - f) / (v - x) - a_1) / (v - x);
            u = (w + x - a_1 / a_2) / 2;

            if ((w == x) || (x == v) || (w == v) || !(u >= a && u <= b) || (std::abs(u - x) >= g / 2)) {
                if (x < (a + b) / 2) {
                    u = x + (1 - t) * (b - x);
                    d_prev = b - x;
                } else {
                    u = a + (1 - t) * (x - a);
                    d_prev = x - a;
                }
            }
            d_cur = std::abs(u - x);
            x_["x"] = u;
            double fu = compute_function(func, x_);
            if (fu > f) {
                if (u < x)
                    a = u;
                else
                    b = u;
                if (fu <= fw || w == x) {
                    v = w;
                    w = u;
                    fv = fw;
                    fw = fu;
                } else {
                    if (fu <= fv || v == x || v == w) {
                        v = u;
                        fv = fu;
                    }
                }
            } else {
                if (u < x)
                    b = x;
                else
                    a = x;
                v = w;
                w = x;
                x = u;
                fv = fw;
                fw = f;
                f = fu;
            }
        }
    }

};