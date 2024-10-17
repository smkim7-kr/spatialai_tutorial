// Inheritance: Creating a hierarchy of classes, allowing subclasses to inherit functionality from a base class.
// This helps avoid code duplication, as subclasses can share functionalities from the parent class.
#include <iostream>
#define Log(x) std::cout << x << std::endl;

class Robot {
public:
    int x = 0, y = 0;
    double speed = 0.1;

    // Function to move the robot by updating its x and y positions
    void Move(int dx, int dy) {
        x += dx * speed;
        y += dy * speed;
    }
};

// NameRobot extends Robot class, inheriting all functionalities of Robot and adding extra features
class NameRobot : public Robot { // NameRobot is a Robot with additional functionality (Polymorphism)
public:    
    const char* Name;

    // Function to print the robot's name
    void PrintName() {
        std::cout << Name << std::endl;
    }
};

int main() {
    NameRobot nr;
    nr.Move(3, 4); // NameRobot object can call member functions from the parent class (Robot)

    // Size comparison: Inherited class (NameRobot) should have a larger size than the base class (Robot)
    std::cout << sizeof(Robot) << ", " << sizeof(NameRobot) << std::endl; 

    return 0;
}
