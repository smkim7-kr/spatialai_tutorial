// can help understand how the code works + optimize code by reducing heap memory allocation
// can built-in tools like valgrind
#include <iostream>
#include <string>
#include <memory>
#define LOG(x) std::cout << x << std::endl

// NOTE: int has defined type, uint32_t has defined type and size

struct AllocationMetrics {
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size) { // monitor memory
	// std::cout << "Allocating " << size << "bytes" << std::endl; // monitoring line
	s_AllocationMetrics.TotalAllocated += size; 
	// can break at return line and monitor the call stack
	return malloc(size); // allocate memory with defined size, and return as void pointer
}

void operator delete(void* memory, size_t size) {
	// std::cout << "Freeing " << size << "bytes" << std::endl; // monitoring line
	s_AllocationMetrics.TotalFreed += size;
	free(memory); // can breakpoint this line and monitor call stack
}

struct Object {
	int x, y, z;
};

static void PrintMemoryUsage() {
	std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << "bytes\n";
}

int main() {
	PrintMemoryUsage();
	Object obj; // stack
	PrintMemoryUsage();
	Object* obj2 = new Object; // heap
	PrintMemoryUsage();
	std::string name = "George";
	PrintMemoryUsage();
	{
		std::unique_ptr<Object> obj3 = std::make_unique<Object>(); // unique pointer also allocated memory to heap - can monitor by overloaded new operator
		PrintMemoryUsage();
	} // delete operator of obj3 called here
	PrintMemoryUsage();

	std::cin.get();
}