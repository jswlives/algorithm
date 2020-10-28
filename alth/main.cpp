#include "array.hpp"
#include <iostream>
#include <stdlib.h>
#include "comm_sort.h"

bool TestSort(int iRumtimes, int iArraySize)
{
	while (iRumtimes > 0)
	{
		array_t<int> starray(iArraySize);
		for (int i = 0; i < iArraySize; ++i)
		{
			starray.add(rand() % 10000, true);
		}
		//starray.print();
		merge_sort(starray);
		//pop_sort(starray);
		//insert_sort(starray);
		//select_sort(starray);
		//quick_sort(starray);

		if (starray.ordered() == false)
		{
			return false;
		}

		iRumtimes--;
		std::cout << "RemainTimes:" << iRumtimes << std::endl;
	}
	return true;
}

int main()
{
	bool isSort = TestSort(100, 100000);
	if (isSort)
	{
		std::cout << "is sorted ^_^!" << std::endl;
	}
	else
	{
		std::cout << "not sorted yet!!!" << std::endl;
	}
}