#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class PhoneList
{
public:
	class Node;
	Node* head;
	Node* tail;
public:
	PhoneList() {
		this->head = NULL;
		this->tail = NULL;
	}
	~PhoneList() {
	
	}
public:
	class Node {
	public:
		string lastname;
		string firstname;
		string phonenumber;
		Node* next;
	public:
		Node() {
			lastname = "";
			firstname = "";
			phonenumber = "";
			next = NULL;
		}
		Node(string lastname, string firstname, string phonenumber) {
			this->firstname = firstname;
			this->lastname = lastname;
			this->phonenumber = phonenumber;
			this->next = NULL;
		}
	};
public:
	void append(string firstname, string lastname, string phonenumber) {
		if (this->head == NULL) this->head = this->tail = new Node(firstname, lastname, phonenumber);
		else this->tail = this->tail->next = new Node(firstname, lastname, phonenumber);
	}
	void display() {
		Node* walker = this->head;
		while (walker != NULL) {
			cout << walker->firstname << " " << walker->lastname << " " << walker->phonenumber << "\n";
			walker = walker->next;
		}
	}
};
int main() {
	PhoneList list;
	list.append("Johnny", "Depp", "012345678");
	list.append("alexander", "rybak", "123456790");
	list.display();
}