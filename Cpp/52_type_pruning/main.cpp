// getting around the type in c++ (strongly-typed system)
// types are enforced by compiler, we can directly access memory in C++
// e.g. get memory than convert int to double (circumvent type)
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

struct Vec2 {
	int x, y;

	int* GetPos() {
		return &x; // linking to same memory without allocating additional memorys
	}
};

int main() {
	int a = 50;
	double value = a; // int to double, thus a and value are at different memory
	// double value = (double) a; // what really happened from above code
	std::cout << value << std::endl; // prints 50 normally

	double sameMemValue = *(double*)&a; // convert int pointer to double pointer, then dereference it
	// by this way, a and sameMemValue takes same memory - type punning
	// copying int pointer (4 bytes) to double pointer (8 bytes) is bad
	std::cout << sameMemValue << std::endl; // not prints 50 because sameMemValue takes memory address of a

	// double& value2 = *(double*)&a;
	// value2 = 0.0; // writing 8 bytes on 4 bytes int memory -> this may cause crash

	Vec2 pos = { 1, 2 }; // struct itself doesn't reserve extra memory, thus 8 bytes (of two integers) reserved here
	int* posarr = (int*)&pos; // convert struct to array
	std::cout << posarr[0] << ", " << posarr[1] << std::endl; // 1, 2

	int y = *(int*)((char*)&pos+4); // shows ability to manipulate memory easily
	std::cout << y << std::endl; // 2

	int* position = pos.GetPos();
	position[1] = 2; // pos = { 0, 2 }

	std::cin.get();
}