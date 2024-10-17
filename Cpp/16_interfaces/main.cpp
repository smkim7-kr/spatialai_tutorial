// Interfaces in C++: Pure virtual functions guarantee that derived classes implement certain functions
// A class with pure virtual functions cannot be instantiated directly; it serves as an interface.
#include <iostream>
#define Log(x) std::cout << x << std::endl;

class Printable {
public:
    // Pure virtual function (interface): forces derived classes to implement this method
    virtual std::string GetClassName() = 0; 
};

// Inheriting from Printable to enforce implementation of the GetClassName() method
class Robot : public Printable { 
public:
    // Another pure virtual function that must be implemented by derived classes
    virtual std::string GetName() = 0;

    // Implements the interface from Printable
    std::string GetClassName() override { 
        return "Robot"; 
    }
};

class NameRobot : public Robot {
private:
    std::string m_Name;
public:
    // Constructor to initialize the robot's name
    NameRobot(const std::string& name) : m_Name(name) {}

    // Must override and define the pure virtual method from the Robot class
    std::string GetName() override { 
        return m_Name; 
    }

    // Optionally override GetClassName() to provide a custom implementation for NameRobot
    std::string GetClassName() override { 
        return "NameRobot"; 
    }
};

// Function that takes a Printable object (supports polymorphism)
void PrintClass(Printable* obj) {
    std::cout << obj->GetClassName() << std::endl; // Uses polymorphism to call the correct GetClassName()
}

int main() {
    // Robot* r = new Robot(); // Error: Cannot instantiate Robot because it has pure virtual functions
	
    Robot* r = new NameRobot("AlphaGo");  // NameRobot can be instantiated because it implements all pure virtual functions
    NameRobot* nr = new NameRobot("Nuro");

    PrintClass(r);  // Prints: NameRobot (since NameRobot overrides GetClassName)
    PrintClass(nr); // Prints: NameRobot

    // PrintClass(new Printable()) // Error: Cannot instantiate Printable as it is an interface

    return 0;
}
