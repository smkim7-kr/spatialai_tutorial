//// singletons - design pattern of C++
//// single instance of a class
//// OOP: benefits of objects - can instantiate multiple times
//// but singleton just instantiate once: data-function only once -> why do we need to use class then?
//// use functon/namespace/global variable instead
//// singleton useful when using functionality that repeatedly reuse globally e.g. random number generator
//// e.g. renderer: only single instance, global set of funcitons, not related to objects
//// ultimately singleton design in C++ organize a bunch of global/static variabls in single blob w/ single namespace
//#include <iostream>
//#include <string>
//#define LOG(x) std::cout << x << std::endl
//
////traditional way
//class Singleton {
//public: 
//	Singleton(const Singleton&) = delete;
//
//	// access class statically
//	static Singleton& Get() {
//		return s_Instance;
//	}
//
//	void Function() {};
//private:
//	// private constructor to prevent instantiation
//	Singleton() {}
//	float m_Member = 0.06f;
//	static Singleton s_Instance; // defined somewhere in c++ file because it's static
//};
//
//Singleton Singleton::s_Instance; // definition of static variable
//
//int main() {
//	Singleton::Get().Function(); // statically access Singleton
//
//	// semantic issue
//	// Singleton instance = Singleton::Get(); // without reference, created new Singleton instance here
//	// instance.Function(); 
//	// solution: delete copy constructor
//	Singleton& instance = Singleton::Get(); // force to use reference
//	instance.Function();
//	std::cin.get();
//}