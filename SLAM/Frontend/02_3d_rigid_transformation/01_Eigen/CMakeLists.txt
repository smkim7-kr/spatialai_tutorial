# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Define the project name and programming language
project(MyEigenProject)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Eigen's include directory manually (assuming Eigen is installed in /usr/include/eigen3)
include_directories(/usr/include/eigen3)

# Add the executable from the main.cpp file
add_executable(MyEigenApp main.cpp)

