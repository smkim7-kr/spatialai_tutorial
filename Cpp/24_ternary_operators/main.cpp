#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

int main() {
    int a = 8;
    
    // Ternary operator: if (a > 5), b = 10; otherwise, b = 5
    int b = a > 5 ? 10 : 5;
    
    // Nested ternary operator:
    // if (b > 5), check if b > 10 (if true, c = 15; else, c = 10); otherwise, c = 5
    int c = b > 5 ? (b > 10 ? 15 : 10) : 5;
    
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;

    return 0;
}
