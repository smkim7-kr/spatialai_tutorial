// Constructors and Destructors in C++
#include <iostream>
#define Log(x) std::cout << x << std::endl;

class Robot {
public:
    int m_x, m_y;

    // Default constructor: called when no arguments are passed during instantiation
    Robot() { 
        m_x = 0; 
        m_y = 0;
    }

    // Overloaded constructor: allows initializing Robot with specific values for x and y
    Robot(int x, int y) { 
        m_x = x;
        m_y = y;
    }

    // Destructor: called when the object is destroyed, useful for freeing resources (e.g., memory)
    ~Robot() { 
        std::cout << "Bye bye robot!" << std::endl;
    }
};

// Preventing users from instantiating a class
class noInstantiate {
private:
    noInstantiate();  // Method 1: Make the constructor private, so users can't instantiate the class
public:
    // noInstantiate() = delete; // Method 2: Delete the constructor explicitly to prevent instantiation
};

int main() {
    // Robot instantiated using default constructor
    Robot r1;
    std::cout << r1.m_x << ", " << r1.m_y << std::endl; // Outputs: 0, 0

    // Robot instantiated using overloaded constructor
    Robot r2(10, 9);
    std::cout << r2.m_x << ", " << r2.m_y << std::endl; // Outputs: 10, 9

    {
        Robot r3(10, 10);  // r3 is created
    } // r3 goes out of scope here, and its destructor is called

    // noInstantiate() // This will cause a compilation error since the constructor is either private or deleted

    return 0;
}
