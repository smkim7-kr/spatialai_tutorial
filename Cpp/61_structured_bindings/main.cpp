// Structured bindings - C++17 feature
// new way to return multiple types (like tuple/pairs)
#include <iostream>
#include <string>
#include <tuple>
#define LOG(x) std::cout << x << std::endl

std::tuple<std::string, int> CreatePerson() {
	return { "Geroge", 25 };
}

int main() {
	auto person = CreatePerson();
	// annoying when accessing data
	std::string& name = std::get<0>(person);
	int age = std::get<1>(person);

	// better approach - contianer of strong and int 
	std::string name2;
	int age2;
	std::tie(name2, age2) = CreatePerson(); // still takes many lines of code
	
	// Before C++17: just use struct for multiple return types

	// After C++17 (Change at Project properties >> C/C++ >> Language >> C++ language standard >> C++17 (or C++20)
	auto [name3, age3] = CreatePerson(); 
	std::cout << name3 << ", " << age3 << std::endl;

	std::cin.get();
}