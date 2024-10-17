//// implementation of fixed-size stack-allocated array from scratch
//#include <iostream>
//#include <array>
//#define LOG(x) std::cout << x << std::endl
//
//int main() { 
//	// Preview
//
//	int array[5]; // stack allocated array, must specify size at compile time
//	int size = 5; 
//	// int wrongarray[size]; // causes an error
//
//	int* heaparr = new int[size]; // heap allocated array
//	delete[] heaparr; // must delete explicitly
//
//	// templated class array from c++11
//	std::array<int, 10> collection; // data type, size
//	collection.size(); // api that the code will implement
//	for (int ele : collection) {
//		std::cout << ele << std::endl;
//	}
//
//	std::cin.get();
//}