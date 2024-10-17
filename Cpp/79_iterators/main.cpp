// iterator: used when iterating over data structure
// vs. index operator: not work on some data structures e.g. sets
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#define LOG(x) std::cout << x << std::endl

int main() {
	std::vector<int> values = { 1, 2, 3, 4, 5 };
	
	// how to iterate?
	// 1) for loop
	for (int i = 0; i < values.size(); i++)
		std::cout << values[i] << std::endl;

	// 2) range-based for loop (from c++17)
	for (int value : values)
		std::cout << value << std::endl;
	// this works because vector provides begin() and end() function which returns iterator of particular position

	// 3) iterator-based for loop (avoid this in most case, this is complicated!)
	for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++) // end() points the next element of the last element of vector
		std::cout << *it << std::endl; // iterator is pointer 
	
	// for data structure w/o simple indexing system, iterators is inevitable! e.g. unordered_map
	using ScoreMap = std::unordered_map<std::string, int>;
	// using ScoreMapConstIter = ScoreMap::const_iterator;
	ScoreMap map;
	map["George"] = 5;
	map["C++"] = 4;
	// how to iterate?
	
	for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++) {
		// 2 elements: (key, value)
		auto& key = it->first;
		auto& value = it->second;
		std::cout << key << " = " << value << std::endl;
	}

	std::cout << "-----------------" << std::endl;
	// range-based for loop with unordered map
	for (auto kv : map) {
		auto& key = kv.first;
		auto& value = kv.second;
		std::cout << key << " = " << value << std::endl;
	}

	// From C++17, structured binding
	for (auto [key, value] : map) {
		std::cout << key << " = " << value << std::endl;
	}

	std::cin.get();
}