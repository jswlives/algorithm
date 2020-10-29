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
			starray.add(rand(), true);
		}
		//starray.print();
		//merge_sort(starray);
		//pop_sort(starray);
		//insert_sort(starray);
		//select_sort(starray);
		quick_sort(starray);

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
	bool isSort = TestSort(10, 10000);
	if (isSort)
	{
		std::cout << "is sorted ^_^!" << std::endl;
	}
	else
	{
		std::cout << "not sorted yet!!!" << std::endl;
	}

/*
	array_t<int> starray(1000);
	starray.add(5);
	starray.add(6);
	starray.add(7);
	starray.add(1);
	starray.add(2);
	starray.add(3);
	//starray.add(6);
	quick_sort(starray);
	starray.print();
	starray.print_sorted();*/

}