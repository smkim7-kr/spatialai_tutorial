// The "this" keyword: a pointer to the current class object
// Accessible only within member functions of a class
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot;

// Forward declarations of external functions
void PrintRobot(Robot* r);
void PrintRobotRef(const Robot& r);

class Robot {
public:
    int m_x = 0, m_y = 0;

    // Constructor that uses the "this" keyword
    Robot(int x, int y) {
        Robot* r = this;  // "this" is a pointer to the current object
        r->m_x = x;  // Accessing member variables using "this"
        r->m_y = y;  // Alternative: this->m_x = x;

        // Call external functions and pass "this" pointer
        PrintRobot(this);  // Pass this object to a function by pointer
        PrintRobotRef(*this);  // Pass this object to a function by reference

        // delete this; // Avoid doing this, freeing memory inside a member function can cause issues
    }

    // Alternative constructor using initializer list
    // Robot(int x, int y) : m_x(x), m_y(y) {}

    // Using "this" in const methods
    int GetX() const {  // In const methods, "this" is a pointer to a const object
        const Robot* r = this;  // "this" must be a pointer to const in const methods
        // r->m_x = 5;  // Error: cannot modify members in const methods
        return r->m_x;
    }
};

// Function that prints Robot using pointer
void PrintRobot(Robot* r) {
    std::cout << r->m_x << ", " << r->m_y << std::endl;
}

// Function that prints Robot using reference
void PrintRobotRef(const Robot& r) {
    std::cout << r.m_x << ", " << r.m_y << std::endl;
}

int main() {
    // Create a Robot object
    Robot r(10, 20);  // Constructor automatically calls PrintRobot and PrintRobotRef

    return 0;
}
