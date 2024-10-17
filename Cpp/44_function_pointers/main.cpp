// Function pointers: Assign a function to a variable.
// Common usage - to call a function normally with input and output.
// By assigning to variables - you can pass functions into other functions, use them as callbacks, etc.
// Function pointers are more common in old C-style code and are less used in modern C++.

#include <iostream>
#include <string>
#include <vector>
#define LOG(x) std::cout << x << std::endl

// Simple function with no input and output
void Print() {
    std::cout << "Hello World!" << std::endl;
}

// Function with an integer input
void PrintWInput(int a) {
    std::cout << "Hello World! " << a << std::endl;
}

// Function that prints a value
void PrintValue(int v) {
    std::cout << "Value: " << v << std::endl;
}

// Function that takes a function pointer as input and applies it to each element of the vector
void ForEach(const std::vector<int>& values, void(*func)(int)) {
    for (int v : values)
        func(v);  // Call the function pointer with each value in the vector
}

int main() {
    // Normal function call
    Print();

    // Function pointer usage (auto keyword is useful for function pointers)
    auto function = Print;  // Assign the function's address to the variable
    function();  // Call the function using the pointer

    // Traditional way of declaring a function pointer (without auto)
    typedef void(*func)();  // Alias for a function pointer type
    func ffunction = Print;  // Assign Print to the function pointer
    ffunction();  // Call the function using the pointer

    // Function pointer with input parameters
    typedef void(*funcwint)(int);  // Alias for function pointer with int input
    funcwint function2 = PrintWInput;  // Assign PrintWInput to the pointer
    function2(5);  // Call the function with argument 5
    function2(10); // Call the function with argument 10

    // Example of passing a function pointer to another function
    std::vector<int> values = { 1, 2, 4, 5 };
    ForEach(values, PrintValue);  // Pass the PrintValue function as a pointer

    // Problem: We need to explicitly define PrintValue as a function
    // Solution: Use a lambda function (inline anonymous function)
    ForEach(values, [](int v) { std::cout << "Value: " << v << std::endl; });  // Lambda function as a function pointer

    return 0;
}
