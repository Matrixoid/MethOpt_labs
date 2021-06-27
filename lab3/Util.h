#pragma once
#include "ProfileMatrix.h"

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

	if (i > j&& j < i - (ia[i] - ia[i - 1])) {
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

void output_x(std::ofstream& F, std::vector<long double> const& x) {
	for (long double x_i : x) {
		F << x_i << std::endl;
		std::cout << x_i << " ";
	}
}