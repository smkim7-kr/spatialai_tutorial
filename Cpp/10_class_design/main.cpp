#include <iostream>
#define Log(x) std::cout << x << std::endl;

class LogSystem {
public:
    // Defining log levels as constants
    const int LogLevelError = 0;
    const int LogLevelInfo = 1;

private: 
    // Private member variable to store the current log level
    int m_loglevel;  // Prefix 'm_' indicates this is a member variable

public:
    // Getter method to retrieve the current log level
    int GetLevel() { 
        return m_loglevel;
    }
    
    // Setter method to update the log level
    void SetLevel(int level) { 
        m_loglevel = level;
    }

    // Logs error messages if the log level allows it
    void Error(const char* message) {
        if (m_loglevel >= LogLevelError) 
            std::cout << "[ERROR]: " << message << std::endl;
    }

    // Logs informational messages if the log level allows it
    void Info(const char* message) {
        if (m_loglevel >= LogLevelInfo)
            std::cout << "[INFO]: " << message << std::endl;
    }
};

int main() {
    LogSystem log;
    log.SetLevel(log.LogLevelError); // Set log level to LogLevelError
    log.Error("Error!");             // This will be printed as it's an error
    log.Info("Info!");               // This will not be printed because log level is set to LogLevelError

    return 0;
}
