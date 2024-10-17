// dynamic cast: safety net when to use casting in C++
// C++ style cast - check whether the cast is valid
// it is tool like function, it is evaluated on runtime (not compiler time) -> thus incur some runtime cost
// mainly used for casts in inheritence (base <-> derived class)
// Base -> Dervied casting: which dervied class?
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

class Base {
public:
	Base() {}
	~Base() {}
	virtual void Makepolymorphic() {}; // need virtual function to support polymorphism of classes when using dynamic_casts
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
	Child* child = new Child(); // child is both Base and Child type
	Base* base = child; // implicit cast 

	// going back to Child is not trivial
	// Child* cp = base; // error because base pointer could be a Child2 class
	Base* malicious = new Child2();
	Child* cp = (Child*)malicious; // need to explicitly cast, but this dangerous
	// malicious pointer is Child2 type, but code above can access private members of Child class -> program might crash

	Child* dp = dynamic_cast<Child*>(base); // valid cast (base is from child)
	if (dp) { // if dp is valid
		std::cout << "dp is valud dynamic casting" << std::endl;
	}
	Child* dp2 = dynamic_cast<Child*>(malicious); // returns nullptr if invalid cast (malicious is from child2)

	// RTTI: runtime type information -> reason why dynamic cast works
	// RTTI also has runtime overhead
	// Disable RTTI : Properties >> C/C++ >> Language >> Enable Run Time Type Information >> No (/GR-)
	// warning when build, access violation when running
	std::cin.get();
}