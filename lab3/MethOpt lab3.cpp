#include <iostream>
#include <fstream>
#include <vector>

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
	std::vector<double> au;

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
				au.push_back(1);
			}
		}
		ia.push_back(ia[ia.size() - 1] + l);
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

	File.close();
	F.close();
}
