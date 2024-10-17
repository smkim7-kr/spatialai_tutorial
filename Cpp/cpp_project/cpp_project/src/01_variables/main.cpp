#include <iostream>

int main() {
	// variables are stored in memory, different data types have different sizes
	int var = 20; // 4 bytes or 32 bits (range -2^31 to 2^31, 1 bit reserved to sign)
	var = 70; // can change the value 
	unsigned int var2 = 30;  // always positive (range 0 to 2^32)

	//other types of data: char, short, int, long, long long
	char a = 65; char b = 'A'; // char can be represented as number, but prints to character
	std::cout << a << ", " << b << std::endl; // 'A', 'A' 

	float fvar = 5.5; // 5.5 is actually defined as double here
	fvar = 5.5f; // append f or F at the end to represent float
	double dvar = 5.5; // double: 8 bytes, float: 4 bytes

	bool istrue = true; // 1 byte, true prints 1 (every integer except 0 is true)
	bool isfalse = false; // prints 0
	std::cout << istrue << ", " << isfalse << std::endl;
	
	std::cout << "Size of bool: " << sizeof(istrue) << " bytes." << std::endl; //sizeof() outputs byte size
	std::cin.get();
}