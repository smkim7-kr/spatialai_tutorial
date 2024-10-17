#pragma once

template<typename T>
class Vector {
public:
	Vector() {
		// allocate memory for 2 elements
		ReAlloc(2); 
	}

	~Vector() {
		Clear(); // calls destructor
		::operator delete(m_Data, m_Capacity * sizeof(T)); // not calls desturctor
	}

	void PushBack(const T& value) {
		if (m_Size >= m_Capacity) // update capacity
			ReAlloc(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(T&& value) { // rvalue reference - prevent copy but instead move
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)// construct in-place
	{
		if (m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity / 2);

		new(&m_Data[m_Size]) T(std::forward<Args>(args)...); // ... unpack, new operator to construct objects in-place
		m_Size++;
		return m_Data[m_Size];
	}

	void PopBack() {
		if (m_Size > 0) {
			m_Size--;
			m_Data[m_Size].~T(); // free resources
		}
	}

	void Clear() {
		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
		m_Size = 0;
 }

	T& operator[](size_t index) { 
		if (index >= m_Size) {
			__debugbreak();
		}
		return m_Data[index];
	}
	const T& operator[](size_t index) const { return m_Data[index]; }

	size_t Size() const { return m_Size; }
private:
	T* m_Data = nullptr;
	size_t m_Size = 0; // number of elements insider vector
	size_t m_Capacity = 0; // how many elements can we store?
	
	void ReAlloc(size_t newCapacity) {
		// 1. allocate new block of memory
		// T* newBlock = new T[newCapacity];
		T* newBlock = (T*)::operator new(newCapacity*sizeof(T));

		size_t size = m_Size;
		if (newCapacity < size)
			m_Size = newCapacity; // in case of downsizing

		// 2. copy/move(better) existing element into new block of memory
		for (size_t i = 0;i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]); // without std::move, this will be copy (which is bad)

		for (size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		// why not using memcpy? more complex types might have their own copy constructor

		// 3. delete previous memory block
		//delete[] m_Data;
		::operator delete(m_Data, m_Capacity * sizeof(T));
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
};