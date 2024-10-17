#include <iostream>
#include <string>
#include <vector>
#include "Vector.h"
#define LOG(x) std::cout << x << std::endl

int main() {
	Vector<int> values;
	values.EmplaceBack(1);
	values.EmplaceBack(2);
	values.EmplaceBack(3);
	values.EmplaceBack(4);
	values.EmplaceBack(5);

	for (int i = 0; i < values.Size(); i++)
		std::cout << values[i] << std::endl;

	// what custom iterator should provide
	for (int value : values)
		std::cout << value << std::endl;

	for (Vector<int>::Iterator it = values.begin(); it != values.end(); it++)
		std::cout << *it << std::endl;
#if 0
	std::vector<int> values = { 1, 2, 3, 4, 5 };

	for (int i = 0; i < values.size(); i++)
		std::cout << values[i] << std::endl;

	// what custom iterator should provide
	for (int value : values)
		std::cout << value << std::endl;

	for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++) 
		std::cout << *it << std::endl;
#endif
	std::cin.get();
}