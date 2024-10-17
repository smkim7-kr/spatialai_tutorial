// Virtual functions: allow methods in a subclass to overwrite base class methods
#include <iostream>
#define Log(x) std::cout << x << std::endl;

class Robot {
public:
    std::string GetName() { 
        return "Robot"; 
    }
};

class NameRobot : public Robot {
private:
    std::string m_Name;
public:
    // Constructor to initialize the robot's name
    NameRobot(const std::string& name) : m_Name(name) {}

    // Overwriting GetName method (not using virtual here, so base class method is still called when using base class pointer)
    std::string GetName() { 
        return m_Name; 
    }
};

class Robot2 {
public:
    // Virtual function to allow overriding in derived classes
    virtual std::string GetName() { 
        return "Robot"; 
    }
};

class NameRobot2 : public Robot2 {
private:
    std::string m_Name;
public:
    // Constructor to initialize the robot's name
    NameRobot2(const std::string& name) : m_Name(name) {}

    // Overriding the base class function using 'override' keyword (optional, but recommended)
    std::string GetName() override { 
        return m_Name; 
    }
};

int main() {
    // Example without virtual function
    Robot* r = new Robot();
    NameRobot* nr = new NameRobot("AlphaGo");
    Log(r->GetName());   // Prints: "Robot"
    Log(nr->GetName());  // Prints: "AlphaGo"

    Robot* r2 = nr;  // Base class pointer, still calls the base class function
    Log(r2->GetName());  // Prints: "Robot" (since Robot::GetName() is called, not NameRobot's)

    // Example with virtual function
    Robot2* vr = new Robot2();
    NameRobot2* vnr = new NameRobot2("AlphaGo");
    Robot2* vr2 = vnr;   // Base class pointer, but calls the derived class's GetName() due to virtual function
    Log(vr2->GetName()); // Prints: "AlphaGo"

    return 0;
}
