#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<double> di;
std::vector<int> ia;
std::vector<double> al;
std::vector<double> au;

struct Comp {
	bool operator()(std::pair<long double, int> a, std::pair<long double, int> b) {
		return a.second < b.second;
	}
};

double getElement(int i, int j) {
	if (i == j) {
		return di[i - 1];
	}
	else if (i > j) {
		int cnt = ia[i] - ia[i - 1];
		int j_t = j - (i - cnt);
		return j_t >= 0 ? al[ia[i - 1] - 1 + j_t] : 0;
	}
	else {
		int cnt = ia[j] - ia[j - 1];
		int i_t = i - (j - cnt);
		return i_t >= 0 ? au[ia[j - 1] - 1 + i_t] : 0;
	}
}

void setElement(int i, int j, double val) {
	if (i == j) {
		di[i - 1] = val;
	}
	else if (i > j) {
		int cnt = ia[i] - ia[i - 1];
		int j_t = j - (i - cnt);
		al[ia[i - 1] - 1 + j_t] = val;
	}
	else {
		int cnt = ia[j] - ia[j - 1];
		int i_t = i - (j - cnt);
		au[ia[j - 1] - 1 + i_t] = val;
	}
}

double getElementIndex(int i, int j) {
	if (i == j) {
		return di[i - 1];
	}
	else if (i > j) {
		int cnt = ia[i] - ia[i - 1];
		int j_t = j - (i - cnt);
		return j_t >= 0 ? ia[i - 1] - 1 + j_t : 0;
	}
	else {
		int cnt = ia[j] - ia[j - 1];
		int i_t = i - (j - cnt);
		return i_t >= 0 ? ia[j - 1] - 1 + i_t : 0;
	}
}

void toLU() {
	for (int i = 1; i <= di.size(); i++) {
		for (int j = 1; j <= di.size(); j++) {
			if (i == 1 && j == 1) {
				setElement(1, 1, getElement(1, 1));
				continue;
			}
			else if (i <= j) {
				double sum = 0;
				for (int k = 1; k <= j - 1; k++) {
					sum += getElement(i, k) * getElement(k, j);
				}
				setElement(i, j, getElement(i, j) - sum);
			}
			else {
				double sum = 0;
				for (int k = 1; k <= i - 1; k++) {
					sum += getElement(i, k) * getElement(k, j);
				}
				setElement(i, j, (getElement(i, j) - sum) / getElement(i, i));
			}
		}
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
	std::cout << std::endl;

	std::cout << getElement(9, 7);

	File.close();
	F.close();
}
