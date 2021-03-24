#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree
{
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;
    class Node;

private:
    Node *root;

public:
    BTree() : root(0){};
    ~BTree() {}

    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry
    {
    private:
        K key;
        D data;
        Node *rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}

        string toString()
        {
            stringstream ss;
            ss << "<"
               << this->key << ","
               << this->data
               << ">";
            return ss.str();
        }
    };

    ///////////////////////////////////////////////////
    ///             CLASS `Node`                    ///
    ///////////////////////////////////////////////////
public:
    class Node
    {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0){};
        ~Node() {}

        bool isFull()
        {
            return (numEntries >= M - 1);
        }

        /// BEGIN STUDENT CODE
        string toString()
        {
            stringstream ss;
            ss << "["
               << "("
               << this->numEntries
               << ")";
            for (int i = 0; i < this->numEntries; i++)
            {
                ss << this->entries[i].toString();
            }
            ss << "]";
            return ss.str();
        }

        /// END STUDENT CODE
    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method run sample test         ///
    /////////////////////////////////////////////////////////////
    void testPrintNode(K *keys, D *data, int size)
    {
        Node node;

        for (int idx = 0; idx < size; idx++)
        {
            node.entries[idx].key = keys[idx];
            node.entries[idx].data = data[idx];
        }
        node.numEntries = size;
        cout << node.toString() << endl;
    }
    bool BTreeSearch(Node *root, K target, Node *&node, int &entryNo)
    {
        if (root == NULL)
            return 0;
        bool found = 0;
        if (target < root->entries[0].key)
            return BTreeSearch(root->firstPtr, target, node, entryNo);
        else
        {
            entryNo = root->numEntries - 1;
            while (target < root->entries[entryNo].key)
            {
                entryNo = entryNo - 1;
                if (entryNo < 0)
                    break;
            }
            if (entryNo < 0)
                found = 0;
            else if (target == root->entries[entryNo].key)
            {
                found = true;
                node = root;
            }
            else
                return BTreeSearch(root->entries[entryNo].rightPtr, target, node, entryNo);
        }
        return found;
    }
    bool search(const K &key, Node *&outNodePtr, int &outEntryIdx)
    {
        return BTreeSearch(root, key, outNodePtr, outEntryIdx);
    }

    void BTreeTraversal(Node *root, string &str)
    {

        int scanCount = 0;
        Node *ptr = root->firstPtr;
        str += root->toString();
        str += " ";
        while (scanCount <= root->numEntries)
        {
            if (ptr != NULL)
            {
                BTreeTraversal(ptr, str);
            }
            if (scanCount <= root->numEntries)
            {

                ptr = root->entries[scanCount].rightPtr;
            }
            scanCount = scanCount + 1;
        }
        return;
    }
    string toStringPreOrder()
    {
        string str = "";
        BTreeTraversal(this->root, str);
        return str;
    }

    void insertEntry(Node *node, int entryNdx, const Entry &newEntry)
    {
        int shifter = node->numEntries;
        while (shifter > entryNdx + 1)
        {
            node->entries[shifter] = node->entries[shifter - 1];
            shifter = shifter - 1;
        }
        node->entries[shifter] = newEntry;
        //node->numEntries = node->numEntries + 1;
        return;
    }
    void splitNode(Node *node, int entryNdx, Entry &upEntry)
    {

        int minEntries = (M / 2);
        Node *rightPtr = new Node();
        int fromNdx = 0;
        // Build right subtree node
        if (entryNdx <= minEntries - 1)
            fromNdx = minEntries;
        else
            fromNdx = minEntries + 1;

        rightPtr->numEntries = node->numEntries - fromNdx;
        int toNdx = 0;
        while (fromNdx < node->numEntries)
        {
            rightPtr->entries[toNdx] = node->entries[fromNdx];
            fromNdx = fromNdx + 1;
            toNdx = toNdx + 1;
        }
        node->numEntries = node->numEntries - rightPtr->numEntries;
        if (entryNdx <= minEntries - 1)
        {
            insertEntry(node, entryNdx, upEntry);
        }
        else
        {
            insertEntry(rightPtr, entryNdx - minEntries - 1, upEntry);
            node->numEntries = node->numEntries - 1;
            rightPtr->numEntries = rightPtr->numEntries + 1;
        }
        // Build entry for parent
        int medianNdx = minEntries;
        upEntry.data = node->entries[medianNdx].data;
        upEntry.key = node->entries[medianNdx].key;
        upEntry.rightPtr = rightPtr;
        rightPtr->firstPtr = node->entries[medianNdx].rightPtr;

        return;
    }
    int searchNode(Node *nodePtr, K target)
    {
        int walker = 0;
        if (target < nodePtr->entries[0].key)
            walker = -1;
        else
        {

            walker = nodePtr->numEntries - 1;
            while (target < nodePtr->entries[walker].key)
            {
                walker = walker - 1;
                if (walker < 0)
                    return walker;
            }
        }
        return walker;
    }
    bool insertNode(Node *&root, const K &key, const D &data, Entry &upEntry)
    {
        bool taller = 0;
        if (root == NULL)
        {
            upEntry.key = key;
            upEntry.data = data;
            upEntry.rightPtr = NULL;
            taller = 1;
        }
        else
        {
            Node *subTree = root->firstPtr;
            int entryNdx = searchNode(root, key);
            if (entryNdx >= 0)
                subTree = root->entries[entryNdx].rightPtr;
            else
                subTree = root->firstPtr;
            taller = insertNode(subTree, key, data, upEntry);
            if (taller)
            {
                if (root->isFull())
                {
                    splitNode(root, entryNdx, upEntry);
                    taller = 1;
                }
                else
                {
                    insertEntry(root, entryNdx, upEntry);
                    taller = 0;
                    root->numEntries = root->numEntries + 1;
                }
            }
        }
        return taller;
    }
    Node *BTreeInsert(Node *root, const K &key, const D &data)
    {
        Entry upEntry;
        bool taller = insertNode(root, key, data, upEntry);
        if (taller)
        {
            Node *newPtr = new Node();
            newPtr->entries[0] = upEntry;
            newPtr->firstPtr = root;
            newPtr->numEntries = 1;
            root = newPtr;
        }
        return root;
    }
    void insert(const K &key, const D &data)
    {

        this->root = BTreeInsert(this->root, key, data);
    }
};
int main()
{
    BTree<int, int, 3> bTree;
    int keys[] = {9, 21, 14};
    int size = sizeof(keys) / sizeof(int);

    for (int idx = 0; idx < size; idx++)
    {
        bTree.insert(keys[idx], idx);
    }

    cout << bTree.toStringPreOrder() << endl;
    return 0;
}
