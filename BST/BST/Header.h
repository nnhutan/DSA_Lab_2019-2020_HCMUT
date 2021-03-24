#pragma once
class BST
{
public:
	class Node;
	Node* root;
public:
	BST();
	~BST();
	void Insert(int);
	Node* DeleteItems(Node*, int);
	void PreOrder(Node*);
	void InOrder(Node*);
	void PostOrder(Node*);
	Node* findSmallest(Node*);
	Node* findLargest(Node*);
	Node* search(int);
	bool isEmpty();
public:
	class Node {
	private:
		int data;
		Node* right;
		Node* left;
		friend class BST;
	public:
		Node();
		Node(int);
		Node(int, Node*, Node*);
		~Node();
	};

};
