// safety - reduce crashes, memory leaks, access violations
// From C++11: favor smart pointers against raw pointers because of memory leaks
// allocate heap memory - automate to reduce human error, thus automatic memory systems exists like smart pointers
// ownership of allocated memory - who is responsible for managing and cleaning up the memory after use?
// e.g. function A, function B: who needs to cleanup memory when both functions need a pointer
// smart pointers - automation of freeing the memory (which is inmportant!) / realiability and maintainability
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

int main() {

	std::cin.get();
}