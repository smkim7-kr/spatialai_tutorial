// Operator overloading: redefine/change the behavior of operators (use only when it makes logical sense)
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

struct Vec3 {
    float x, y, z;

    // Constructor to initialize the Vec3 object
    Vec3(float x, float y, float z)
        : x(x), y(y), z(z) {}

    // Method to add two vectors
    Vec3 Add(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Overloading the + operator to add two Vec3 objects
    Vec3 operator+(const Vec3& other) const {
        return Add(other);  // Alternatively: return Vec3(x + other.x, y + other.y, z + other.z);
    }
};

// Overloading the << operator to print Vec3 objects
std::ostream& operator<<(std::ostream& stream, const Vec3& pos) {
    stream << pos.x << ", " << pos.y << ", " << pos.z;  // Stream outputs the Vec3's components
    return stream;
}

int main() {
    Vec3 position(3.0f, 1.5f, 0.1f);
    Vec3 speed(0.4f, 0.5f, 0.3f);
    
    // Using the Add method to add two Vec3 objects
    Vec3 newpos = position.Add(speed);
    
    // Operator + overloading makes the code cleaner
    Vec3 goodpos = position + speed;

    // Overloading the << operator allows us to print the Vec3 object easily
    std::cout << goodpos << std::endl;  // Outputs: 3.4, 2, 0.4

    return 0;
}
