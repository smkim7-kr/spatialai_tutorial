#include <iostream>
#include <string>
#define Log(x) std::cout << x << std::endl;

class Robot {
private:
	int m_x, m_y;
public:
	Robot()
		: m_x(0), m_y(0)
	{}

	Robot(int x, int y)
		: m_x(x), m_y(y)
	{}

	void GetX() {}

	void GetY() const {}
};

class ScopedPtr { // automatically deleted when get out of scope
private:
	Robot* m_Robot;
public:
	ScopedPtr(Robot* r)
		:m_Robot(r) 
	{}

	~ScopedPtr() {
		delete m_Robot;
	}

	// arrow operator overloading
	Robot* operator->() {
		return m_Robot;
	}

	Robot* operator->() const {
		return m_Robot;
	}
};

struct Vec3 {
	int x, y, z; // offset: 0, 4, 8
};

int main() {
	Robot r;
	Robot* ptr = &r;
	// ptr.GetX() // error

	Robot& r2 = *ptr; // dereference ptr
	r2.GetX();
	(*ptr).GetX(); // alternative approach
	ptr->GetX(); // same meaning - arrow operaotr is much simple to use

	// arrow operator overloading
	ScopedPtr robot = new Robot();
	robot->GetX(); // use arrow operator overloading

	const ScopedPtr robot2 = new Robot();
	robot2->GetY(); // const object call const methods

	// finding offest using arrow operator
	std::ptrdiff_t offsetX = (std::ptrdiff_t)&(((Vec3*)nullptr)->x) - (std::ptrdiff_t)(Vec3*)nullptr;
    std::ptrdiff_t offsetY = (std::ptrdiff_t)&(((Vec3*)0)->y) - (std::ptrdiff_t)(Vec3*)0;
	// useful when serializing data

	std::cin.get();
}