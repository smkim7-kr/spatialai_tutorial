# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CoordinateTransforms)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Eigen3 library (required by the project)
find_package(Eigen3 3.3 REQUIRED)

# Add the executable target
add_executable(CoordinateTransforms main.cpp)

# Link the Eigen3 library to the target
target_link_libraries(CoordinateTransforms Eigen3::Eigen)

# Enable warnings for better debugging (optional)
target_compile_options(CoordinateTransforms PRIVATE -Wall -Wextra -pedantic)
