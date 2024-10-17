// Optimizing vector usage
// Avoid unnecessary copying and dynamic resizing of vectors
#include <iostream>
#include <string>
#include <vector>
#define Log(x) std::cout << x << std::endl;

struct Vec3 {
    int x, y, z;

    // Constructor
    Vec3(int x, int y, int z)
        : x(x), y(y), z(z) 
    {}

    // Copy constructor
    Vec3(const Vec3& other)
        : x(other.x), y(other.y), z(other.z) 
    {
        std::cout << "Copied!" << std::endl;  // Indicate when a copy is made
    }
};

int main() {
    // Initial approach: standard push_back causes multiple copies
    std::vector<Vec3> vectors;
    vectors.push_back({2, 3, 4});
    vectors.push_back({5, 7, -1});
    vectors.push_back({2, 0, 9});

    // The issue:
    // When using push_back with temporary objects, multiple copies are made.
    // These copies happen because the object is first created in the main function stack,
    // then moved to the vector's memory.

    // Optimization 1: Pre-define the capacity of the vector to avoid reallocations.
    // Optimization 2: Use emplace_back to construct the object directly in vector memory.

	std::cout << "---------" << std::endl;
    std::vector<Vec3> vectors2;
    vectors2.reserve(3);  // Reserve memory for 3 Vec3 objects, avoiding resizing overhead.

    // Using emplace_back constructs the objects directly in vector's memory.
    vectors2.emplace_back(2, 3, 4);  // Directly constructs the Vec3 in vector memory.
    vectors2.emplace_back(5, 7, -1);
    vectors2.emplace_back(2, 0, 9);

    // The advantage of emplace_back is that it avoids extra copies,
    // because the object is constructed directly in place in the vector.

    return 0;
}
