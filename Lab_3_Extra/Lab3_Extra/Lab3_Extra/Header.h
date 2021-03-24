#pragma once
#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting
{
private:
    static T *Partition(T *start, T *end);

public:
    static void QuickSort(T *start, T *end);
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *left, T *middle, T *right);
    static void mergeSort(T *start, T *end);
    static void insertionSort(T *start, T *end);
    static void hybridQuickSort(T *start, T *end, int min_size);
    static void TimSort(T *start, T *end, int min_size);
};
#endif /* SORTING_H */
