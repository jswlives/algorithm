#include "array.hpp"
#include <iostream>
#include <stdlib.h>
#include "comm_sort.h"

int main()
{
	int runtimes = 1000;
	array_t<int> starray(runtimes);
	for (int i = 0; i < runtimes; ++i)
	{
		starray.add(rand(), true);
	}
	//starray.print();
	merge_sort(starray);
	//pop_sort(starray);
	//insert_sort(starray);
	//select_sort(starray);
	//starray.print();
	starray.print_sorted();
}