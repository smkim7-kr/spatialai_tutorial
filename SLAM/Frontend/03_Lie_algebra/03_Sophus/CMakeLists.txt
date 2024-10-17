cmake_minimum_required(VERSION 3.10)

project(SophusExample)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Eigen3 (Sophus depends on Eigen)
find_package(Eigen3 3.3 REQUIRED)

# Include the Sophus library
find_package(Sophus REQUIRED)

# Add the executable
add_executable(SophusExample main.cpp)

# Link libraries
target_link_libraries(SophusExample Sophus::Sophus Eigen3::Eigen)
