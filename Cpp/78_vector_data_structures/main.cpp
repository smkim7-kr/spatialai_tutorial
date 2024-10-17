// std::vetcor: dynamic size, heap-allocated
#include <iostream>
#include <string>
#include "Vector.h"
#define LOG(x) std::cout << x << std::endl


struct Vec3 {
	float x = 0.f, y = 0.f, z = 0.f;
	Vec3() {}
	Vec3(float scalar)
		:x(scalar), y(scalar), z(scalar) {}
	Vec3(float x, float y, float z)
		:x(x), y(y), z(z) {}
	Vec3(const Vec3& other) // copy
		:x(other.x), y(other.y), z(other.z) {
		std::cout << "Copy\n";
	}
	Vec3(const Vec3&& other) // move
		:x(other.x), y(other.y), z(other.z) {
		std::cout << "Copy\n";
	}

	Vec3& operator=(const Vec3& other) {
		std::cout << "Copy\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vec3& operator=(Vec3&& other) {
		std::cout << "Move\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	~Vec3() { std::cout << "Destroy\n"; }

};

template<typename T>
void PrintVector(const Vector<T>& vec) {
	for (size_t i = 0; i < vec.Size(); i++)
		std::cout << vec[i] << std::endl;
	std::cout << "------------------------" << std::endl;
}


void PrintVector(const Vector<Vec3>& vec) {
	for (size_t i = 0; i < vec.Size(); i++)
		std::cout << vec[i].x << ", " << vec[i].y << ", " << vec[i].z << std::endl;
	std::cout << "------------------------" << std::endl;
}

int main() {
	Vector<std::string> vec;
	vec.PushBack("George");
	vec.PushBack("C++");
	vec.PushBack("Over capacity"); // reallocation triggered
	// vec.EmplaceBack("Haha")

	PrintVector(vec);

	Vector<Vec3> pts;
	pts.PushBack(Vec3(1.0f));
	pts.PushBack(Vec3(1.0f, 2.0f, 3.3f));
	pts.PushBack(Vec3());
	pts.PopBack();
	PrintVector(pts);
	pts.EmplaceBack(1.0f, 2.0f, 3.0f); // will construct at data block, not on main stack
	pts.EmplaceBack(1.0f);
	PrintVector(pts);
	pts.EmplaceBack();
	pts.PopBack();
	PrintVector(pts);
	pts.Clear();
	PrintVector(pts);

	std::cin.get();
}