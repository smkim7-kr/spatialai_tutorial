// static keyword in C++: 
// 1) Outside a class/struct: limits the visibility of a symbol/variable to the current translation unit.
// 2) Inside a class/struct: makes a variable/method shared among all instances of the class/struct.

#include <iostream>
#define Log(x) std::cout << x << std::endl;

int s_var = 10;  // Global variable in this file (main.cpp)

// Why use static?
// - To avoid name conflicts with global variables across different translation units.
// - Make variables static unless they need to be linked across multiple files.

struct Robot {
    int x, y;  // Instance-specific variables
    void Print() {
        std::cout << x << ", " << y << std::endl;
    }
};

// Static variables in a struct: shared among all instances of the struct
struct s_Robot {
    static int x, y;  // Static variables are shared across all instances of s_Robot
    void Print() {
        std::cout << x << ", " << y << std::endl;
    }
};

// Static variables must be initialized outside the struct/class definition
int s_Robot::x;
int s_Robot::y;

int main() {
    Log(s_var);  // Prints the value of s_var, declared in this file

    // Instance of Robot (each instance has its own x and y)
    Robot r1 = { 0, 7 };
    r1.Print();  // Prints: 0, 7

    Robot r2 = { -1, 3 };
    r2.Print();  // Prints: -1, 3

    // Instances of s_Robot (static variables are shared between instances)
    s_Robot sr1;
    sr1.x = 0; sr1.y = 7;

    s_Robot sr2;
    sr2.x = -1; sr2.y = 3;

    sr1.Print();  // Prints: -1, 3 (static variables shared, so sr1 sees changes made by sr2)
    sr2.Print();  // Prints: -1, 3

    // Access static variables directly using the struct name
    std::cout << s_Robot::x << ", " << s_Robot::y << std::endl;  // Prints: -1, 3

    return 0;
}
