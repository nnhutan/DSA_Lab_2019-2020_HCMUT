#pragma once
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class K, class V>
class BKUTree {
public:
    class AVLTree;
    class SplayTree;

    class Entry {
    public:
        K key;
        V value;
        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree* avl;
    SplayTree* splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5) {}
    ~BKUTree() { this->clear(); }

    void add(K key, V value) {
      avl-> add(key, value);
    };
    void remove(K key);
    V search(K key, vector<K>& traversedList);

    void traverseNLROnAVL(void (*func)(K key, V value));
    void traverseNLROnSplay(void (*func)(K key, V value));

    void clear();

    class SplayTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            typename AVLTree::Node* corr;

            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
        };

    public:
        Node* root;

        SplayTree() : root(NULL) {};
        ~SplayTree() { this->clear(); };

        void add(K key, V value);
        void add(Entry* entry);
        void remove(K key);
        V search(K key);

        void traverseNLR(void (*func)(K key, V value));

        void clear();
    };

    class AVLTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            int balance;
            typename SplayTree::Node* corr;
            friend class AVLTree;
            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = NULL;
            }
        };

    public:
        Node* root;

        AVLTree() : root(NULL) {};
        ~AVLTree() { this->clear(); };


        Node* insertAvlTree(Node* root, Entry* value, bool& taller);
        void leftBalance(Node* root, bool& taller);
        void rightBalance(Node* root, bool& taller);
        Node* rotateLeft(Node* root);
        Node* rotateRight(Node* root);
        void add(K key, V value);
        void add(Entry* entry);

        void deleteRightBalance(Node* &root, bool& shorter);
        void deleteLeftBalance(Node* &root, bool& shorter);
        void AVLDelete(Node* &root, K deleteKey, bool& shorter, bool& success);
        void remove(K key);

        bool search(Node* r, K value, V&result);
        V search(K key);

        void printPreorder(Node* r, void(*func)(K key, V value));
        void traverseNLR(void (*func)(K key, V value));

        void clear();
    };
};
