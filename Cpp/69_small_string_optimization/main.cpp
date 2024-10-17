// Small string optimization - SSO
// so much negativity associated with std::strings, it's not as bad as you think
// C++ standard library optimized small strings -> they don't need "heap" allocation, can be stored in stack!
// strings are usually bad because they allocate memory to heap
// "small" meaning varies, VS defines 15 characters (<15 will store memory at stack)
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

void* operator new(size_t size) {
	std::cout << "Allocating " << size << "butes\n";
	return malloc(size);
}

int main() {
	// Debug - 8 bytes, Release - no allocation
	std::string name = "George"; // std::string -> heap allocation overhead? NOPE
	
	std::string longname = "George Kiiiiiiim"; // Debug/Release - allocate 32 bytes (>15 characters)

	std::cin.get();
}