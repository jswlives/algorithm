#pragma once
#include <memory>

template<typename T>
class array_t
{
public:
	array_t(int iCapacity);
	~array_t();

public:
	int add(const T& element, bool shift_overflow = false);
	int size() { return count; }
	T& operator[](int idx);
	void print();
	void print_sorted();
	bool ordered();

private:
	T* pdata;
	int capacity;
	int count;
};
