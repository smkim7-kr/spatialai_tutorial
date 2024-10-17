// C++ is strongly-typed language and support implicit/explicit conversion supported to cast types
// 2 types of explicit type conversions: c, c++ style
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

class Base {
public:
	Base() {}
	virtual ~Base() {}
};

class Child : public Base {
public:
	Child() {}
	~Child() {}
};

class Child2 : public Base {
public:
	Child2() {}
	~Child2() {}
};

int main() {
	int a = 5;
	double b = a; // implicit 

	double c = 5.15;
	int d = c; // implicit

	double e = 5.15;
	int f = (int)e; // explicit (c-style casting)
	double g = (int)e + 5.3;
	double h = (int)(e + 5.3);
	std::cout << g << std::endl; // 10.3

	// c++ style casting
	// four types - static, reinerpret, dynamic, const cast
	// they are just syntax sugaring of c style - advantage: able to search for syntax doing type casting in the code
	double s = static_cast<int>(e) + 5.3; 

	// double s = static_cast<Child2*>(e) + 5.3; // this gives an error, compiler checks for invalid type conversion
	Child* child = new Child();
	Base* base = child; // how can we find which dervied class is c? (Child, Child2?) -> use dynamic_cast
	Child* c1 = dynamic_cast<Child*>(base); // this gives valid pointer
	Child2* c2 = dynamic_cast<Child2*>(base); // c2 is nullptr since base pointer is pointing to Child class, not Child2

	std::cin.get();
}