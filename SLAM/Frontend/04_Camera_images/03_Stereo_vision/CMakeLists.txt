# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(StereoVisionPointCloud)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find Open3D package
find_package(Open3D REQUIRED)

# Add the executable target
add_executable(stereo_point_cloud main.cpp)

# Link OpenCV and Open3D libraries to the executable
target_link_libraries(stereo_point_cloud ${OpenCV_LIBS} Open3D::Open3D)

# Enable more compiler warnings (optional)
target_compile_options(stereo_point_cloud PRIVATE -Wall -Wextra -pedantic)
