#pragma once
#include <sstream>
#include <string>

std::string toString(long double num) {
	std::ostringstream str_stream;
	str_stream.precision(15);
	str_stream << num;
	return str_stream.str();
}

std::pair<double, int> get_number(std::string func, long long n) {

	std::string num = "";
	int i = 0;
	int sign_after_coma = 0;
	bool flag = false;
	while ((func[i] >= '0' && func[i] <= '9' || func[i] == '.') && i < func.size()) {
		if (flag) {
			sign_after_coma++;
		}
		if (func[i] == '.') {
			flag = true;
			i++;
			continue;
		}
		num += func[i];
		i++;
	}
	long double a = 0;
	long long dec = 1;
	for (int i = num.size() - 1; i >= 0; i--) {
		char dig = num[i];
		int d = dig - 48;
		a += d * dec;
		dec *= 10;
	}
	if (num == "") {
		a = 1;
	}
	a *= n;
	dec = 1;
	for (int i = 0; i < sign_after_coma; i++) {
		dec *= 10;
	}
	a /= dec;

	if (a == 0) {
		return { 0, 1 };
	}

	std::pair<double, int> res;
	res.first = a;
	res.second = i;
	return res;
}
