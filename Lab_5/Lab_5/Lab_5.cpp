#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};

void printNSpace(int n)
{
	for (int i = 0; i < n - 1; i++)
		cout << " ";
}

void printInteger(int& n)
{
	cout << n << " ";
}

template <class T>
class AVLTree
{
public:
	class Node;

private:
	Node* root;

protected:
	int getHeightRec(Node* node)
	{
		if (node == NULL)
			return 0;
		int lh = this->getHeightRec(node->pLeft);
		int rh = this->getHeightRec(node->pRight);
		return (lh > rh ? lh : rh) + 1;
	}

public:
	AVLTree() : root(nullptr) {}
	~AVLTree() {}
	int getHeight()
	{
		return this->getHeightRec(this->root);
	}
	void printTreeStructure()
	{
		int height = this->getHeight();
		if (this->root == NULL)
		{
			cout << "NULL\n";
			return;
		}
		queue<Node*> q;
		q.push(root);
		Node* temp;
		int count = 0;
		int maxNode = 1;
		int level = 0;
		int space = pow(2, height);
		printNSpace(space / 2);
		while (!q.empty())
		{
			temp = q.front();
			q.pop();
			if (temp == NULL)
			{
				cout << " ";
				q.push(NULL);
				q.push(NULL);
			}
			else
			{
				cout << temp->data;
				q.push(temp->pLeft);
				q.push(temp->pRight);
			}
			printNSpace(space);
			count++;
			if (count == maxNode)
			{
				cout << endl;
				count = 0;
				maxNode *= 2;
				level++;
				space /= 2;
				printNSpace(space / 2);
			}
			if (level == height)
				return;
		}
	}

	void insert(const T& value)
	{
		//TODO
		bool taller = 1;
		root = insertAvlTree(root, value, taller);
	}
	Node* insertAvlTree(Node* root, T value, bool& taller)
	{
		if (root == NULL)
		{
			root = new Node(value);
			taller = 1;
			return root;
		}
		if (value < root->data)
		{
			root->pLeft = insertAvlTree(root->pLeft, value, taller);
			if (taller)
			{
				if (root->balance == BalanceValue::LH)
					root = leftBalance(root, taller);
				else if (root->balance == BalanceValue::EH)
					root->balance = BalanceValue::LH;
				else if (root->balance == BalanceValue::RH)
				{
					root->balance = EH;
					taller = 0;
				}
			}
		}
		else
		{
			root->pRight = insertAvlTree(root->pRight, value, taller);
			if (taller)
			{
				if (root->balance == RH)
					root = rightBalance(root, taller);
				else if (root->balance == EH)
					root->balance = RH;
				else
				{
					root->balance = EH;
					taller = 0;
				}
			}
		}
		return root;
	}
	Node* leftBalance(Node* root, bool& taller)
	{
		Node* leftTree = root->pLeft;
		if (leftTree->balance == LH)
		{
			root->balance = EH;
			root = rotateRight(root);
			leftTree->balance = EH;
			/*cout << '[' << root->value << ':' << root->Balance << ']' << endl;
				cout << '[' << leftTree->value << ':' << leftTree->Balance << ']';*/
			taller = 0;
		}
		else if (leftTree->pRight != NULL)
		{
			Node* rightTree = leftTree->pRight;
			if (rightTree->balance == LH)
			{
				root->balance = RH;
				leftTree->balance = EH;
			}
			else if (rightTree->balance == EH)
				leftTree->balance = EH;
			else
			{
				root->balance = EH;
				leftTree->balance = LH;
			}
			rightTree->balance = EH;
			root->pLeft = rotateLeft(leftTree);
			root = rotateRight(root);
			taller = 0;
		}
		return root;
	}
	Node* rightBalance(Node* root, bool& taller)
	{

		Node* rightTree = root->pRight;
		if (rightTree->balance == RH)
		{
			root->balance = EH;
			root = rotateLeft(root);
			rightTree->balance = EH;
			taller = 0;
		}
		else if (rightTree->pLeft != NULL)
		{
			Node* leftTree = rightTree->pLeft;
			if (leftTree->balance == LH)
			{
				root->balance = EH;
				rightTree->balance = RH;
			}
			else if (leftTree->balance == EH)
			{
				rightTree->balance = EH;
			}
			else
			{
				root->balance = LH;
				rightTree->balance = EH;
			}
			leftTree->balance = EH;
			root->pRight = rotateRight(rightTree);
			root = rotateLeft(root);
			taller = 0;
		}
		return root;
	}
	Node* rotateLeft(Node* root)
	{

		Node* tempPtr = root->pRight;
		root->pRight = tempPtr->pLeft;
		tempPtr->pLeft = root;
		return tempPtr;
	}
	Node* rotateRight(Node* root)
	{
		Node* tempPtr = root->pLeft;
		root->pLeft = tempPtr->pRight;
		tempPtr->pRight = root;
		return tempPtr;
	}
	Node* deleteRightBalance(Node* root, bool& shorter) {
		if (root->balance == LH) {
			root->balance = EH;
		}
		else if (root->balance == EH) {
			root->balance = RH;
			shorter = 0;
		}
		else if(root->pRight!=NULL){
			
			Node* rightTree = root->pRight;
			if (rightTree->balance == LH) {
				Node* leftTree = rightTree->pLeft;
				if (leftTree->balance == LH) {
					rightTree->balance = RH;
					root->balance = EH;
				}
				else if (leftTree->balance == EH) {
					root->balance = LH;
					rightTree->balance = EH;
				}
				else {
					root->balance = LH;
					rightTree->balance = EH;
				}
				leftTree->balance = EH;
				root->pRight = rotateRight(rightTree);
				root = rotateLeft(root);
			}
			else {
				if (rightTree->balance != EH) {
					root->balance = EH;
					rightTree->balance = EH;
				}
				else {
					root->balance = RH;
					rightTree->balance = LH;
					shorter = 0;
				}
				root = rotateLeft(root);
			}
		}
		if (root->pRight == NULL&& root->pLeft!=NULL) {
			root->pLeft->balance = EH;
			root->balance = EH;
			root = rotateRight(root);
		}
		/*if (root->pRight == NULL && root->pLeft != NULL) {

			root->pLeft->balance = EH;
			root->balance = EH;
			root = rotateRight(root);
		}*/
		return root;
	}
	Node* deleteLeftBalance(Node* root, bool& shorter) {
		
		if (root->balane == RH) {
			root->balance = EH;
		}
		else if (root->balance == EH) {
			root->balance = LH;
			shorter = 0;
		}
		else if(root->pRight!=NULL) {
			Node* leftTree = root->pLeft;
			if (leftTree->balance == RH) {
				Node* rightTree = leftTree->pRight;
				if (rightTree->balance == LH) {
					leftTree->balance = LH;
					root->balance = EH;
				}
				else if (rightTree->balance == EH) {
					root->balance = RH;
					leftTree->balance = EH;
				}
				else {
					root->balance = RH;
					leftTree->balance = EH;
				}
				rightTree->balance = EH;
				root->pLeft = rotateRight(leftTree);
				root = rotateRight(root);
			}
			else {
				if (leftTree->balance != EH) {
					root->balance = EH;
					leftTree->balance = EH;
				}
				else {
					root->balance = LH;
					leftTree->balance = RH;
					shorter = 0;
				}
				root = rotateRight(root);
			}
		}
		return root;
	}
	Node* AVLDelete(Node* root, T deleteKey, bool& shorter, bool& success)
	{
		if (root == NULL) {
			shorter = 0;
			success = 0;
			return NULL;
		}
		if (deleteKey < root->data) {
			root->pLeft = AVLDelete(root->pLeft, deleteKey, shorter, success);
			if (shorter) root = deleteRightBalance(root, shorter);
		}
		else if (deleteKey > root->data) {
			root->pRight = AVLDelete(root->pRight, deleteKey, shorter, success);
			if (shorter)root = deleteRightBalance(root, shorter);
		}
		else {
			Node* deleteNode = root;
			if (root->pRight == NULL) {
				Node* newRoot = root->pLeft;
				success = true;
				shorter = true;
				delete deleteNode;
				return newRoot;
			}
			else if (root->pLeft == NULL) {
				Node* newRoot = root->pRight;
				success = true;
				shorter = true;
				delete deleteNode;
				return newRoot;
			}
			else {
				Node* exchPtr = root->pLeft;
				while (exchPtr->pRight != NULL) {
					exchPtr = exchPtr->pRight;
				}
				root->data = exchPtr->data;
				root->pLeft = AVLDelete(root->pLeft, exchPtr->data, shorter, success);
				if (shorter) root = deleteRightBalance(root, shorter);
			}
		}
		return root;
	}
	void remove(const T& value)
	{
		bool shorter = 0, success = 0;
		root = AVLDelete(root, value, shorter, success);
		//TODO
	}
	void printInorder(Node* r) {
		if (r == NULL)return;
		printInorder(r->pLeft);
		cout << r->data << " ";

		printInorder(r->pRight);
	}
	void printInorder() {
		//TODO
		printInorder(root);
	}
	bool search(Node* r, T value) {
		if (r == NULL) return 0;
		if (value > r->data) return search(r->pRight, value);
		else if (value < r->data)return search(r->pLeft, value);
		else return 1;
	}
	bool search(const T& value) {
		//TODO
		return search(root, value);
	}
	class Node
	{
	private:
		T data;
		Node* pLeft, * pRight;
		BalanceValue balance;
		friend class AVLTree<T>;

	public:
		Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
		~Node() {}
	};
};
int main()
{
	AVLTree<int> avl;
	int arr[] = { 10,52,98,32,68,92,40,13,42,63,99,100 };
	for (int i = 0; i < 12; i++) {
		avl.insert(arr[i]);
	}
	avl.remove(10);
	avl.remove(52);
	avl.remove(98);
	avl.printTreeStructure();
	avl.remove(32);
	avl.remove(68);
	avl.printTreeStructure();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
