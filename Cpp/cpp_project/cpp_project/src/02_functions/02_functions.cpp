// functions are useful when to use modularize the code or when repeated codes exist
#include <iostream>

// return_type function(input_parameters)
int Product(int a, int b) {
	return a * b; // must return something - exception: main function (return 0; in default) 
}

// use void return type when nothing to return
void Print(int a) {
	std::cout << a << std::endl;
}

int main() {
	int result1 = Product(3, 5);
	int result2 = Product(10, 20);
	int result3 = Product(1, -1); // repeated codes are simplified using functions
	std::cout << result1 << ", " << result2 << ", " << result3 << std::endl;

	Print(20);
	Print(30);
	// NOTE: do not overuse functions! There is overhead when creating funcitons (jumping around memory etc.)
	std::cin.get();
}