#include <sstream>
#include <iostream>
#include <type_traits>
#include "Header.h"
#include <string>
using namespace std;

template <class T>
T *Sorting<T>::Partition(T *start, T *end)
{
	// TODO: return the pointer which points to the pivot after rearrange the array.
	cout << "Quick sort: ";
	printArray(start, end);
	T *p = start;
	T *i = start;
	T *j = end;
	while (i < j)
	{
		do
		{
			i = i + 1;
		} while (*i < *p);
		do
		{
			j = j - 1;
		} while (*j > *p);
		T temp = *i;
		*i = *j;
		*j = temp;
	}
	if (i >= j)
	{
		T temp = *i;
		*i = *j;
		*j = temp;
	}
	T temp = *p;
	*p = *j;
	*j = temp;
	//	cout << j - start << " ";

	return j;
}
template <class T>
void Sorting<T>::QuickSort(T *start, T *end)
{
	// TODO
	// In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
	if (start < end)
	{
		T *p = Partition(start, end);
		QuickSort(start, p);
		QuickSort(p + 1, end);
	}
}
template <class T>
void Sorting<T>::merge(T *left, T *middle, T *right)
{
	int n = right - left + 1;

	T *temp = new T(n);
	T *l = left, *m = middle + 1;
	for (int i = 0; i < n; i++)
	{
		if (l > middle)
		{
			temp[i] = *m;
			m++;
		}
		else if (m >= right)
		{
			temp[i] = *l;
			l++;
		}
		else if (*l < *m)
		{
			temp[i] = *l;
			l++;
		}
		else
		{
			temp[i] = *(m);
			m++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		*(left + i) = temp[i];
	}
	//delete[] temp;
}
template <class T>
void Sorting<T>::mergeSort(T *start, T *end)
{

	if (start == end)
		return;
	int n = ((end - start) / 2);
	mergeSort(start, start + n);
	mergeSort(start + n + 1, end);
	merge(start, start + n, end);
}

template <class T>
void Sorting<T>::insertionSort(T *start, T *end)
{
	T *current = start + 1;
	while (current < end)
	{
		T temp = *current;
		T *walker = current - 1;
		while (walker >= start && *walker > temp)
		{
			*(walker + 1) = *walker;
			walker = walker - 1;
		}
		*(walker + 1) = temp;
		current++;
	}
}

template <class T>
void Sorting<T>::hybridQuickSort(T *start, T *end, int min_size)
{

	if (end - start >= min_size && end > start)
	{
		T *p = Partition(start, end);
		hybridQuickSort(start, p, min_size);
		hybridQuickSort(p + 1, end, min_size);
	}
	else if (end > start)
	{
		insertionSort(start, end);
		printArray(start, end);
	}
	//else if (start < end) insertionSort(start, end);
}
template <class T>
void Sorting<T>::TimSort(T *start, T *end, int min_size)
{
	if (end - start <= min_size || min_size == 0)
	{
		insertionSort(start, end);
		cout << "Insertion Sort: ";
		printArray(start, end);
		return;
	}
	T *s = start;
	while (s < end)
	{
		T *e;
		if (s + min_size >= end)
			e = end;
		else
			e = s + min_size;
		insertionSort(s, e);
		s = s + min_size;
	}
	cout << "Insertion Sort: ";
	printArray(start, end);
	s = start;
	int size = min_size;
	int count = 0;
	while (size < end - start)
	{
		while (s < end)
		{
			T *r;
			if (s + (size * 2) > end)
				r = end;
			else
				r = s + (size * 2);
			merge(s, s + size - 1, r);
			cout << "Merge " << ++count << ": ";
			printArray(start, end);
			s = s + (size * 2);
		}
		s = start;
		size = size * 2;
	}
	delete s;
}

bool isPermutation(string a, string b)
{
	//TODO
	int la = a.length(), lb = b.length();
	if (la != lb)
		return 0;
	else
	{
		for (int i = 0; i < la; i++)
		{
			for (int j = i + 1; j < la; j++)
			{
				if (a[j] < a[i])
				{
					char temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
		for (int i = 0; i < lb; i++)
		{
			for (int j = i + 1; j < lb; j++)
			{
				if (b[j] < b[i])
				{
					char temp = b[i];
					b[i] = b[j];
					b[j] = temp;
				}
			}
		}
		if (a == b)
			return 1;
		else
			return 0;
	}
}
int main()
{
	/*Sorting<int> s;
	int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
	cout << "Index of pivots: ";
	s.QuickSort(&array[0], &array[20]);
	cout << "\n";
	cout << "Array after sorting: ";
	for (int i : array) cout << i << " ";*/
	/*  Index of pivots : 2 0 0 6 1 0 2 1 0 0 2 1 0 0 0 0 0 0 1 0
		  Array after sorting : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20*/

	/*int arr[] = { 0,2,4,3,1,4,10,21,3,4,6,7,2,1,4,-5,-7,-9 };
	Sorting<int>::mergeSort(&arr[0], &arr[17]);*/
	//for (int i = 0; i < 6; i++) cout << arr[i] << " ";
	/*	0, 2
		0, 2, 4
		1, 3
		1, 3, 4
		0, 1, 2, 3, 4, 4*/
	/*int arr[] = { 1 };
		Sorting<int>::mergeSort(&arr[0], &arr[0]);
	*/
	//	int array[] = {1, 2, 6, 4, 7, 8, 5, 3};
	//int min_size = 4;
	//Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);
	//for (int i = 0; i < 8; i++)cout << array[i] << " ";
	// int array[] = {2, 6, 4, 12, 23, 1, 0, -12};
	// int min_size = 4;
	//Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);
	Sorting<int> s;
	int array[] = {19, 20, 18, 17, 12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3};
	int min_size = 4;
	s.TimSort(&array[0], &array[20], min_size);
	// Sorting<int> s;
	// int array[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	// int min_size = 4;
	// s.TimSort(&array[0], &array[10], min_size);
	///*string a = "abba";
	/*string b = "baba";
	cout << isPermutation(a, b);*/
}