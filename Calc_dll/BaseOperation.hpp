#pragma once
#include <string>
#include <cmath>
#include <vector>
#include <exception>

class BaseOperation {
public:
	enum operType {
		binary,
		postfix,
		prefix
	};

	enum priority {
		low,
		mid,
		high
	};

	BaseOperation(operType opType = operType::binary, priority prior = priority::low) {
		this->opType = opType;
		this->prior = prior;
	}
	virtual ~BaseOperation() = default;


	virtual double calculate(const std::vector<double>&) = 0;

	priority GetPriority() {
		return prior;
	}

	operType GetType() {
		return opType;
	}

	std::string to_string() {
		return str;
	}
protected:
	operType opType;
	priority prior;
	std::string str;
};
