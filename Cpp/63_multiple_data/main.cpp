// std::variant supported in C++17
// list possible data (not sure which data) 
#include <iostream>
#include <string>
#include <fstream>
#include <variant> // header
#define LOG(x) std::cout << x << std::endl

enum class ErrorCode {
	None = 0, NotFound = 1, NoAccess = 2
};

std::variant<std::string, ErrorCode> ReadFileWithOptional(const std::string& filepath) { // can use std::variant replacing std::optional, return 
	std::ifstream stream(filepath);
	if (stream) { 
		stream.close();
		std::string result;
		return result; // std::string for read success
	}
	return ErrorCode::NotFound; // error code for read failure
}

int main() {
	std::variant<std::string, int> data;
	data = "George";
	std::cout << std::get<std::string>(data) << "\n";
	data = 25;
	// data = false; // accepts, can't access later so avoid this
	std::cout << std::get<int>(data) << "\n";
	// std::cout << std::get<std::string>(data) << "\n"; // this throws exception

	int idx = data.index(); // 1: tells which index of variant is the data type
	auto* val = std::get_if<std::string>(&data); // std::get_if returns nullptr if data type is not std::string, if yes, returns pointer to data
	if (val) { std::string& v = *val; }
	else {}

	// similar to type-safe union (std::variant variable is slightly larger than largest type)
	// should use std::variant instead of union (except for low-level programming etc.)
	std::cin.get();
}