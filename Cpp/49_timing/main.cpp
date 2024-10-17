// library chrono in C++ for timing
// need to use operating system timing library for very precise timing
#include <iostream>
#include <string>
#include <thread>
#include <chrono> // header library for timing
#define LOG(x) std::cout << x << std::endl

struct Timer {
	// automatic object lifetime timer
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << duration.count()*1000.0f << "ms" << std::endl;
	}
};

void Print() {
	Timer timer; // timer constructor called here

	for (int i = 0; i < 100; i++) {
		std::cout << "Hello\n";
		// faster than std::cout << "Hello" << std::endl;
	}
} // Timer desturctor called here

int main() {
	using namespace std::literals::chrono_literals; // need for expressing time like 1s = 1 second

	auto start = std::chrono::high_resolution_clock::now(); // returns current time
	std::this_thread::sleep_for(1s); // thread sleep for 1 second
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;
	std::cout << duration.count() << "s" << std::endl; // returns 1+epsilon time (negligable time epsilon due to overhead etc.)

	// automatic timing function execution time
	Print();

	// for higher precision (which is not the case mostly) - platform specific library e.g. Win32 API query performance counter

	std::cin.get();
}