// union - like struct/class, but only can reserve one member
// used instead of type punning, useful when to give two names for same variable e.g. (x,y,z) and (r.g.b)
// usually without name (annonymous)
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

struct Vec2 {
	float x, y;
};

struct Vec4 { // one interpretation: two Vec2 structs
	union { // struct is a member of union
		struct {
			float x, y, z, w;
		};
		struct {
			Vec2 a, b; // reserve same memory of first struct (x,y,z,w) <-> (a,b)
		};
	};


	// Vec2& GetA() {
	//	 return *(Vec2*)&x;
	// 
};

void PrintVec2(const Vec2& v) {
	std::cout << v.x << ", " << v.y << std::endl;
}

int main() {
	struct Union {
		union { // annonymouse
			float a;
			int b;
		}; // two different ways to address same memory - a and b
	};

	Union u;
	u.a = 2.0f;
	std::cout << u.a << ", " << u.b << std::endl; // u.b prints 1073741824, which is byte representation of float for 2

	Vec4 v4 = { 1.0f, 2.0f, 3.0f, 4.0f };
	v4.x = 2.0f;

	PrintVec2(v4.a); // 1, 2
	PrintVec2(v4.b); // 3, 4
	v4.z = 200.0f; // z and b.x occupies same memory
	std::cout << "---------------------------" << std::endl;
	PrintVec2(v4.b); // 200, 4

	std::cin.get();
}