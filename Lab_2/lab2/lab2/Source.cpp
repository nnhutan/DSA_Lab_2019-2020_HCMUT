#include<iostream>
#include "Source1.cpp"
#include <cassert>
template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void push(T item);
    T pop();
    T top();
    bool empty();
    int size();
    void clear();
};
template <class T>
void Stack<T>::push(T item) {
    // TODO: Push new element into the top of the stack
    this->list.add(0, item);

}

template <class T>
T Stack<T>::pop() {
    // TODO: Remove an element on top of the stack
    return this->list.removeAt(0);

}

template <class T>
T Stack<T>::top() {
    // TODO: Get value of the element on top of the stack

    return this->list.get(0);
}
template <class T>
bool Stack<T>::empty() {
    // TODO: Determine if the stack is empty
    return this->size() == 0;

}
template <class T>

int  Stack<T>::size() {
    // TODO: Get the size of the stack
    return this->list.size();
}
template <class T>
void Stack<T>::clear() {
    // TODO: Clear all elements of the stack
    this->list.clear();

}

int main() {
    Stack<int> stack;

    int item[] = { 3, 1, 4, 5, 2, 8, 10, 12 };
    for (int idx = 0; idx < 8; idx++) stack.push(item[idx]);

    assert(stack.top() == 12);

    stack.pop();
    stack.pop();

    cout << stack.top();
}