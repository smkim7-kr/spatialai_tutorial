#include <iostream> // Includes the iostream library (standard library) during the preprocessor step
#include "Log.h"    // Includes the local Log.h file using the relative path

// Note: Use angle brackets <> for system header files (e.g., <iostream>)
//       Use double quotes "" for local header files (e.g., "Log.h")

int main() {
    // Initialize logging and log a message
    InitLog();
    Log("Hello world!");

    return 0;
}
