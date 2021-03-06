#pragma once

#include "All_inclusive.h"

struct Parabola_method {
	double operator()(double a, double b, double eps) {
		double x1 = a;
		double x;
		double x2;
		double x3 = b;
		double f1 = function(x1);
		double f2;
		double f3 = function(x3);
		double a_proto = a;
		double b_proto = b;
		double cur;
		double D = 1;
		int i = 1;
		while (true) {
			x2 = (a_proto + b_proto) / 2;
			f2 = function(x2);
			if (f2 <= f1 && f2 <= f2) {
				break;
			}
			else if (f2 <= f1 && f2 >= f3) {
				a_proto = x2;
			}
			else {
				b_proto = x2;
			}
		}

		while (D > eps) {
			double a_0 = f1;
			double a_1 = (f2 - f1) / (x2 - x1);
			double a_2 = ((f3 - f1) / (x3 - x1) - (f2 - f1) / (x2 - x1)) / (x3 - x2);
			x = (x1 + x2 - a_1 / a_2) / 2;
			if (i != 1) {
				D = abs(x - cur);
			}
			cur = x;

			double f = function(x);
			if (x1 < x && x < x2 && f >= f2) {
				a = x;
				b = x3;
				x1 = x;
				f1 = f;
			}
			else if (x1 < x && x < x2 && f < f2) {
				a = x1;
				b = x2;
				x3 = x2;
				f3 = f2;
				x2 = x;
				f2 = f;

			}
			else if (x2 < x && x < x3 && f >= f2) {
				a = x2;
				b = x3;
				x3 = x;
				f3 = f;

			}
			else {
				a = x1;
				b = x;
				x1 = x2;
				f1 = f2;
				x2 = x;
				f2 = f;

			}

			i++;
		}
		double f = function(x);
		return f;
	}
    double operator()(std::string func, double a, double b, double eps, long double & x) {
        std::map<std::string, long double> x1;
        std::map<std::string, long double> x2;
        std::map<std::string, long double> x3;
        std::map<std::string, long double> x4;
        x1["x"] = a;
        x3["x"]  = b;
        double f1 = compute_function(func,x1);
        double f2;
        double f3 = compute_function(func, x3);
        double a_proto = a;
        double b_proto = b;
        double cur;
        double D = 1;
        int i = 1;
        while (true) {
            x2["x"] =  (a_proto + b_proto) / 2;
            f2 = compute_function(func, x2);
            if (f2 <= f1 && f2 <= f2) {
                break;
            }
            else if (f2 <= f1 && f2 >= f3) {
                a_proto = x2["x"];
            }
            else {
                b_proto = x2["x"];
            }
        }

        while (D > eps) {
            double a_0 = f1;
            double a_1 = (f2 - f1) / (x2["x"] - x1["x"] );
            double a_2 = ((f3 - f1) / (x3["x"] - x1["x"] ) - (f2 - f1) / (x2["x"] - x1["x"] )) / (x3["x"] - x2["x"]);
            x = (x1["x"] + x2["x"] - a_1 / a_2) / 2;
            if (i != 1) {
                D = abs(x - cur);
            }
            cur = x;
            x4["x"] = x;
            double f = compute_function(func,x4);
            if (x1["x"] < x && x < x2["x"] && f >= f2) {
                a = x;
                b = x3["x"];
                x1["x"] = x;
                f1 = f;
            }
            else if (x1["x"] < x && x < x2["x"] && f < f2) {
                a = x1["x"];
                b = x2["x"];
                x3 = x2;
                f3 = f2;
                x2["x"] = x;
                f2 = f;

            }
            else if (x2["x"] < x && x < x3["x"] && f >= f2) {
                a = x2["x"];
                b = x3["x"];
                x3["x"] = x;
                f3 = f;
            }
            else {
                a = x1["x"];
                b = x;
                x1 = x2;
                f1 = f2;
                x2["x"] = x;
                f2 = f;
            }
            i++;
        }
        x1["x"] = x;
        return compute_function(func, x1);
    }
};