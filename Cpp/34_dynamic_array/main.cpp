// Standard Template Library (STL) - allows users to decide the data type using templates
// std::vector - dynamic array data structure (can resize dynamically)
// Resizing can be slow when the vector's size exceeds its buffer capacity, causing overhead due to reallocation.
#include <iostream>
#include <string>
#include <vector>
#define Log(x) std::cout << x << std::endl;

struct Vec3 {
    int x, y, z;
};

// Overloading the << operator to print Vec3
std::ostream& operator<<(std::ostream& stream, const Vec3& vec3) {
    stream << vec3.x << ", " << vec3.y << ", " << vec3.z;
    return stream;
}

// Function that accepts a vector by reference (avoiding copying)
void foo(const std::vector<Vec3>& v) {}

int main() {
    // Raw array - size cannot be changed dynamically
    Vec3 v[5];
    Vec3* vptr = new Vec3[5];  // Heap allocation for an array of Vec3

    // std::vector - dynamic array (can grow in size)
    std::vector<int> arr;  // Vector of integers
    std::vector<Vec3> vectors;  // Vector of Vec3 objects (stored contiguously in memory)

    // Problem with vector resizing: It can be slow, especially when it has to reallocate memory.
    std::vector<Vec3*> vectorptrs;  // Vector of pointers to Vec3 (heap-allocated)

    // Adding elements to the vector using push_back
    vectors.push_back({2, 3, 4});  // Adds a Vec3 object to the vector
    vectors.push_back({5, 7, -1}); // Adds another Vec3 object

    // Accessing and printing vector elements using a for-loop
    for (int i = 0; i < vectors.size(); i++)
        std::cout << vectors[i] << std::endl;

    // Using a range-based for-loop with reference to prevent copying
    for (const Vec3& v : vectors)
        std::cout << v << std::endl;

    // Erasing the second element from the vector using an iterator
    vectors.erase(vectors.begin() + 1);  // Removes the second element

    // Clearing the entire vector
    vectors.clear();  // Clears all elements from the vector

    return 0;
}
