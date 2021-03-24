#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

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
        int l = posFromRoot.length();
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
    // STUDENT ANSWER BEGIN 
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
    int getHeight() {
        // TODO: return height of the binary tree.
        return height(this->root);
    }
    string preOrder(Node*r,string &s) {
        // TODO: return the sequence of values of nodes in pre-order.
        if (r == NULL)
            return"";
        /* first print data of node */
        s += to_string(r->value);
        s += " ";
        
        /* then recur on left sutree */
        preOrder(r->pLeft,s);
        /* now recur on right subtree */
        preOrder(r->pRight,s);
      
        return s;
    
    }
    string inOrder(Node* r, string &a) {
        // TODO: return the sequence of values of nodes in pre-order.
        if (r == NULL)
            return"";
        inOrder(r->pLeft,a);
        /* first print data of node */
        a += to_string(r->value);
        a += " ";

        /* then recur on left sutree */
        /* now recur on right subtree */
        inOrder(r->pRight,a);
       
        return a;
      
    }
    string postOrder(Node* r, string &s) {
        // TODO: return the sequence of values of nodes in pre-order.
       
        if (r == NULL)
        
            return"";
            
        
        /* first print data of node */

        /* then recur on left sutree */
        postOrder(r->pLeft,s);
        /* now recur on right subtree */
        postOrder(r->pRight,s);
        s += to_string(r->value);
        s += " ";
        
       
        return s;
    }
    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        string s;
        return preOrder(this->root,s);
    }

    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        string s;
        return inOrder(this->root,s);
    }

    string postOrder() {
        // TODO: return the sequence of values of nodes in post-order.
        string s;
        return postOrder(this->root,s);
    }
    // STUDENT ANSWER END
    int countTwoChildrenNode(Node*r,int& n)
    {
        if (r == NULL) return 0;
        if (r->pLeft != NULL && r->pRight != NULL) n = n + 1;
        countTwoChildrenNode(r->pLeft, n);
        countTwoChildrenNode(r->pRight, n);
        return n;
    }
    int countTwoChildrenNode()
    {
        int n=0;
        return countTwoChildrenNode(this->root, n);
    }
    int sumOfLeafs(Node * r, int &n) {
        //TODO
        if (r == NULL) return 0;
        if (r->pLeft == NULL && r->pRight == NULL) n = n + r->value;
        sumOfLeafs(r->pLeft, n);
        sumOfLeafs(r->pRight, n);
        return n;

    }
    int sumOfLeafs() {
        //TODO
        int n = 0;
        return sumOfLeafs(this->root, n);
    }
    void BFS(Node*r,int level)
    {
        if (r == NULL)
            return;
        else if (level == 0)
            cout << r->value << " ";
        else // level > 0  
        {
            BFS(r->pLeft, level - 1);
            BFS(r->pRight, level - 1);
        }
    }
    void BFS()
    {
        int h = getHeight();
        for (int i = 0; i <= h; i++)
        BFS(this->root,i);
    }
    bool isBST(Node*r) {
        // TODO: return true if a tree is a BST; otherwise, return false.
        if (r == NULL) return 1;
            if ((r->pLeft!=NULL&&r->value <= r->pLeft->value) || (r->pRight!=NULL&&r->value >= r->pRight->value)) return 0;
            if (!isBST(r->pLeft) || !isBST(r->pRight)) return 0;
        
        return 1;
       
      
    }
    bool isBST() {
        // TODO: return true if a tree is a BST; otherwise, return false.
        
       return isBST(root);
    }
};
int main() {

    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 6);
    binaryTree.addNode("L", 3, 4);
    binaryTree.addNode("R", 5, 100);
    binaryTree.addNode("LL", 4, 2);
    binaryTree.addNode("LR", 6, 5);
    binaryTree.addNode("LLL", 7, 0);
    binaryTree.addNode("LLLR", 8, 1);
    binaryTree.addNode("RR", 9, 101);
    binaryTree.addNode("RL", 10, 50);
    binaryTree.addNode("RLL", 11, 10);
    binaryTree.addNode("RLR", 12, 51);

    cout << binaryTree.isBST();
}