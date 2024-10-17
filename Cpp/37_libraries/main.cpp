// best project setup - everything you need to run and compile should be in the repositories
// good to keep versions of dependencies or take physical binaries in working directories 
// large serious projects, compile library of source code (can easily debug and modify source code)
// small projects, link against binaries (difficult to change/debug source code) e.g. GLFW 32-bit binaries
// 32/64-bit binaries, depend on application target (NOT your local machine!)
// include directories - bunch of header files, library directories - lib/dll files

// linking methods 
// static: library put into executables (technically faster)
// dynamic: link at runtime on the fly - execultable looks for dynamic library at runtime

// Usually put dependencies under "Dependencies" directory
// lib directory - (dynamic) *.dll file and *dll.lib file (static) *.lib file
// set additioanl include directories ${SolutionDir}Dependencies\GLFW\include at Properties>C/C++>General>Additional include Directories
#include <iostream>
#include <string>
#include "GLFW/glfw3.h" // #include <GLFW/glfw3.h>

#define Log(x) std::cout << x << std::endl;

// int glfwInit() { return 0; } // glfwInit() definition 
// Add gkfw3.lib to Properties>Linker>Input>Additional Dependencies 
// Add ${SolutionDir}Dependencies\GLFW\lib-vc2022 to Properties>Linker>General>Additioanal Library Directories
// This will allow to link to lib file and detect glfwInit() function definition 

// extern "C" int glfwInit(); // name mangling with function defined in C language
// can use explicit declaration of function without including header files (#include "...h')

int main() {
	int a = glfwInit(); // build will create link problem because glfw3.h file only has funcwtion declaration
	std::cin.get();
}