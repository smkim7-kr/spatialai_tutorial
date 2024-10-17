# CMake minimum version required for this project.
cmake_minimum_required(VERSION 3.10)

# Project name and language.
project(MyProject)

# Specify the C++ standard to use.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory for header files.
include_directories(include)

# Add the library. The first argument is the target name (MyLibrary).
# The second argument is the list of source files for the library.
add_library(MyLibrary src/MyLibrary.cpp)

# Create the first executable from the main.cpp file.
add_executable(MainProgram src/main.cpp)

# Create the second executable from another_main.cpp file.
add_executable(AnotherProgram src/another_main.cpp)

# Link the second executable (AnotherProgram) to the library (MyLibrary).
target_link_libraries(AnotherProgram PRIVATE MyLibrary)

