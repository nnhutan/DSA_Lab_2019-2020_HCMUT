#include <iostream>
#include <string>
using namespace std;
class AvlTree {
public:
	class Node;
	Node* root;
public:
	AvlTree() { root = NULL; }
	~AvlTree() {}
	Node* insertAvlTree(Node* root, int value, bool& taller);
	Node* leftBalance(Node* root, bool& taller);
	Node* rightBalance(Node* root, bool& taller);
	Node* rotateLeft(Node* root);
	Node* rotateRight(Node* root);
	void insert(int);
	void inorder(Node* root);
	void inorder();
public:
	class Node {
	private:
		int value;
		Node* pLeft;
		Node* pRight;
		string Balance;
		friend class AvlTree;
	public:
		Node() { this->value = 0; pLeft = NULL; pRight = NULL; Balance = "EH"; }
		Node(int value, string balance){
			this->value = value; pLeft = NULL; pRight = NULL; Balance = balance;
		}
		
		//Node* deleteAvlTree();
	};	
};

AvlTree::Node* AvlTree::insertAvlTree(Node* root, int value, bool& taller)
{
	if (root == NULL) {
		root = new Node(value, "EH");
		taller = 1;
		return root;
	}
	if (value < root->value) {
		root->pLeft = insertAvlTree(root->pLeft, value, taller);
		if (taller) {
			if (root->Balance == "LH") root = leftBalance(root, taller);
			else if (root->Balance == "EH") root->Balance = "LH";
			else {
				root->Balance = "EH";
				taller = 0;
			}
		}
	}
	else {
		root->pRight = insertAvlTree(root->pRight, value, taller);
		if (taller) {
			if (root->Balance == "RH") root = rightBalance(root, taller);
			else if (root->Balance == "EH")root->Balance = "RH";
			else {
				root->Balance = "EH";
				taller = 0;
			}
		}
	}
	return root;
}
AvlTree::Node* AvlTree::leftBalance(Node* root, bool& taller)
{
	Node* leftTree = root->pLeft;
	if (leftTree->Balance == "LH") {
		root->Balance = "EH";
		root = rotateRight(root);
		leftTree->Balance == "EH";
		cout << '[' << root->value << ':' << root->Balance << ']' << endl;
		cout << '[' << leftTree->value << ':' << leftTree->Balance << ']';
		taller = 0;
	}
	else {
		Node* rightTree = leftTree->pRight;
		if (rightTree->Balance == "LH") {
			root->Balance = "RH";
			leftTree->Balance = "EH";
		}
		else if (rightTree->Balance == "EH")leftTree->Balance = "EH";
		else {
			root->Balance="EH";
			leftTree->Balance = "LH";
				
		}
		rightTree->Balance = "EH";
		root->pLeft = rotateLeft(leftTree);
		root = rotateRight(root);
		taller = 0;
	}
	return root;
}
AvlTree::Node* AvlTree::rightBalance(Node* root, bool& taller)
{
	
	Node* rightTree = root->pRight;
	if (rightTree->Balance == "RH") {
		root->Balance = "EH";
		root = rotateLeft(root);
		rightTree->Balance = "EH";
		taller = 0;
	}
	else {
		Node* leftTree = rightTree->pLeft;
		if (leftTree->Balance == "LH") {
			root->Balance = "EH";
			rightTree->Balance = "RH";
		}
		else if (leftTree->Balance == "EH") {
			rightTree->Balance = "EH";
		}
		else {
			root->Balance = "LH";
			rightTree->Balance = "EH";
		}
		leftTree->Balance = "EH";
		root->pRight = rotateRight(rightTree);
		root = rotateLeft(root);
		taller = 0;
	}
	return root;
}
AvlTree::Node* AvlTree::rotateLeft(Node* root)
{

	Node* tempPtr = root->pRight;
	root->pRight = tempPtr->pLeft;
	tempPtr->pLeft = root;
	return tempPtr;
}
AvlTree::Node* AvlTree::rotateRight(Node* root)
{
	Node* tempPtr = root->pLeft;
	root->pLeft = tempPtr->pRight;
	tempPtr->pRight = root;
	return tempPtr;
}
void AvlTree::insert(int value)
{
	bool taller = 0;
	root = insertAvlTree(root, value, taller);
}
void AvlTree::inorder(Node* r)
{
	if (r == NULL) return;
	cout << r->value << " ";
	inorder(r->pLeft);
	inorder(r->pRight);
}
void AvlTree::inorder()
{
	inorder(this->root);
}
int main()
{
	
	AvlTree avl;
	avl.insert(8);
	avl.insert(7);
	avl.insert(11);
	avl.insert(10);
	avl.insert(9);
	avl.inorder();
	cout << endl;
	avl.insert(5);
	avl.inorder();
	cout << endl;
	avl.insert(6);
	avl.inorder();
	cout << endl;
	avl.insert(2);

	avl.inorder();
}

