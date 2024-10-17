// const keyword: promises that something will not change
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;
    const int* const pm_x;  // A const pointer to a const int (cannot change the value or the address)

public:
    // Constructor to initialize member variables
    Robot(int x, int y, const int* ptr)
        : m_x(x), m_y(y), pm_x(ptr) {
    }

    // const method: this method promises not to modify any member variables
    int GetX() const {
        // m_x = 3; // Error: cannot modify member variable inside a const method
        return m_x;
    }

    // Overloaded GetX: non-const version of the function
    int GetX() {
        return m_x;
    }

    // A method returning a const pointer to a const int (cannot modify content or address)
    const int* const GetPointerX() const {
        return pm_x;
    }

    void SetX(int x) {
        m_x = x;
    }
};

// Function that accepts a const reference to a Robot
void PrintRobot(const Robot& robot) {
    // If GetX() isn't marked as const, this would cause an error
    std::cout << robot.GetX() << std::endl;
}

int main() {
    int a = 5;
    a = 2;  // Variable 'a' can be modified

    // const variable
    const int b = 5;
    // b = 5; // Error: cannot modify a const variable

    const int MAX_CAPACITY = 200;  // const is useful for defining constants

    // Pointers and const
    int* c = new int;  // A non-const pointer
    *c = 2;  // 1) Can change the content of 'c'
    c = &a;  // 2) Can change the address stored in 'c'

    const int* c2 = new int;  // A pointer to a const int (cannot change the content)
    int const* c3 = new int;  // Equivalent to const int* (cannot change the content)
    // *c2 = 3; *c3 = 3; // Error: cannot modify the content

    int* const c4 = new int;  // A const pointer to an int (cannot change the address)
    // c4 = nullptr; // Error: cannot change the address

    const int* const c5 = new int;  // A const pointer to a const int (cannot change both content and address)

    // const in class
    int initial_value = 10;
    Robot* r = new Robot(5, 10, &initial_value); 
    r->SetX(10);  // Modifying m_x through SetX
    PrintRobot(*r);  // Print the value of m_x

    return 0;
}
