// stroing any data - void pointe
// C++17 safer, much better days - std::any
// use std::variant for large size data types (Class object etc.)
#include <iostream>
#include <string>
#include <variant>
#include <any> // header
#define LOG(x) std::cout << x << std::endl

/* Way to debug memory allocation
void* operator new(size_t size) {
	return malloc(size);
}
*/

int main() {
	std::any data;
	data = 2;
	data = "Geroge";
	data = std::string("Geroge");

	std::string str = std::any_cast<std::string>(data); // if data is not std::string, will throw exception
	// copying data is slow, use reference
	std::string& strRef = std::any_cast<std::string&>(data); // not additional memory allocation by using reference

	// vs. std::variant
	// variants need to require to list types - this makes type safe (which is better than any)
	std::any data2 = "Geroge";
	// std::string string = std::any_cast<std::string>(data2); // error because data is const char[]
	std::variant<int, std::string> data3;
	data3 = "George";
	std::string string = std::get<std::string>(data3); // copying data is slow

	// how they stored
	// variants stores all data in union
	// any is union (for small types), void pointer (For large types)
	// for small types, it is similar to variant, for lrage types, it has huge storage memory with dynamic allocation

	// when to use std::any?
	// std::variant can replace std::any in most cases
	std::cin.get();
}