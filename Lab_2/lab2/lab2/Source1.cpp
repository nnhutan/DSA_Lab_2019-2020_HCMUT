#include <iostream>
using namespace std;
template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~DLinkedList() {};
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    bool empty();
    int indexOf(const T& item);
    void set(int index, const T& e);
    T get(int index);
    bool contains(const T& item);
public:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T& data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
        string toString()
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
            return ss.str();
        }
    };

};





    template <class T>
    void DLinkedList<T>::add(const T& e) {
        /* Insert an element into the end of the list. */
        if (this->count == 0) {
            this->head = this->tail = new Node(e);
        }
        else {
            Node* newnode = new Node(e);
            newnode->previous = this->tail;
            this->tail = this->tail->next = newnode;
        }
        this->count++;
    }

    template<class T>
    void DLinkedList<T>::add(int index, const T& e) {
        /* Insert an element into the list at given index. */
        if (this->count == 0 || index >= this->count) { add(e); return; }
        else {
            if (index == 0) {
                Node* newnode = new Node(e);
                newnode->next = this->head;
                this->head->previous = newnode;
                this->head = newnode;
            }
            else {
                Node* p = this->head;
                for (int i = 0; i < index - 1; i++) {
                    p = p->next;
                }
                Node* newnode = new Node(e);
                newnode->next = p->next;
                newnode->previous = p;
                p->next = p->next->previous = newnode;

            }
            this->count++;

        }

    }

    template<class T>
    int DLinkedList<T>::size() {
        /* Return the length (size) of list */
        return this->count;
    }

    template<class T>
    T DLinkedList<T>::get(int index) {
        /* Give the data of the element at given index in the list. */

        if (empty() || index < 0 || index >= this->count) throw out_of_range("The index is out of range!");
        Node* pnode = this->head;
        for (int i = 0; i < index; i++)	pnode = pnode->next;
        return pnode->data;

    }

    template <class T>
    void DLinkedList<T>::set(int index, const T& e) {
        /* Assign new value for element at given index in the list */
        if (empty() || index < 0 || index >= this->count) throw out_of_range("The index is out of range!");
        Node* pnode = this->head;
        for (int i = 0; i < index; i++) pnode = pnode->next;
        pnode->data = e;
    }

    template<class T>
    bool DLinkedList<T>::empty() {
        /* Check if the list is empty or not. */
        return (this->count < 1);
    }

    template<class T>
    int DLinkedList<T>::indexOf(const T& item) {
        /* Return the first index wheter item appears in list, otherwise return -1 */
        if (this->count == 0) return -1;
        Node* pnode = this->head;
        int i = 0;
        while (pnode != NULL) {
            if (pnode->data == item) {
                return i;
            }
            i++;
            pnode = pnode->next;
        }
        return -1;

    }

    template<class T>
    bool DLinkedList<T>::contains(const T& item) {
        /* Check if item appears in the list */
        return (this->indexOf(item) != -1);
    }