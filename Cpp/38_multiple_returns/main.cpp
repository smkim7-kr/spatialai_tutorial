// Best way - return using struct for clarity and maintainability
#include <iostream>
#include <string>
#include <array>
#include <tuple>  // To use tuple
#define Log(x) std::cout << x << std::endl;

// Method 1: Pass multiple outputs by reference
void multipleReturns(int& a, std::string& str) {
    a = 2;
    str = "Bad";
}

// Method 1': Improvement - Pass pointers (can optionally update based on non-null pointers)
void multipleReturnspPtr(int* aout, std::string* strout) {
    if (aout)
        *aout = 10;
    if (strout)
        *strout = "Not good yet";
}

// Method 2: Return an array
static std::array<std::string, 2> multipleReturnspArray() {
    std::array<std::string, 2> outputs = { "Hello", "World!" };
    return outputs;
}

// Method 3: Return a tuple
static std::tuple<std::string, std::string> multipleReturnspTuple() {
    return std::make_tuple("Hello", "World!");
}

// Method 3: Return a pair
static std::pair<std::string, std::string> multipleReturnspPair() {
    return std::make_pair("Hello", "World!");
}

// Method 4: Return using a struct (Best way)
struct StrInt {
    std::string name;
    int size;
};

static StrInt multipleReturnsStruct() {
    return { "Hello", 6 };  // Initialize struct directly
}

int main() {
    // Method 1: Pass by reference, function modifies variables
    int a1 = 3;
    std::string str1 = "Method1";
    multipleReturns(a1, str1);
    Log(a1);  // Outputs 2
    Log(str1);  // Outputs "Bad"

    // Method 1': Using pointers for optional updates
    multipleReturnspPtr(&a1, &str1);
    Log(a1);  // Outputs 10
    Log(str1);  // Outputs "Not good yet"

    // Method 2: Return an array
    auto arr = multipleReturnspArray();
    Log(arr[0]);  // Outputs "Hello"
    Log(arr[1]);  // Outputs "World!"

    // Method 3: Return a tuple
    std::tuple<std::string, std::string> t = multipleReturnspTuple();
    std::cout << std::get<0>(t) << ", " << std::get<1>(t) << std::endl;  // Access by index (not very clear)

    // Method 3: Return a pair
    auto p = multipleReturnspPair();
    std::cout << p.first << ", " << p.second << std::endl;  // Still unclear what 'first' and 'second' represent

    // Method 4: Returning a struct (best approach)
    StrInt si = multipleReturnsStruct();
    std::cout << si.size << ": " << si.name << std::endl;  // Access through names, clearer and more maintainable

    return 0;
}
