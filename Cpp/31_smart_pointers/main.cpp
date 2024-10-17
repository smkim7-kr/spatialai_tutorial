// Smart Pointers - automatic management of new/delete (unique_ptr, shared_ptr, weak_ptr)
// Use smart pointers to avoid manual memory management (new/delete).
// Prefer unique_ptr first, and use shared_ptr only when copying is necessary.

#include <iostream>
#include <string>
#include <memory>  // Required for smart pointers
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;
public:
    Robot() : m_x(0), m_y(0) {}

    Robot(int x, int y) : m_x(x), m_y(y) {}

    int GetX() const {
        return this->m_x;
    }
};

int main() {
    // unique_ptr: Automatically destroyed when it goes out of scope, cannot be copied.
    // Stack-allocated, low overhead.
    { // Empty scope
        std::unique_ptr<Robot> robot(new Robot());
        // std::unique_ptr<Robot> robot = new Robot(); // Not allowed implicitly, must use std::make_unique

        robot->GetX();  // Access member via unique_ptr

        std::unique_ptr<Robot> robot2 = std::make_unique<Robot>();  // Preferred way to create unique_ptr, safer
        robot2->GetX();

        // std::unique_ptr<Robot> r2 = robot; // Copying is disallowed! No two unique_ptrs can point to the same memory.
    } // unique_ptr is destroyed here, and memory is automatically freed

    // shared_ptr: Allows copying (reference counting tracks ownership)
    // Memory is deleted when the reference count reaches 0. Higher overhead than unique_ptr due to reference counting.
    std::shared_ptr<Robot> sharedRobot2;
    {
        std::shared_ptr<Robot> sharedRobot = std::make_shared<Robot>();  // std::make_shared is safer and recommended
        sharedRobot2 = sharedRobot;  // Copying is allowed, both sharedRobot and sharedRobot2 share ownership.
    }  // sharedRobot goes out of scope, but reference count = 1 (still pointed to by sharedRobot2), so memory is not destroyed.

    // weak_ptr: Does not increase the reference count.
    // Used to "observe" shared_ptr without taking ownership of the object.
    std::weak_ptr<Robot> weakRobot;
    {
        std::shared_ptr<Robot> sharedRobot = std::make_shared<Robot>();  // reference count = 1
        weakRobot = sharedRobot;  // weak_ptr does not increase reference count (still = 1)
    }  // sharedRobot goes out of scope, reference count = 0, so the object is destroyed.

    return 0;
}
