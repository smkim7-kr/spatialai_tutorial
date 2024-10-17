// Visibility in C++: no direct impact on performance, but helps in organizing code and providing access control
// Three types of visibility: private, protected, and public
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

struct sRobot { // In struct, default visibility is public
    int x, y; // Public by default
};

class Robot { // In class, default visibility is private
private: // Private members can only be accessed within this class
    int X, Y;
    void Print() {}  // Private methods can only be called from within the class

protected: // Protected members can be accessed by this class and its subclasses
    int pX, pY;

public:
    Robot() {  // Public constructor
        X = 2; 
        Y = 1; 
        Print();  // Can call private methods within the class
    }
};

// NameRobot inherits from Robot
class NameRobot : public Robot {
public:
    NameRobot() { 
        pX = 10;  // Can access protected members from Robot
        pY = 20;  
    }

    void PrintName() { 
        Log("Name");  // Public method accessible from anywhere
    }
};

int main() {
    Robot* r = new Robot();
    // r->X = 2;  // Error: Can't access private members from outside the class
    // r->Print(); // Error: Can't access private methods from outside the class

    NameRobot* nr = new NameRobot();
    // nr->pX = 10;  // Error: Can't access protected members from outside the class
    nr->PrintName();  // This is allowed because PrintName() is public

    // Visibility is used for better code readability and maintenance.
    // It signals the developer about how to interact with the class and its members.
    // CPUs and compilers don't understand "private" or "protected"—these are purely for code organization and access control.
    
    return 0;
}
