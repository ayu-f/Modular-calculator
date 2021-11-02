#pragma once
#include "BaseOperation.hpp"

class Multiplication : public BaseOperation {
public:
	Multiplication() {
		opType = operType::binary;
		str = "*";
		prior = priority::mid;
	}

	virtual double calculate(std::vector<double> num) override {
		if (num.size() != 2)
			throw std::exception("Error: Invalid input");

		return num.at(0) * num.at(1);
	}

	~Multiplication() = default;
};