// Copying data/memory occurs a lot in C++
// Avoid unnecessary copying because it incurs overhead
#include <iostream>
#include <string>
#include <cstring>
#define Log(x) std::cout << x << std::endl;

struct Vec2 {
    int x, y;
};

class String {
private:
    char* m_Buffer;
    unsigned int m_Size;

public:
    // Constructor to initialize the string
    String(const char* string) {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];  // +1 for null termination character
        memcpy(m_Buffer, string, m_Size);
        m_Buffer[m_Size] = 0;  // Null-terminate the string
    }

    // Copy constructor - deep copy to avoid sharing memory
    String(const String& other)
        : m_Size(other.m_Size)
    {
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    // Destructor to free memory
    ~String() {
        delete[] m_Buffer;
    }

    // Operator[] for element access
    char& operator[](unsigned int index) {
        return m_Buffer[index];
    }

    // Friend function to allow access to private members for printing
    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

// Overloading the << operator for printing String objects
std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream << string.m_Buffer;  // Access the private member m_Buffer directly
    return stream;
}

// Function that causes unnecessary copying (by value)
void PrintString(String string) {
    std::cout << string << std::endl;
}

// Function that avoids copying (by reference)
void PrintStringRef(const String& string) {
    std::cout << string << std::endl;
}

int main() {
    // Assignment operator = always copies values (unless dealing with pointers)
    int a = 2;
    int b = a;  // 'a' and 'b' have different memory addresses

    Vec2 v1 = { 0, 0 };
    Vec2 v2 = v1;  // Struct copy: 'v1' and 'v2' have different memory addresses

    Vec2* pv1 = new Vec2();  // Heap allocation
    Vec2* pv2 = pv1;  // Copying the pointer, 'pv1' and 'pv2' point to the same memory address

    // Default copy constructors does shallow copay

    // Self-defined String class
    String string = "George";
    String str2 = string;  // Solution: deep copy - each String reserves its own memory, so changes don't affect the other
    str2[2] = 'a';  // Modifying 'str2' not also modifies 'string' because of deep copy, each of them reserves seperate memory
    PrintString(string);   // Causes an unnecessary copy
    PrintString(str2);     // Causes an unnecessary copy
    PrintStringRef(string); // Prevents copy, passes by reference
    PrintStringRef(str2);   // Prevents copy, passes by reference

    return 0;
}
