// don't use "using namespace std"
// std:: signifies this is C++ library function, rather than user-defined functions
// can have same functions/variable from different namespaces, thus required to exaplicitly show it remove ambiguiity
// never use namespace in header files!! Hard to track error and debug
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

namespace example {
	void print(const std::string& text) {
		std::cout << text << std::endl;
	}
}

namespace another {
	void print(const char* text) {
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << text << std::endl;
	}
}

namespace localif {}

using namespace example;
using namespace another; // which one should be called when to use print function

int main() {
	print("What?"); // another::print() will be called here because "What?" is const char[]
	std::string str = "Hello";
	print(str); // example::print() will be called when inputting std::string

	// without namespace
	example::print("Great!"); // can avoid ambiguity

	if (true) {
		using namespace localif; /// use namespace is local-limited scope if you must need to use it
	}
	std::cin.get();
}