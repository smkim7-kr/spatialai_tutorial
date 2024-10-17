// singletons - design pattern of C++
// single instance of a class
// OOP: benefits of objects - can instantiate multiple times
// but singleton just instantiate once: data-function only once -> why do we need to use class then?
// use functon/namespace/global variable instead
// singleton useful when using functionality that repeatedly reuse globally e.g. random number generator
// e.g. renderer: only single instance, global set of funcitons, not related to objects
// ultimately singleton design in C++ organize a bunch of global/static variabls in single blob w/ single namespace
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

//traditional way
class Random {
public:
	Random(const Random&) = delete; // prevent copying

	// access class statically
	static Random& Get() {
		static Random s_Instance; // static variable inside static memory, need no explicit declartion
		return s_Instance;
	}
	static float Float() { return Get().IFloat(); }; // internal retreival
private:
	float IFloat() { return m_RandomGenerator; }; // internal actual function that returns class member
	// private constructor to prevent instantiation
	Random() {}
	float m_RandomGenerator = 0.5f;
};

namespace RandomClass {
	static float s_RandomGenerator = 0.5f;
	static float Float() { return s_RandomGenerator; } // can hide definition to other files
}
int main() {
	// float number = Random::Get().Float();
	float number = Random::Float(); // do not need to call Get()
	std::cout << number << std::endl;

	// Summary: Singleton create once, lifetime = lifetime of application
	// access non-static variables by indirect functions
	
	// Replacing class to namespace
	float number2 = RandomClass::Float();
	std::cout << number2 << std::endl;
	std::cin.get();
}