# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SO3_SE3_Perturbation VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(so3_se3_perturbation main.cpp)

# Optional: Enable more warnings (helpful for debugging)
target_compile_options(so3_se3_perturbation PRIVATE -Wall -Wextra -pedantic)

