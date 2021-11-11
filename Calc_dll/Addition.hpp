#pragma once
#include "BaseOperation.hpp"

class Addition : public BaseOperation {
public:
	Addition() { 
		opType = operType::binary;
		str = "+";
		prior = priority::low;
	}
	
	double calculate(const std::vector<double>& num) override {
		if (num.size() != 2)
			throw std::exception("Error! Invalid input: Addition operator can have only two input parameters.");

		return num.at(0) + num.at(1);
	}

	~Addition() = default;
};
