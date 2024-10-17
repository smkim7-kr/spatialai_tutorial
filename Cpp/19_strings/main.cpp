// Strings - group of characters
#include <iostream>
#include <string>
#include <cstring> // for strlen
#define Log(x) std::cout << x << std::endl;

void Print(const std::string& string) { 
    // Passing strings by const reference to avoid copying and ensure immutability
    Log(string);
}

int main() {
    // char - 8 bits
    // A single char can hold 256 different values (2^8), but this is insufficient to represent all languages, leading to variants like UTF-16.
    // "Normal" char - 1 byte = 8 bits
    // A string is essentially an array of chars (characters)
    const char* name = "George"; // C-style string (const char array)
    strlen(name);  // Get the length of the string (excluding null terminator)
    // name[1] = 'a'; // Error: cannot modify because 'name' is a const pointer

    // C-style strings are stored as contiguous blocks of memory, ending with a null termination character ('\0')
    // This character signals the end of the string, so the computer knows when to stop reading the array.
    char name2[6] = { 'G', 'e', 'o', 'r', 'g', 'e' };  // No null terminator, computer cannot determine where the string ends
    char rightname2[7] = { 'G', 'e', 'o', 'r', 'g', 'e', '\0' };  // Correct: null terminator included

    // C++ std::string
    // std::string provides a more robust and user-friendly interface for handling strings
    std::string name3 = "George";  // std::string can be modified, unlike const char arrays
    Log(name3);
    name3.size();  // Get the length of the string (built-in function in std::string)

    // Appending strings
    // std::string supports operator overloading for concatenation
    std::string right1 = "Hello";
    right1 += " World!";  // += operator is overloaded in std::string, allowing easy concatenation
    std::string right2 = std::string("Hello") + " World!";  // Concatenation using +
	// std::string right3 = "Hello" + "World!"; // const char * + const char * isn't possible

    // Searching within strings
    bool contains = right2.find("lo") != std::string::npos;  // Checks if the substring "lo" exists

    return 0;
}
