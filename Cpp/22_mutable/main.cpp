// mutable keyword: used in two main cases 1) with const methods 2) with lambdas
// mutable means something that can change, even in contexts where immutability is expected
#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
    mutable int m_x = 1, m_y = 2;  // mutable variables can be modified even in const methods
    mutable int m_DebugCount = 0;  // Used for tracking purposes, mutable allows modification in const methods

public:
    // const method: can modify mutable members
    int GetX() const {
        m_x = 3;  // Allowed because m_x is mutable
        m_DebugCount++;  // Also allowed because m_DebugCount is mutable
        return m_x;
    }

    // Non-const method: can modify any member variable
    int GetY() {
        m_y = 5;
        m_DebugCount++;
        return m_y;
    }
};

int main() {
    const Robot r1;  // A const Robot object
    r1.GetX();  // Calls the const method GetX(), which can modify mutable members
    // r1.GetY();  // Error: cannot call non-const methods on a const object

    // Mutable with lambdas (a rare case)
    int x = 8;
	// without mutable, changing x will call error
    auto f = [=]() mutable {  // [=] means capture by value, mutable allows modification of captured variables
        x++;  // Modifies the local copy of x (doesn't affect the original x outside the lambda)
        Log("Hello");
    };
    f();  // Calls the lambda and increments the local copy of x

    return 0;
}
