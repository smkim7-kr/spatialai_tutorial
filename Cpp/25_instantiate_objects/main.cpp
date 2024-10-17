// Stack and Heap in C++
// Stack objects: automatic lifespan (live within the scope)
// Heap objects: lifespan is manually controlled by the programmer
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    int m_x, m_y;
public:
    // Default constructor
    Robot()
        : m_x(0), m_y(0)
    {}

    // Parameterized constructor
    Robot(int x, int y)
        : m_x(x), m_y(y)
    {}

    // Getter for x position
    const int GetPositionX() const { return m_x; }
};

void newScope() {
    Robot localr(4, 5);  // Stack-allocated object
}  // localr is destroyed when the scope ends

int main() {
    // Stack allocation: use this whenever possible for speed and efficiency
    Robot r;  // Calls default constructor
    int x = r.GetPositionX();  // x = 0

    Robot r2(3, 4);  // Calls parameterized constructor
    int x2 = r2.GetPositionX();  // x2 = 3

    std::cout << x << ", " << x2 << std::endl;

    // Heap allocation: use when you need the object to outlive the scope
    // or when dealing with large objects (stack memory is limited)
    Robot* robotptr;
    {   
        Robot pr(7, 8);  // Stack-allocated object, destroyed when {} scope ends
        Robot* pr2 = new Robot(3, 4);  // Heap-allocated object
        robotptr = pr2;
        Log(robotptr->GetPositionX());  // Prints position of heap-allocated object
        delete pr2;  // Frees the memory allocated for pr2
    }  // pr is destroyed here as it is stack-allocated

    // Clean up heap memory
    delete robotptr;  // Manually delete heap-allocated object

    return 0;
}
