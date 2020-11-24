#include "array.hpp"
#include <iostream>
#include <stdlib.h>
#include "comm_sort.h"
#include "search.h"

array_t<int> gen_array(int itype, int iArraySize)
{
	array_t<int> starray(iArraySize);
	for (int i = 0; i < iArraySize; ++i)
	{
		if (itype == 1)
		{
			starray.add(1, true);
		}
		else if (itype == 2)
		{
			starray.add(i, true);
		}
		else if (itype == 3)
		{
			starray.add(iArraySize - 1);
		}
		else
		{
			starray.add(rand() % iArraySize);
		}
	}
	return starray;
}

bool TestSort(int iArraySize)
{

	//starray.print();
	//merge_sort(starray);
	//pop_sort(starray);
	//insert_sort(starray);
	//select_sort(starray);

	for (int i = 1; i <= 4; i++)
	{
		array_t<int> arrays = gen_array(i, iArraySize);
		quick_sort(arrays);

		if (arrays.ordered() == false)
		{
			return false;
		}
		std::cout << "run:" << i << std::endl;
	}

	return true;
}

int main()

{
	/*
	bool isSort = TestSort(10000);
	if (isSort)
	{
		std::cout << "is sorted ^_^!" << std::endl;
	}
	else
	{
		std::cout << "not sorted yet!!!" << std::endl;
	}*/

	array_t<int> arrays(100);
	arrays.add(1);
	arrays.add(2);
	arrays.add(4);
	arrays.add(4);
	arrays.add(4);
	arrays.add(4);
	arrays.add(4);
	arrays.add(4);
	arrays.add(5);

	std::cout << binsearch_first_ge(arrays, 3) << std::endl;

}