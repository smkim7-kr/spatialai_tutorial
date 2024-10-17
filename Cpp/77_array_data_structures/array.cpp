#include <iostream>
#include <array>
#include <string>

template<typename T, size_t S>
class Array {
public:
	/* 
	Array(int size) {
		// m_Data = (int*)alloca(size * sizeof(int)); // alloca command allocates memory in stack, lack compiler optimization 
	}
	*/
	constexpr size_t Size() const { return S; } // by adding constexpr, it assures the function can be evaluated at compile time

	// T operator[](int index) { return m_Data[index]; } // return value can be inefficient (e.g. std::string), cannot modify like data[i] = 2
	T& operator[](size_t index) { 
		if (!(index < S)) // protects out-of-range access - checked in debug mode
			__debugbreak();
		return m_Data[index]; 
	}
	const T& operator[](size_t index) const { return m_Data[index]; } // if instance Array is const, this const function will be called, can read data e.g. data[i], cannot modify data e.g. data[i] = 2
	// use size_t instead of int as input since int accepts negative value

	// access data
	T* Data() { return m_Data; }
	const T* Data() const { return m_Data; }
private:
	// int* m_Data; // how can we control the size? use template
	T m_Data[S];
};

int main() {
	Array<int, 5> data; // templated class, specify size at compile time
	Array<std::string, 2> anotherdata;
	const auto& arrayRef = data;
	static_assert(data.Size() < 10, "Size is too large!"); // static_assert is evaluated at runtime

	memset(&data[0], 0, data.Size() * sizeof(int)); // set all value to 0
	data[1] = 5;

	for (size_t i = 0; i < data.Size(); i++) {
		std::cout << data[i] << std::endl;
		std::cout << arrayRef[i] << std::endl;
	}
	data[0] = 10; // allowed
	// arrayRef[0] = 20; // not allowed, const function called

	/* range based for-loop, need to define iterator
	for (auto& ele : data) {
		std::cout << ele << std::endl;
	}
	*/
	

	std::cin.get();
}