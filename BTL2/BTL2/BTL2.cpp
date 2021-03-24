#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename K, class V>
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

public:
	AVLTree *avl;
	SplayTree *splay;
	queue<K> keys;
	int maxNumOfKeys;

public:
	BKUTree(int maxNumOfKeys = 5)
	{
		avl = NULL;
		splay = NULL;
		this->maxNumOfKeys = maxNumOfKeys;
		keys;
	}
	//~BKUTree() { this->clear(); }

	void add(K key, V value)
	{
		if (this->splay == NULL)
		{
			BKUTree<int, int>::SplayTree *newAVLTree = new SplayTree();
			newAVLTree->add(key, value);
			this->splay = newAVLTree;
		}
		else
			this->splay->add(key, value);
	}
	void print()
	{

		this->avl->printPreorder();
	}
	//void remove(K key);
	//V search(K key, vector<K>& traversedList);

	void traverseNLROnAVL(void (*func)(K key, V value))
	{
		this->avl->traverseNLR(func);
	}
	void traverseNLROnSplay(void (*func)(K key, V value))
	{
		this->splay->traverseNLR(func);
	}

	//void clear();

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

			Node(Entry *entry = NULL, Node *parent = NULL, Node *left = NULL, Node *right = NULL)
			{
				this->entry = entry;
				this->left = left;
				this->parent = parent;
				this->right = right;
				this->corr = NULL;
			}
			friend class SplayTree;
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
		}
		void zigzag(Node *&root)
		{
			rotateRight(root->right);
			rotateLeft(root);
		}
		void zagzig(Node *&root)
		{
			rotateLeft(root->left);
			rotateRight(root);
		}
		void zigzig(Node *&root)
		{
			rotateRight(root);
			rotateRight(root);
		}
		void zagzag(Node *&root)
		{
			rotateLeft(root);
			rotateLeft(root);
		}
		void splay(Node *&root, bool splayOnce)
		{
			if (root->parent == NULL)
			{
				return;
			}
			Node *Parent = root->parent;
			Node *grand = Parent->parent;
			//ONLY ZIG OR ZAG
			if (grand == NULL)
			{
				//ZIG
				if (root == Parent->left)
					rotateRight(this->root);
				//ZAG
				else
					rotateLeft(this->root);
			}
			else
			{
				if (Parent == grand->left)
				{
					//ZIGZIG
					if (root == Parent->left)
					{
						if ((grand->parent != NULL))
						{
							if (grand->parent->right == NULL)
								zigzig(grand->parent->left);
							else if (grand->parent->left == NULL)
								zigzig(grand->parent->right);
							else
								zigzig((grand->parent->left == grand) ? grand->parent->left : grand->parent->right);
						}
						else
							zigzig(this->root);
					}
					//ZAGZIG
					else
					{
						if ((grand->parent != NULL))
						{
							if (grand->parent->right == NULL)
								zagzig(grand->parent->left);
							else if (grand->parent->left == NULL)
								zagzig(grand->parent->right);
							else
								zagzig((grand->parent->left == grand) ? grand->parent->left : grand->parent->right);
						}
						else
							zagzig(this->root);
					}
				}
				else
				{
					//ZAGZAG
					if (root == Parent->right)
					{
						if ((grand->parent != NULL))
						{
							if (grand->parent->right == NULL)
								zagzag(grand->parent->left);
							else if (grand->parent->left == NULL)
								zagzag(grand->parent->right);
							else
								zagzag((grand->parent->left == grand) ? grand->parent->left : grand->parent->right);
						}
						else
							zagzag(this->root);
					}
					//ZIGZAG
					else
					{
						if ((grand->parent != NULL))
						{
							if (grand->parent->right == NULL)
								zigzag(grand->parent->left);
							else if (grand->parent->left == NULL)
								zigzag(grand->parent->right);
							else
								zigzag((grand->parent->left == grand) ? grand->parent->left : grand->parent->right);
						}
						else
							zigzag(this->root);
					}
				}
			}
			if (!splayOnce)
				splay(root, 0);
		}

		void add(K key, V value)
		{
			Entry *newentry = new Entry(key, value);
			add(newentry);
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
					Node *x = new Node(entry, prev);
					prev->left = x;
					splay(x);
				}
				else
				{
					Node *x = new Node(entry, prev);
					prev->right = x;
					splay(x);
				}
			}
		}

		//void remove(K key);
		// V search(K key);
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
			traverseNLR(this->root, func);
		}

		//void clear();
	};

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

			Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
			{
				this->entry = entry;
				this->left = left;
				this->right = right;
				this->balance = 0;
				this->corr = NULL;
			}
			friend class AVLTree;
		};

	public:
		Node *root;

		AVLTree() : root(NULL){};
		// ~AVLTree() { this->clear(); };

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
				case 1:
					root->balance = 0;
					root->left->balance = 0;
					root->right->balance = 2;
					break;
				case 0:
					root->left->balance = 0;
					root->right->balance = 0;
					break;
				case 2:
					root->balance = 0;
					root->right->balance = 0;
					root->left->balance = 1;
					break;
				}
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
				case 1:
					root->balance = 0;
					root->left->balance = 0;
					root->right->balance = 2;
					break;
				case 0:
					root->left->balance = 0;
					root->right->balance = 0;
					break;
				case 2:
					root->balance = 0;
					root->right->balance = 0;
					root->left->balance = 2;
					break;
				}
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
				return;
			}
			if (value->key < root->entry->key)
			{
				insertAvlTree(root->left, value, taller);
				if (taller)
				{
					switch (root->balance)
					{
					case 1:
						leftBalance(root, taller);
						break;
					case 2:
						root->balance = 0;
						taller = 0;
						break;
					case 0:
						root->balance = 1;
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
					case 2:
						rightBalance(root, taller);
						break;
					case 1:
						root->balance = 0;
						taller = 0;
						break;
					case 0:
						root->balance = 2;
						break;
					}
				}
			}
			else
				throw "Duplicate key";
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
					root->left = AVLDelete(root->left, findmax->entry->key, shorter, success);
					if (shorter)
					{
						root = deleteRightBalance(root, shorter);
					}
				}
			}
			return root;
		}

		void traverseNLR(Node *r, void (*func)(K key, V value))
		{

			if (r == NULL)
				return;
			(*func)(r->entry->key, r->entry->value);
			traverseNLR(r->left, func);
			traverseNLR(r->right, func);
		}
		void printPreorder(Node *r)
		{
			if (r == NULL)
				return;
			printPreorder(r->left);
			cout << r->entry->key << " ";
			printPreorder(r->right);
		}
		void printPreorder()
		{
			printIgnore(root);
		}
		bool search(Node *r, K value)
		{
			if (r == NULL)
				return 0;
			if (value > r->entry->key)
				return search(r->right, value);
			else if (value < r->entry->key)
				return search(r->left, value);
			else
				return 1;
		}
		bool search(const K &value)
		{
			return search(root, value);
		}

		void add(K key, V value)
		{
			Entry *newentry = new Entry(key, value);
			add(newentry);
		}
		void add(Entry *entry)
		{
			bool taller = 1;

			insertAvlTree(root, entry, taller);
		}
		void remove(K key)
		{
			bool shorter = 0;
			bool success = 0;
			root = AVLDelete(root, key, shorter, success);
		}
		// V search(K key);

		void traverseNLR(void (*func)(K key, V value))
		{
			traverseNLR(root, func);
		}

		// void clear();
	};
};
void printKey(int key, int value)
{
	cout << key << endl;
}
int main()
{
	/*BKUTree<int, int>* tree = new BKUTree<int, int>();
	int keys[] = { 1, 3, 5, 7, 9, 2, 4 };
	for (int i = 0; i < 7; i++) tree->add(keys[i], keys[i]);
	tree->traverseNLROnAVL(printKey);*/
	BKUTree<int, int> *tree = new BKUTree<int, int>();
	int keys[] = {15, 3, 21, 10, 9, 8, 6, 2, 4, 0, 1, 17, 7};
	for (int i = 0; i < 13; i++)
		tree->add(keys[i], keys[i]);
	tree->traverseNLROnSplay(printKey);
	return 0;
}