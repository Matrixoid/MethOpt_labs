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
	std::string num;
	int k = 0;
	int sign_after_coma = 0;
	bool flag = false;
	char sign = '+';
	if (func[0] == '-' || func[0] == '+') {
		if (func[0] == '-') {
			sign = '-';
			func = func.erase(0, 1);
		}
		else
			func = func.erase(0, 1);
	}
	while ((func[k] >= '0' && func[k] <= '9' || func[k] == '.') && k < func.size()) {
		if (flag) {
			sign_after_coma++;
		}
		if (func[k] == '.') {
			flag = true;
			k++;
			continue;
		}
		num += func[k];
		k++;
	}
	long double a = 0;
	long long dec = 1;
	for (int i = num.size() - 1; i >= 0; i--) {
		char dig = num[i];
		int d = dig - 48;
		a += d * dec;
		dec *= 10;
	}
	if (num.empty()) {
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
	res.first = (sign == '+') ? a : -a;
	res.second = (sign == '+') ? k : k + 1;
	return res;
}

std::string skip_whitespace(const std::string& s) {
	std::string res;
	for (char i : s) {
		if (i != 32) {
			res += i;
		}
	}
	return res;
}

std::string remove_number(const std::string& s) {
	std::pair<double, int> n = get_number(s, 1);
	std::string res = skip_whitespace(s);
	for (int i = 0; i <= n.second; i++) {
		res.erase(0, 1);
	}
	return res;
}
