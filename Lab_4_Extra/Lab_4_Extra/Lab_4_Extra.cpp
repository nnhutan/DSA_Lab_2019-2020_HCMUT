#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
	class Node;
private:
	Node* root;
public:
	BinarySearchTree() : root(nullptr) {}
	~BinarySearchTree()
	{
		// You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
	}

	//Helping function

	void add(T value) {
		//TODO
		if (root == NULL) root = new Node(value);
		else {
			Node* pWalk = root;
			Node* parent = pWalk;
			while (pWalk != NULL) {
				parent = pWalk;
				if (parent->value >= value) pWalk = pWalk->pLeft;
				else pWalk = pWalk->pRight;
			}
			if (parent->value >= value) parent->pLeft = new Node(value);
			else parent->pRight = new Node(value);
		}

	}
	Node* findSmallest(Node* root)
	{
		Node* current = root;
		/* loop down to find the leftmost leaf */
		while (current->pLeft != NULL) {
			current = current->pLeft;
		}
		return current;
	}
	Node* DeleteItems(Node* root, T data, int& t)
	{
		t++;
		if (root == NULL) return root;
		else if (root->value > data) root->pLeft = DeleteItems(root->pLeft, data, t);
		else if (root->value < data) root->pRight = DeleteItems(root->pRight, data, t);
		else {
			if (root->pLeft == NULL) {
				Node* temp = root->pRight;
				delete root;
				if (t == 1) { this->root = temp; };
				return temp;
			}
			else if (root->pRight == NULL) {
				Node* temp = root->pLeft;
				delete root;
				if (t == 1) { this->root = temp; };
				return temp;
			}
			else {
				Node* temp = findSmallest(root->pRight);
				root->value = temp->value;
				root->pRight = DeleteItems(root->pRight, temp->value, t);
			}
		}
		return root;
	}
	void deleteNode(T value) {
		//TODO
		int t = 0;
		DeleteItems(root, value, t);

	}
	string inOrderRec(Node* root) {
		stringstream ss;
		if (root != nullptr) {
			ss << inOrderRec(root->pLeft);
			ss << root->value << " ";
			ss << inOrderRec(root->pRight);
		}
		return ss.str();
	}

	string inOrder() {
		return inOrderRec(this->root);
	}

	void InOrder(Node* root)
	{
		if (root == NULL) return;
		InOrder(root->pLeft);
		cout << root->value << " ";
		InOrder(root->pRight);
	}

	bool find(Node * root,T i) {
		// TODO: return true if value i is in the tree; otherwise, return false.
		Node* p = root;
		while (p != NULL) {
			if (p->value > i)p = p->pLeft;
			else if (p->value < i)p = p->pRight;
			else return 1;
		}
		return 0;
	}
	bool find(T i) {
		// TODO: return true if value i is in the tree; otherwise, return false.
		return find(root, i);
	}
	void sum(Node* root, T l, T r,T&sumsum) {
		// TODO: return the sum of all element in the tree has value in range [l,r].
		if (root == NULL) return;
		sum(root->pLeft,l,r,sumsum);
		if ((root->value - l) * (root->value - r) <= 0) sumsum += root->value;
		sum(root->pRight,l,r,sumsum);
	}
	T sum(T l, T r) {
		// TODO: return the sum of all element in the tree has value in range [l,r].
		T sumsum = (T)0;
		 sum(root, l, r, sumsum);
		 return sumsum;
	}
	T getMin(Node*root) {
		//TODO: return the minimum values of nodes in the tree.
		if (root->pLeft == NULL) return root->value;
		else return getMin(root->pLeft);
	}

	T getMax(Node*root) {
		//TODO: return the maximum values of nodes in the tree.
		if (root->pRight == NULL) return root->value;
		else return getMax(root->pRight);
	}
	T getMin() {
		//TODO: return the minimum values of nodes in the tree.
		return getMin(root);
	}

	T getMax() {
		//TODO: return the maximum values of nodes in the tree.
		return getMax(root);
	}
	void InOrder()
	{
		InOrder(root);
	}
	class Node
	{
	private:
		T value;
		Node* pLeft, * pRight;
		friend class BinarySearchTree<T>;
	public:
		Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
		~Node() {}
	};
};
#define SEPARATOR "#<ab@17943918#@>#"
template<class K, class V>
class BinaryTree
{
public:
	class Node;
private:
	Node* root;
public:
	BinaryTree() : root(nullptr) {}
	~BinaryTree()
	{
		// You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
	}
	class Node
	{
	private:
		K key;
		V value;
		Node* pLeft, * pRight;
		friend class BinaryTree<K, V>;
	public:
		Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
		~Node() {}
	};
	void addNode(string posFromRoot, K key, V value)
	{
		if (posFromRoot == "")
		{
			this->root = new Node(key, value);
			return;
		}
		Node* walker = this->root;
		int l = (int)posFromRoot.length();
		for (int i = 0; i < l - 1; i++)
		{
			if (!walker)
				return;
			if (posFromRoot[i] == 'L')
				walker = walker->pLeft;
			if (posFromRoot[i] == 'R')
				walker = walker->pRight;
		}
		if (posFromRoot[l - 1] == 'L')
			walker->pLeft = new Node(key, value);
		if (posFromRoot[l - 1] == 'R')
			walker->pRight = new Node(key, value);
	}

	//Helping functions
	int height(Node* r) {
		if (r == NULL)
			return -1;
		else {
			/* compute the height of each subtree */
			int lheight = height(r->pLeft);
			int rheight = height(r->pRight);

			/* use the larger one */
			if (lheight > rheight)
				return (lheight + 1);
			else return (rheight + 1);
		}
	}
	int getDiameter(Node* root) {
		if (root->pLeft == NULL && root->pRight == NULL) return 1;
		else if (root->pLeft == NULL) return height(root->pRight) + 2;
		else if (root->pRight == NULL)return height(root->pLeft) + 2;
		else return height(root->pLeft) + height(root->pRight) + 3;
	}
	int getDiameter() {
		//TODO

		return getDiameter(root);
	}
};
int main()
{
	BinarySearchTree<int> bst;
	for (int i = 0; i < 10; ++i) {
		bst.add(i);
	}
	cout << bst.getMin() << endl;
	cout << bst.getMax() << endl;
}