
# CMake and Ninja: A Detailed Guide

## Introduction
CMake and Ninja are powerful tools used in modern software development to streamline the building process. CMake is a cross-platform build system generator that creates configuration files for various platforms, while Ninja is a small and efficient build system often used for large projects, particularly in C++.

This guide will help you understand the fundamentals of CMake and Ninja, how they work together, and how to use them effectively in your projects.

---

## 1. CMake

### 1.1 What is CMake?
CMake is an open-source tool designed to control the build process of software projects. It generates build system files for various platforms and compilers, such as Makefiles, Visual Studio project files, or Ninja build files. CMake abstracts away platform-specific details, making it easier to build cross-platform software.

### 1.2 Basic CMake Workflow
CMake works by reading a configuration file called `CMakeLists.txt`, which contains instructions for generating the build system.

1. Create a project directory:
    ```
    mkdir MyProject && cd MyProject
    ```

2. Add a `CMakeLists.txt` file:
    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(MyProject)

    add_executable(CMaketutorial main.cpp)
    ```

3. Generate the build system:
    ```
    mkdir buiild && cd build && cmake ..
    ```

4. Build the project:
    ```
    make
    ```

This simple example compiles a project with a `main.cpp` file.

### 1.3 CMakeLists.txt File Explained
A `CMakeLists.txt` file defines how the project should be built. Here’s a breakdown of common commands:

- `cmake_minimum_required(VERSION X.Y)`: Specifies the minimum required version of CMake.
- `project(ProjectName)`: Defines the project’s name.
- `add_executable(target_name source_files)`: Adds an executable target with specified source files.
- `target_link_libraries(target_name libraries)`: Links external libraries to the target.

Example:
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(SOURCES main.cpp main2.cpp)

add_executable(MyExecutable ${SOURCES})
target_link_libraries(MyExecutable PRIVATE mylibrary)
```

### 1.4 Configuring CMake for Ninja
To use Ninja as your build system, specify it when running CMake:

```bash
mkdir build && cd build && cmake -G Ninja .. && ninja
```

This will generate a `build.ninja` file that Ninja will use to build your project

ninja have same effect to make 

### 1.5 Advantages of Using Ninja
- **Speed**: Ninja is faster than most other build systems, particularly for large projects.
- **Minimalism**: Ninja has a very small footprint and is easy to use.
- **Parallelism**: Ninja supports parallel builds out of the box, making it great for multi-core systems.

---

### 2. Resources
- [CMake Documentation](https://cmake.org/documentation/)
- [Ninja Build System](https://ninja-build.org/)

