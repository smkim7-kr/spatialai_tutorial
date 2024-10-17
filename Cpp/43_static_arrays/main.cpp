// Static Arrays in C++
// Arrays with constant size after initialization, both new and old styles.
#include <iostream>
#include <string>
#include <array>
#define LOG(x) std::cout << x << std::endl

// Old style: Requires explicit tracking of array size.
void PrintArray(int* array, unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
        std::cout << array[i] << std::endl;
}

// New style: Using std::array. Templates allow size to be determined automatically.
template <std::size_t size>
void PrintNewArray(const std::array<int, size>& data) {
    for (const auto& elem : data)
        std::cout << elem << std::endl;
}

int main() {
    // Both styles are stored on the stack.
    std::array<int, 5> arr = {1, 2, 3, 4, 5};  // New style using std::array
    int oldarr[5] = {1, 2, 3, 4, 5};  // Old style using C-style array

    // The new style (std::array) is preferred because:
    // 1) It keeps track of its own size.
    // 2) It provides iterator support and various methods (e.g., size, begin, end).

    // Print using old-style array
    PrintArray(oldarr, 5);  // Need to manually track and pass the array size.

    // Print using new-style std::array
    PrintNewArray(arr);  // Size is automatically deduced, safer and cleaner.

    // std::array provides methods like size(), begin(), and end().
    std::cout << "Size of new-style array: " << arr.size() << std::endl;

    // Bounds checking in debug mode:
    // arr[5] = 10;  // This would raise an out-of-bounds error if checked.
    // oldarr[5] = 10;  // No bounds checking in C-style arrays, might silently corrupt memory.

    return 0;
}
