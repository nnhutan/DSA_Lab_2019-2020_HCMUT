#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <exception>
#include <stdexcept>
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
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true);
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true);
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
    else
    {
        while (ptr != this->tail)
        {
            ss << ptr->data << ", ";
            ptr = ptr->next;
        }
        ss << ptr->data << "]";
    }
    return ss.str();
}

//DESTRUCTOR
template <class T>
FragmentLinkedList<T>::~FragmentLinkedList()
{
    this->clear();
}

//ADD
template <class T>
void FragmentLinkedList<T>::add(const T &element)
{
    if (empty())
        this->fragmentPointers[0] = this->tail = new Node(element, NULL, NULL);
    else
        this->tail = this->tail->next = new Node(element, NULL, this->tail);
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
        this->fragmentPointers[0] = this->fragmentPointers[0]->prev = new Node(element, this->fragmentPointers[0], NULL);
    else
    {
        Node *pnode = this->fragmentPointers[0];
        for (int i = 0; i < index - 1; i++)
        {
            pnode = pnode->next;
        }
        pnode->next = pnode->next->prev = new Node(element, pnode->next, pnode);
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

//REMOVE AT INDEX
template <class T>
T FragmentLinkedList<T>::removeAt(int index)
{
    if (empty() || index >= this->count || index < 0)
        throw out_of_range("The index is out of range!");
    T value = this->get(index);
    Node *pnode = this->fragmentPointers[0];
    if (index == 0)
        this->fragmentPointers[0] = this->fragmentPointers[0]->next;
    else
    {
        for (int i = 0; i < index; i++)
            pnode = pnode->next;
        if (index == this->count - 1)
            this->tail = pnode->prev;
        else
            pnode->next->prev = pnode->prev;
        pnode->prev->next = pnode->next;
    }
    this->count--;
    delete pnode;
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
    if (this->indexOf(item) == -1)
        return 0;
    this->removeAt(this->indexOf(item));
    return true;
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
    while (this->fragmentPointers[0] != NULL)
    {
        Node *tmp = this->fragmentPointers[0];
        this->fragmentPointers[0] = this->fragmentPointers[0]->next;
        delete tmp;
    }
    this->count = 0;
    delete[] fragmentPointers;
    this->fragmentPointers = new Node *[2];
    this->fragmentPointers[0] = NULL;
    this->fragmentPointers[1] = NULL;
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
    int i = 0;
    while (pnode != NULL)
    {
        if (pnode->data == item)
        {
            return i;
        }
        i++;
        pnode = pnode->next;
    }
    return -1;
}

//CONTAINS
template <class T>
bool FragmentLinkedList<T>::contains(const T &item)
{
    return (this->indexOf(item) != -1);
}

//BEGIN
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::begin(int index)
{
    return Iterator(index, this, 1);
}

//END
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::end(int index)
{
    return Iterator(index, this, 0);
}

//CONSTRUCTOR OF CLASS ITERATOR
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, bool begin)
{
    this->pList = pList;
    if (!pList)
    {
        this->pNode = NULL;
        this->index = -1;
        return;
    }
    if (begin)
    {
        this->pNode = pList->fragmentPointers[0];
        this->index = 0;
    }
    else
    {
        this->pNode = NULL;
        this->index = this->pList->size();
    }
}

//CONSTRUCTOR OF CLASS ITERATOR
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(int fragmentIndex, FragmentLinkedList<T> *pList, bool begin)
{
    this->pList = pList;
    if (!pList || (!begin && fragmentIndex == -1))
    {
        this->pNode = NULL;
        this->index = -1;
        return;
    }
    if (begin)
    {
        this->pNode = pList->fragmentPointers[fragmentIndex];
        this->index = fragmentIndex * (this->pList->fragmentMaxSize);
    }
    else
    {
        this->pNode = this->pList->fragmentPointers[fragmentIndex];
        for (int i = 0; i < (this->pList->fragmentMaxSize); i++)
        {
            this->pNode = this->pNode->next;
            if (this->pNode == NULL)
                break;
        }
        this->index = (fragmentIndex + 1) * (this->pList->fragmentMaxSize);
        if (this->index >= this->pList->size())
            this->index = this->pList->size() - 1;
    }
}

//OPERATOR =
template <class T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
    //Iterator *it = new Iterator(pList, true);
    this->pList = iterator.pList;
    this->pNode = iterator.pNode;
    this->index = iterator.index;
    //*this = iterator;
    return *this;
}

//OPERATOR *
template <typename T>
T &FragmentLinkedList<T>::Iterator::operator*()
{
    if ((this->pNode) == NULL)
        throw std::out_of_range("Segmentation fault!");
    return this->pNode->data;
}

// OPERATOR !=
template <typename T>
bool FragmentLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
    return (this->pNode != iterator.pNode);
}

//REMOVE ITERATOR
template <typename T>
void FragmentLinkedList<T>::Iterator::remove()
{
    if (this->pNode == NULL)
        throw std::out_of_range("Segmentation fault!");
    if (this->index == 0)
    {
        this->pList->removeAt(this->index);
        this->pNode = NULL;
        this->index = -1;
    }
    else
    {
        this->pNode = this->pList->fragmentPointers[0];
        for (int i = 0; i < this->index - 1; i++)
        {
            this->pNode = this->pNode->next;
        }
        this->pList->removeAt(this->index);
        this->index -= 1;
    }
}

//SET ITERATOR
template <typename T>
void FragmentLinkedList<T>::Iterator::set(const T &element)
{
    this->pNode->data = element;
}

//OPERATOR ++IT
template <typename T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator++()
{
    if (this->index == -1)
        this->pNode = this->pList->fragmentPointers[0];
    else if (this->index == this->pList->size())
        throw std::out_of_range("Segmentation fault!");
    else
        this->pNode = this->pNode->next;
    this->index += 1;
    return *this;
}

//OPERATOR IT++
template <typename T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    if (this->index == -1)
        this->pNode = this->pList->fragmentPointers[0];
    else if (this->index == this->pList->size())
        throw std::out_of_range("Segmentation fault!");
    else
        this->pNode = this->pNode->next;
    this->index += 1;
    return tmp;
}

#endif
// END: STUDENT ANSWER

int main()
{
    // TESTCASE INPUT
    // === Example
    /*FragmentLinkedList<int> fList;
	 for(int i = 0; i < 20 ; i++)
		 fList.add(i, i +1);
	 cout << fList.toString() << endl;
	 for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
		 cout << *it << " ";
	 cout << endl;*/
    FragmentLinkedList<int> fList;
    for (int i = 0; i < 20; i++)
        fList.add(i * 2);
    cout << fList.toString();
    cout << endl;
    FragmentLinkedList<int>::Iterator i = fList.begin();
    i.remove();
    i.remove();
    i++;
    for (FragmentLinkedList<int>::Iterator v = fList.begin(); v != fList.end(2); v++)
    {
        cout << *v << " ";
    }
    cout << endl;
    cout << fList.toString();
    return 0;
}
