// lvalue: locator values (they have location)
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

int GetValue() {
	return 10;
}

int& GetValue2() { // returns lvalue reference
	static int value = 10;
	return value;
}

void SetValue(int value) {}

void SetValue2(int& value) {} // lvalue reference

void SetValue3(const int& value) {} // const lvalue reference

void PrintName(const std::string& name) {
	std::cout << name << std::endl;
}

void PrintName2(const std::string&& name) { // only acceps temporaty objects: rvalue reference
	std::cout << name << std::endl;
}

void PrintNameboth(const std::string& name) { // accepts lvalue, rvalue overloaded even though const lvalue input is used
	std::cout << "[lvalue]: " << name << std::endl;
}

void PrintNameboth(const std::string&& name) { // overloaded function, accepts rvalue
	std::cout << "[rvalue]: " << name << std::endl;
}


int main() {
	int i = 10; // left side i, right side 10 (left, right of =)
	// lvalue has location memory i, rvalue is value without location memory e.g. (10 = i is weird)
	int a = i; // lvalue and rvalue have both memory

	int j = GetValue(); // rvalue is result of function (temporary value, no storage), stored to lvalue j
	// GetValuue() = 5; // this doesn't work because GetValue() is rvalue

	GetValue2() = 5; // this works fine

	SetValue(i); // lvalue 
	SetValue(10); // rvalue (temporary storage)

	// only have lvalue reference of lvalue (not rvalue)
	SetValue2(i);
	// SetValue2(10); // this gives an error

	// special rule: lvalue of reference of rvalue is accepted when lvalue is const
	const int temp = 10;
	const int& a = temp;
	//const int& a = 10; // same as int temp = 10; const int& a = temp;
	SetValue3(i);
	SetValue3(10); // accpets this for const lvalue reference

	// lvalue: firstName, lastName, fullName
	// rvalue: "George", "Kim", firstName+lastName
	std::string firstName = "George";
	std::string lastName = "Kim";
	std::string fullName = firstName + lastName;
	PrintName(fullName); 
	PrintName(firstName + lastName); // compatible with temporary rvalues with const lvalue reference

	// rvalue reference
	// PrintName2(fullName); // causes error
	PrintName2(firstName + lastName); 

	// overloading lvalue, rvalue
	PrintNameboth(fullName); 		
	PrintNameboth(firstName + lastName); // can detect temporary values by overloading

	// why this is useful? -> move semantics
	// optimization purpose: if rvalue(temporary). can use it freely because only used in running scope
	std::cin.get();
}