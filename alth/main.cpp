#include "array.hpp"
#include <iostream>
#include <stdlib.h>
#include "comm_sort.h"

int main()
{
	int runtimes = 10;
	array_t<int> starray(runtimes);
	for (int i = 0; i < runtimes; ++i)
	{
		starray.add(rand() % runtimes, true);
	}

	//pop_sort(starray);
	//insert_sort(starray);
	//select_sort(starray);
	starray.print_sorted();
	merge_sort(starray);
	starray.print_sorted();
	starray.print();
}