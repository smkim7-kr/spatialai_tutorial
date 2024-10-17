#include <iostream>
#include <string>
#include "GLFW/glfw3.h" // both static and dynamic linking supports equal header files
#define Log(x) std::cout << x << std::endl;

// Add glfw3dll.lib to Properties>Linker>Input>Additional Dependencies 
// gkfw3.dll and glfw3dll.lib are run togehter
// copy gkfw3.dll to the path where exe executables exists (search path is executable's directory)
// Add ${SolutionDir}Dependencies\GLFW\lib-vc2022 to Properties>Linker>General>Additioanal Library Directories
// This will allow to link to lib file and detect glfwInit() function definition 

// project consufration type Properties>Confiruation Properties > General > Configuration type (.exe, .lib etc.)
// set compiler path to use <> - add ${SolutionDIr}\library_project_path into Properties > C/C++ > General > Additional Include Directories 
// executable - main cpp file with #include "...h" or <...h> file from library project 
// library - cpp (definition) with #include "...h" file from library project and h (declaration) file
// <> is usually used for external project (outside the solution)

// linking to libraries
// exe project > Add > Reference - select lib project
// visual studio automatically link to lib file 
// also automatically builds both exe and lib project at once when it builds (lib project first, then exe project automatically)

// adavantage of static linking!
// only need exe file to run the whole program (wherever exe file is)

int main() {
	int a = glfwInit();
	std::cin.get();
}