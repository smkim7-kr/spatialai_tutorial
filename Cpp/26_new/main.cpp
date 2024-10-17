// The new keyword: allocates continuous free memory of the requested size in the heap
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

	int GetX(){
		return m_x;
	}
};

int main() {
    // The new keyword is an operator that allocates memory in the heap
    int a = 2;  // Stack allocation

    int* b = new int;  // Allocates 4 bytes (for an int) in the heap
    int* c = new int[50];  // Allocates memory for 50 integers (200 bytes) in the heap

    delete b;  // Frees the memory allocated for b
    delete[] c;  // Frees the array of integers

    // Allocating memory for an object using new
    Robot* r = new Robot();  // Allocates memory for Robot + calls the default constructor
    // C-style memory allocation (not recommended in C++):
    // Robot* r = (Robot*)malloc(sizeof(Robot)); 
    // This only allocates memory and does NOT call the constructor (not C++ style).

    Robot* r2 = new Robot[30];  // Allocates memory for 30 Robot objects (using default constructor for each)

    // Placement new: special operator that places the object in a pre-allocated memory area
    Robot* r3 = new(r2) Robot();  // This reuses the memory from r2 for the new Robot
    std::cout << (bool)(r2 == r3) << std::endl;  // Checks if r2 and r3 point to the same memory location
	std::cout << r3[2].GetX() << std::endl; 

    delete r;  // Frees memory for the first Robot
    delete[] r2;  // Frees memory for the array of Robots


    return 0;
}
