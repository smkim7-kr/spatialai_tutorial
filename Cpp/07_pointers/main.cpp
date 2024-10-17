// Instructions, data, and variables are all stored in memory
// Pointers store memory addresses and are useful for managing memory
#include <iostream>
#include <cstring>  // Include this for memset

int main() {
    // A memory address of 0 is not valid, so it represents null
    void* ptr = 0;            // Void pointer: holds a memory address, but data type is not specified
    void* ptr2 = nullptr;      // nullptr is equivalent to 0 for pointers
    void* ptr3 = NULL;         // NULL is also the same as nullptr

    int var = 8;               // Variable 'var' is stored in memory

    // Pointers store the memory address of variables
    void* ptr4 = &var;         // ptr4 holds the memory address of 'var'
    int* ptr5 = &var;          // Pointer to 'var' with correct type (int*)
    double* ptr6 = (double*)&var; // This works, but it's not type-safe; types of pointers only matter for convenience

    // Dereferencing: accessing or manipulating data through its address
    int* good_ptr = &var;      // Correctly typed pointer
    *good_ptr = 10;            // Dereferencing and modifying 'var' through the pointer
    std::cout << "var changes from 8 to 10: " << var << std::endl;

    // Memory allocation on stack and heap
    char* buffer = new char[8]; // Allocated on the heap (manual memory management)
    memset(buffer, 0, 8);       // Initialize the buffer to zero (8 bytes)
    delete[] buffer;            // Explicitly free heap memory with 'delete'

    char** ptr_buffer = &buffer; // Double pointer: holds the address of a pointer (pointer to pointer)

    return 0;
}
