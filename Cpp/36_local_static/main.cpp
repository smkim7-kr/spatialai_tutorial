// Two considerations when declaring a variable:
// 1) Lifetime: How long the variable will remain in memory.
// 2) Scope: Where the variable can be accessed.

// A static local variable's lifetime lasts until the end of the program, but its scope is limited to the block in which it is declared.

#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

// Global variable (lifetime: entire program, scope: everywhere)
int globalVar = 0;

void foo() {
    // Static local variable: 
    // - Lifetime: until the program ends (initialized only once)
    // - Scope: limited to this function
    static int i = 0;
    i++;  // Increment the static variable
    Log(i);  // Outputs the value of i
}

// Singleton class: allows only one instance of the class
class Singleton {
private:
    static Singleton* s_instance;  // Pointer to the singleton instance

public:
    // Returns a reference to the single instance of the class
    static Singleton& Get() {
        return *s_instance;
    }

    void foo() {
        // Example function in Singleton
    }
};

// External definition of Singleton's static instance pointer
Singleton* Singleton::s_instance = nullptr;

// Better Singleton class using static local variables
class StaticSingleton {
public:
    // Returns a reference to the static instance
    static StaticSingleton& Get() {
        static StaticSingleton instance;  // Static local variable, initialized once, lifetime until program ends
        return instance;
    }
};

int main() {
    foo();  // i = 1 (static i is incremented)
    foo();  // i = 2 (static i retains its value between calls)
    foo();  // i = 3

    // Accessing Singleton (classic approach)
    Singleton::Get().foo();  // Requires external setup, which can be cumbersome

    // Accessing StaticSingleton (modern approach)
    StaticSingleton::Get();  // No need for external initialization, more elegant

    return 0;
}
