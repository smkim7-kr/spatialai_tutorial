// CI: process of continuously integrating code during development automatically
// some error can occur not on runtime (supporting multiple platforms etc.)
// Not ideal for programmers to take all times at testing -> thus automatic tests is required
// build-test automatically for every commit 
// use Jenkins for example
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

int main() {

	std::cin.get();
}