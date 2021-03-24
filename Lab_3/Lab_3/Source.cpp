#ifndef SORTING_H
#define SORTING_H

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
	static void printArray(T* start, T* end)
	{
		int size = end - start;
		for (int i = 0; i < size; i++)
			cout << start[i] << " ";
		cout << endl;
	}

	static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);

public:
	static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
	static void selectionSort(T* start, T* end);
	static void oddEvenSort(T* start, T* end);
};

#endif /* SORTING_H */

template<class T>
void Sorting<T>::sortSegment(T* start, T* end, int segment_idx, int cur_segment_total)
{
	T* current = start + segment_idx + cur_segment_total;
	while (current < end) {
		T temp = *current;
		T* walker = current - cur_segment_total;
		while (walker >= start && (temp) < *walker) {
			*(walker + cur_segment_total) = *(walker);
			walker = walker - cur_segment_total;
		}
		*(walker + cur_segment_total) = temp;
		current = current + cur_segment_total;
	}
}
template<class T>
void Sorting<T>::ShellSort(T* start, T* end, int* num_segment_list, int num_phases)
{
	int n = start - end;
	for (int i = 0; i < num_phases; i++) {
		int segment = 0;
		while (segment < num_segment_list[num_phases - i - 1]) {
			sortSegment(start, end, segment, num_segment_list[num_phases - i - 1]);
			segment += 1;
		}
		cout << num_segment_list[num_phases - i - 1] << " segments: ";
		printArray(start, end);
	}

}
template<class T>
void Sorting<T>::selectionSort(T* start, T* end)
{
	T* curr = start;
	while (curr < end - 1) {
		T* smallest = curr;
		T* walker = curr + 1;
		while (walker < end) {
			if (*walker < *smallest) smallest = walker;
			walker += 1;
		}

		T tmp = *curr;
		*curr = *smallest;
		*smallest = tmp;
		curr += 1;
		printArray(start, end);
	}

}
template <class T>
void Sorting<T>::oddEvenSort(T* start, T* end)
{
	while (1)
	{
		int count = 0;

		T* crr = start;
		while (crr + 2 <= end) {
			if (*crr > * (crr + 1)) {
				T temp = *crr;
				*crr = *(crr + 1);
				*(crr + 1) = temp;
				count++;
			}
			crr = crr + 2;

		}
		T* curr = start + 1;
		while (curr + 2 <= end) {
			if (*curr > * (curr + 1)) {
				T temp = *curr;
				*curr = *(curr + 1);
				*(curr + 1) = temp;
				count++;
			}
			curr = curr + 2;
		}

		
		printArray(start, end);
	
		if (count == 0) break;
	}
}
template <class T>
class SLinkedList {
public:
	class Node; // Forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	~SLinkedList() {};
	void add(T e)
	{
		Node* pNew = new Node(e);

		if (this->count == 0)
		{
			this->head = this->tail = pNew;
		}
		else
		{
			this->tail->next = pNew;
			this->tail = pNew;
		}

		this->count++;
	}
	int size()
	{
		return this->count;
	}
	void printList()
	{
		stringstream ss;
		ss << "[";
		Node* ptr = head;
		while (ptr != tail)
		{
			ss << ptr->data << ",";
			ptr = ptr->next;
		}

		if (count > 0)
			ss << ptr->data << "]";
		else
			ss << "]";
		cout << ss.str() << endl;
	}
public:
	class Node {
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node() {
			next = 0;
		}
		Node(T data) {
			this->data = data;
			this->next = nullptr;
		}
	};

	void bubbleSort();
};

template<class T>
void SLinkedList<T>::bubbleSort()
{
	Node* current = tail;
	while (current != head) {
		Node* walker = head;
		while (walker != current)
		{
			if (walker->data > walker->next->data) {

				T temp = walker->data;
				walker->data = walker->next->data;
				walker->next->data = temp;
			}
			walker = walker->next;
		}
		Node* prev = head;
		while (prev->next != current) {
			prev = prev->next;
		}
		current = prev;
		printList();
	}
}
int main() {
	/*int num_segment_list[] = { 1, 3, 5 };
	int num_phases = 3;
	int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

	Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
	for (int i = 0; i < 10; i++) cout << array[i] << ", ";
	cout << endl;*/
	/*int arr[] = { 9, 2, 8, 1, 0, -2 };
	Sorting<int>::selectionSort(&arr[0], &arr[6]);*/
	/*int arr[] = { 1,2,3,4,5 };
	SLinkedList<int> list;
	for (int i = 0; i < int(sizeof(arr)) / 4; i++)
		list.add(arr[i]);
	list.bubbleSort();*/
	/*int num_segment_list[] = { 1, 3, 5 };
	int num_phases = 3;
	int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

	Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);*/
	int arr[] = { 9, 30, 1, -7, 7, -9, 5, 6,-1,-2 };
	Sorting<int>::oddEvenSort(&arr[0], &arr[10]);

}