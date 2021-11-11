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

	bool IsOper(const std::string& token);
	bool IsOperPrefix(const std::string& token);
	bool IsOperPostfix(const std::string& token);
	bool IsOperBinary(const std::string& token);
	bool isNumber(const std::string& str);

	void Parse(std::string& out_token, int& inout_i, const std::string& str);
	// true - if arg1 >= arg2
	bool notLowerPrior(const std::string& str1, const std::string& str2);
	void HandleClosingParenthesis();
	void HandleBinaryOperation(const std::string& token);

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

