// move semantics: after C++11, prevent copying object one place to another (e.g. copy object into function)
// biggest usage of lvalues and rvalues
// copy object in stack to function -> move semantics just move objects instaed of copying
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

class String {
public:
	String() = default;
	String(const char* str) {
		printf("Created~\n");
		m_Size = strlen(str);
		m_Data = new char[m_Size];
		memcpy(m_Data, str, m_Size);
	}

	String(const String& other) { // copy constrructor
		printf("Copied~\n"); // Need to prevent this copy as possible 
		m_Size = other.m_Size;
		m_Data = new char[m_Size]; // copy allocates new heap memory
		memcpy(m_Data, other.m_Data, m_Size);
	}

	String(String&& other) noexcept { // move constructor with rvalue reference
		printf("Moved~\n");  // shallow copy 
		m_Size = other.m_Size;
		m_Data = other.m_Data; // simply assigning data pointer, prevent new memory allocation

		// hollow object - empty old string other
		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	~String() {
		printf("Destroyed~\n");
		delete m_Data;
	}

	void Print() {
		for (uint32_t i = 0; i < m_Size; i++) {
			printf("%c", m_Data[i]);
		}
		printf("\n");
	}
private:
	char* m_Data;
	uint32_t m_Size;
};

class Object {
public:
	Object(const String& name) // lvalue input
		:m_Name(name)
	{
	}

	Object(String&& name) // temporary input (rvalue)
		:m_Name((String&&)name) // explicit casting to prevent copy
	{
	}

	void PrintName() {
		m_Name.Print();
	}
private:
	String m_Name;
};

int main() {
	Object obj(String("George")); // copy String("Geroge") into Object obj.m_Name - allocate memory twice! (inefficient)

	// copy m_Name -> move to m_Name
	// Object obj(String("George")); // rvalue: "George"
	std::cin.get();
}