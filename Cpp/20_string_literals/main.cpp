#include <iostream>
#include <string>
#include <cstring> // for strlen
#define Log(x) std::cout << x << std::endl;

int main() {
    // String literals - by default const char[] (extra character is the null terminator '\0')
    const char name[9] = "Ger\0rge";  // '\0' ends the string early, so it only prints "Ger"
    Log(name); // Only prints: Ger
    std::cout << "Length of name: " << strlen(name) << std::endl; // Prints: 3

    // Modifying string literals stored in read-only memory results in an error.
    // To avoid the const constraint, use a char array or cast it.
    char* gname = (char*)"George";  // Cast string literal into char* to allow modification (though not recommended)

    // Different char types in C++
    const wchar_t* name2 = L"George";      // Wide character string (wchar_t is 2 or 4 bytes depending on the compiler)
    const char16_t* name3 = u"George";     // UTF-16 encoded string (2 bytes per character)
    const char32_t* name4 = U"George";     // UTF-32 encoded string (4 bytes per character)
    
    // C++14 String literals
    using namespace std::string_literals;  // Enables "s" suffix for std::string literals
    std::string newoption = "Hello"s + "World!";  // Using "s" to concatenate strings
    std::wstring ws = L"Hello"s + L"World!";      // Wide string with "s" suffix

    // Raw string literals
    const char* example = R"(L1
        L2
        L3
        L4)"; // Raw strings ignore escape characters and can span multiple lines
    std::cout << example << std::endl;

    // Modifiable char array (not read-only memory)
    char ex[] = "What";  // No const needed for char arrays (not pointers)
    ex[2] = 'e';         // Modifying a character in the array (now it becomes "Whet")
    Log(ex);             // Prints: Whet

    return 0;
}
