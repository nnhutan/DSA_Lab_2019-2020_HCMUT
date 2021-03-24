#include <iostream>
#include <math.h>
#include <queue>
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

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
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
    void insertAvlTree(Node *&root, T value, bool &taller)
    {
        if (root == NULL)
        {
            root = new Node(value);
            taller = 1;
            return;
        }
        if (value < root->data)
        {
            insertAvlTree(root->pLeft, value, taller);
            if (taller)
            {
                switch (root->balance)
                {
                case LH:
                    leftBalance(root, taller);
                    break;
                case RH:
                    root->balance = EH;
                    taller = 0;
                    break;
                case EH:
                    root->balance = LH;
                    break;
                }
            }
        }
        else
        {
            insertAvlTree(root->pRight, value, taller);
            if (taller)
            {
                switch (root->balance)
                {
                case RH:
                    rightBalance(root, taller);
                    break;
                case LH:
                    root->balance = EH;
                    taller = 0;
                    break;
                case EH:
                    root->balance = RH;
                    break;
                }
            }
        }
    }
    void leftBalance(Node *&root, bool &taller)
    {
        switch (root->pLeft->balance)
        {
        case LH:
            rotateRight(root);
            root->balance = EH;
            root->pRight->balance = EH;
            taller = 0;
            break;
        case RH:
            rotateLeft(root->pLeft);
            rotateRight(root);
            switch (root->balance)
            {
            case LH:
                root->balance = EH;
                root->pLeft->balance = EH;
                root->pRight->balance = RH;
                break;
            case EH:
                root->pLeft->balance = EH;
                root->pRight->balance = EH;
                break;
            case RH:
                root->balance = EH;
                root->pRight->balance = EH;
                root->pLeft->balance = LH;
                break;
            }
            break;
        }
        taller = 0;
    }
    void rightBalance(Node *&root, bool &taller)
    {
        switch (root->pRight->balance)
        {
        case RH:
            rotateLeft(root);
            root->balance = EH;
            root->pLeft->balance = EH;
            taller = 0;
            break;
        case LH:
            rotateRight(root->pRight);
            rotateLeft(root);
            switch (root->balance)
            {
            case LH:
                root->balance = EH;
                root->pLeft->balance = EH;
                root->pRight->balance = RH;
                break;
            case EH:
                root->pLeft->balance = EH;
                root->pRight->balance = EH;
                break;
            case RH:
                root->balance = EH;
                root->pRight->balance = EH;
                root->pLeft->balance = RH;
                break;
            }
            break;
        }
        taller = 0;
    }
    void rotateLeft(Node *&root)
    {
        Node *tempPtr = root->pRight;
        root->pRight = tempPtr->pLeft;
        tempPtr->pLeft = root;
        root = tempPtr;
    }
    void rotateRight(Node *&root)
    {
        Node *tempPtr = root->pLeft;
        root->pLeft = tempPtr->pRight;
        tempPtr->pRight = root;
        root = tempPtr;
    }
    void insert(const T &value)
    {
        bool taller = 1;
        insertAvlTree(root, value, taller);
    }

    Node *deleteRightBalance(Node *root, bool &shorter)
    {
        if (root->balance == LH)
        {
            root->balance = EH;
            return root;
        }
        else if (root->balance == EH)
        {
            root->balance = RH;
            shorter = false;
            return root;
        }
        else
        {
            if (root->pRight->balance == LH)
            {
                rotateRight(root->pRight);
                rotateLeft(root);
                if (root->balance == LH)
                {
                    root->pRight->balance = RH;
                    root->pLeft->balance = EH;
                }
                else if (root->balance == RH)
                {
                    root->pRight->balance = EH;
                    root->pLeft->balance = LH;
                }
                else
                {
                    root->pRight->balance = EH;
                    root->pLeft->balance = EH;
                }
                root->balance = EH;
            }
            else
            {
                rotateLeft(root);
                if (root->balance == RH)
                {
                    root->pLeft->balance = root->pRight->balance = EH;
                    root->balance = EH;
                }
                else
                {
                    root->balance = LH;
                    root->pLeft->balance = RH;
                    root->pRight->balance = EH;
                    shorter = false;
                }
            }
        }
        return root;
    }
    Node *deleteLeftBalance(Node *root, bool &shorter)
    {
        if (root->balance == RH)
        {
            root->balance = EH;
            return root;
        }
        else if (root->balance == EH)
        {
            root->balance = LH;
            shorter = false;
            return root;
        }
        else
        {
            if (root->pLeft->balance == RH)
            {
                rotateLeft(root->pLeft);
                rotateRight(root);
                if (root->balance == RH)
                {
                    root->pLeft->balance = LH;
                    root->pRight->balance = EH;
                }
                else if (root->balance == LH)
                {
                    root->pRight->balance = RH;
                    root->pLeft->balance = EH;
                }
                else
                {
                    root->pRight->balance = EH;
                    root->pLeft->balance = EH;
                }
                root->balance = EH;
            }
            else
            {
                rotateRight(root);
                if (root->balance == LH)
                {
                    root->pRight->balance = root->pLeft->balance = EH;
                    root->balance = EH;
                }
                else
                {
                    root->balance = RH;
                    root->pLeft->balance = EH;
                    root->pRight->balance = LH;
                    shorter = false;
                }
            }
        }
        return root;
    }
    Node *AVLDelete(Node *root, T deleteKey, bool &shorter, bool &success)
    {
        if (root == NULL)
        {
            success = shorter = 0;
            return root;
        }
        else if (deleteKey < root->data)
        {
            root->pLeft = AVLDelete(root->pLeft, deleteKey, shorter, success);
            if (shorter)
                root = deleteRightBalance(root, shorter);
        }
        else if (deleteKey > root->data)
        {
            root->pRight = AVLDelete(root->pRight, deleteKey, shorter, success);
            if (shorter)
                root = deleteLeftBalance(root, shorter);
        }
        else
        {
            if (root->pLeft == NULL)
            {
                Node *tmp = root->pRight;
                success = shorter = true;
                delete root;
                return tmp;
            }
            else if (root->pRight == NULL)
            {
                Node *tmp = root->pLeft;
                success = shorter = true;
                delete root;
                return tmp;
            }
            else
            {
                Node *findmax = root->pLeft;
                while (findmax->pRight != NULL)
                {
                    findmax = findmax->pRight;
                }
                root->data = findmax->data;
                root->pLeft = AVLDelete(root->pLeft, findmax->data, shorter, success);
                if (shorter)
                {
                    root = deleteRightBalance(root, shorter);
                }
            }
        }
        return root;
    }
    void remove(const T &value)
    {
        bool shorter = 0;
        bool success = 0;
        root = AVLDelete(root, value, shorter, success);
    }

    void printInorder(Node *r)
    {
        if (r == NULL)
            return;
        printInorder(r->pLeft);
        cout << r->data << " ";
        printInorder(r->pRight);
    }
    void printInorder()
    {
        printInorder(root);
    }
    bool search(Node *r, T value)
    {
        if (r == NULL)
            return 0;
        if (value > r->data)
            return search(r->pRight, value);
        else if (value < r->data)
            return search(r->pLeft, value);
        else
            return 1;
    }
    bool search(const T &value)
    {
        return search(root, value);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
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
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63, 99, 100};
    for (int i = 0; i < 12; i++)
    {
        avl.insert(arr[i]);
    }
    avl.printTreeStructure();
    for (int i = 11; i >= 0; i--)
    {
        avl.remove(arr[i]);
        avl.printTreeStructure();
        cout << "=====================================" << endl;
    }
    avl.printTreeStructure();
}