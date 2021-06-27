#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ProfileMatrix.h"

std::vector<long double> b;
std::vector<long double> x;

double long eps = 1e-10;


// Получает элемент матрицы A с номером i, j
// Матрица A представлена в профильном виде
//
// i - это номер строки(нумерация с 1)
// j - это номер столбца(нумерация с 1)
// 
// Если i = j, то этот элемент находится на главной диагонали, значит возьмёт его из массива di
//
// Если i > j. то этот элемент находится в нижней треугольной матрице,
// значит возьмёт его из массива al.
// j - i + cnt - это индекс элемента в профиле строки,
// если j - i + cnt < 0, то значит этот элемент не хранится в профиле строки, значит это 0
// В массиве al этот элемент будет иметь индекс ia[i - 1] - 1 + j - i + cnt.
// ia[i - 1] - 1 - это индекс первого эелемента в профиле строки i
// cnt - количество элементов в профиле строки i
// ia[i - 1] - 1 + cnt - это индекс первого элемента в профиле строки (i + 1)
// 
// Если i < j. то этот элемент находится в верхней треугольной матрице,
// значит возьмёт его из массива au.
// i - j + cnt - это индекс элемента в профиле столбца,
// если i - j + cnt < 0, то значит этот элемент не хранится в профиле столбца, значит это 0
// В массиве au этот элемент будет иметь индекс ia[j - 1] - 1 + i - j + cnt.
// ia[j - 1] - 1 - это индекс первого эелемента в профиле стобца j
// cnt - количество элементов в профиле столбца j
// ia[j - 1] - 1 + cnt - это индекс первого элемента в профиле столбца (j + 1)
//
// На лекции сказали, что мы можем быть уверены в том, что профили строки и столбца одинаковы.
// Количество элементов в профиле строки i равно количеству элементов в профиле столбца j.
long double get_element(long long i, long long j) {
	if (i == j) {
		return di[i - 1];
	}
	else if (i > j) {
		long long cnt = ia[i] - ia[i - 1];
		if (j < i - cnt) {
			return 0;
		}
		else {
			return al[ia[i - 1] - 1 + j - i + cnt];
		}
	}
	else {
		long long cnt = ia[j] - ia[j - 1];
		if (i < j - cnt) {
			return 0;
		}
		else {
			return au[ia[j - 1] - 1 + i - j + cnt];
		}
	}
}

// Для матрицы устанавливает новое значение на место элемента с индексами i, j
// Работает только для тех элементов, которые изначально были в профиле!!!
//
// i - номер строки(нумерация с 1)
// j - номер столбца(нумерация с 1)
// val - новое значение
//
// Индекс элемента в профильном формате находит также как и в функции get_Element(long long, long long).
void set_element(long long i, long long j, long double val) {
	if (i == j) {
		di[i - 1] = val;
	}
	else if (i > j) {
		long long cnt = ia[i] - ia[i - 1];
		if (j < i - cnt) {
			return;
		}
		else {
			al[ia[i - 1] - 1 + j - i + cnt] = val;
		}
	}
	else {
		long long cnt = ia[j] - ia[j - 1];
		if (i < j - cnt) {
			return;
		}
		else {
			au[ia[j - 1] - 1 + i - j + cnt] = val;
		}
	}
}

bool belongs_to_the_profile(long long i, long long j) {

	if (i > j && j < i - (ia[i] - ia[i - 1])) {
		return false;
	}

	if (i < j && i < j - (ia[j] - ia[j - 1])) {
		return false;
	}

	return true;

}

long double get_elementL(long long i, long long j) {
	if (i == j) {
		return di[i - 1];
	}
	else if (i > j) {
		long long cnt = ia[i] - ia[i - 1];
		if (j < i - cnt) {
			return 0L;
		}
		else {
			return al[ia[i - 1] - 1 + j - i + cnt];
		}
	}
	else {
		return 0L;
	}
}

long double get_elementU(long long i, long long j) {
	if (i == j) {
		return 1L;
	}
	else if (i > j) {
		return 0L;
	}
	else {
		long long cnt = ia[j] - ia[j - 1];
		if (i < j - cnt) {
			return 0L;
		}
		else {
			return au[ia[j - 1] - 1 + i - j + cnt];
		}
	}
}

void toLU() {
	long long r = 1;
	long long c = 1;

	while (r - 1 != di.size() && c - 1 != di.size()) {
		for (long long i = c; i <= di.size(); i++) {
			if (i < c) {
				break;
			}
			long long sum = 0;
			for (long long k = 1; k <= c - 1; k++) {
				sum += get_elementL(i, k) * get_elementU(k, c);
			}
			set_element(i, c, get_element(i, c) - sum);
		}
		c++;

		for (long long j = r + 1; r != di.size() && j <= di.size(); j++) {
			if (r >= j) {
				break;
			}
			long long sum = 0;
			for (long long k = 1; k <= r - 1; k++) {
				sum += get_elementL(r, k) * get_elementU(k, j);
			}
			set_element(r, j, (get_element(r, j) - sum) / get_elementL(r, r));
		}
		r++;
	}
}

void fromLU() {
	std::ofstream F;
	F.open("fromLU_matrix.txt");
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = 1; j <= di.size(); j++) {
			long long sum = 0;
			for (long long k = 1; k <= di.size(); k++) {
				sum += get_elementL(i, k) * get_elementU(k, j);
			}
			F << sum << " ";
		}
		F << std::endl;
	}
}

void multiply_string(long long i, long double m) {
	for (long long j = 1; j <= di.size(); j++) {
		if (belongs_to_the_profile(i, j)) {
			set_element(i, j, get_element(i, j) * m);
		}
	}
	b[i - 1] *= m;
}

void subtract_strings(long long i, long long j) {
	for (long long k = 1; k <= di.size(); k++) {
		set_element(j, k, get_element(j, k) - get_element(i, k));
		/*if(get_element(j, k) - get_element(i, k) < eps)
			set_element(j, k, 0);*/
	}

	b[j - 1] -= b[i - 1];
}

std::vector<long double> return_y() {
	std::vector<long double> y;
	for (long long i = 1; i <= di.size(); i++) {
		long double sum = b[i - 1];
		long long y_it = y.size();
		for (long long j = 1; j <= y.size(); j++) {
			sum -= (y_it > 0) ? (y[j - 1] * get_elementL(i, j)) : 0;
			y_it--;
		}
		sum /= get_elementL(i, i);
		y.push_back(sum);
	}
	return y;
}

std::vector<long double> return_x() {
	std::vector<long double> x;
	std::vector<long double> y = return_y();
	for (long long i = di.size(); i >= 1; i--) {
		long double sum = y[i - 1];
		long long x_it = x.size();
		for (long long j = di.size(); j >= di.size() - x.size(); j--) {
			sum -= (x_it > 0) ? (x[x_it - 1] * get_element(i, j)) : 0;
			x_it--;
		}
		sum /= get_elementU(i, di.size() - x.size());
		x.insert(x.begin(), sum);
	}
	return x;
}

void return_x(long long i) {
	long double sum = b[i - 1];
	long long x_it = x.size();
	for (long long j = di.size(); j >= di.size() - x.size(); j--) {
		sum -= (x_it > 0) ? (x[x_it - 1] * get_element(i, j)) : 0;
		x_it--;
	}
	sum /= get_element(i, di.size() - x.size());
	x.insert(x.begin(), sum);
}

void Gauss() {
	// Прямой ход
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = i + 1; j <= di.size(); j++) {
			if (belongs_to_the_profile(j, i)) {
				multiply_string(j, get_element(i, i) / get_element(j, i));
				subtract_strings(i, j);
			}
		}
	}

	// Обратный ход
	for (int i = di.size(); i >= 1; i--) {
		return_x(i);
	}
}

void outputA() {
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = 1; j <= di.size(); j++) {
			std::cout << get_element(i, j) << " ";
		}
		std::cout << "= " << b[i - 1] << std::endl;
	}
}

void outputL() {
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = 1; j <= di.size(); j++) {
			std::cout << get_elementL(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

void outputU() {
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = 1; j <= di.size(); j++) {
			std::cout << get_elementU(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::ifstream File;
	File.open("test2\\input.txt");

	std::ifstream ms;
	ms.open("test2\\matrix_size.txt");

	long long n;
	ms >> n;

	profile(File, n);

	File.open("test2\\b.txt");
	for (long long i = 0; i < n; i++) {
		long double b_i;
		File >> b_i;
		b.push_back(b_i);
	}
	File.close();

	for (double d : di) {
		std::cout << d << " ";
	}
	std::cout << std::endl;

	for (int i : ia) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for (double l : al) {
		std::cout << l << " ";
	}
	std::cout << std::endl;
	
	for (double u : au) {
		std::cout << u << " ";
	}
	std::cout << std::endl << std::endl;

	toLU();
	outputL();
	std::cout << std::endl;
	outputU();

	std::vector<long double> x = return_x();
	for (int i = 0; i < 4; i++) {
		std::cout << x[i] << " ";
	}

	//fromLU();

	/*outputA();
	std::cout << std::endl;
	Gauss();
	outputA();
	std::cout << std::endl;

	for (long long i = 0; i < x.size(); i++) {
		std::cout << x[i] << " ";
	}*/
}
