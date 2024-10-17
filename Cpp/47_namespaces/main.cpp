// C language don't have namespaces, only C++ has
// In C, people solved redundancy by embedding library names into symbol names (e.g. prepending library name)
// C++ solved this issues by namespace - to avoid naming conflicts
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

namespace example {
	void print(const char* text) {
		std::cout << text << std::endl;
	}

	void print2(const char* text) {
		std::cout << "Another: " << text << std::endl;
	}

	namespace func { // nested namespace
		void nestedprint(const char* text) {
			std::cout << text << std::endl;
		}
	}
}

namespace another {
	void print(const char* text) { // if we have same symboal names (class, function, variable), we need to differentiate using namespaces
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << text << std::endl;
	}
}

using namespace example;
using namespace another;

int main() {
	example::print("George");
	another::print("George");

	using example::print; // can specify namespace of particular function
	print("George");
	example::print2("George");

	namespace a = example; // namespace aliasing
	using namespace example::func; 
	namespace b = example::func; // nested namespace, good example to use aliasing
	b::nestedprint("Geroge");
	std::cin.get();
} // use namespace in smaller scope as possible