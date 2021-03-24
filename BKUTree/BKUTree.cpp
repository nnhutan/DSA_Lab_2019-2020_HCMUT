#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdexcept>
using namespace std;

void printNSpace(int n)
{
	for (int i = 0; i < n - 1; i++)
		cout << " ";
}

template <class K, class V>
class BKUTree
{
public:
	class AVLTree;
	class SplayTree;

	class Entry
	{
	public:
		K key;
		V value;

		Entry(K key, V value) : key(key), value(value) {}
	};

private:
	AVLTree *avl;
	SplayTree *splay;
	queue<K> keys;
	int maxNumOfKeys;

public:
	BKUTree(int maxNumOfKeys = 5)
	{
		this->avl = NULL;
		this->splay = NULL;
		this->maxNumOfKeys = maxNumOfKeys;
	}
	~BKUTree() { this->clear(); }

	//==========     TESTER     ==========//
	void checkNode(vector<K> &nodeAVL, vector<K> &nodeSPLAY)
	{
		if (avl == NULL)
			return;
		checkTrueNode(nodeAVL, nodeSPLAY, avl->root);
	}
	void checkTrueNode(vector<K> &nodeAVL, vector<K> &nodeSPLAY, typename AVLTree::Node *f)
	{
		if (!f)
			return;
		typename SplayTree::Node *r = f->corr;
		if (r->entry->key != f->entry->key)
		{
			nodeAVL.push_back(f->entry->key);
			nodeSPLAY.push_back(r->entry->key);
		}
		checkTrueNode(nodeAVL, nodeSPLAY, f->left);
		checkTrueNode(nodeAVL, nodeSPLAY, f->right);
	}

	void add(K key, V value)
	{
		if (this->avl == NULL || this->splay == NULL)
		{
			this->splay = new SplayTree();
			this->avl = new AVLTree();
		}
		Entry *newentry = new Entry(key, value);
		this->splay->add(newentry);
		this->avl->add(newentry);
		this->splay->root->corr = this->avl->insertNode;
		this->splay->root->corr->corr = this->splay->root;
		int size = keys.size();
		if (size >= maxNumOfKeys)
			keys.pop();
		keys.push(key);
	}

	void remove(K key)
	{
		this->splay->remove(key);
		this->avl->remove(key);

		vector<K> KEY;
		while (keys.size() != 0)
		{
			if (keys.front() != key)
				KEY.push_back(keys.front());
			keys.pop();
		}

		for (auto it : KEY)
			keys.push(it);
		KEY.clear();

		if (this->splay->root != NULL)
			keys.push(this->splay->root->entry->key);

		int n = keys.size();
		if (n > this->maxNumOfKeys)
			keys.pop();
	}

	V search(K key, vector<K> &traversedList)
	{
		if (this->splay->root->entry->key == key)
		{
			int n = keys.size();
			if (n >= maxNumOfKeys)
				keys.pop();
			keys.push(key);
			return this->splay->root->entry->value;
		}

		vector<K> KEY;
		V result;
		while (keys.size() != 0)
		{
			KEY.push_back(keys.front());
			keys.pop();
		}
		for (auto i : KEY)
			keys.push(i);
		if (find(KEY.begin(), KEY.end(), key) != KEY.end())
		{
			typename BKUTree<K, V>::SplayTree::Node *target = this->splay->search(this->splay->root, key, traversedList);
			if (target == NULL)
				throw "Not found";
			this->splay->Splay(target, 1);
			if (target->parent == NULL)
				this->splay->root = target;
			result = target->entry->value;
		}
		else
		{
			typename BKUTree<K, V>::AVLTree::Node *target = this->avl->search(this->splay->root->corr, key, traversedList);
			if (target == NULL)
			{
				target = this->avl->search(this->avl->root, key, traversedList);
				if (target == NULL)
					throw "Not found";
			}
			this->splay->Splay(target->corr, 1);
			if (target->corr->parent == NULL)
				this->splay->root = target->corr;
			result = target->entry->value;
		}

		int n = keys.size();
		if (n >= maxNumOfKeys)
			keys.pop();
		keys.push(key);
		KEY.clear();
		return result;
	}

	void traverseNLROnAVL(void (*func)(K key, V value))
	{
		this->avl->traverseNLR(func);
	}
	void traverseNLROnSplay(void (*func)(K key, V value))
	{
		this->splay->traverseNLR(func);
	}

	void clear()
	{
		this->avl->clear();
		this->splay->clear();
		this->avl = NULL;
		this->splay = NULL;
		while (!keys.empty())
		{
			keys.pop();
		}
		this->maxNumOfKeys = 5;
	}

	//HELP ME
	void print()
	{
		cout << "======================================================================\n";
		cout << "Keys: [";
		queue<K> temp = keys;
		while (temp.size())
		{
			cout << temp.front() << ", ";
			temp.pop();
		}
		cout << "]\n";
		cout << "........................................................\n";
		this->splay->printTreeStructure();
		cout << "PreOrder: ";
		this->splay->print();
		cout << endl;
		cout << "........................................................\n";
		this->avl->printTreeStructure();
		cout << "PreOrder: ";
		this->avl->print();
		cout << endl;
		cout << "........................................................\n";
		cout << "======================================================================\n\n\n\n";
	}

	//////////////////////////////////////
	///       CLASS SPLAYTREE         ///
	////////////////////////////////////
	class SplayTree
	{
	public:
		class Node
		{
			Entry *entry;
			Node *left;
			Node *right;
			Node *parent;
			typename AVLTree::Node *corr;
			friend class SplayTree;
			friend class BKUTree<K, V>;
			Node(Entry *entry = NULL, Node *parent = NULL, Node *left = NULL, Node *right = NULL)
			{
				this->entry = entry;
				this->left = left;
				this->parent = parent;
				this->right = right;
				this->corr = NULL;
			}
		};

	public:
		Node *root;

		SplayTree() : root(NULL){};
		~SplayTree() { this->clear(); };

		void rotateLeft(Node *&root)
		{
			Node *tempPtr = root->right;
			root->right = tempPtr->left;
			tempPtr->left = root;
			root = tempPtr;
			root->parent = root->left->parent;
			root->left->parent = root;
			if (root->left->right != NULL)
				root->left->right->parent = root->left;
			if (root->parent != NULL)
			{
				if (root->parent->left == root->left)
					root->parent->left = root;
				else
					root->parent->right = root;
			}
		}
		void rotateRight(Node *&root)
		{
			Node *tempPtr = root->left;
			root->left = tempPtr->right;
			tempPtr->right = root;
			root = tempPtr;
			root->parent = root->right->parent;
			root->right->parent = root;
			if (root->right->left != NULL)
				root->right->left->parent = root->right;
			if (root->parent != NULL)
			{
				if (root->parent->right == root->right)
					root->parent->right = root;
				else
					root->parent->left = root;
			}
		}
		void zigzag(Node *root)
		{
			Node *ptr = root->right;
			rotateRight(ptr);
			rotateLeft(root);
		}
		void zagzig(Node *root)
		{
			Node *ptr = root->left;
			rotateLeft(ptr);
			rotateRight(root);
		}
		void zigzig(Node *root)
		{
			rotateRight(root);
			rotateRight(root);
		}
		void zagzag(Node *root)
		{
			rotateLeft(root);
			rotateLeft(root);
		}
		void Splay(Node *&root, bool SplayOnce)
		{
			if (root->parent == NULL)
			{
				return;
			}
			Node *Parent = root->parent;
			Node *grand = Parent->parent;
			if (grand == NULL)
			{
				//ZIG
				if (root == Parent->left)
					rotateRight(Parent);
				//ZAG
				else
					rotateLeft(Parent);
			}
			else
			{
				if (Parent == grand->left)
				{
					//ZIGZIG
					if (root == Parent->left)
						zigzig(grand);
					//ZAGZIG
					else
						zagzig(grand);
				}
				else
				{
					//ZAGZAG
					if (root == Parent->right)
						zagzag(grand);
					//ZIGZIG
					else
						zigzag(grand);
				}
			}
			if (!SplayOnce)
				Splay(root, 0);
		}

		void add(Entry *entry)
		{
			if (this->root == NULL)
				this->root = new Node(entry);
			else
			{
				Node *walker = this->root;
				Node *prev = walker;
				while (walker != NULL)
				{
					prev = walker;
					if (walker->entry->key > entry->key)
						walker = walker->left;
					else if (walker->entry->key < entry->key)
						walker = walker->right;
					else
						throw "Duplicate key";
				}
				if (prev->entry->key > entry->key)
				{
					Node *node = new Node(entry, prev);
					prev->left = node;
					Splay(node, 0);
					this->root = node;
				}
				else
				{
					Node *node = new Node(entry, prev);
					prev->right = node;
					Splay(node, 0);
					this->root = node;
				}
			}
		}
		void add(K key, V value)
		{
			add(new Entry(key, value));
		}

		Node *search(Node *root, K key, vector<K> &traversedList)
		{
			if (root == NULL)
				return NULL;
			traversedList.push_back(root->entry->key);
			if (root->entry->key > key)
				return search(root->left, key, traversedList);
			else if (root->entry->key < key)
				return search(root->right, key, traversedList);
			else
			{
				traversedList.pop_back();
				return root;
			}
		}
		V search(K key)
		{
			vector<K> traversedList;
			Node *target = search(root, key, traversedList);
			traversedList.clear();
			if (target == NULL)
				throw "Not found";
			Splay(target, 0);
			this->root = target;
			return target->entry->data;
		}

		void remove(K key)
		{
			vector<K> traversedList;
			Node *nodeDel = search(root, key, traversedList);
			traversedList.clear();
			if (nodeDel == NULL)
				throw "Not found";
			Splay(nodeDel, 0);
			this->root = nodeDel;
			if (this->root->left == NULL)
			{
				if (this->root->right != NULL)
				{
					this->root->right->parent = NULL;
					this->root = this->root->right;
					delete nodeDel;
				}
				else
				{
					delete this->root;
					this->root = NULL;
				}
			}
			else
			{
				if (this->root->right == NULL)
				{
					this->root->left->parent = NULL;
					this->root = this->root->left;
					delete nodeDel;
				}
				else
				{
					this->root->left->parent = NULL;
					Node *walker = this->root->left;
					while (walker->right != NULL)
						walker = walker->right;
					Splay(walker, 0);
					walker->right = this->root->right;
					this->root->right->parent = walker;
					delete nodeDel;
					this->root = walker;
				}
			}
		}

		void traverseNLR(Node *root, void (*func)(K key, V value))
		{

			if (root == NULL)
				return;
			(*func)(root->entry->key, root->entry->value);
			traverseNLR(root->left, func);
			traverseNLR(root->right, func);
		}
		void traverseNLR(void (*func)(K key, V value))
		{
			traverseNLR(this->root, func);
		}

		void clear(Node *root)
		{
			if (root == NULL)
				return;
			clear(root->left);
			clear(root->right);
			if (root->entry != NULL)
				delete root->entry;
			delete root;
		}
		void clear()
		{
			clear(root);
			root = NULL;
		}

		//HELP ME
		void print(Node *r)
		{
			if (r == NULL)
				return;
			cout << "[" << r->entry->key << ", " << r->corr->entry->key << "] ";
			print(r->left);
			print(r->right);
		}
		void print()
		{
			print(root);
		}
		int getHeightRec(Node *node)
		{
			if (node == NULL)
				return 0;
			int lh = this->getHeightRec(node->left);
			int rh = this->getHeightRec(node->right);
			return (lh > rh ? lh : rh) + 1;
		}
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
			queue<Node *> q;
			q.push(root);
			Node *temp;
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
					cout << temp->entry->key;
					q.push(temp->left);
					q.push(temp->right);
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
	};

	/////////////////////////////////////
	///       CLASS AVLTREE           ///
	////////////////////////////////////
	class AVLTree
	{
	public:
		class Node
		{
			Entry *entry;
			Node *left;
			Node *right;
			int balance;
			typename SplayTree::Node *corr;
			friend class AVLTree;
			friend class BKUTree<K, V>;
			Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
			{
				this->entry = entry;
				this->left = left;
				this->right = right;
				this->balance = 0;
				this->corr = NULL;
			}
		};

	public:
		Node *root;
		Node *insertNode;

		AVLTree() : root(NULL), insertNode(NULL){};
		~AVLTree() { this->clear(); };

		void rotateLeft(Node *&root)
		{
			Node *tempPtr = root->right;
			root->right = tempPtr->left;
			tempPtr->left = root;
			root = tempPtr;
		}
		void rotateRight(Node *&root)
		{
			Node *tempPtr = root->left;
			root->left = tempPtr->right;
			tempPtr->right = root;
			root = tempPtr;
		}
		void leftBalance(Node *&root, bool &taller)
		{
			switch (root->left->balance)
			{
			case 1:
				rotateRight(root);
				root->balance = 0;
				root->right->balance = 0;
				taller = 0;
				break;
			case 2:
				rotateLeft(root->left);
				rotateRight(root);
				switch (root->balance)
				{
				case 0:
					root->left->balance = 0;
					root->right->balance = 0;
					break;
				case 1:
					root->left->balance = 0;
					root->right->balance = 2;
					break;
				case 2:
					root->left->balance = 1;
					root->right->balance = 0;
					break;
				}
				root->balance = 0;
				break;
			}
			taller = 0;
		}
		void rightBalance(Node *&root, bool &taller)
		{
			switch (root->right->balance)
			{
			case 2:
				rotateLeft(root);
				root->balance = 0;
				root->left->balance = 0;
				taller = 0;
				break;
			case 1:
				rotateRight(root->right);
				rotateLeft(root);
				switch (root->balance)
				{
				case 0:
					root->left->balance = 0;
					root->right->balance = 0;
					break;
				case 1:
					root->left->balance = 0;
					root->right->balance = 2;
					break;
				case 2:
					root->left->balance = 1;
					root->right->balance = 0;
					break;
				}
				root->balance = 0;
				break;
			}
			taller = 0;
		}
		void insertAvlTree(Node *&root, Entry *value, bool &taller)
		{
			if (root == NULL)
			{
				root = new Node(value);
				taller = 1;
				this->insertNode = root;
				return;
			}
			if (value->key < root->entry->key)
			{
				insertAvlTree(root->left, value, taller);
				if (taller)
				{
					switch (root->balance)
					{
					case 0:
						root->balance = 1;
						break;
					case 1:
						leftBalance(root, taller);
						break;
					case 2:
						root->balance = 0;
						taller = 0;
						break;
					}
				}
			}

			else if (value->key > root->entry->key)
			{
				insertAvlTree(root->right, value, taller);
				if (taller)
				{
					switch (root->balance)
					{
					case 0:
						root->balance = 2;
						break;
					case 1:
						root->balance = 0;
						taller = 0;
						break;
					case 2:
						rightBalance(root, taller);
						break;
					}
				}
			}
			else
				throw "Duplicate key";
		}
		void add(Entry *entry)
		{
			bool taller = 1;
			insertAvlTree(root, entry, taller);
		}
		void add(K key, V value)
		{
			add(new Entry(key, value));
		}

		Node *deleteRightBalance(Node *root, bool &shorter)
		{
			if (root->balance == 1)
			{
				root->balance = 0;
				return root;
			}
			else if (root->balance == 0)
			{
				root->balance = 2;
				shorter = false;
				return root;
			}
			else
			{
				if (root->right->balance == 1)
				{
					rotateRight(root->right);
					rotateLeft(root);
					if (root->balance == 1)
					{
						root->right->balance = 2;
						root->left->balance = 0;
					}
					else if (root->balance == 2)
					{
						root->right->balance = 0;
						root->left->balance = 1;
					}
					else
					{
						root->right->balance = 0;
						root->left->balance = 0;
					}
					root->balance = 0;
				}
				else
				{
					rotateLeft(root);
					if (root->balance == 2)
					{
						root->left->balance = root->right->balance = 0;
						root->balance = 0;
					}
					else
					{
						root->balance = 1;
						root->left->balance = 2;
						root->right->balance = 0;
						shorter = false;
					}
				}
			}
			return root;
		}
		Node *deleteLeftBalance(Node *root, bool &shorter)
		{
			if (root->balance == 2)
			{
				root->balance = 0;
				return root;
			}
			else if (root->balance == 0)
			{
				root->balance = 1;
				shorter = false;
				return root;
			}
			else
			{
				if (root->left->balance == 2)
				{
					rotateLeft(root->left);
					rotateRight(root);
					if (root->balance == 2)
					{
						root->left->balance = 1;
						root->right->balance = 0;
					}
					else if (root->balance == 1)
					{
						root->right->balance = 2;
						root->left->balance = 0;
					}
					else
					{
						root->right->balance = 0;
						root->left->balance = 0;
					}
					root->balance = 0;
				}
				else
				{
					rotateRight(root);
					if (root->balance == 1)
					{
						root->right->balance = root->left->balance = 0;
						root->balance = 0;
					}
					else
					{
						root->balance = 2;
						root->left->balance = 0;
						root->right->balance = 1;
						shorter = false;
					}
				}
			}
			return root;
		}
		Node *AVLDelete(Node *root, K deleteKey, bool &shorter, bool &success)
		{
			if (root == NULL)
			{
				success = shorter = 0;
				return root;
			}
			else if (deleteKey < root->entry->key)
			{
				root->left = AVLDelete(root->left, deleteKey, shorter, success);
				if (shorter)
					root = deleteRightBalance(root, shorter);
			}
			else if (deleteKey > root->entry->key)
			{
				root->right = AVLDelete(root->right, deleteKey, shorter, success);
				if (shorter)
					root = deleteLeftBalance(root, shorter);
			}
			else
			{
				if (root->left == NULL)
				{
					Node *tmp = root->right;
					success = shorter = true;
					delete root;
					return tmp;
				}
				else if (root->right == NULL)
				{
					Node *tmp = root->left;
					success = shorter = true;
					delete root;
					return tmp;
				}
				else
				{
					Node *findmax = root->left;
					while (findmax->right != NULL)
					{
						findmax = findmax->right;
					}
					root->entry = findmax->entry;
					root->corr = findmax->corr;
					findmax->corr->corr = root;
					root->left = AVLDelete(root->left, findmax->entry->key, shorter, success);
					if (shorter)
					{
						root = deleteRightBalance(root, shorter);
					}
				}
			}
			return root;
		}
		void remove(K key)
		{
			bool shorter = 0;
			bool success = 0;
			root = AVLDelete(root, key, shorter, success);
		}

		Node *search(Node *root, K key, vector<K> &traversedList)
		{
			if (root == NULL)
				return NULL;
			if (traversedList.size() > 0)
			{
				if (root->entry->key == traversedList[0])
					return NULL;
			}
			traversedList.push_back(root->entry->key);
			if (root->entry->key > key)
				return search(root->left, key, traversedList);
			else if (root->entry->key < key)
				return search(root->right, key, traversedList);
			else
			{
				traversedList.pop_back();
				return root;
			}
		}
		V search(K key)
		{
			vector<K> traversedList;
			Node *target = search(root, key, traversedList);
			if (target != NULL)
			{
				traversedList.clear();
				return target->entry->value;
			}
			else
			{
				traversedList.clear();
				throw "Not found";
			}
		}

		void traverseNLR(Node *r, void (*func)(K key, V value))
		{

			if (r == NULL)
				return;
			(*func)(r->entry->key, r->entry->value);
			traverseNLR(r->left, func);
			traverseNLR(r->right, func);
		}
		void traverseNLR(void (*func)(K key, V value))
		{
			traverseNLR(root, func);
		}

		void clear(Node *root)
		{
			if (root == NULL)
				return;
			clear(root->left);
			clear(root->right);
			if (root->entry != NULL)
				delete root->entry;
			delete root;
		}
		void clear()
		{
			clear(root);
			root = NULL;
			insertNode = NULL;
		}

		//HELP ME
		void print(Node *r)
		{
			if (r == NULL)
				return;
			cout << "[" << r->entry->key << ", " << r->corr->entry->key << "] ";
			print(r->left);
			print(r->right);
		}
		void print()
		{
			print(root);
		}
		int getHeightRec(Node *node)
		{
			if (node == NULL)
				return 0;
			int lh = this->getHeightRec(node->left);
			int rh = this->getHeightRec(node->right);
			return (lh > rh ? lh : rh) + 1;
		}
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
			queue<Node *> q;
			q.push(root);
			Node *temp;
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
					cout << temp->entry->key;
					q.push(temp->left);
					q.push(temp->right);
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
	};
};

void printKey(int key, int value)
{
	cout << key << " ";
}
// int main()
// {
// 	// BKUTree<int, int> *tree = new BKUTree<int, int>();
// 	// int keys[] = {10, 7, 14, 15, 12, 11, 6, 8, 9}; //11
// 	// for (int i = 0; i < 9; i++)
// 	// 	tree->add(keys[i], keys[i]);
// 	// //tree->traverseNLROnAVL(printKey);
// 	// tree->print();
// 	// tree->remove(11);
// 	// tree->print();
// 	// tree->remove(14);
// 	// tree->print();
// 	// tree->remove(8);
// 	// tree->print();
// 	// tree->remove(7);
// 	// tree->print();
// 	// tree->remove(6);
// 	// tree->print();
// 	// tree->remove(10);
// 	// tree->print();
// 	// tree->remove(12);
// 	// tree->print();
// 	// tree->remove(9);
// 	// tree->print();
// 	// tree->remove(15);
// 	// tree->print();

// 	// BKUTree<int, int> *tree = new BKUTree<int, int>();
// 	// int keys[] = {10, 7, 14, 15, 12, 11, 6, 8, 9, 1, 50, 67, 102, 45, 74, 32, 27, 29, 56, 95, 100, 22, 76, 87, 89, 54, 69, 99, 88, 71, 73, 85, 90, 106, 121, 112, 83, 92};
// 	// int n = sizeof(keys) / sizeof(int);
// 	// for (int i = 0; i < n; i++)
// 	// 	tree->add(keys[i], keys[i]);
// 	// //tree->traverseNLROnAVL(printKey);
// 	// tree->print();
// 	BKUTree<int, int> *tree = new BKUTree<int, int>();
// 	int keys[] = {1, 3, 5, 7, 9, 2, 4};
// 	for (int i = 0; i < 7; i++)
// 	{
// 		tree->add(keys[i], i);
// 	}
// 	tree->print();
// 	vector<int> abc;
// 	tree->search(3, abc);
// 	tree->print();
// 	for (auto it : abc)
// 	{
// 		/* code */
// 		cout << it << " ";
// 	}
// 	cout << endl;

// 	tree->search(1, abc);
// 	for (auto it : abc)
// 	{
// 		/* code */
// 		cout << it << " ";
// 	}
// }
void printTree(int key, int value)
{
	cout << key << " ";
	cout << endl;
}
// int main()
// {
// 	try
// 	{
// 		BKUTree<int, int> tree;
// 		vector<int> vt;
// 		tree.add(1, 2);
// 		tree.add(3, 4);
// 		tree.add(5, 4);
// 		tree.add(7, 34);
// 		tree.add(9, 123);
// 		tree.add(13, 5432);
// 		tree.add(15, 123);
// 		tree.add(2, 454);
// 		tree.add(4, 372);
// 		tree.add(34, 243);
// 		tree.add(20, 242);
// 		tree.add(10, 241);
// 		tree.add(31, 1234);
// 		tree.remove(9);
// 		tree.remove(2);
// 		tree.remove(7);
// 		tree.remove(34);
// 		tree.remove(13);
// 		cout << "AVL : ";
// 		tree.traverseNLROnAVL(printTree);
// 		cout << '\n';
// 		cout << "splay : ";
// 		tree.traverseNLROnSplay(printTree);
// 		cout << '\n';
// 		tree.avl->printTreeStructure();
// 		cout << tree.search(6, vt);
// 		cout << '\n';
// 		for (auto i = vt.begin(); i != vt.end(); i++)
// 		{
// 			cout << *i << " ";
// 		}
// 		cout << '\n';
// 		tree.traverseNLROnSplay(printTree);
// 		// BKUTree<int,int>::SplayTree SPlay;
// 		// SPlay.add(4,7);
// 		// SPlay.add(3,7);
// 		// SPlay.add(2,7);
// 		// SPlay.add(1,7);
// 		// SPlay.add(5,7);
// 		// SPlay.traverseNLR(printTree);
// 		tree.clear();
// 	}
// 	catch (const char *msg)
// 	{
// 		cout << msg << endl;
// 	}
// 	return 0;
// }