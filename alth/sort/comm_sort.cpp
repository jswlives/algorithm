
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
ð������
���Ӷ�: O(n2)
Ҫ�㣺������Ԫ�������
ȱ�㣺���������Ȳ��������
*/
void pop_sort(array_t<int>& array)
{
	for (int j = array.size() -1; j >= 0; --j)//����Խ��
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
��������
���Ӷ�:O(n2)
Ҫ�㣺�����������δ�������䡣��ʼ����������ֻ��һ��Ԫ�أ���������ĵ�һ��Ԫ�ء������㷨�ĺ���˼����ȡδ���������е�Ԫ�أ�
	���������������ҵ����ʵĲ���λ�ý�����룬����֤��������������һֱ�����ظ�������̣�ֱ��δ����������Ԫ��Ϊ�գ��㷨����
�ŵ㣺����ð������Ԫ�ؽ���������
*/

void insert_sort(array_t<int>& array)
{
	for (int j = 1; j < array.size(); ++j)//����Խ��
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
ѡ������
���Ӷȣ�O(n2)
Ҫ�㣺�������������δ�������䣬ÿ�λ��δ�����������ҵ���С��Ԫ�أ�����ŵ������������ĩβ����֮����
ȱ��:���ȶ�����
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

//ʱ�临�Ӷ�O(nlogn),���ռ临�Ӷ���O(n)
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
		while (right > left && array[right] >= array[pivot])//��>�� ���ڻ�׼ֵ��ҪŲ��ȥ
		{
			right--;
		}
		while (right > left && array[left] <= array[pivot])//��>=�� ���ڻ�׼ֵ������������Ų
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
����Ҫ��:
1���������Ƭ����������
2���ٶ���������ݹ�����
*/
void quick_sort(array_t<int>& array)
{
	quick_sort_c(array, 0, array.size() - 1);
}