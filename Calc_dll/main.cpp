#include <iostream>
#include <windows.h>
#include "Calculator.hpp"

int main(void) {
	const std::string plugPath = ("../plugins");
	Calculator calc;
	calc.Run(plugPath);
	getchar();
	return 0;
}