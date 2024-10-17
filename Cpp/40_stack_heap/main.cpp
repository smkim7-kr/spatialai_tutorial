// Stack memory vs Heap memory
// Stack: Fast, fixed-size memory allocation. Automatically managed (freed when scope ends).
// Heap: Dynamic memory allocation. Can change size, but slower and requires manual management.

#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;
public:
    // Constructors
    Robot() : m_x(0), m_y(0) {}
    Robot(int x, int y) : m_x(x), m_y(y) {}
};

int main() {
    // Stack allocation (fast, fixed-size)
    int sval = 5;  // Stack-allocated integer
    int sarr[5];   // Stack-allocated array
    Robot sr;      // Stack-allocated Robot object

    // Stack allocations are fast because they only require a single CPU instruction
    // to increment the stack pointer. Variables allocated on the stack are typically
    // close together in memory and freed automatically when the function (scope) ends.

    // Heap allocation (dynamic, slower)
    // When 'new' is called, underlying 'malloc' or similar functions are called to allocate memory.
    // Heap allocation involves searching for free memory, bookkeeping, etc., making it slower.

    int* hval = new int;  // Dynamically allocated integer on the heap
    *hval = 5;
    int* harr = new int[5];  // Dynamically allocated array on the heap
    Robot* hr = new Robot(); // Dynamically allocated Robot object on the heap

    // Heap allocations are slower because of the complexity involved in finding
    // free memory and managing allocations. Heap-allocated variables are not
    // guaranteed to be close to each other in memory.

    // Remember to free heap memory when done using 'delete' to avoid memory leaks
    delete hval;       // Free dynamically allocated integer
    delete[] harr;     // Free dynamically allocated array
    delete hr;         // Free dynamically allocated Robot object

    // Stack vs Heap performance:
    // Stack allocation is faster because it involves simply adjusting the stack pointer.
    // Heap allocation is slower due to more complex operations (memory search, bookkeeping).
    // Accessing heap memory can also result in cache misses, further slowing down performance.

    // When scope ends, stack-allocated objects are automatically freed.
    
    return 0;
}
