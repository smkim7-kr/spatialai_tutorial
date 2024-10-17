// From a computer's perspective, pointers and references serve similar purposes.
// However, references are not new variables like pointers; they must reference an existing variable and do not occupy extra memory.
#include <iostream>
#define Log(x) std::cout << x << std::endl;

void Increment(int value) {  // Pass-by-copy: this creates a copy, so it doesn't modify the original variable
    value++;
}

/*
void Increment(int* value) {
    (*value)++;  // Pass-by-pointer: this would modify the original variable
}
*/

void Increment(int& value) {  // Pass-by-reference: this directly modifies the original input variable
    value++;
}

int main() {
    int a = 10;
    int* ptr = &a;  // Pointer: '&' is used to get the memory address of variable 'a'
    int& ref = a;   // Reference: '&' is part of the type, functioning differently from pointers
    // ref does not truly "exist" as a separate entity; it's just an alias for variable 'a'
    std::cout << ref << " will print a value of 10" << std::endl;

    int b = 5;
    int c = 8;
    int& ref2 = b;
    ref2 = c; // This does not switch the reference; instead, it assigns 'c' to 'b', making 'b' equal to 8
	std::cout << b << " will print a value of 8" << std::endl;

    return 0;
}
