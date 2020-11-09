#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include "array.h"
#include <iostream>

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


template<typename T>
void array_t<T>::print()
{
	std::cout << "=========begin============" << std::endl;
	for (int i = 0; i < count; ++i)
	{
		std::cout << "idx:" << i << " value:" << pdata[i] << std::endl;
	}
	std::cout << "=========end============" << std::endl;
}

template<typename T>
bool array_t<T>::ordered(bool reserve)
{
	for (int i = 0; i < count-1; ++i)
	{
		if (!reserve && pdata[i] > pdata[i+1])
		{
			std::cout << "index:" << i << std::endl;
			return false;
		}
		if (reserve && pdata[i] < pdata[i + 1])
		{
			std::cout << "index:" << i << std::endl;
			return false;
		}
	}
	return true;
}

template<typename T>
void array_t<T>::print_sorted()
{
	if (ordered())
	{
		std::cout << "array is sorted:)" << std::endl;
	}
	else
	{
		std::cout << "XXXXXXXXXXXXXXXXXX" << std::endl;
	}
}