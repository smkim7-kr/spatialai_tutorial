// order of evaluation
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

void PrintSum(int a, int b) {
	std::cout << a << " + " << b << " = " << (a + b) << std::endl;
}

int main() {
	// Before C++17
	int value = 0;
	PrintSum(value++, value++); // undefined behavior because it depends on the used compiler
	// 1 + 0  = 1 in MSVC Debug Mode
	// 0 + 0 = 0 in MSVC Release Mode -> this is because compiler optimize code and run in parallel 

	PrintSum(++value, ++value); // undefined behavior 
	// 2 + 2 = 4 in MSVC Debug/Release Mode

	// From C++17
	// New rule on postfix-expression -> the expression needs to be evaluated first
	PrintSum(value++, value++); // 1 + 0 = 1 is MSVC Release Mode, still not deterministic

	std::cin.get();
}