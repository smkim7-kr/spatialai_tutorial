# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define the project name and set the language to C++
project(CameraCoordinateTransformation)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the Eigen library (assuming it is installed in /usr/include/eigen3)
# If Eigen is installed in a non-standard location, you may need to modify the path.
include_directories(/usr/include/eigen3)

# Add the executable target
add_executable(CameraCoordinateTransformation main.cpp)
