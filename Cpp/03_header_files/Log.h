#pragma once // Ensures the header file is included only once in a single translation unit

// Any other files that need to use the declared functions can include this header file with '#include "Log.h"'

// Declaration of the Log function, which logs a message
void Log(const char* message);

// Declaration of the InitLog function, which initializes the logging process
void InitLog();
