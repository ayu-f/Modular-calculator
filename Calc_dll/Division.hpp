#pragma once
#include "BaseOperation.hpp"

class Division : public BaseOperation {
public:
	Division() {
		opType = operType::binary;
		str = "/";
		prior = priority::mid;
	}

	virtual double calculate(std::vector<double> num) override {
		if (num.size() != 2)
			throw std::exception("Error: Invalid input");

		return num.at(0) - num.at(1);
	}

	~Division() = default;
};
