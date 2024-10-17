// Lambda functions - Anonymous, quick, disposable functions.
// Lambda functions can be used anywhere function pointers are used.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // For std::find_if
#define LOG(x) std::cout << x << std::endl

// Function that accepts a function pointer (or lambda) and applies it to each element in the vector
void ForEach(const std::vector<int>& values, void(*func)(int)) {
    for (int v : values)
        func(v);  // Call the function (or lambda) for each value
}

// Main function demonstrating the use of lambdas
int main() {
    std::vector<int> values = { 1, 2, 4, 5 };

    // Lambda function - [ captures ](intpt) { function body }
    auto lambda = [](int v) { std::cout << "Value: " << v << std::endl; };
    ForEach(values, lambda);  // Pass lambda to the ForEach function

    // Capturing external variables in lambda functions
    int a = 5;

    // Lambda capture examples:
    auto lambdaval = [=](int v) { std::cout << "Value (by value capture): " << a << std::endl; };  // Capture by value
    auto lambdaref = [&](int v) { std::cout << "Value (by reference capture): " << a << std::endl; };  // Capture by reference
    auto lambdavala = [a](int v) { std::cout << "Value (only a by value): " << a << std::endl; };  // Capture only a by value
    auto lambdarefa = [&a](int v) { std::cout << "Value (only a by reference): " << a << std::endl; };  // Capture only a by reference

    // Example of using lambda for conditional checks
    std::vector<int> values2 = { 1, 2, 4, 5 };
    
    // Using std::find_if with a lambda to find the first value greater than 3
    auto it = std::find_if(values2.begin(), values2.end(), [](int v) { return v > 3; });
    
    if (it != values2.end()) {  // Ensure that the element was found
        std::cout << "First value greater than 3: " << *it << std::endl;  // Output: 4
    }

    return 0;
}
