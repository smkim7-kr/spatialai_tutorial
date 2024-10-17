#include <iostream>

int main() {
    // Integer types
    int var = 20; // 4 bytes or 32 bits (range -2^31 to 2^31, 1 bit reserved for sign)
    var = 70; // can change the value
    unsigned int var2 = 30; // 4 bytes, always positive (range 0 to 2^32)

    // Character types
    char a = 65; // ASCII value of 'A'
    char b = 'A'; // direct character initialization
    std::cout << "char can be initialized with a number or character" << std::endl;
    std::cout << "char a = 65; char b = 'A' prints: a = " << a << ", b = " << b << std::endl << std::endl;

    // Floating point types
    float fvar = 5.5f; // 4 bytes, 'f' denotes float (5.5 is double by default)
    double dvar = 5.5; // 8 bytes, double precision
    std::cout << "float and double are used for decimal values" << std::endl;

    // Boolean types
    bool istrue = true;  // true prints 1
    bool isfalse = false; // false prints 0
    std::cout << "bool prints as either 0 (false) or 1 (true)" << std::endl;
    std::cout << "istrue = " << istrue << ", isfalse = " << isfalse << std::endl;

    // Size of a bool type in memory
    std::cout << "Size of bool: " << sizeof(istrue) << " bytes." << std::endl;

    return 0;
}
