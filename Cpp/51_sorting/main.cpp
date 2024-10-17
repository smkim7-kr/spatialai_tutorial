// std::sort() - use optimized built function provide by C++ O(nlogn)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // to use std::sort
#include <functional> // to add rules in sorting
#define LOG(x) std::cout << x << std::endl

int main() {
	std::vector<int> values = { 4, 5, 2, 7, 8, 1, 9 };
	std::sort(values.begin(), values.end()); // range by input two iterators
	for (int v : values)
		std::cout << v << std::endl;

	// sorting rules defined by functional header
	std::sort(values.begin(), values.end(), std::greater<int>()); // descedning order
	for (int v : values)
		std::cout << v << std::endl;

	// User-defined sorting rules
	std::sort(values.begin(), values.end(), [](int a, int b) {
		// return type bool: true means a ordered before b and vice versa
		if (a == 1)
			return false;
		if (b == 1)
			return true;
		return a < b; // ascending list with 1 at the end
		}); // user-defined lambda function
	for (int v : values)
		std::cout << v << std::endl;

	std::cin.get();
}