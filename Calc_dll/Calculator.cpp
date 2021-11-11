#include"Calculator.hpp"

void Calculator::InitOperations() {
	BaseOperation* add = new Addition;
	BaseOperation* mult = new Multiplication;
	BaseOperation* sub = new Substraction;
	BaseOperation* div = new Division;

	operations[add->to_string()] = add;
	operations[mult->to_string()] = mult;
	operations[sub->to_string()] = sub;
	operations[div->to_string()] = div;
}

void Calculator::LoadDll(const std::string& pluginsPath) {
	if (!std::filesystem::exists(pluginsPath))
		throw std::exception("Error: No files in file input");

	for (auto plug : std::filesystem::directory_iterator(pluginsPath)) {
		HMODULE dll = LoadLibrary((plug.path().c_str()));
		if (!dll)
			throw std::exception("Error: Files in directory is not dll format");

		auto loader = (baseOper)GetProcAddress(dll, "LoadOperation");
		if (!loader)
			throw std::exception("Error: Invalid dll library");
		BaseOperation* op = loader();
		operations[op->to_string()] = op;

		libs.push_back(dll);
	}
}

void Calculator::GetExpression() {
	std::cout << "Input:" << std::endl;
	std::getline(std::cin, expression);

	if (expression.empty())
		throw std::exception("Error: Empty input");
}

bool Calculator::IsOper(const std::string& token) {
	return operations.find(token) != operations.end();
}

bool Calculator::IsOperPrefix(const std::string& token) {
	auto tmp = operations.find(token);
	if (tmp == operations.end())
		return false;
	return tmp->second->GetType() == BaseOperation::operType::prefix;
}

bool Calculator::IsOperPostfix(const std::string& token) {
	auto tmp = operations.find(token);
	if (tmp == operations.end())
		return false;
	return tmp->second->GetType() == BaseOperation::operType::postfix;
}

bool Calculator::IsOperBinary(const std::string& token) {
	auto tmp = operations.find(token);
	if (tmp == operations.end())
		return false;
	return tmp->second->GetType() == BaseOperation::operType::binary;
}

// true - if arg1 >= arg2
bool Calculator::notLowerPrior(const std::string& str1, const std::string& str2) {
	auto tmp1 = operations.find(str1);
	auto tmp2 = operations.find(str2);

	return tmp1->second->GetPriority() >= tmp2->second->GetPriority();
}

void Calculator::Parse(std::string& out_token, int& inout_i, const std::string& str) {
	//std::string token;
	if (isdigit(str[inout_i])) {
		while (isdigit(str[inout_i]) || str[inout_i] == '.' && inout_i < str.size()) {
			out_token.insert(out_token.end(), str[inout_i]);
			inout_i++;
		}
	}
	else if (str[inout_i] == ')' || str[inout_i] == '(') {
		out_token.insert(out_token.end(), str[inout_i]);
		inout_i++;
	}
	else {
		for (auto& strOper : operations) {
			std::string tmp = str.substr(inout_i, strOper.first.size());
			if (tmp.compare(strOper.first) == 0) {
				inout_i += tmp.size();
				out_token =  tmp;
				return;
			}
		}
		//if not found valid symbol
		out_token = str[inout_i];
	}
}

void Calculator::HandleClosingParenthesis() {
	if (!stack.empty())
		while (stack.top() != "(") {
			polish.push_back(stack.top());
			stack.pop();
		}
	stack.pop();
}

void Calculator::HandleBinaryOperation(const std::string& token) {
	while (!stack.empty() && IsOper(stack.top()) && (IsOperPrefix(stack.top()) || notLowerPrior(stack.top(), token))) {
		polish.push_back(stack.top());
		stack.pop();
	}
	stack.push(token);
}

void Calculator::ToPolishNotation() {
	for (int i = 0; i < expression.size();) {
		// just space - go to next char
		if (std::isspace(expression[i])){ 
			i++;
			continue;
		}
		std::string token;
		Parse(token, i, expression); // parse one token (number/operation/parenthesis)
		if (isNumber(token) || IsOperPostfix(token)) {
			polish.push_back(token);
		}
		// if token is prefix or )
		else if (IsOperPrefix(token) || token == "(") {
			stack.push(token);
		}
		else if (token == ")") {
			HandleClosingParenthesis();
		}
		else if (IsOperBinary(token)) {
			HandleBinaryOperation(token);
		}
		else {
			throw std::exception("Error: Invalid expression input");
		}
	}

	while (!stack.empty()) {
		polish.push_back(stack.top());
		stack.pop();
	}
}

bool Calculator::isNumber(const std::string& str) {
	if (str.empty() || str == "-")
		return false;

	for (char s : str)
		if (!isdigit(s) && s != '.' && s != '-')
			return false;

	return true;
}

double Calculator::calculate() {
	auto polish = this->polish;
	while (polish.size() != 1) {
		unsigned i;
		for (i = 0; i < polish.size(); ++i)
			if (!isNumber(polish[i]))
				break;

		auto op = operations.at(polish[i]);
		if (op->GetType() == BaseOperation::operType::binary) {
			double res = op->calculate({ std::stod(polish[i - 2]), std::stod(polish[i - 1]) });
			polish[i - 2] = std::to_string(res);
			polish.erase(polish.begin() + i - 1);
			polish.erase(polish.begin() + i - 1);
		}
		else {
			double res = op->calculate({ std::stod(polish[i - 1]) });
			polish[i - 1] = std::to_string(res);
			polish.erase(polish.begin() + i);
		}
	}

	double result = std::stod(polish.front());
	return result;
}

void Calculator::Run(const std::string& plugPath) {
	InitOperations();

	try {
		LoadDll(plugPath);
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	try {
		GetExpression();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		return;
	}

	try {
		ToPolishNotation();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		return;
	}

	double res;
	try {
		res = calculate();
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		return;
	}
	std::cout << "Answer: " << res << std::endl;
}