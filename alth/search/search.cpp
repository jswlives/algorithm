#include "search.h"

int binsearch_i(array_t<int>& array, int low, int height, int value)
{
	while (low <= height)
	{
		int mid = (low + height) / 2;
		if (array[mid] == value)
		{
			return mid;
		}
		if (array[mid] > value)
		{
			height = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

//二分查找
int binsearch(array_t<int>& array, int value)
{
	return binsearch_i(array, 0, array.size() - 1, value);
}

int binsearch_first_i(array_t<int>& array, int low, int height, int value)
{
	while (low <= height)
	{
		int mid = (low + height) / 2;
		if (array[mid] == value)
		{
			if (mid > low &&  array[mid-1] == value)
			{
				height = mid - 1;
			}
			else
			{
				return mid;
			}
		}
		else if (array[mid] > value)
		{
			height = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

//查找第一个
int binsearch_first(array_t<int>& array, int value)
{
	return binsearch_first_i(array, 0, array.size() - 1, value);
}

int binsearch_last_i(array_t<int>& array, int low, int height, int value)
{
	while (low <= height)
	{
		int mid = (low + height) / 2;
		if (array[mid] == value)
		{
			if (mid < height&& array[mid + 1] == value)
			{
				low = mid + 1;
			}
			else
			{
				return mid;
			}
		}
		else if (array[mid] > value)
		{
			height = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

//查找最后一个
int binsearch_last(array_t<int>& array, int value)
{
	return binsearch_last_i(array, 0, array.size() - 1, value);
}


int binsearch_first_ge_i(array_t<int>& array, int low, int height, int value)
{
	while (low <= height)
	{
		int mid = (low + height) / 2;
		if (array[mid] >= value)
		{
			if (mid > low && array[mid-1] >= value)
			{
				height = mid - 1;
			}
			else
			{
				return mid;
			}
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

//第一个大于等于
int binsearch_first_ge(array_t<int>& array, int value)
{
	return binsearch_first_ge_i(array, 0, array.size() - 1, value);
}
