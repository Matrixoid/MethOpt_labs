#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<long double> di;
std::vector<long long> ia;
std::vector<long double> al;
std::vector<long double> au;
std::vector<long double> b;
std::vector<long double> x;

double long eps = 1e-10;

struct Comp {
	bool operator()(std::pair<long double, int> a, std::pair<long double, int> b) {
		return a.second < b.second;
	}
};


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

	if (i > j && j < i - (ia[i] - ia[i - 1])) {
		return false;
	}

	if (i < j && i < j - (ia[j] - ia[j - 1])) {
		return false;
	}

	return true;

}

//void toLU() {
//	for (long long i = 1; i <= di.size(); i++) {
//		long long cnt = ia[i] - ia[i - 1];
//		for (long long j = i - cnt; j < i; j++) {
//			long double a = get_element(i, j);
//			for (long long k = j - cnt; k < j; k++) {
//				a -= get_element(i, k) * get_element(k, j);
//			}
//			set_element(i, j, a);
//		}
//	}
//}

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
	// ������ ���
	for (long long i = 1; i <= di.size(); i++) {
		for (long long j = i + 1; j <= di.size(); j++) {
			if (belongs_to_the_profile(j, i)) {
				multiply_string(j, get_element(i, i) / get_element(j, i));
				subtract_strings(i, j);
			}
		}
	}

	// �������� ���
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

int main()
{
	std::fstream File;
	File.open("input.txt");

	std::ofstream F;
	F.open("output.txt");

	int n;
	File >> n;

	ia.push_back(1);
	std::vector <std::pair<long double, int>> au_temp;
	std::vector<int> helper(n);

	for (int i = 0; i < n; i++) {
		bool flagl = false;
		int l = 0;
		for (int j = 0; j < n; j++) {
			double elem;
			File >> elem;
			if (i == j) {
				di.push_back(elem);
			}
			else if (i > j) {
				if (elem != 0)
					flagl = true;
				if (flagl) {
					l++;
					al.push_back(elem);
				}
			}
			else {
				if (elem != 0) {
					helper[j] = helper[j] != 0 ? helper[j] : i + 1;
				}
			}
		}
		ia.push_back(ia[ia.size() - 1] + l);
	}
	File.close();

	File.open("input.txt");
	File >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; ++j) {
			double elem;
			File >> elem;
			if (j > i) {
				if (helper[j] <= i + 1 && helper[j] != 0) {
					au_temp.emplace_back(elem, j);
				}
			}
		}
	}

	File.close();
	std::stable_sort(au_temp.begin(), au_temp.end(), Comp());

	File.open("b.txt");
	for (long long i = 0; i < n; i++) {
		long double b_i;
		File >> b_i;
		b.push_back(b_i);
	}

	for (std::pair<double, int> u : au_temp) {
		au.push_back(u.first);
	}

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

	outputA();
	std::cout << std::endl;
	Gauss();
	outputA();
	std::cout << std::endl;

	for (long long i = 0; i < x.size(); i++) {
		std::cout << x[i] << " ";
	}

	File.close();
	F.close();
}
