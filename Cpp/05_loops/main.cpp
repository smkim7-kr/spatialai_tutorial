// Demonstrating loops: while, for, and do-while
#include <iostream>

int main() {
    // Inefficient repeated code
    std::cout << "ahh this is inefficient!" << std::endl;
    std::cout << "ahh this is inefficient!" << std::endl;
    std::cout << "ahh this is inefficient!" << std::endl;
    std::cout << "ahh this is inefficient!" << std::endl;
    std::cout << "ahh this is inefficient!" << std::endl;

    // Using a for loop to repeat the task more efficiently
    for (int i = 0; i < 5; ++i) {  // (initialization; condition; update)
        std::cout << "using for loop is more efficient" << std::endl;
    }

    // For loop with some parts left blank (valid in C++)
    int j = 0;
    for (; j < 5; ) {  // initialization and update are omitted
        std::cout << "it is valid to leave parts of the for loop blank" << std::endl;
        j++; // manually updating the loop variable
    }

    // While loop: repeats as long as the condition is true
    int i = 0;
    while (i < 5) {
        std::cout << "you can use a while loop instead of a for loop" << std::endl;
        i++;
    }

    // Do-while loop: guarantees the block runs at least once
    int k = 0;
    do {
        std::cout << "do-while loop will execute at least once" << std::endl;
        k++;
    } while (k < 5);

    return 0;
}
