#pragma once
#include <iostream>
#include <string>
#include <vector>

class Parser {
private:
	std::string delimeter;
public:

	Parser(std::string delimeter) : delimeter(delimeter) {}
	Parser() = delete;
	~Parser() = default;

	std::vector<std::string> splitString(const std::string& str) {
		size_t start = 0;
		size_t end = str.find(delimeter);
		std::vector<std::string> splitted;

		while (end != std::string::npos) {
			splitted.push_back(str.substr(start, end - start));
			start = end + delimeter.length();
			end = str.find(delimeter, start);
		}

		splitted.push_back(str.substr(start, end));

		return splitted;
	}

	bool isNumber(std::string& str) {
		if (str.empty() || str == "-")
			return false;

		for (char s : str)
			if (!isdigit(s) && s != '.' && s != '-')
				return false;

		return true;
	}

	void ParseString(std::string& str, int i) {
		
	}
};
