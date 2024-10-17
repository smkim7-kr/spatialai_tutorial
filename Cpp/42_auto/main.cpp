// The auto keyword in C++ automatically deduces the type of a variable at compile time.
// It's useful for long-named types or when you're unsure of the type. Avoid using auto for primitive types (e.g., int, float, etc.) for clarity.

#include <iostream>
#include <string>
#include <vector>
#define LOG(x) std::cout << x << std::endl

class Robot {
private:
    int m_x, m_y;
public:
    // Constructors
    Robot() : m_x(0), m_y(0) {}
    Robot(int x, int y) : m_x(x), m_y(y) {}

    // Function to return a reference to m_x
    int& getX() {
        return m_x;
    }
};

// Function that returns a string (could be changed to char* without changing main function)
std::string GetName() {
    return "George";
}

int main() {
    int a = 5;
    auto b = a;  // auto deduces b is of type int
    auto c = 7.2;  // auto deduces c is of type double

    auto name = GetName();  // auto deduces name as std::string
    int a2 = name.size();   // Will cause an error if GetName() returns a char*
    // Pro: Allows easy API changes without changing calling code
    // Con: You might not realize the return type has changed, leading to runtime issues

    // Example with a vector of strings
    std::vector<std::string> strings;
    strings.push_back("Seoul");
    strings.push_back("Tokyo");

    // Traditional way of using a vector iterator (long type)
    for (std::vector<std::string>::iterator it = strings.begin();
        it != strings.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Simplified using auto, avoiding long iterator type declaration
    for (auto it = strings.begin();  // auto deduces the iterator type
        it != strings.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Example with const reference and auto
    Robot r;
    const auto& r_x = r.getX();  // Const and reference (&) should be specified explicitly

    return 0;
}
