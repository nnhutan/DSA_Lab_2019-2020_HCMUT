

#include <stddef.h>
#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cstdlib>
#include <stdexcept>
#include <cwchar>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T &element) = 0;
    virtual void add(int index, const T &element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T &item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T &element) = 0;
    virtual int indexOf(const T &item) = 0;
    virtual bool contains(const T &item) = 0;
    virtual string toString() = 0;
};

#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    Node *tail;
    int fragmentMaxSize;
    int count;

public:
    FragmentLinkedList(int fragmentMaxSize = 3)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
        this->tail = NULL;
    }
    virtual ~FragmentLinkedList();
    virtual void add(const T &element);
    virtual void add(int index, const T &element);
    virtual T removeAt(int index);
    virtual bool removeItem(const T &item);
    virtual bool empty();
    virtual int size();
    virtual void clear();
    virtual T get(int index);
    virtual void set(int index, const T &element);
    virtual int indexOf(const T &item);
    virtual bool contains(const T &item);
    virtual string toString();
    Iterator begin(int index = 0);
    Iterator end(int index = -1);

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true);
        Iterator(FragmentLinkedList<T> *pList = 0, int fragmentIndex = 0, bool begin = true);
        Iterator &operator=(const Iterator &iterator);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        void set(const T &element);
        Iterator &operator++();
        Iterator operator++(int);
    };
};

//IMPLEMENTATION
//TO STRING
template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];
    if (this->count == 0)
        ss << "]";
    {
        ss << ptr->data;

        while (ptr->next != NULL)
        {
            ptr = ptr->next;
            ss << ", " << ptr->data;
        }

        ss << "]";
    }
    return ss.str();
}

//DESTRUCTOR
template <class T>
FragmentLinkedList<T>::~FragmentLinkedList()
{
    if (!empty())
    {
        if (this->fragmentPointers[0]->next == NULL)
        {
            Node *pnode = this->fragmentPointers[0];
            this->fragmentPointers[0] = NULL;
            this->tail = NULL;
            delete pnode;
        }
        else
        {
            for (Node *pnode = this->fragmentPointers[0]; pnode != NULL; pnode = pnode->next)
            {
                Node *tmp = pnode;
                delete tmp;
            }
            this->tail = NULL;
            this->fragmentPointers[0] = NULL;
            for (int i = 0; i < ((this->count - 1) / this->fragmentMaxSize) + 2; i++)
                this->fragmentPointers[i] = NULL;
        }
    }
    delete[] fragmentPointers;
    fragmentPointers = new Node *[2];
    fragmentPointers[0] = NULL;
    fragmentPointers[1] = NULL;
    this->count = 0;
    this->fragmentMaxSize = 0;
}

//ADD
template <class T>
void FragmentLinkedList<T>::add(const T &element)
{
    if (empty())
    {
        Node *node = new Node(element, NULL, NULL);
        this->fragmentPointers[0] = node;
        this->tail = node;
    }
    else
    {
        Node *node = new Node(element, NULL, this->tail);
        this->tail->next = node;
        this->tail = node;
    }
    this->count++;
    int n = ((this->count - 1) / this->fragmentMaxSize);
    Node **fragTemp = new Node *[n + 2];
    fragTemp[n + 1] = this->tail;
    Node *node = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if (i % this->fragmentMaxSize == 0)
            fragTemp[i / this->fragmentMaxSize] = node;
        node = node->next;
    }
    delete[] fragmentPointers;
    this->fragmentPointers = fragTemp;
}

//ADD AT INDEX
template <class T>
void FragmentLinkedList<T>::add(int index, const T &element)
{
    if (empty() || index >= this->count)
    {
        add(element);
        return;
    }
    else if (index <= 0)
    {
        Node *node = new Node(element, this->fragmentPointers[0], NULL);
        this->fragmentPointers[0]->prev = node;
        this->fragmentPointers[0] = node;
        this->count++;
    }
    else
    {
        Node *pnode = this->fragmentPointers[0];
        for (int i = 0; i < index; i++)
        {
            pnode = pnode->next;
        }
        Node *node = new Node(element, pnode, pnode->prev);
        pnode->prev->next = node;
        pnode->prev = node;
        this->count++;
    }
    int n = ((this->count - 1) / this->fragmentMaxSize);
    Node **fragTemp = new Node *[n + 2];
    fragTemp[n + 1] = this->tail;
    Node *node = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if (i % this->fragmentMaxSize == 0)
            fragTemp[i / this->fragmentMaxSize] = node;
        node = node->next;
    }
    delete[] fragmentPointers;
    this->fragmentPointers = fragTemp;
}

//REMOVE AT INDEX
template <class T>
T FragmentLinkedList<T>::removeAt(int index)
{
    if (empty() || index >= this->count || index < 0)
        throw out_of_range("The index is out of range!");
    if ((this->count) == 1 && index == 0)
    {
        Node *pnode = this->fragmentPointers[0];
        this->fragmentPointers[0] = NULL;
        this->tail = NULL;
        T value = pnode->data;
        delete pnode;
        this->count--;
        int n = ((this->count - 1) / this->fragmentMaxSize);
        Node **fragTemp = new Node *[n + 2];
        fragTemp[n + 1] = this->tail;
        Node *node = this->fragmentPointers[0];
        for (int i = 0; i < this->count; i++)
        {
            if (i % this->fragmentMaxSize == 0)
                fragTemp[i / this->fragmentMaxSize] = node;
            node = node->next;
        }
        delete[] fragmentPointers;
        this->fragmentPointers = fragTemp;
        return value;
    }
    if ((this->count) != 1 && index == 0)
    {
        Node *pnode = this->fragmentPointers[0];
        T value = pnode->data;
        this->fragmentPointers[0]->next->prev = NULL;
        this->fragmentPointers[0] = pnode->next;
        delete pnode;
        this->count--;
        int n = ((this->count - 1) / this->fragmentMaxSize);
        Node **fragTemp = new Node *[n + 2];
        fragTemp[n + 1] = this->tail;
        Node *node = this->fragmentPointers[0];
        for (int i = 0; i < this->count; i++)
        {
            if (i % this->fragmentMaxSize == 0)
                fragTemp[i / this->fragmentMaxSize] = node;
            node = node->next;
        }
        delete[] fragmentPointers;
        this->fragmentPointers = fragTemp;
        return value;
    }
    if (index == (this->count) - 1)
    {
        Node *pnode = this->tail;
        T value = pnode->data;
        this->tail->prev->next = NULL;
        this->tail = pnode->prev;
        delete pnode;
        this->count--;
        int n = ((this->count - 1) / this->fragmentMaxSize);
        Node **fragTemp = new Node *[n + 2];
        fragTemp[n + 1] = this->tail;
        Node *node = this->fragmentPointers[0];
        for (int i = 0; i < this->count; i++)
        {
            if (i % this->fragmentMaxSize == 0)
                fragTemp[i / this->fragmentMaxSize] = node;
            node = node->next;
        }
        delete[] fragmentPointers;
        this->fragmentPointers = fragTemp;
        return value;
    }
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < index; i++)
    {
        pnode = pnode->next;
    }
    T value = pnode->data;
    pnode->next->prev = pnode->prev;
    pnode->prev->next = pnode->next;
    delete pnode;
    this->count--;
    int n = ((this->count - 1) / this->fragmentMaxSize);
    Node **fragTemp = new Node *[n + 2];
    fragTemp[n + 1] = this->tail;
    Node *node = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if (i % this->fragmentMaxSize == 0)
            fragTemp[i / this->fragmentMaxSize] = node;
        node = node->next;
    }
    delete[] fragmentPointers;
    this->fragmentPointers = fragTemp;
    return value;
}

//REMOVE ITEM
template <class T>
bool FragmentLinkedList<T>::removeItem(const T &item)
{
    if (empty())
        return 0;
    int t = 0;
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if ((pnode->data) == item)
        {
            if (this->count == 1)
            {
                this->fragmentPointers[0] = NULL;
                this->tail = NULL;
            }
            else if (pnode == this->fragmentPointers[0])
            {
                pnode->next->prev = NULL;
                this->fragmentPointers[0] = pnode->next;
            }
            else if (i == this->count - 1)
            {
                this->tail->prev->next = NULL;
                this->tail = this->tail->prev;
            }
            else
            {
                pnode->prev->next = pnode->next;
                pnode->next->prev = pnode->prev;
            }
            Node *tmp = pnode;
            pnode = pnode->next;
            delete tmp;
            t++;
        }
        else
            pnode = pnode->next;
    }
    this->count -= t;
    int n = ((this->count - 1) / this->fragmentMaxSize);
    Node **fragTemp = new Node *[n + 2];
    fragTemp[n + 1] = this->tail;
    Node *node = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if (i % this->fragmentMaxSize == 0)
            fragTemp[i / this->fragmentMaxSize] = node;
        node = node->next;
    }
    delete[] fragmentPointers;
    this->fragmentPointers = fragTemp;
    return t;
}

//EMPTY
template <class T>
bool FragmentLinkedList<T>::empty()
{
    return this->count < 1;
}

//SIZE
template <class T>
int FragmentLinkedList<T>::size()
{
    return this->count;
}

//CLEAR
template <class T>
void FragmentLinkedList<T>::clear()
{
    if (empty())
        return;
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        Node *tmp = pnode;
        pnode = pnode->next;
        delete tmp;
    }
    for (int i = 0; i < ((this->count - 1) / this->fragmentMaxSize) + 2; i++)
        this->fragmentPointers[i] = NULL;
    this->count = 0;
    this->tail = NULL;
}

//GET
template <class T>
T FragmentLinkedList<T>::get(int index)
{
    if (empty() || index < 0 || index >= this->count)
        throw out_of_range("The index is out of range!");
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < index; i++)
        pnode = pnode->next;
    return pnode->data;
}

//SET
template <class T>
void FragmentLinkedList<T>::set(int index, const T &element)
{
    if (empty() || index < 0 || index >= this->count)
        throw out_of_range("The index is out of range!");
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < index; i++)
        pnode = pnode->next;
    pnode->data = element;
}

//INDEX OF ITEM
template <class T>
int FragmentLinkedList<T>::indexOf(const T &item)
{
    if (empty())
        return -1;
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if (pnode->data == item)
            return i;
        pnode = pnode->next;
    }
    return -1;
}

//CONTAINS
template <class T>
bool FragmentLinkedList<T>::contains(const T &item)
{
    if (empty())
        return 0;
    Node *pnode = this->fragmentPointers[0];
    for (int i = 0; i < this->count; i++)
    {
        if (pnode->data == item)
            return 1;
        pnode = pnode->next;
    }
    return 0;
}

//BEGIN
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::begin(int index)
{
    Iterator iterator(this, index, 1);
    return iterator;
}

//END
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::end(int index)
{
    Iterator iterator(this, index, 0);
    return iterator;
}

//CONSTRUCTOR OF CLASS ITERATOR
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, bool begin)
{
    this->pList = pList;
    if (begin)
        this->pNode = pList->fragmentPointers[0];
    else
        this->pNode = NULL;
}

//CONSTRUCTOR OF CLASS ITERATOR
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, int fragmentIndex, bool begin)
{
    this->pList = pList;
    if (begin)
        this->pNode = pList->fragmentPointers[fragmentIndex];
    else
    {
        if (fragmentIndex == -1)
            this->pNode = NULL;
        else
        {
            this->pNode = this->pList->fragmentPointers[fragmentIndex];
            for (int i = 0; i < (this->pList->fragmentMaxSize); i++)
            {
                this->pNode = this->pNode->next;
                if (this->pNode == NULL)
                    break;
            }
        }
    }
}

//OPERATOR =
template <class T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
    *this = iterator;
    return *this;
}

//OPERATOR *
template <typename T>
T &FragmentLinkedList<T>::Iterator::operator*()
{
    if (this->pNode == NULL)
        return this->pList->fragmentPointers[0]->data;
    return this->pNode->data;
}

// OPERATOR !=
template <typename T>
bool FragmentLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
    return !(this->pNode == iterator.pNode);
}

//OPERATOR ++IT
template <typename T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator++()
{
    if (pNode == NULL)
        pNode = this->pList->fragmentPointers[0];
    else
        pNode = pNode->next;
    return *this;
}

//OPERATOR IT++
template <typename T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    if (this == NULL)
        *this = this->pList->begin();
    else
        ++(*this);
    return temp;
}

//REMOVE ITERATOR
template <typename T>
void FragmentLinkedList<T>::Iterator::remove()
{
    Iterator iterator = this->pList->begin();
    int i = 0;
    for (iterator; iterator != *this; iterator++)
    {
        i++;
    }
    this->pNode = iterator.pNode->prev;
    this->pList->removeAt(i);
}

//SET ITERATOR
template <typename T>
void FragmentLinkedList<T>::Iterator::set(const T &element)
{
    this->pNode->data = element;
}
#endif
// END: STUDENT ANSWER

int main()
{
    FragmentLinkedList<int> fList;
    //  FragmentLinkedList<int>* t;
    for (int i = 0; i < 10; i++)
        fList.add(i, i + 1);
    cout << fList.toString() << endl;
    /*for (int i = 0; i < 3; i++)
		fList.add(i+1);
	
	cout << fList.toString() << endl;
	fList.removeItem(3);
	cout << fList.toString() << endl;*/
    /*FragmentLinkedList<int>::Iterator it = fList.begin(0);
	it.remove();

	it++;
	it.remove();*/

    /*cout << fList.toString() << endl;
	for (FragmentLinkedList<int>::Iterator it = fList.begin(1); it != fList.end(3); it++) { it.set(0); }*/

    for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
        cout << *it << " ";
    cout << endl;

    return 0;
}
