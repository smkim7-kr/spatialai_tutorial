// virtual destructors - important part for polymorphism
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

class Base {
public:
	Base() { std::cout << "Base Constructed\n"; }
	virtual ~Base() { std::cout << "Base Destructed\n"; } // with virtual, signals that there is possibility that Base Class has a child 
};

class Child : public Base {
public:
	Child() { std::cout << "Child Constructed\n"; }
	~Child() { std::cout << "Child Desctructed\n"; }
};

int main() {
	// Base construct-destruct
	Base* b = new Base();
	delete b;
	std::cout << "-----------------\n";
	// Base construct - Child construcct - Child destruct - Base destruct
	Child* c = new Child();
	delete c;
	std::cout << "-----------------\n";
	// Base construct - Child construct - Base destruct (without virtual) 	// Child is not destructed here! memory leak happened
	// Base construct - Child construcct - Child destruct - Base destruct (with virtual destructor)
	Base* poly = new Child();
	delete poly; // if Base destructor is not virtual, does not realize destructor at Child class

	// conclusion: whenever writing class than might be extending, need to declare destructor as virtual
	std::cin.get();
}