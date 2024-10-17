// optional data - when return type may not have nothing to return (e.g. reading file failed)
// New feature from C++17
#include <iostream>
#include <string>
#include <fstream>
#include <optional> // header for optional data
#define LOG(x) std::cout << x << std::endl

std::string ReadFile(const std::string& filepath) {
	std::ifstream stream(filepath);
	if (stream) { // read file successfully
		stream.close();
		std::string result;
		return result;
	}

	return std::string(); // read file failed
}

std::string ReadFileWithSuccess(const std::string& filepath, bool& success) {
	std::ifstream stream(filepath);
	if (stream) { // read file successfully
		stream.close();
		std::string result;
		success = true;
		return result;
	}

	success = false;
	return std::string(); // read file failed
}

std::optional<std::string> ReadFileWithOptional(const std::string& filepath) {
	std::ifstream stream(filepath);
	if (stream) { // read file successfully
		stream.close();
		std::string result;
		return result;
	}

	return {}; // read file failed
}

int main() {
	std::string data = ReadFile("data.txt");
	// how can we check if data.txt file read successfully?
	if (data != "") { std::cout << "Failed" << std::endl; } // this is not clever, file may be valid but empty

	bool filesuccess;
	std::string data2 = ReadFileWithSuccess("data.txt", filesuccess);
	if (!filesuccess) { std::cout << "Failed" << std::endl; } // still not particularly nice
	
	// std::optional
	std::optional<std::string> data3 = ReadFileWithOptional("data.txt");
	if (data3) { std::cout << "File read successfully" << std::endl; }

	// accessiing data
	auto str3 = data3.value();

	// if data3 not exist, it will return "No file" as default
	std::string value = data3.value_or("No file");
	std::cout << value << std::endl;

	std::cin.get();
}