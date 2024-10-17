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

	String(const String& other) { 
		printf("Copied~\n"); 
		m_Size = other.m_Size;
		m_Data = new char[m_Size]; 
		memcpy(m_Data, other.m_Data, m_Size);
	}

	String(String&& other) noexcept { 
		printf("Moved~\n");  
		m_Size = other.m_Size;
		m_Data = other.m_Data; 

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	String& operator=(String&& other) noexcept { // assignment operator
		printf("Assigned~\n");

		if (this != &other) { // prevent dest = std::move(std) 
			delete[] m_Data;

			m_Size = other.m_Size;
			m_Data = other.m_Data;

			other.m_Size = 0;
			other.m_Data = nullptr;
		}

		return *this;

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
	Object(const String& name) 
		:m_Name(name)
	{
	}

	Object(String&& name)
		:m_Name(std::move(name)) // move temporary string name into permanent memory m_Name
	{
	}

	void PrintName() {
		m_Name.Print();
	}
private:
	String m_Name;
};

int main() {
	String str = "Hello";
	String dest2;

	String dest = std::move(str); // move input rvalue, use move constructor
	// String dest(std::move(str)); // same effect, dest is constructed using move constructor

	// assignment operator = is called when assigned to EXISTING variable
	// dest = "new string"; // same as dest.operator=("new string");

	// transforming ownership without copying 
	str.Print();
	dest2.Print();
	// dest = str; // no copy assignment operator
	dest2 = std::move(str);
	str.Print();
	dest2.Print();
	std::cin.get();
}