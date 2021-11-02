#pragma once
#include"BaseOperation.hpp"
#include"Addition.hpp"
#include"Multiplication.hpp"
#include"Substraction.hpp"
#include"Division.hpp"

#include <map>
#include <stack>
#include <filesystem>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

typedef BaseOperation* (*baseOper)();

class Calculator {
private:
	std::vector<HMODULE> libs;
	std::string expression;
	std::stack<std::string> stack;
	std::vector<std::string> polish;
	std::map<std::string, BaseOperation*> operations;
	

	void InitOperations();
	void LoadDll(const std::string& pluginsPath);
	void GetExpression();

	bool IsOper(std::string token);
	bool IsOperPrefix(std::string token);
	bool IsOperPostfix(std::string token);
	bool IsOperBinary(std::string token);
	bool isNumber(std::string& str);

	std::string Parse(std::string str, int& i);
	// true - if arg1 >= arg2
	bool notLowerPrior(std::string str1, std::string str2);

	void ToPolishNotation();
	double calculate();
public:
	void Run(const std::string& plugPath);

	~Calculator() {
		for (auto dll : libs) {
			FreeLibrary(dll);
		}
		free(operations["+"]);
		free(operations["-"]);
		free(operations["*"]);
		free(operations["/"]);
	}
};

