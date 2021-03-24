#include <iostream>
#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    static void reheapDown(T* start, T*end , int index)
    {
        if (end-start <= 0 || index<0 || index>end-start) return;

        T* left = start+(index * 2 + 1);
        T* right = start+(index * 2 + 2);
        T* large;
        if (left <= end) {
            if (right <= end && *right > *left)
                large = right;
            else
                large = left;
            if (*large > *(start+index)) {
                std::swap(*large, *(start + index));
                reheapDown(start, end, large-start);
            }
        }

    }
    //Helping functions go here
    static void heapSort(T* start, T* end) {
        //TODO
       
        int position = (end - start) / 2 - 1;
        while (position >= 0) {
            reheapDown(start, end - 1, position);
            position = position - 1;
        }
        Sorting<T>::printArray(start, end);
        T *last = end-1;
        while (last > start) {
            swap(*start, *last);
            last = last - 1;
            reheapDown(start, last, 0);
        }
            
        Sorting<T>::printArray(start, end);
    }

};
#endif /* SORTING_H */
int main()
{
    int arr[4] = { -1,0,2,3 };
    Sorting<int>::heapSort(&arr[0], &arr[4]);


}

