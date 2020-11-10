
#include "array.h"
#include "comm_sort.h"

template<typename T>
void swap(T* a, T* b)
{
	if (a == b)
	{
		std::cout << "swap self" << std::endl;
	}
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

//此处做了简化，其实多了交换次数
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


//==================================================
//==================================================
//双边循环法（严蔚敏版）
//直观易，但容易出错
int partation_v1(array_t<int>& array, int begin, int end)
{
	int pivot = array[begin];

	int left = begin;
	int right = end;

	while (left != right)//跟（left < right）一样， 下面的while（right > left）已经保证了
	{
		while (right > left && array[right] > pivot)//小于等于基准值的放左边（> 或者 >= 都可以）
		{
			right--;
		}
		while (right > left && array[left] <= pivot)//大于基准值的放右边(必须 <= ， 否则可能死循环)
		{
			left++;
		}
		if (left < right)
		{
			swap(&array[left], &array[right]);
		}
	}
	swap(&array[begin], &array[left]);//不管哪种分区法，基准元素都要放到分区位置

	return left;

}


//单边循环法(小灰灰算法版)
//mark的元素永远<= pivot
int partation_v2(array_t<int>& array, int begin, int end)
{
	int pivot = array[begin];
	int mark = begin;
	for (int i = begin + 1; i <= end; ++i)
	{
		if (array[i] < pivot)// <= 或者 < 都可以?
		{
			swap(&array[++mark], &array[i]);
		}
	}
	swap(&array[begin], &array[mark]);//不管哪种分区法，基准元素都要放到分区位置
	return mark;
}

//算法导论版, 极客时间版，等同于单边循环法
int partation_v3(array_t<int>& array, int begin, int end)
{
	int pivot = array[end];
	int mark = begin;
	for (int i = begin; i < end; ++i)
	{
		if (array[i] < pivot)
		{
			swap(&array[mark], &array[i]);
			mark++;
		}
		else
		{
			//++i
		}
	}
	swap(&array[mark], &array[end]);//不管哪种分区法，基准元素都要放到分区位置
	return mark;
}


/*
def Partition(A, p, r) :
	# 输入：对A[p..r]进行划分
	# 输出：划分完成后pivot的新位置

	pivot = A[r]
	nextExchangeId = p
	# i要从p开始，防止A[p]是 < pivot的元素，后面被换到 >= pivot的一边
	for i in range(p, r) :
		if A[i] < pivot :
			A[nextExchangeId], A[i] = A[i], A[nextExchangeId]
			nextExchangeId += 1
			# 最后将pivot换到中间，并返回这个中间位置，用于下次Partition
	A[nextExchangeId], A[r] = A[r], A[nextExchangeId]
	return nextExchangeId*/


//挖坑填数法，优点是埋坑，不用交换元素，减少交换次数
int partation_v4(array_t<int>& array, int begin, int end) //返回调整后基准数的位置  
{
	int i = begin;
	int j = end;
	int pivot = array[begin]; //s[l]即s[i]就是第一个坑  
	while (i < j)
	{
		// 从右向左找小于x的数来填s[i] 
		while (i < j && array[j] >= pivot)
		{
			j--;
		}

		if (i < j)
		{
			array[i] = array[j];//将s[j]填到s[i]中，s[j]就形成了一个新的坑
			i++;
		}

		//从左向右找大于或等于x的数来填s[j]
		while (i < j && array[i] < pivot)
		{
			i++;
		}
		if (i < j)
		{
			array[j] = array[i];//将s[i]填到s[j]中，s[i]就形成了一个新的坑
			j--;
		}
	}
	//退出时，i等于j。将x填到这个坑中。  
	array[i] = pivot; //不管哪种分区法，基准元素都要放到分区位置

	return i;
}

void quick_sort_c(array_t<int>& array, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}
	//std::cout << "===============" << std::endl;
	int idx = partation_v1(array, begin, end);
	quick_sort_c(array, begin, idx - 1);
	quick_sort_c(array, idx + 1, end);
}

//https://zhuanlan.zhihu.com/p/266835035
/*
快排要点:
1．先从数列中取出一个数作为基准数。
2．分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。
3．再对左右区间重复第二步，直到各区间只有一个数。
*/
void quick_sort(array_t<int>& array)
{
	quick_sort_c(array, 0, array.size() - 1);
}


int repartation(array_t<int>& array, int begin, int end)
{
	int pivot = array[begin];

	int left = begin;
	int right = end;

	while (left != right)//跟（left < right）一样， 下面的while（right > left）已经保证了
	{
		while (right > left&& array[right] < pivot)//小于等于基准值的放左边（> 或者 >= 都可以）
		{
			right--;
		}
		while (right > left&& array[left] >= pivot)//大于基准值的放右边(必须 <= ， 否则可能死循环)
		{
			left++;
		}
		if (left < right)
		{
			swap(&array[left], &array[right]);
		}
	}
	swap(&array[begin], &array[left]);//不管哪种分区法，基准元素都要放到分区位置

	return left;

}

//找第K个元素，那么index肯定落在第index-1
int find_no_n_c(array_t<int>& array, int k, int begin, int end)
{
	std::cout << "find:" << k << "from:";
	for (int i = begin; i <= end; ++i)
	{
		std::cout << array[i] << ",";
	}
	std::cout << std::endl;

	if (begin >= end)
	{
		return array[begin];
	}
	int partation = repartation(array, begin, end);
	std::cout << "partation:" << partation << std::endl << std::endl;

	if (k > (partation + 1))
	{
		return find_no_n_c(array, k, partation + 1, end);
	}
	else if (k < (partation + 1))
	{
		return find_no_n_c(array, k, begin, partation - 1);
	}
	else
	{
		return array[partation];//?
	}
}

//找第K个元素，那么index肯定落在第index-1
int find_no_n(array_t<int>& array, int idx)
{
	if (idx > array.size() || idx <= 0)
	{
		return -1;
	}
	//int k = array.size() - idx + 1;
	return find_no_n_c(array, idx, 0, array.size()-1);
}