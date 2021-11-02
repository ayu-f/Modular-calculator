#pragma once
#include"../Calc_dll/BaseOperation.hpp"

class Factorial : public BaseOperation {
public:
	Factorial() {
		opType = operType::postfix;
		str = "!";
		prior = priority::high;
	}

	virtual double calculate(std::vector<double> num) override {
		if (num.size() != 1)
			throw std::exception("Error: Invalid input");

		if (num[0] == 0 || num[0] == 1)
			return 1;

		double res = 1, tmp = fabs(num[0]);

		for (unsigned i = 2; i <= round(tmp); ++i)
			res *= i;

		res = num[0] > 0 ? res : -res;
		return res;
	}

	~Factorial() = default;
};

extern "C" __declspec(dllexport) BaseOperation * LoadOperation() {
	BaseOperation* fact = new Factorial;
	return fact;
}