
#include "array.h"
#include "comm_sort.h"

template<typename T>
void swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}


/*
冒泡排序
复杂度: O(n2)
要点：把最大的元素往后沉
缺点：交换次数比插入排序多
*/
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

/*
插入排序
复杂度:O(n2)
要点：已排序区间和未排序区间。初始已排序区间只有一个元素，就是数组的第一个元素。插入算法的核心思想是取未排序区间中的元素，
	在已排序区间中找到合适的插入位置将其插入，并保证已排序区间数据一直有序。重复这个过程，直到未排序区间中元素为空，算法结束
优点：比起冒泡排序，元素交换次数少
*/

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


/*
选择排序
复杂度：O(n2)
要点：分已排序区间和未排序区间，每次会从未排序区间中找到最小的元素，将其放到已排序区间的末尾，与之交换
缺点:不稳定排序
*/

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

//时间复杂度O(nlogn),但空间复杂度是O(n)
void merge_sort(array_t<int>& array)
{
	merge_sort_c(array, 0, array.size() - 1);
}

int partation(array_t<int>& array, int begin, int end)
{
	int pivot = begin;

	int left = begin;
	int right = end;

	while (left != right)
	{
		while (right > left && array[right] >= array[pivot])//用>， 等于基准值的要挪过去
		{
			right--;
		}
		while (right > left && array[left] <= array[pivot])//用>=， 等于基准值的留下来不用挪
		{
			left++;
		}
		if (left < right)
		{
			swap(&array[left], &array[right]);
		}
	}
	swap(&array[begin], &array[left]);

	return left;

}

void quick_sort_c(array_t<int>& array, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}
	int idx = partation(array, begin, end);
	quick_sort_c(array, begin, idx - 1);
	quick_sort_c(array, idx + 1, end);
}


/*
快排要点:
1、把数组分片成两个部分
2、再对左右数组递归排序
*/
void quick_sort(array_t<int>& array)
{
	quick_sort_c(array, 0, array.size() - 1);
}