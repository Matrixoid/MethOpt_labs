#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Comp {
	bool operator()(std::pair<long double, int> a, std::pair<long double, int> b) {
		return a.second < b.second;
	}
};

int main()
{
	std::fstream File;
	File.open("input.txt");

	std::ofstream F;
	F.open("output.txt");

	int n;
	File >> n;

	std::vector<double> di;
	std::vector<int> ia;
	ia.push_back(1);
	std::vector<double> al;
	std::vector <std::pair<long double, int>> au;
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
					au.emplace_back(elem, j);
				}
			}
		}
	}

	File.close();
	std::stable_sort(au.begin(), au.end(), Comp());

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
	
	for (std::pair<double, int> u : au) {
		std::cout << u.first << " ";
	}
	std::cout << std::endl;

	File.close();
	F.close();
}
