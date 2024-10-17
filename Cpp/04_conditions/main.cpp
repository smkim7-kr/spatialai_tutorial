// Conditions and branching cause jumps to different areas of memory, introducing overhead
#include <iostream>

int main() {
    int x = 5;
    
    // Compare if x is equal to 5
    bool comparison = (x == 5); // == operator compares two integers
    if (comparison) {  // If comparison is true, execute this block
        std::cout << "x is 5!" << std::endl;
    }

    // This block will not execute because 0 is considered false
    if (0) {
        std::cout << "0 is false, so this will not be printed" << std::endl;
    }

    // Non-null pointer is considered true
    const char* ptr = "haha";
    if (ptr) {
        std::cout << "Anything that is not null or 0 is true" << std::endl;
    }

    // nullptr is considered false
    const char* ptr2 = nullptr;
    if (ptr2) {
        std::cout << "nullptr is false" << std::endl;
    } 
    else if (ptr2 == "hee") { // This condition is also false
        std::cout << "This is not true either" << std::endl;
    } 
    else {
        std::cout << "This will be printed because the if condition is false" << std::endl;
    }

    return 0;
}
