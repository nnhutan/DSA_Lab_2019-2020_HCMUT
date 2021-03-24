#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T& element) = 0;
    virtual void add(int index, const T& element) = 0;
    virtual T& removeAt(int index) = 0;
    virtual bool removeItem(const T& item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T& get(int index) = 0;
    virtual void set(int index, const T& element) = 0;
    virtual int indexOf(const T& item) = 0;
    virtual bool contains(const T& item) = 0;
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
    Node** fragmentPointers;
    int fragmentMaxSize;
    int count;

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node * [2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList() {
    };
    virtual void add(const T& element) {
 
        if (this->fragmentPointers[0] == NULL) {
            Node* node = new Node(element,NULL,NULL);
            this->fragmentPointers[0] = node;
            this->fragmentPointers[1] = node;
    }
        else {
            Node* node = new Node(element, NULL, fragmentPointers[1]);
            fragmentPointers[1]->next = node;
            fragmentPointers[1] = node;
        }
        this->count++;
    }
    virtual void add(int index, const T& element) {
        if (empty()) {
            Node* node = new Node(element, NULL, NULL);
            this->fragmentPointers[0] = node;
            this->fragmentPointers[1] = node;
            this->count += 1;
            return;
       }
        if (index <= 0) {
            Node *node=new Node(element, this->fragmentPointers[0], NULL);
                this->fragmentPointers[0]->prev = node;
                this->fragmentPointers[0] = node;
                this->count++;
        }
        else if (index >= this->count) {
            add(element);
        }
        else {
            Node* pnode = this->fragmentPointers[0];
            for (int i = 0; i < index; i++) {
                pnode = pnode->next;
            }
            Node *node=new Node(element, pnode, pnode->prev);
            pnode->prev->next = node;
            pnode->prev = node;
            this->count++;
        }
        
    }
    virtual T& removeAt(int index) {
         if (empty() || index < 0 || index >= this->count) throw std::out_of_range("The index is out of range!"); 
        if (index == 0) {
            if ((this->count) - 1 == 1) {
                Node* pnode = this->fragmentPointers[0];
                T el = pnode->data;
                this->fragmentPointers[0] = NULL;
                this->fragmentPointers[1] = NULL;
               // delete pnode;
                this->count--;
                return pnode->data;
            }
            else {
                Node* pnode = this->fragmentPointers[0];
                T el = pnode->data;
                pnode->next->prev = NULL;
                this->fragmentPointers[0] = pnode->next;
                //delete pnode;
                this->count--;
                return pnode->data;
            }
        }
        else if (index == this->count - 1) {
            Node* pnode = fragmentPointers[1];
            T el = pnode->data;
            fragmentPointers[1]->prev->next = NULL;
            fragmentPointers[1] = pnode->prev;
           // delete pnode;
            this->count--;
            return pnode->data;
        }
        else {
            Node* pnode = fragmentPointers[0];
            for (int i = 0; i < index; i++) {
                pnode = pnode->next;
            }
            T el = pnode->data;
            pnode->prev->next = pnode->next;
            pnode->next->prev = pnode->prev;
            //delete pnode;
            this->count--;
            return pnode->data;
        }
    }
    virtual bool removeItem(const T& item) {
        int t = 0;
        Node* pnode =this->fragmentPointers[0];
        while(pnode!=NULL) {
            if (pnode->data == item) {
                if (pnode->prev == NULL && pnode->next == NULL) {
                   this-> fragmentPointers[0] = NULL;
                   this-> fragmentPointers[1] = NULL;
                   Node* temp = pnode;
                   pnode = pnode->next;
                    delete temp;
                    t++;
                }
                else if (pnode->prev == NULL&& pnode->next!=NULL) {
                    pnode->next->prev = NULL;
                    this->fragmentPointers[0] = pnode->next;
                    Node* temp = pnode;
                    pnode = pnode->next;
                    delete temp;
                    t++;
                }
                else if (pnode->prev != NULL && pnode->next == NULL) {
                    pnode->prev->next = NULL;
                    this->fragmentPointers[1] = pnode->prev;
                    Node* temp = pnode;
                    pnode = pnode->next;
                    delete temp;
                    t++;
                }
                else {
                    pnode->prev->next = pnode->next;
                    pnode->next->prev = pnode->prev;
                    Node* temp = pnode;
                    pnode = pnode->next;
                    delete temp;
                    t++;
                }
            }
            else {
                pnode = pnode->next;
            }
        }
        this->count -= t;
        return t;
    }
    virtual bool empty() {
        return (this->fragmentPointers[0] == NULL);
    }
    virtual int size() {
        return this->count ;
    }
    virtual void clear() {
        Node* node = this->fragmentPointers[0];
        for (int i = 0; i < this->count; i++) {
            if (node == NULL) delete this->fragmentPointers[1];
            else {
                node = node->next;
                delete node->prev;
            }
         }
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
        this->count = 0;
    }
    virtual T& get(int index) {
        Node* pnode = this->fragmentPointers[0];
        for (int i = 0; i < index; i++) pnode = pnode->next;
        return pnode->data;
    }
    virtual void set(int index, const T& element) {
        Node* pnode = this->fragmentPointers[0];
        for (int i = 0; i < index; i++) pnode = pnode->next;
        pnode->data = element;
    }
    virtual int indexOf(const T& item) {
        int i = 0;
        for (Node* pnode = this->fragmentPointers[0]; pnode != NULL; pnode = pnode->next) {
            if (pnode->data == item) {
                return i;
            }
            i++;
        }
        return -1;
    }
    virtual bool contains(const T& item) {
        for (Node* pnode = this->fragmentPointers[0]; pnode != NULL; pnode = pnode->next) {
            if (pnode->data == item) {
                return 1;
            }
        }
        return 0;
    }
    virtual string toString();
    Iterator begin(int index = 0);
    Iterator end(int index = -1);

public:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node* next, Node* prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node* next, Node* prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T>* pList;
        Node* pNode;

    public:
        Iterator(FragmentLinkedList<T>* pList = 0, bool begin = true);
        Iterator(FragmentLinkedList<T>* pList = 0, int fragmentIndex = 0, bool begin = true);
        Iterator& operator=(const Iterator& iterator);
        T& operator*() {

            return this->pNode->data;
        }
        bool operator!=(const Iterator& iterator);
        void remove();
        void set(const T& element);
        Iterator& operator++();
        Iterator operator++(int);
    };
};

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node* ptr = this->fragmentPointers[0];

    if (this->count == 0)
        ss << "]";
    else
    {
        ss << ptr->data;

        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
            ss << ", " << ptr->data;
        }

        ss << "]";
    }

    return ss.str();
    // TODO

    // END: TODO

    return ss.str();
}

#endif
// END: STUDENT ANSWER

int main()
{
    FragmentLinkedList<int> list;
    cout << list.size();

    // TESTCASE INPUT
    // === Example
    /*FragmentLinkedList<int> fList;

     for(int i = 0; i < 20 ; i++)
         fList.add(i, i * i);

     for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
         cout << *it << " ";
     cout << endl;*/
    // === END: Example
    // END: TESTCASE INPUT

    return 0;
}
