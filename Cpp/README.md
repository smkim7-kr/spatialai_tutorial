# C++ tutorial 
### based on [The Cherno C++ Playlist](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb)

| tutorial                        | tl;dr                                                        |
| ------------------------------- | ------------------------------------------------------------ |
| [01_variables](./01_variables)   | variables have diverse data types - int, float, bool etc.<br />```int var = 20; char a = 65;``` |
| [02_functions](./02_functions)   | functions are useful when to modularize the code or repeated codes exist<br />```int Product(int a, int b) {}``` |
| [03_header_files](./03_header_files) | ".h" header files have declaration of functions<br />```#pragma once ... void Log(const char* message);``` |
| [04_conditions](./04_conditions) | conditions and branching jumps different areas of memory, thus there are overheads<br />```if (ptr) {...} else if {...} else {...}``` |
| [05_loops](./05_loops)           | while and for - when same codes are executed multiple times<br />```for (int i = 0; i < 5; ++i) {...}``` |
| [06_control_flow](./06_control_flow) | continue, break, return - determine when to end a loop/function<br />```for (int i = 0; i < 5; ++i) {...continue...break...}``` |
| [07_pointers](./07_pointers)     | pointers are the number which stores memory address; types of pointers doesn't matter!<br />```int var = 8; int* ptr = &var;``` |
| [08_references](./08_references) | references do not occupy extra memory unlike pointers, they need to reference an existing variable<br />```void Increment(int& value) {...}``` |
| [09_class_structs](./09_class_structs) | class and structs are ways to group data and functionality, useful for object-oriented programming<br />```class Player {int x, y;}; struct s_Player {int x, y;};``` |
| [10_class_design](./10_class_design) | set member variables private, retrieve/update member variables by public Get()/Set() methods<br />```class LogSystem { private: int m_x; public: int GetX() { return m_x; } };``` |
| [11_static](./11_static)         | static keyword declares variables/functions visible to current file. Static inside class/struct is shared by all instances<br />```struct s_Robot { static int x; } int s_Robot::x;``` |
| [12_enums](./12_enums)           | enums group integral constants with logical sense<br />```enum Choice { A, B, C }; Choice::B;``` |
| [13_constructors_destructors](./13_constructors_destructors) | constructors/destructors are special functions when instantiating/destroying objects<br />```class Robot { int m_x; Robot() { m_x = 0; }; ~Robot() {} };``` |
| [14_inheritance](./14_inheritance) | inheritance creates hierarchy of classes, inherited classes can access non-private members/methods of parent classes<br />```class Robot { ... }; class NameRobot : public Robot { ... };``` |
| [15_virtual_functions](./15_virtual_functions) | to overwrite function in child class, base class function needs to be virtual; virtual functions take computational overhead<br />```class Robot { virtual int GetX() {...} }``` |
| [16_interfaces](./16_interfaces) | interface is a type of virtual function - "pure virtual functions" that force subclasses to define a method<br />```class Robot { virtual int GetX() = 0; }``` |
| [17_visibility](./17_visibility) | visibility determines the scope of methods/members; 3 types - private, protected, public<br />```class R { protected: int pX; }; class CR : public R { CR() { pX = 10; } };``` |
| [18_arrays](./18_arrays)         | arrays are collections of variables stored in contiguous memory, usually of the same type; array is a pointer<br />```int arr[5]; int* arr2 = arr; std::array<int, 5> arr3; arr3.size();``` |
| [19_strings](./19_strings)       | string is an array of characters<br />```const char* cstyle = "foo"; char strarr[4] = {'f','o','o','\0}; std::string best = "foo";``` |
| [20_string_literals](./20_string_literals) | string literals are const char[] by default; they are stored in read-only memory<br />```char name[4] = "foo"; const char* name2 = "foo";``` |
| [21_const](./21_const)           | const keyword signals that a variable/function/pointer cannot change; const before/after * determines what cannot change<br />```const int a = 5; const int* const b = 10; int func() const {}``` |
| [22_mutable](./22_mutable)       | mutable allows a variable to be changed in a const function<br />```mutable int x = 1; int func() const { x = 10; }``` |
| [23_constructor_initializer_list](./23_constructor_initializer_list) | constructor initializer lists have better performance than initializing inside methods<br />```Constructor() : m_x(0), m_y(0) {}``` |
| [24_ternary_operators](./24_ternary_operators) | ternary operators simplify branching expressions<br />```int a = 8; int b = a > 5 ? 10 : 5;``` |
| [25_instantiate_objects](./25_instantiate_objects) | instantiate objects on the stack rather than the heap if possible; stack objects live in scope, heap objects need explicit destruction<br />```Class* hr = new Class(); { Class sr; } delete hr;``` |
| [26_new](./26_new)               | using new allocates memory in the heap, which takes overhead; placement new prevents new memory allocation<br />```int* arr = new int[50]; int* arr2 = new(arr) int;``` |
| [27_implicit_explicit](./27_implicit_explicit) | explicit constructors prevent implicit conversions<br />(implicit) ```Class c(0); Class c2 = {0}; func({0});```<br />(explicit) ```Class e(10)``` is the only accepted instantiation format |
| [28_operators](./28_operators)   | operators include new, *, +, <<; overloading redefines the behavior of an operator; use overloading minimally<br />```ClassInt operator+(const ClassInt& y) const { return ClassInt(this->val + y.val); }``` |
| [29_this](./29_this)             | this keyword is the address of the current object<br />```class C{ int m_x = 0; C(int x) {this->m_x = x} };``` |
| [30_object_lifetime](./30_object_lifetime) | stack-based objects are destroyed when scope {} ends; use unique pointers to automatically delete heap-based objects<br />```{ Class c; Class* c2 = new Class(); }``` => class c destroyed out of this scope |
| [31_smart_pointers](./31_smart_pointers) | Smart pointers automatically manage memory; use smart pointers instead of new/delete<br />```std::unique_ptr<Object> obj = std::make_unique<Object>();``` |
| [32_copy_constructors](./32_copy_constructors) | copy constructors perform shallow copy by default; self-define copy constructors for deep copy<br />```ClassName(const ClassName& other) { x= other.x; };``` |
| [33_arrow](./33_arrow)           | arrow operators are useful when handling pointers<br />```Obj1->x = 10; (*Obj1).x = 10;``` |
| [34_dynamic_array](./34_dynamic_array) | vectors are dynamic arrays; they resize automatically<br />```std::vector<int> arr;``` |
| [35_vector_optimization](./35_vector_optimization) | Use reserve() to reserve memory and emplace_back() instead of push_back() to avoid unnecessary copying<br />```vec.reserve(3); vec.emplace_back(2, 3, 4);``` |
| [36_local_static](./36_local_static) | Static local variables have local scope but last until the program ends<br />```void foo() { static int i = 0; }``` |
| [37_libraries](./37_libraries)   | Libraries can be linked statically or dynamically<br />```#include "GLFW/glfw3.h"``` |
| [38_multiple_returns](./38_multiple_returns) | Use structs for clarity when returning multiple objects<br />```static StructExample multipleReturnsStruct() { return { "Hello", 6 }; }``` |
| [39_templates](./39_templates)   | Templates are blueprints; they can take different types and parameters when instantiated<br />```template <typename T> T val = 10;``` |
| [40_stack_heap](./40_stack_heap) | Stack allocations are faster, heap allocations are slower<br />```int sval = 5; int* hval = new int(10);``` |
| [41_macros](./41_macros)         | Avoid macros; they abstract away their functionality<br />```#if 0 #endif``` |
| [42_auto](./42_auto)             | The auto keyword allows the compiler to detect the type; useful for long type names<br />```const auto& obj_x = Obj.getX()``` |
| [43_static_arrays](./43_static_arrays) | Prefer std::array to C-style arrays<br />```std::array<int, 5> arr = {1, 2, 3, 4, 5};``` |
| [44_function_pointers](./44_function_pointers) | Function pointers assign a function to a variable; not commonly used in modern C++<br />```auto function = SomeFunction; SomeFunction();``` |
| [45_lambdas](./45_lambdas)       | Lambda functions are anonymous, quick, and disposable functions<br />```auto lambda = [](int v) { std::cout << "Value: " << v; };``` |
