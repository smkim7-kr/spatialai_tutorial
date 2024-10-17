#include <iostream>

void Log(const char* message) {
	std::cout << message << std::endl;
}

int main() {
	Log("Hello world!");
	std::cin.get();
}