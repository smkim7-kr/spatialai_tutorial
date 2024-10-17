// benchmarking: evaluate performance of the code/program - so many ways to benchmark
// it may cause overhead
#include <iostream>
#include <string>
#include <chrono>
#include <array>
#define LOG(x) std::cout << x << std::endl

class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
public:
	Timer() {
		m_start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		Stop();
	}
	void Stop() {
		auto endtime = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endtime).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;
		std::cout << duration << "us, " << ms << "ms\n";
	}
};

int main() {
	int value = 0;
	{
		Timer timer; // put timer in interested scope
		for (int i = 0; i < 1000000; ++i)
			value += 2;
	} // time destructor called here

	// benchmarking depends on compiler e.g. Debug vs. Release (release mode - compiler optimize the code iteself)
	// profile in release mode (more useful as debug includes several safety checks)
	std::cout << value << std::endl;

	// Example: unique pointers vs shared pointers
	struct V2 {
		float x, y;
	};

	{ // make_shared
		std::array<std::shared_ptr<V2>, 1000> sharedptrs;
		Timer timer;
		for (int i = 0; i < sharedptrs.size(); i++)
			sharedptrs[i] = std::make_shared<V2>();
	}


	{ // new shared
		std::array<std::shared_ptr<V2>, 1000> sharedptrs;
		Timer timer;
		for (int i = 0; i < sharedptrs.size(); i++)
			sharedptrs[i] = std::shared_ptr<V2>(new V2());
	}


	{ // make unique - fastest in debug/release mode
		std::array<std::unique_ptr<V2>, 1000> uniquedptrs;
		Timer timer;
		for (int i = 0; i < uniquedptrs.size(); i++)
			uniquedptrs[i] = std::make_unique<V2>();
	}

	__debugbreak();
	std::cin.get();
}