#include "array.hpp"
#include <iostream>

int main()
{
	jsw::array_t<int> starray(10);
	for (int i = 0; i < 100; ++i)
	{
		starray.add(i, true);
	}
	for (int i = 0; i < starray.size(); ++i)
	{
		std::cout << starray[i] << std::endl;
	}

}