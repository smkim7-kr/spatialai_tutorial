// Implicit - automatic conversion (e.g., data conversion)
// Explicit - bans implicit conversions
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;
    std::string name;

public:
    // Default constructor
    Robot()
        : m_x(0), m_y(0), name("None")
    {}

    // Parameterized constructor (implicit)
    Robot(int x, int y)
        : m_x(x), m_y(y), name("None")
    {}

    // Overloaded constructor for string (implicit)
    Robot(std::string name)
        : m_x(-1), m_y(-1), name(name)
    {}

    // Explicit constructor to prevent implicit conversions
    explicit Robot(int x, int y, std::string name)
        : m_x(x), m_y(y), name(name)
    {}

    // Method to print the robot's details
    void Print() const {
        std::cout << m_x << ", " << m_y << ", " << name << std::endl;
    }
};

// Function to print the details of a Robot object
void PrintRobot(const Robot& robot) {
    robot.Print();
}

int main() {
    Robot r(3, 4);  // Calls parameterized constructor
    Robot r2 = { 3, 4 };  // Implicit conversion (using the parameterized constructor)
    
    Robot r3 = std::string("George");  // Implicit conversion (using the string constructor)

    // Implicit conversion in function call, passing {2,4} directly as a Robot object
    PrintRobot({ 2, 4 });  
    
    // Passing a string (allowed due to implicit conversion via the string constructor)
    const std::string str = "George";
    PrintRobot(str);  
    
    // Explicit constructor prevents implicit conversion
    // Robot r4 = {4, 5, "George"};  // Error due to explicit constructor
    Robot r4(4, 5, "George");  // Correct, explicit constructor called directly

    Robot r5 = Robot(4, 5, "George");  // Allowed, even with explicit, as it uses direct initialization

    return 0;
}
