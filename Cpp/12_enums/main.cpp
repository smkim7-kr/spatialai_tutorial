// Enumerators (enums): Grouping constants with integral values with logical sense
#include <iostream>
#define Log(x) std::cout << x << std::endl;

// Ungrouped variables
int a = 0;
int b = 1;
int c = 2; 

// Logically grouped using enum
enum Choice { // By default, enum uses 32-bit integers
    A,  // 0
    B,  // 1
    C   // 2
};

enum Choice2 { 
    A2 = -1,  // Explicitly setting values to avoid conflicts with other enums
    B2 = 4, 
    C2 = 9
};

enum Choice3 : unsigned char { // Using unsigned char for memory optimization
    A3 = 5, 
    B3,  // B3 becomes 6
    C3   // C3 becomes 7
};

enum Choice4 { 
    A4 = 7, 
    B4,  // B4 becomes 8
    C4   // C4 becomes 9
};

int main() {
    Choice choice = B;  // Assigning value from the enum
    if (choice == 1) {  // Compare the enum value directly
        Log("This will be printed");
    }

    Log(Choice4::C4);  // Prints the value of C4, which is 9

    return 0;
}
