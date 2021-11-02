#pragma once
#include "BaseOperation.hpp"

class Substraction : public BaseOperation {
public:
	Substraction() {
		opType = operType::binary;
		str = "-";
		prior = priority::low;
	}

	virtual double calculate(std::vector<double> num) override {
		if (num.size() != 2)
			throw std::exception("Error: Invalid input");

		return num.at(0) - num.at(1);
	}

	~Substraction() = default;
};