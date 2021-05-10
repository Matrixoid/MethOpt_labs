#include <iostream>
#include "Dychotomy_method.h"
#include "Golden_ratio_method.h"
#include "Fibonacci_method.h"
#include "Parabola_method.h"
#include "Combined_Brent_method.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	Dychotomy_method dm;
	Golden_ratio_method gdm;
	Fibonacci_method fm;
	Parabola_method pm;
	Combined_Brent_method cbm;
	
	std::vector<double> partd = { 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9 };
	for (auto l : partd) {

		double eps = l;
		double e = extr(a, b, eps);

		std::cout.precision(15);

		std::cout << "Метод дихотомии:" << std::endl;
		double d = dm(a, b, eps);
		std::cout << std::endl;

		std::cout << "Метод золотого сечения:" << std::endl;
		double g = gdm(a, b, eps);
		std::cout << std::endl;

		std::cout << "Метод Фибоначчи:" << std::endl;
		double f = fm(a, b, eps);
		std::cout << std::endl;

		std::cout << "Метод аппроксимирующей параболы:" << std::endl;
		double p = pm(a, b, eps);
		std::cout << std::endl;

		std::cout << "Комбинированный метод Брента:" << std::endl;
		double c = cbm(a, b, eps);
		std::cout << std::endl << std::endl;

		std::cout << "Погрешности:" << std::endl;
		std::cout << std::abs(e - d) << std::endl;
		std::cout << std::abs(e - g) << std::endl;
		std::cout << std::abs(e - f) << std::endl;
		std::cout << std::abs(e - p) << std::endl;
		std::cout << std::abs(e - c) << std::endl;
		std::cout << std::endl;
		
		
	}

}