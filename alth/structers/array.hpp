#include <cassert>
#include <cstdint>
#include <cstring>
#include "array.h"
namespace jsw {

template<typename T>
array_t<T>::array_t(int iCapacity)
{
	pdata = new T[iCapacity];
	capacity = iCapacity;
	count = 0;
}

template<typename T>
array_t<T>::~array_t()
{
	delete[] pdata;
}

template<typename T>
int array_t<T>::add(const T& element, bool shift_overflow)
{
	if (count >= capacity && !shift_overflow)
	{
		return -1;
	}
	if (count < capacity)
	{
		pdata[count++] = element;
	}
	else
	{
		memmove(pdata, pdata + 1, sizeof(T) * (capacity - 1));
		pdata[count - 1] = element;
	}
	return 0;
}

template<typename T>
T& array_t<T>::operator [](int idx)
{
	assert(idx < count);
	return pdata[idx];
}


}
