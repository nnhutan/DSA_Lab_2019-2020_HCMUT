#include <iostream>
#include <queue>
#include <vector>
using namespace std;

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
    BKUTree(int maxNumOfKeys = 5) {}
    ~BKUTree() { this->clear(); }

    void add(K key, V value);
    void remove(K key);
    V search(K key, vector<K> &traversedList);

    void traverseNLROnAVL(void (*func)(K key, V value));
    void traverseNLROnSplay(void (*func)(K key, V value));

    void clear();

    class SplayTree
    {
    public:
        class Node
        {
            Entry *entry;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;

            Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
        };

    public:
        Node *root;

        SplayTree() : root(NULL){};
        ~SplayTree() { this->clear(); };

        void add(K key, V value);
        void add(Entry *entry);
        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value));

        void clear();
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
        };

    public:
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };

        void add(K key, V value);
        void add(Entry *entry);
        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value));

        void clear();
    };
};

int main()
{
    BKUTree<int, int> *tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    //tree->traverseNLROnAVL(print);
}