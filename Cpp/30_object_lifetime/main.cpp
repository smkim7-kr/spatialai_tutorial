// Stack vs Heap
// Stack-based variables are destroyed when their scope ends (function, if statement, loop, or any scope {})
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;  // Member variables in class scope
public:
    Robot()
        : m_x(0), m_y(0)
    {
        std::cout << "Created Entity" << std::endl;
    }

    ~Robot() {
        std::cout << "Destroyed Entity" << std::endl;
    }
};

// This function is incorrect
int* CreateArray() {
    int array[50];  // Allocated on the stack
    return array;  // Returning a pointer to stack memory (dangerous, as memory is freed after function ends)
}

int* CreateArraySol() {
    // Solution 1: Allocate array on the heap
    int* array = new int[50];  // Dynamically allocated on the heap, memory persists until explicitly deleted
    return array; 
}

void CreateArraySol2(int* array) {
    // Solution 2: Pass the array as an argument to avoid stack issues
}

class ScopedPtr {  // This simulates a simple smart pointer: automatically manages memory
private:
    Robot* m_r;
public:
    // Constructor
    ScopedPtr(Robot* r)
        : m_r(r) {}

    // Destructor automatically deletes the managed object
    ~ScopedPtr() {
        delete m_r;
    }
};

int main() {
    {
        Robot r;  // Created on the stack
    }  // "Destroyed Entity" is called here when the scope ends

    {
        Robot* r = new Robot();  // Created on the heap
    }  // Not destroyed here (memory leak)

    // Incorrect usage: returns pointer to already freed stack memory
    int* a = CreateArray();  // 'a' points to invalid memory, undefined behavior

    // Correct usage: array allocated on the heap
    int* b = CreateArraySol();  // 'b' points to valid memory

    // Passing an array as an argument
    int* arr = new int[50];  // Array allocated on the heap
    CreateArraySol2(arr);  // Using array safely

    // ScopedPtr simulates smart pointer behavior, managing memory automatically
    {
        ScopedPtr sptr = new Robot();  // sptr manages the Robot pointer
    }  // "Destroyed Entity" called automatically when sptr goes out of scope

    return 0;
}
