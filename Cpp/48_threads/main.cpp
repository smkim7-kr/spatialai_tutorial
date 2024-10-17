// thread is mainly used for optimization
#include <iostream>
#include <string>
#include <thread> // header to use thread class
#define LOG(x) std::cout << x << std::endl

static bool isFinished = false;

void doWork() {
	using namespace std::literals::chrono_literals;

	std::cout << "Started thread id: " << std::this_thread::get_id() << std::endl; // log running thread id

	while (!isFinished) {
		std::cout << "Working...\n"; // keep looping
		std::this_thread::sleep_for(1s); // sleep thread for 1 second during loop - prevnet 100% CPU usage
	}
}

int main() {
	std::thread worker(doWork); // immediate create thread worker executing function doWork(function pointer input, thus no ())
	std::cin.get(); // wait to press enter key
	isFinished = true; // this will break loop in doWork

	// wait to thread to finish
	worker.join(); // block other threads until this thread running doWork (worker) finishes
	std::cout << "Finished" << std::endl;
	std::cout << "Started thread id: " << std::this_thread::get_id() << std::endl; // log running thread id - this will be different from thread worker

	std::cin.get(); // this will not run until worker thread doing doWork() finishes
}