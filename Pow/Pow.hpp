#pragma once
#include"../Calc_dll/BaseOperation.hpp"

class Pow : public BaseOperation {
public:
	Pow() {
		opType = operType::binary;
		str = "^";
		prior = priority::high;
	}

	double calculate(const std::vector<double>& num) override {
		if (num.size() != 2)
			throw std::exception("Error! Invalid input: Exponentiation of a number operator can have only two input parameters.");

		return pow(num[0], num[1]);
	}

	~Pow() = default;
};

extern "C" __declspec(dllexport) BaseOperation * LoadOperation() {
	BaseOperation* pow = new Pow;
	return pow;
}