#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>
#include <exception>
#include <stdexcept>
#include <algorithm>
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
	FragmentLinkedList(int fragmentMaxSize = 5)
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
	int m = n + 2;
	Node **fragTemp = new Node *[m];
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
	if (index > this->count || index < 0)
		throw out_of_range("The index is out of range!");
	if (empty() || index == this->count)
	{
		add(element);
		return;
	}
	else if (index == 0)
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
	int m = n + 2;
	Node **fragTemp = new Node *[m];
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
	{
		this->fragmentPointers[0] = this->fragmentPointers[0]->next;
		if (this->fragmentPointers[0] == NULL)
			this->tail = NULL;
	}
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
	if (this->fragmentPointers[0] != NULL)
	{
		int n = ((this->count - 1) / this->fragmentMaxSize);
		int m = n + 2;
		Node **fragTemp = new Node *[m];
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
	return value;
}

//REMOVE ITEM
template <class T>
bool FragmentLinkedList<T>::removeItem(const T &item)
{
	if (empty() || this->indexOf(item) == -1)
		return 0;
	this->removeAt(this->indexOf(item));
	return 1;
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
	this->tail = NULL;
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
	if (index < 0 || index >= ((this->count - 1) / this->fragmentMaxSize) + 1)
		throw out_of_range("The index is out of range!");
	return Iterator(index, this, 1);
}

//END
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::end(int index)
{
	if (index < -1 || index >= ((this->count - 1) / this->fragmentMaxSize) + 2)
		throw out_of_range("The index is out of range!");
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
	if (!pList)
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
		if (fragmentIndex == -1)
		{
			this->pNode = NULL;
			this->index = this->pList->size();
			return;
		}
		this->pNode = this->pList->fragmentPointers[fragmentIndex];
		for (int i = 0; i < (this->pList->fragmentMaxSize); i++)
		{
			this->pNode = this->pNode->next;
			if (this->pNode == NULL)
				break;
		}
		this->index = (fragmentIndex + 1) * (this->pList->fragmentMaxSize);
		if (this->index >= this->pList->size())
			this->index = this->pList->size();
	}
}

//OPERATOR =
template <class T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
	this->pList = iterator.pList;
	this->pNode = iterator.pNode;
	this->index = iterator.index;
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
	if (this->pNode == NULL && iterator.pNode == NULL && this->index == iterator.index)
		return 0;
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
	if (this->pNode == NULL)
		throw std::out_of_range("Segmentation fault!");
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

class BusSystem;
#ifndef BUS_NODE
#define BUS_NODE
class Bus
{
private:
	string CODE;
	string LP;
	string CASE;
	int TIMEA;
	int TIMEB;
	friend class BusSystem;

public:
	Bus()
	{
		this->CODE = "";
		this->LP = "";
		this->CASE = "";
		this->TIMEA = 0;
		this->TIMEB = 0;
	}
	/*Bus(string CODE, string LP, string CASE, int TIMEA, int TIMEB) {
		this->CODE = CODE;
		this->LP = LP;
		this->CASE = CASE;
		this->TIMEA = TIMEA;
		this->TIMEB = TIMEB;
	}*/
	~Bus() {}
	bool operator==(const Bus &bus) const
	{
		return this->CODE == bus.CODE && this->LP == bus.LP && this->CASE == bus.LP &&
			   this->TIMEA == bus.TIMEA && this->TIMEB == bus.TIMEB;
	}
	friend ostream &operator<<(ostream &os, const Bus &bus)
	{
		cout << endl;
		cout << "Bus: "
			 << "(" << bus.CODE << " " << bus.LP << " " << bus.CASE << " " << bus.TIMEA << " " << bus.TIMEB << ")";
		return os;
	}
};
#endif

#ifndef BUS_SYSTEM
#define BUS_SYSTEM
class BusSystem
{
private:
	FragmentLinkedList<Bus> *BUS;
	int N; //THE MAXIMUM NUMBER OF TRIPS PER ROUTER.
public:
	BusSystem()
	{
		this->BUS = new FragmentLinkedList<Bus>();
		this->N = 0;
	}
	~BusSystem()
	{
		this->BUS->clear();
	}
	string query(string instruction)
	{
		//CREATE A VECTOR "Request" TO STORE REQUEST.
		vector<string> Request;
		//PUSH PARAMETERS OF REQUEST TO VECTOR "Request".
		istringstream str(instruction);
		while (!str.eof())
		{
			string tmp;
			str >> tmp;
			if (tmp != "")
				Request.push_back(tmp);
		}
		//CREATE A VARIABLE INT "nParameter" TO STORE THE NUMBER OF PARAMETERS INT THE REQUEST.
		size_t nParameter = Request.size();
		size_t nSpaces = count(instruction.begin(), instruction.end(), ' ');
		cout << '(' << nParameter << ':' << nSpaces << ')';
		if (nParameter - 1 != nSpaces) return "-1";
		//CREATE A VARIABLE STRING "command" TO STORE THE COMMAND OF THE REQUEST.
		string command = Request[0];
		//CHECK THE VALIDITY OF THE REQUEST
		if (command == "SQ" && (Request[1].find_first_not_of("0123456789") != string::npos || nParameter != 2))	return "-1";
		else if (command == "INS")
		{
			if (Request[1].size() > 5 || Request[2].size() > 10)
				return "-1";
			if (nParameter == 6)
			{
				if ((Request[3] != "1" && Request[3] != "0") || Request[4].find_first_not_of("0123456789") != string::npos ||
					Request[5].find_first_not_of("0123456789") != string::npos)
					return "-1";
			}
			else
			{
				if (Request[3].find_first_not_of("0123456789") != string::npos ||
					Request[4].find_first_not_of("0123456789") != string::npos)
					return "-1";
			}
		}
		else if (command == "DEL")
		{
			if (Request[1].size() > 5)
				return "-1";
			if (nParameter == 3 || nParameter == 4)
			{
				if (Request[2].find_first_not_of("0123456789") != string::npos)
					return "-1";
				if (nParameter == 4)
					if (Request[3].find_first_not_of("0123456789") != string::npos)
						return "-1";
			}
		}
		else if (command == "CS" || command == "CE" || command == "GS" || command == "GE")
		{
			if (Request[1].size() > 5 || Request[2].find_first_not_of("0123456789") != string::npos)
				return "-1";
			if (nParameter == 4)
				if (Request[3] != "1" && Request[3] != "0")
					return "-1";
		}

		//PERFORM REQUEST
		//SET THE MAXIMUM NUMBER OF TRIPS PER ROUTER.
		if (command == "SQ")
		{
			this->N = stoi(Request[1]);
			return "1";
		}

		//ADD A TRIP TO THE LIST
		else if (command == "INS")
		{ //INS 50 50D1-23342 1234 5678
			if (Request[1].size() > 5 || Request[2].size() > 10)
				return "-1";
			Bus newbus;
			newbus.CODE = Request[1];
			newbus.LP = Request[2];
			if (nParameter == 6)
			{
				newbus.CASE = Request[3];
				newbus.TIMEA = stoi(Request[4]);
				newbus.TIMEB = stoi(Request[5]);
			}
			else
			{
				newbus.CASE = '0';
				newbus.TIMEA = stoi(Request[3]);
				newbus.TIMEB = stoi(Request[4]);
			}

			//cout << "[" << newbus.TIMEA << "]" << endl;
			//VARIABLE INT "checkN" STORES THE CURRENT TRIP NUMBER OF THE ROUTE WITH CODE <CODE>.
			int checkN = 0;
			//VARIABLE BOOL "flag" TO CHECK ADDING THE TRIP TO THE LIST.
			bool flag = 1;
			for (FragmentLinkedList<Bus>::Iterator it = this->BUS->begin(); it != this->BUS->end(); it++)
			{
				if (newbus.CODE == (*it).CODE)
					checkN++;
				if ((newbus.LP == (*it).LP && newbus.TIMEA <= (*it).TIMEB) ||
					(newbus.LP != (*it).LP && newbus.CODE == (*it).CODE && newbus.TIMEA == (*it).TIMEA))
					flag = 0;
			}
			if (flag == 1 && checkN <= this->N)
			{
				this->BUS->add(newbus);
				checkN++;
				return to_string(checkN);
			}
			else
				return "-1";
			//cout << "[" << newbus.TIMEB << "]" << endl;
		}

		//DELETE A TRIP FROM THE LIST.
		else if (command == "DEL")
		{
			//DEL <CODE> [<TIME_A>[<TIME_B>]
			string CodeDel = Request[1];
			int TimeDelA = -1, TimeDelB = -1;
			if (nParameter == 3 || nParameter == 4)
			{
				TimeDelA = stoi(Request[2]);
				if (nParameter == 4)
					TimeDelB = stoi(Request[3]);
			}
			int nTripDele = 0;
			for (FragmentLinkedList<Bus>::Iterator it = this->BUS->begin(); it != this->BUS->end(); it++)
			{
				if (TimeDelA == -1 && TimeDelB == -1)
				{
					if ((*it).CODE == CodeDel)
					{
						it.remove();
						nTripDele++;
					}
				}
				else if (TimeDelA != -1 && TimeDelB == -1)
				{
					if ((*it).CODE == CodeDel && (*it).TIMEA == TimeDelA)
					{
						it.remove();
						nTripDele++;
					}
				}
				else if (TimeDelA != -1 && TimeDelB != -1)
				{
					if ((*it).CODE == CodeDel && (*it).TIMEA >= TimeDelA && (*it).TIMEB <= TimeDelB)
					{
						it.remove();
						nTripDele++;
					}
				}
			}
			return to_string(nTripDele);
		}

		//RETURN THE NUMBER OF TRIPS THAT HAVE STARTED BUT HAVE NOT YET ARRIVED AT...
		//...THE BUS STOP OF THE ROUTE WITH CODE <CODE> AT THE CONSIDERED TIME <TIME>.
		else if (command == "CS")
		{
			//CS <CODE>	<TIME>[<CASE>]
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			int nTrips = 0;
			for (FragmentLinkedList<Bus>::Iterator it = this->BUS->begin(); it != this->BUS->end(); it++)
				//cout << (*it).TIMEA << NowTime << (*it).TIMEB;
				if ((*it).CODE == CodeTrip && (*it).TIMEA <= NowTime &&
					(*it).TIMEB >= NowTime && (CaseCheck == "-1" || CaseCheck == (*it).CASE))
					nTrips++;
			return to_string(nTrips);
		}

		//RETURN THE NUMBER OF TRIPS THAT HAVE ENDED OF THE ROUTE WITH CODE <CODE> AT...
		//...THE CONSIDERED TIME <TIME>.
		else if (command == "CE")
		{
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			int nTrips = 0;
			for (FragmentLinkedList<Bus>::Iterator it = this->BUS->begin(); it != this->BUS->end(); it++)
				if ((*it).CODE == CodeTrip && (*it).TIMEB < NowTime && (CaseCheck == "-1" || CaseCheck == (*it).CASE))
					nTrips++;
			return to_string(nTrips);
		}

		//RETURN THE LICENSE PLATE OF THE BUS TRIP OF THE ROUTE WITH CODE <CODE> WHICH HAS...
		//... STARTED AT THE TIME CLOSEST TO THE CONSIDERED TIME <TIME>.
		else if (command == "GS")
		{
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			Bus target;
			bool flag = 1;
			for (FragmentLinkedList<Bus>::Iterator it = this->BUS->begin(); it != this->BUS->end(); it++)
			{
				if (CaseCheck == "-1")
				{
					if ((*it).TIMEA >= NowTime && (*it).CODE == CodeTrip && flag)
					{
						target = *it;
						flag = 0;
					}
					else if ((*it).TIMEA >= NowTime && ((*it).TIMEA - NowTime) < (target.TIMEA - NowTime) && (*it).CODE == CodeTrip)
						target = *it;
					else if (((*it).TIMEA - NowTime) == (target.TIMEA - NowTime) && (*it).CODE == CodeTrip)
					{
						if ((*it).CASE == "0" && target.CASE == "1")
							target = *it;
					}
				}
				else
				{
					if ((*it).TIMEA >= NowTime && (*it).CASE == CaseCheck && (*it).CODE == CodeTrip && flag)
					{
						target = *it;
						flag = 0;
					}
					else if ((*it).TIMEA >= NowTime && ((*it).TIMEA - NowTime) < (target.TIMEA - NowTime) && (*it).CODE == CodeTrip && (*it).CASE == CaseCheck)
						target = *it;
				}
			}
			return target.LP;
		}

		//RETURN THE LICENSE PLATE OF THE BUS TRIP OF THE ROUTE WITH CODE <CODE> WHICH HAS...
		//... ENDED AT THE TIME CLOSEST TO THE CONSIDERED TIME <TIME>.
		else if (command == "GE")
		{
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			Bus target;
			bool flag = 1;
			for (FragmentLinkedList<Bus>::Iterator it = this->BUS->begin(); it != this->BUS->end(); it++)
			{
				if (CaseCheck == "-1")
				{
					if ((*it).TIMEB < NowTime && (*it).CODE == CodeTrip && flag)
					{
						target = *it;
						flag = 0;
					}
					else if ((*it).TIMEB < NowTime && (NowTime - (*it).TIMEB) < (NowTime - target.TIMEB) && (*it).CODE == CodeTrip)
						target = *it;
					else if ((NowTime - (*it).TIMEB) == (NowTime - target.TIMEB) && (*it).CODE == CodeTrip)
					{
						if ((*it).CASE == target.CASE)
							target = ((*it).TIMEA > target.TIMEA) ? *it : target;
						else if ((*it).CASE == "0" && target.CASE == "1")
							target = *it;
					}
				}
				else
				{
					if ((*it).TIMEB < NowTime && (*it).CASE == CaseCheck && (*it).CODE == CodeTrip && flag)
					{
						target = *it;
						flag = 0;
					}
					else if ((*it).TIMEB < NowTime && (NowTime - (*it).TIMEB) < (NowTime - target.TIMEB) && (*it).CODE == CodeTrip && (*it).CASE == CaseCheck)
						target = *it;
					else if ((*it).TIMEB < NowTime && (NowTime - (*it).TIMEB) == (NowTime - target.TIMEB) && (*it).CODE == CodeTrip && (*it).CASE == CaseCheck)
						target = ((*it).TIMEA > target.TIMEA) ? *it : target;
				}
			}
			return target.LP;
		}

		//IF REQUEST IS NOT COMPLETED, RETURN "-1"
		return "-1";
	}
	void print()
	{
		this->BUS->toString();
	}
};
#endif

int main()
{
	BusSystem *bs = new BusSystem();
	cout << bs->query("SQ 500") << endl;						//1
	cout << bs->query("INS 50 50D1-23342 1 1234 5678") << endl; //1
	cout << bs->query("INS 38 50D1-23343 0 1236 5679") << endl; //1
	cout << bs->query("INS 50 50D1-23344 0 1237 5680") << endl; //1
	cout << bs->query("INS 53 50D1-23345 0 1238 5681") << endl; //1
	cout << bs->query("INS 50 50D1-23346 1 1239 5682") << endl; //1
	cout << bs->query("INS 51 50D1-23347 1 1240 5683") << endl; //1
	cout << bs->query("INS 50 50D1-23348 0 1241 5684") << endl; //1
	cout << bs->query("INS 50 50D1-23349 1 1242 5685") << endl; //1
	cout << bs->query("INS 49 50D1-23350 0 1243 5686") << endl; //1
	cout << bs->query("CS 50 2134") << endl;					//1
	cout << bs->query("GE 50 5685") << endl;					//1
	cout << "[" << bs->query("DEL 49") << "]" << endl;

	bs->print();
}
/* Note:
	* You change anything in this answer
	* such that your implementation must have BusSystem class with method query.
	* This query method should return the output of each instruction
*/