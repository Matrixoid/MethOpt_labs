#pragma once
#include "ProfileMatrix.h"

// �������� ������� ������� A � ������� i, j
// ������� A ������������ � ���������� ����
//
// i - ��� ����� ������(��������� � 1)
// j - ��� ����� �������(��������� � 1)
// 
// ���� i = j, �� ���� ������� ��������� �� ������� ���������, ������ ������ ��� �� ������� di
//
// ���� i > j. �� ���� ������� ��������� � ������ ����������� �������,
// ������ ������ ��� �� ������� al.
// j - i + cnt - ��� ������ �������� � ������� ������,
// ���� j - i + cnt < 0, �� ������ ���� ������� �� �������� � ������� ������, ������ ��� 0
// � ������� al ���� ������� ����� ����� ������ ia[i - 1] - 1 + j - i + cnt.
// ia[i - 1] - 1 - ��� ������ ������� ��������� � ������� ������ i
// cnt - ���������� ��������� � ������� ������ i
// ia[i - 1] - 1 + cnt - ��� ������ ������� �������� � ������� ������ (i + 1)
// 
// ���� i < j. �� ���� ������� ��������� � ������� ����������� �������,
// ������ ������ ��� �� ������� au.
// i - j + cnt - ��� ������ �������� � ������� �������,
// ���� i - j + cnt < 0, �� ������ ���� ������� �� �������� � ������� �������, ������ ��� 0
// � ������� au ���� ������� ����� ����� ������ ia[j - 1] - 1 + i - j + cnt.
// ia[j - 1] - 1 - ��� ������ ������� ��������� � ������� ������ j
// cnt - ���������� ��������� � ������� ������� j
// ia[j - 1] - 1 + cnt - ��� ������ ������� �������� � ������� ������� (j + 1)
//
// �� ������ �������, ��� �� ����� ���� ������� � ���, ��� ������� ������ � ������� ���������.
// ���������� ��������� � ������� ������ i ����� ���������� ��������� � ������� ������� j.
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

// ��� ������� ������������� ����� �������� �� ����� �������� � ��������� i, j
// �������� ������ ��� ��� ���������, ������� ���������� ���� � �������!!!
//
// i - ����� ������(��������� � 1)
// j - ����� �������(��������� � 1)
// val - ����� ��������
//
// ������ �������� � ���������� ������� ������� ����� ��� � � ������� get_Element(long long, long long).
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