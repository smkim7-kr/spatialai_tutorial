# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(TransformationMaps VERSION 1.0)

# Set the C++ standard (use C++11 or higher)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(TransformationMaps main.cpp)

# Enable more warnings during compilation (optional, for debugging purposes)
target_compile_options(TransformationMaps PRIVATE -Wall -Wextra -pedantic)
