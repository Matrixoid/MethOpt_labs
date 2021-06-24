#pragma once
#include <sstream>
#include <string>
#include <cmath>

std::string toString(long double num) {
	std::ostringstream str_stream;
	str_stream.precision(10);
	if((long long) num == num ){
        str_stream.precision(0);

    }
    str_stream<< std::fixed << num;

	return str_stream.str();
}


std::pair<double, int> get_number(std::string func, long long n) {
	long double a = 1;
    size_t k = 0;
	if (func[0] >= '0' && func[0] <= '9') {
        a = std::stold(func, &k);
    }
	a *=n;
	std::pair<double, int> res;
	res.first = a;
	res.second = k;
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
	for (int i = 0; i < n.second; i++) {
		res.erase(0, 1);
	}
	if (res[0] == '*'){
        res.erase(0, 1);
	}
	return res;
}
