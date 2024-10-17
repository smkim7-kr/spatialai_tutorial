// conditional breakpoint: trigger breakpoint when condition is met (if statement)
// action breakpoint: allow to take action (generally print on console) when breakpoint is hit 
// 2 types of action breakpoint: keep program running after taking action / paise execution when breakpoint is met
// useful when to inspect what causes bug at current state
// to prevent terminate application - recompile repetition, which will slow down the workflow
// use it if possible, speed up coding time in c++
// cons: slow down the program, but they are just debugging tools :)
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

int main() {

	std::cin.get(); // breakpoint on the right click of red button
	// example of action breakpoint: The correct output is : {(float)x}, {(float)y}
	// no need to stop the program, check log while running the program
	// example of condition btrakpoint: any boolean expression like x> 500
	// action will be called iff condition is satisfied

	// continue code execution (check / uncheck)
	// condition is very useful when using loop 
}