// Demonstrating continue, break, and return
#include <iostream>

int main() {
    // continue: skips the current iteration and moves to the next one
    for (int i = 0; i < 5; ++i) {
        if (i % 2 == 0) // skip even numbers
            continue;
        std::cout << i << std::endl;
    }
    std::cout << "only odd numbers are printed" << std::endl;

    // break: exits the loop when the condition is met
    for (int i = 0; i < 5; ++i) {
        if (i == 3) // exit the loop when i is 3
            break;
        std::cout << i << std::endl;
    }
    std::cout << "loop exits before it prints 3" << std::endl;

    // return: exits the function (ends the program in the case of main)
    for (int i = 0; i < 5; ++i) {
        if (i == 3) // exits the program when i is 3
            return 0;
        std::cout << i << std::endl;
    }
    std::cout << "this line won't be printed because return ends the main function" << std::endl;

    return 0;
}
