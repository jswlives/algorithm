
#include "array.h"
#include "comm_sort.h"

template<typename T>
void swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

//交换次数多
void pop_sort(array_t<int>& array)
{
	for (int j = array.size() -1; j >= 0; --j)//不会越界
	{
		for (int i = 0; i < j; ++i)
		{
			if (array[i] > array[i+1])
			{
				swap<int>(&array[i], &array[i + 1]);
			}
		}
	}
}

//元素交换次数少
void insert_sort(array_t<int>& array)
{
	for (int j = 1; j < array.size(); ++j)//不会越界
	{
		int value = array[j];
		int i = j - 1;
		for (; i >= 0; --i)
		{
			if (array[i] > value)
			{
				array[i + 1] = array[i];
			}
			else
			{
				break;
			}
		}
		array[i + 1] = value;
	}
}

//不稳定
void select_sort(array_t<int>& array)
{
	for (int i = 0; i < array.size()-1; ++i)
	{
		for (int j = i+1; j < array.size(); ++j)
		{
			if (array[j] < array[i])
			{
				swap(&array[i], &array[j]);
			}
		}
	}
}

void merge(array_t<int>& array, int begin, int end, int lbegin, int lend, int rbegin, int rend)
{

	int array_size = end - begin + 1;
	array_t<int> temp_array(array_size);

	while (lbegin <= lend && rbegin <= rend)
	{
		if (array[lbegin] <= array[rbegin])
		{
			temp_array.add(array[lbegin++]);
		}
		else
		{
			temp_array.add(array[rbegin++]);
			rbegin++;
		}
	}
	while (lbegin <= lend)
	{
		temp_array.add(array[lbegin++]);
	}
	while (rbegin <= rend)
	{
		temp_array.add(array[rbegin++]);
	}
	for (int i = 0; i < temp_array.size(); ++i)
	{
		array[begin + i] = temp_array[i];
	}
	//std::cout << "end================" << std::endl;

}

void merge_sort_c(array_t<int>& array, int begin, int end)
{
	//std::cout << "begin:" << begin << " end:" << end << std::endl;
	if (begin >= end)
	{
		return;
	}
	int mid = (begin + end) / 2;

	merge_sort_c(array, begin, mid);
	merge_sort_c(array, mid + 1, end);
	merge(array, begin, end, begin, mid, mid + 1, end);
}

void merge_sort(array_t<int>& array)
{
	merge_sort_c(array, 0, array.size() - 1);
}