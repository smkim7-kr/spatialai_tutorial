// Log.cpp file contains definitions of functions declared in Log.h
#include <iostream>
#include "Log.h"

// Function to initialize the logging process
void InitLog() {
    Log("Initialize log");
}

// Function to log a message
void Log(const char* message) {
    std::cout << message << std::endl;
}
