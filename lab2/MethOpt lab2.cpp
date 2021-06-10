#include <iostream>
#include "Parser.h"
#include "Compute_gradient.h"
#include "GradientDescent_method.h"
#include "ConjugateGradients_method.h"

int main()
{
    std::cout.precision(15);
    SteepestDescent_method<Dychotomy_method> sdm_d;
    SteepestDescent_method<Golden_ratio_method> sdm_gr;
    SteepestDescent_method<Parabola_method> sdm_p;
    SteepestDescent_method<Fibonacci_method> sdm_f;
    SteepestDescent_method<Combined_Brent_method> sdm_cb;
    ConjugateGradient_method cgm;
    std::string func = "-4*x - 2*y + x*x + y*y - 5";
    std::string func1 = "64*x*x + 126*x*y + 64*y*y - 10*x + 30*y + 13";
    std::string func2 = "x*x - 2*x*y + y*y";

    std::cout << cgm(func) << "\n";
    std::cout << sdm_d(func) << "\n";
    std::cout << sdm_gr(func) << "\n";
    std::cout << sdm_p(func) << "\n";
    std::cout << sdm_f(func) << "\n";
    std::cout << sdm_cb(func) << "\n";
}