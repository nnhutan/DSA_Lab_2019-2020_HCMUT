#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;
template <class T>
class SLinkedList
{
public:
	class Iterator; //forward declaration
	class Node;     //forward declaration

protected:
	Node* head;
	Node* tail;
	int count;

public:
	SLinkedList() : head(NULL), tail(NULL), count(0) {};
	~SLinkedList();
	void add(const T& e);
	void add(int index, const T& e);
	T removeAt(int index);
	bool removeItem(const T& removeItem);
	bool empty();
	int size();
	void clear();
	T get(int index);
	void set(int index, const T& e);
	int indexOf(const T& item);
	bool contains(const T& item);
	string toString();

	SLinkedList(const SLinkedList& list)
	{
		this->count = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	Iterator begin()
	{
		return Iterator(this, true);
	}
	Iterator end()
	{
		return Iterator(this, false);
	}

public:
	class Node
	{
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;

	public:
		Node()
		{
			next = 0;
		}
		Node(Node* next)
		{
			this->next = next;
		}
		Node(T data, Node* next = NULL)
		{
			this->data = data;
			this->next = next;
		}
	};

	class Iterator
	{
	private:
		SLinkedList<T>* pList;
		Node* current;
		int index;

	public:
		Iterator(SLinkedList<T>* pList = NULL, bool begin = true);
		Iterator& operator=(const Iterator& iterator);
		void remove();
		void set(const T& e);
		T& operator*();
		bool operator!=(const Iterator& iterator);
		Iterator& operator++();
		Iterator operator++(int);
	};
};


template<class T>
SLinkedList<T>::~SLinkedList()
{
}

template <class T>
void SLinkedList<T>::add(const T& e) {
	/* Insert an element into the end of the list. */
	if (this->count == 0)		this->tail = this->head = new Node(e, NULL);
	else this->tail = this->tail->next = new Node(e, NULL);
	this->count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
	/* Insert an element into the list at given index. */
	if (this->count == 0 || index >= this->count) {
		add(e);
		return;
	}
	else if (index <= 0)	this->head = new Node(e, this->head);
	else {
		Node* pnode = this->head;
		for (int i = 0; i < index - 1; i++)   pnode = pnode->next;
		pnode->next = new Node(e, pnode->next);
	}
	this->count++;
}

template<class T>
int SLinkedList<T>::size() {
	/* Return the length (size) of list */
	return this->count;
}

template<class T>
T SLinkedList<T>::get(int index) {
	/* Give the data of the element at given index in the list. */
	if (empty() || index < 0 || index >= this->count) throw std::out_of_range("Index is out of range");
	Node* pNode = this->head;
	for (int i = 0; i < index; i++) pNode = pNode->next;
	return pNode->data;

}
template <class T>
void SLinkedList<T>::set(int index, const T& e) {
	if (index < 0 || index >= this->count) 	throw std::out_of_range("Index is out of range");
	Node* pNode = this->head;
	for (int i = 0; i < index; i++) pNode = pNode->next;
	pNode->data = e;
}
template<class T>
bool SLinkedList<T>::empty() {
	/* Check if the list is empty or not. */
	return (this->count == 0);
}
template<class T>
int SLinkedList<T>::indexOf(const T& item) {
	/* Return the first index wheter item appears in list, otherwise return -1 */
	Node* pNode = this->head;
	int i = 0;
	while (pNode != NULL) {
		if (pNode->data == item) {
			return i;
		}
		i++;
		pNode = pNode->next;
	}
	return -1;
}
template<class T>
bool SLinkedList<T>::contains(const T& item) {
	/* Check if item appears in the list */
	return (this->indexOf(item) != -1);
}
template<class T>
string SLinkedList<T>::toString()
{
	stringstream ss;
	ss << "[";
	Node* ptr = head;
	while (ptr != tail) {
		ss << ptr->data << ",";
		ptr = ptr->next;
	}

	if (count > 0)
		ss << ptr->data << "]";
	else
		ss << "]";
	return ss.str();
}
template <class T>
T SLinkedList<T>::removeAt(int index)
{
	if (index >= this->count || index < 0) throw out_of_range("");
	T value = this->get(index);
	if (index == 0) {
		Node* pNode = this->head;
		this->head = pNode->next;
		delete pNode;
		this->count--;
		return value;
	}
	Node* pNode = this->head;
	for (int i = 0; i < index - 1; i++) {
		pNode = pNode->next;
	}
	Node* tmp = pNode->next;
	pNode->next = pNode->next->next;
	delete tmp;
	if (index == this->count - 1) this->tail = pNode;
	this->count--;
	return value;

}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
	if (this->indexOf(item) == -1) return false;
	this->removeAt(this->indexOf(item));
	return true;
}

template<class T>
void SLinkedList<T>::clear() {
	while (this->head != NULL) {
		Node* currentNode = this->head;
		this->head = this->head->next;
		delete currentNode;
	}
	this->count = 0;
}

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
	this->pList = pList;
	if (begin) {
		if (pList != NULL) {
			this->current = this->pList->head;
			this->index = 0;
		}
		else {
			this->current = NULL;
			this->index = -1;
		}
	}
	else {
		this->current = NULL;
		if (pList != NULL) this->index = this->pList->size();
		else this->index = 0;
	}
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
	/*
		Assignment operator
		* Set this current, index, pList to iterator corresponding elements.
	*/
	this->current = iterator.current;
	this->pList = iterator.pList;
	this->index = iterator.index;
	//*this = iterator;
	return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
	/*
		Remove a node which is pointed by current
		* After remove current points to the previous node of this position (or node with index - 1)
		* If remove at front, current points to previous "node" of head (current = NULL, index = -1)
		* Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
	*/
	if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
	else if (this->index == 0) {
		this->pList->removeAt(this->index);
		this->current = NULL;
		this->index = -1;
	}
	else {
		this->current = this->pList->head;
		for (int i = 0; i < this->index - 1; i++) {
			this->current = this->current->next;
		}
		this->pList->removeAt(this->index);
		this->index -= 1;
	}
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
	/*
		Set the new value for current node
		* Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
	*/
	if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
	this->current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
	/*
		Get data stored in current node
		* Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
	*/
	//if ((this->current)==NULL) throw std::out_of_range("Segmentation fault!");
	return this->current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
	/*
		Operator not equals
		* Returns true if two iterators points the same node and index
	*/

	return !(this->current == iterator.current);
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
	/*
		Prefix ++ overload
		* Set current to the next node
		* If iterator corresponds to the previous "node" of head, set it to head
		* Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
	*/
	if (this->index == -1) this->current = this->pList->head;
	//else if (this->current == this->pList->tail) throw std::out_of_range("Segmentation fault!");
	else this->current = this->current->next;
	this->index++;
	return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
	/*
		Postfix ++ overload
		* Set current to the next node
		* If iterator corresponds to the previous "node" of head, set it to head
		* Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
	*/
	Iterator tmp = *this;
	if (this->index == -1) this->current = this->pList->head;
	//else if (this->current == this->pList->tail) throw std::out_of_range("Segmentation fault!");
	else this->current = this->current->next;
	this->index++;
	return tmp;
}
int main() {
	SLinkedList<int> list;

	int size = 10;
	for (int idx = 0; idx < size; idx++) {
		list.add(idx);
	}

	SLinkedList<int>::Iterator it;
	int expvalue = 0;
	for (it = list.begin(); it != list.end(); it++) {
		assert(*it == expvalue);
		expvalue += 1;
	}
	cout << list.toString();
}