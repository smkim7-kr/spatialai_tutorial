# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(UndistortImage)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add the executable target
add_executable(undistort_image main.cpp)

# Link OpenCV libraries to the target
target_link_libraries(undistort_image ${OpenCV_LIBS})

# Enable extra compiler warnings (optional, for debugging)
target_compile_options(undistort_image PRIVATE -Wall -Wextra -pedantic)
