// Arrays - collection of variables (usually of the same type)
#include <iostream>
#include <string>
#include <array>
#define Log(x) std::cout << x << std::endl;

int main() {
    // Array of 5 integers (on the stack)
    int example[5];
    example[2] = 10;  // Set the third element to 10
    // example[5] // WARNING: Accessing out of bounds, this can lead to undefined behavior!

    // Arrays store data contiguously in memory
    for (int i = 0; i < 5; ++i)
        example[i] = 10;  // Accesses memory based on offset (i * sizeof(int))

    // Arrays can be treated as pointers
    int* ptr = example;  // Pointer to the first element of the array
    *(ptr + 2) = 6;      // Same as example[2] = 6
    *(int*)((char*)ptr + 8) = 6;  // Also modifies example[2] using pointer arithmetic (8 bytes = 2 * sizeof(int))

    // Array allocated on the heap
    int* heaparray = new int[5];  // Dynamically allocate an array on the heap
    for (int i = 0; i < 5; ++i)
        heaparray[i] = 10;
    delete[] heaparray;  // Always free dynamically allocated memory with delete[]

    // Stack arrays are preferred over heap arrays due to lower overhead and better performance

    // C++11 array
    // For regular arrays, there is no direct way to find the size
    int a[5]; 
    int count = sizeof(a) / sizeof(int);  // Correctly finds the size of the array (5 elements)
    
    int* b = new int[5]; 
    sizeof(b);  // Incorrect: this returns the size of the pointer, not the array size

    // Use a static const size for arrays if you need the size available later
    static const int size = 5; 
    int sizeKnownArray[size];

    // C++11 std::array - safer and provides additional functionality, though slightly slower than raw arrays
    std::array<int, 5> newArray;
    newArray.size();  // Provides the size of the array directly

    return 0;
}
