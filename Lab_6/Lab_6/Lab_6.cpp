#include<iostream>
using namespace std;

void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    if (numberOfElements <= 0 || index<0 || index>numberOfElements) return;

    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int large = 0;
    if (left <= numberOfElements - 1) {
        if (right <= numberOfElements && maxHeap[right] > maxHeap[left])
            large = right;
        else
            large = left;
        if (maxHeap[large] > maxHeap[index]) {
            std::swap(maxHeap[large], maxHeap[index]);
            reheapDown(maxHeap, numberOfElements, large);
        }
    }

}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if (numberOfElements <= 0 || index<0 || index>numberOfElements) return;
    if (index > 0) {
        int parent = (index - 1) / 2;
        if (maxHeap[index] > maxHeap[parent]) {
            std::swap(maxHeap[index], maxHeap[parent]);
            reheapUp(maxHeap, numberOfElements, parent);
        }
    }
}


template <class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    int getItem(T item);
    void remove(T item);
    void clear();
    int size();
    bool isEmpty();
    T peek();
    bool contains(T item);
    bool pop();
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }


private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};
template<class T>
void Heap<T>::push(T item) {
    if (count >= capacity) ensureCapacity(10);
    int last = count;
    elements[last] = item;
    count++;
    reheapUp(last);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    this->capacity = this->capacity + minCapacity;
    T* el = new T[capacity];
    for (int i = 0; i < count; i++) {
        el[i] = elements[i];
    }
    this->elements = new T[capacity];
    for (int i = 0; i < count; i++) {
        elements[i] = el[i];
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    if (count > capacity || position<0 || position>count) return;
    if (position > 0) {
        int parent = (position - 1) / 2;
        if (elements[position] > elements[parent]) {
            std::swap(elements[position], elements[parent]);
            reheapUp(parent);
        }
    }
}

template <class T>
int Heap<T>::getItem(T item)
{
    // TODO: return the index of item in heap
    if (count > capacity) return -1;
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == item)
            return i;
    }
    return -1;
}
template <class T>
void Heap<T>::remove(T item)
{
    // TODO: remove the element with value equal to item
    if (count > capacity) return;
    int index = getItem(item);
    if (index > -1)
    {
        elements[index] = elements[count - 1];
        count--;
        ensureCapacity(-1);
        this->capacity += 1;
        reheapDown(index);
    }
}

template <class T>
void Heap<T>::clear()
{
    // TODO: delete all elements in heap
    delete[] elements;
    capacity = 10;
    count = 0;
    elements = new T[capacity];
}


template<class T>
int Heap<T>::size() {
    return count;
}

template<class T>
bool Heap<T>::isEmpty() {
    return (count == 0);
}

template<class T>
T Heap<T>::peek() {
    return elements[0];
}

template<class T>
bool Heap<T>::contains(T item) {
    if (count == 0)return 0;
    // TODO: return the index of item in heap
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == item)
            return 1;
    }
    return 0;
}

template<class T>
bool Heap<T>::pop() {
    if (count == 0)return 0;
    int index = 0;

    elements[index] = elements[count - 1];
    count--;
    reheapUp(index);
    reheapDown(index);

    return 1;
}

int main()
{
    std::cout << "Hello World!\n";
}
