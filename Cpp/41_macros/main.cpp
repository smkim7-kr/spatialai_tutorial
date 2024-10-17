// Macros vs Templates
// Macros: Use the preprocessor to automate a process (replace arguments with defined expressions)
// Templates: Evaluated at compile time, macros are just pure text replacement.
// Avoid overusing macros as they can lead to confusing or error-prone code.

#include <iostream>
#include <string>

// Simple macro to replace std::cin.get() - Avoid using such macros as they can confuse users
#define WAIT std::cin.get()

// Macro to log information, better usage since it simplifies logging
#define LOG(x) std::cout << x << std::endl

// Modify macro behavior depending on build mode (Debug vs Release)
// Define PR_DEBUG in Debug mode and PR_RELEASE in Release mode in your project settings:
// Project >> Properties >> C/C++ >> Preprocessor >> Preprocessor Definitions
#ifdef PR_DEBUG
    // In Debug mode, log output is enabled
    #define LOG(x) std::cout << x << std::endl
#else
    // In Release mode, log output is disabled (no logging)
    #define LOG(x) 
#endif

// Example of using #if and #endif to conditionally compile blocks of code
#if 0
// This code will not be compiled because #if 0 disables the block
#endif

// Multi-line macro example (avoid space before or after the backslash)
#define MAIN int main()\
{\
    std::cin.get();\
}

int main() {
    WAIT; // Example of a bad macro usage. Avoid macros like this as they obscure intent.
    LOG("George"); // A better use of macros. Simplifies logging in debug mode but can be turned off in release mode.
}
