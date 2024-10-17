// Functions help modularize code and avoid repetition
#include <iostream>

// Function declaration: return_type function_name(parameter_list)
int Product(int a, int b) {
    // Returns the product of two integers
    return a * b; // Every function (except void) must return a value
}

// Use 'void' as the return type when there is no value to return
void Print(int value) {
    std::cout << value << std::endl; // Prints an integer value
}

int main() {
    // Using the Product function to simplify repeated calculations
    int result1 = Product(3, 5);
    int result2 = Product(10, 20);
    int result3 = Product(1, -1);
    
    // Print results of the Product function
    std::cout << result1 << ", " << result2 << ", " << result3 << std::endl;

    // Using the Print function to print individual values
    Print(20);
    Print(30);

    // NOTE: Do not overuse functions; each function call has an overhead (e.g., memory jumps)
    return 0;
}
