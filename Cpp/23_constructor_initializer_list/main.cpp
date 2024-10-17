// Constructor initializer list: use it to initialize member variables for better performance
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;  // Member variables
public:
    // Default constructor using initializer list
    Robot()
        : m_x(0), m_y(0)  // Initializes member variables directly
    {}

    // Parameterized constructor using initializer list
    Robot(int x, int y)
        : m_x(x), m_y(y)  // Initializes member variables with given values
    {
        // Initializing variables here would mean an extra step of default construction
        // m_x = x; // This would initialize m_x twice (once to 0 and again to x)
    }
};

int main() {
    // Constructor initializer list avoids the overhead of initializing members twice
    Robot r;  // Calls default constructor
    Robot r2(10, 20);  // Calls parameterized constructor

    return 0;
}
