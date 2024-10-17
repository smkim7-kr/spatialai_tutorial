// C++17 feature - playing with strings is slow: they allocate memory
// std::string and other operations allocate memory
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

static uint32_t s_AllocCount = 0; // keep track of number of allocations

// new operator overloading for tracking memory allocation
void* operator new(size_t size) { 
	s_AllocCount++;
	std::cout << "Allocating" << size << std::endl;
	return malloc(size);
}

void PrintName(const std::string& name) {
	std::cout << name << std::endl;
}

void PrintName2(std::string_view name) { // overloaded function for string_view input
	std::cout << name << std::endl;
}

int main() {
	std::string name = "Geroge"; // 1 allocation, 8 bytes 
	PrintName(name);
	std::cout << s_AllocCount << " allocations" << std::endl; 

	s_AllocCount = 0;
	PrintName("Geroge"); // 1 allocation, 8 bytes 
	std::cout << s_AllocCount << " allocations" << std::endl;

	s_AllocCount = 0;
	std::string name2 = "Geroge Kim"; // 1 allocation, 8 bytes 
	std::string firstName2 = name2.substr(0, 6); // 1 allocation, 8 bytes 
	std::string lastName2 = name2.substr(7, 3); // 1 allocation, 8 bytes 
	PrintName(name2.substr(0, 6)); // 1 allocation, 8 bytes (Creating own memory string that can be mutated) 
	PrintName(lastName2); // No additional allocation here
	std::cout << s_AllocCount << " allocations" << std::endl;
	// 4 allocations in total! -> how to optimize this

	// Reducing memory allocation 
	// string view: const char pointer to existing string & size 
	// rather than allocating new memory, taking window view of existing memory/string
	s_AllocCount = 0;
	std::string name3 = "Geroge Kim"; // 1 allocation, 8 bytes 
	std::string_view firstName3(name3.c_str(), 6); // No additional allocation here
	std::string_view lastName3(name3.c_str() + 7, 3); // No additional allocation here
	PrintName2(firstName3); // No additional allocation here
	PrintName2(lastName3); // No additional allocation here
	std::cout << s_AllocCount << " allocations" << std::endl;

	// Removing all memory allocation - not use std::string
	s_AllocCount = 0;
	const char* name4 = "George Kim"; // cstring 
	std::string_view firstName4(name4, 6); // No additional allocation here
	std::string_view lastName4(name4 + 7, 3); // No additional allocation here
	PrintName2(firstName4); // No additional allocation here
	PrintName2(lastName4); // No additional allocation here
	std::cout << s_AllocCount << " allocations" << std::endl;

	// NOTE
	PrintName2("Geroge"); // this also allocate no memory

	std::cin.get();
}