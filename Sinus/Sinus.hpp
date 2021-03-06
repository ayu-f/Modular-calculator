#pragma once
#include"../Calc_dll/BaseOperation.hpp"

class Sinus : public BaseOperation {
public:
	Sinus() {
		opType = operType::prefix;
		str = "sin";
		prior = priority::high;
	}

	double calculate(const std::vector<double>& num) override {
		if (num.size() != 1)
			throw std::exception("Error! Invalid input: Sinus can have only one input parameter.");

		return sin(num.at(0));
	}

	~Sinus() = default;
};


extern "C" __declspec(dllexport) BaseOperation * LoadOperation() {
	BaseOperation* sin = new Sinus;
	return sin;
}