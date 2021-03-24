
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class V, int M> // K: key, V: data, M: order
class BTree
{
    /// Convention: left < key <= right

public:
    class Entry;
    class Node;

private:
    Node* pRoot;

public:
    BTree() : pRoot(0) {};
    void clear(Node*& pRoot) {}
    void clear() {}
    ~BTree() {}

    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry
    {
    private:
        K key;
        V value; // accept all type
        Node* rightPtr;
        friend class BTree<K, V, M>;

    public:
        Entry(K key = K{}, V value = V{}) : key(key), value(value), rightPtr(0) {}
        ~Entry() {}

        string toString()
        {
            stringstream ss;
            // Hidden code
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
        Entry entries[M - 1];
        Node* firstPtr;
        int numEntries;
        friend class BTree<K, V, M>;

    public:
        Node() : firstPtr(0), numEntries(0) {};
        ~Node() {}
        bool isFull() { return (numEntries >= M - 1); }

        string toString()
        {
            stringstream ss;
            // Hidden code
            return ss.str();
        }
    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method implementation          ///
    /////////////////////////////////////////////////////////////
public:
    /// insert(inKey, inValue)
    /// BEGIN STUDENT CODE
    // Helping function
    void insertEntry(Node* node, int entryNdx, Entry newEntry)
    {
        int shifter = node->numEntries + 1;
        while (shifter > entryNdx + 1)
        {
            node->entries[shifter] = node->entries[shifter - 1];
            shifter = shifter - 1;
        }
        node->entries[shifter] = newEntry;
        node->numEntries = node->numEntries + 1;
        return;
    }

    void splitNode(Node* node, int entryNdx, Entry upEntry)
    {
        int minEntries = (M / 2) + 1;
        Node* rightPtr = new Node();
        int fromNdx = 0;
        // Build right subtree node
        if (entryNdx <= minEntries)
            fromNdx = minEntries + 1;
        else
            fromNdx = minEntries + 2;
        int toNdx = 1;
        rightPtr->numEntries = node->numEntries - fromNdx + 1;
        while (fromNdx <= node->numEntries)
        {
            rightPtr->entries[toNdx] = node->entries[fromNdx];
            fromNdx = fromNdx + 1;
            toNdx = toNdx + 1;
        }
        node->numEntries = node->numEntries - rightPtr->numEntries;
        if (entryNdx <= minEntries)
            insertEntry(node, entryNdx, upEntry);
        else
        {
            insertEntry(rightPtr, entryNdx - minEntries, upEntry);
            node->numEntries = node->numEntries - 1;
            rightPtr->numEntries = rightPtr->numEntries + 1;
        }
        // Build entry for parent
        int medianNdx = minEntries + 1;
        upEntry.value = node->entries[medianNdx].value;
        upEntry.rightPtr = rightPtr;
        rightPtr->firstPtr = node->entries[medianNdx].rightPtr;

        return;
    }
    int searchNode(Node* nodePtr, K target)
    {
        int walker = 0;
        if (target < nodePtr->entries[0].key)
            walker = 0;
        else
        {

            int walker = nodePtr->numEntries - 1;
            while (target < nodePtr->entries[walker].key)
            {
                walker = walker - 1;
            }
        }
        return walker;
    }
    bool insertNode(Node* root, Entry data, Entry upEntry)
    {
        bool taller = 0;
        if (root == NULL)
        {
            upEntry.key = data.key;
            upEntry.value = data.value;
            upEntry.rightPtr = NULL;
            taller = 1;
        }
        else
        {
            Node* subTree = root->firstPtr;
            int entryNdx = searchNode(root, data.key);
            if (entryNdx >= 0)
                subTree = root->entries[entryNdx].rightPtr;
            else
                subTree = root->firstPtr;
            taller = insertNode(subTree, data, upEntry);
            if (taller)
            {
                if (root->isFull())
                {
                    splitNode(root, entryNdx + 1, upEntry);
                    taller = 1;
                    //root->numEntries = root->numEntries + 1;
                }
                else
                {
                    insertEntry(root, entryNdx + 1, upEntry);
                    taller = 0;
                    root->numEntries = root->numEntries + 1;
                }
            }
        }
        return taller;
    }
    Node* BTreeInsert(Node* root, Entry data)
    {
        Entry upEntry = data;
        bool taller = insertNode(root, data, upEntry);
        if (taller)
        {
            // Tree has grown. Create new root.

            Node* newPtr = new Node();
            // newPtr->entries[1] = upEntry;
            newPtr->entries[0] = upEntry;
            //newPtr->entries[1] = upEntry;
            newPtr->firstPtr = root;
            newPtr->numEntries = 1;
            root = newPtr;
            //root->entries[0] = root->entries[1];
        }
        return root;
    }
    void insert(const K& inKey, const V& inValue)
    {

        Entry newentry(inKey, inValue);

        pRoot = BTreeInsert(pRoot, newentry);
    }

    void print()
    {
        //cout << pRoot->entries[0].key;
        //cout << pRoot->firstPtr->entries[1].key;
        cout << pRoot->firstPtr->entries[1].key;
    } /// END STUDENT CODE

    void BTreeTraversal(Node* root, string &str) {
       
      int scanCount = 0;
            Node * ptr = root->firstPtr;
            str += root->toString();
            str += " ";
        while (scanCount <= root->numEntries) {
            if (ptr != NULL) {
                BTreeTraversal(ptr,str);
            }
            if (scanCount <= root->numEntries) {
             
                ptr = root->entries[scanCount].rightPtr;
            }
            scanCount = scanCount + 1;
        }
        return;
    }
    string toStringInOrder() {
        string str = "";
        BTreeTraversal(pRoot, str);
        return str;
    }
    bool BTreeSearch(Node* root, K target, Node* &node, int &entryNo) {
        if (root == NULL) return 0;
        bool found = 0;
        if (target < root->entries[0].key) return BTreeSearch(root->firstPtr, target, node, entryNo);
        else {
            entryNo = root->numEntries-1;
            while (target < root->entries[entryNo].key)
            {
                entryNo = entryNo - 1;
                if (entryNo < 0) break;
            }
            if (entryNo < 0) found = 0;
            else if (target == root->entries[entryNo].key) {
                found = true;
                node = root;
            }
            else return BTreeSearch(root->entries[entryNo].rightPtr, target, node, entryNo);
        }
        return found;
   }
    bool search(const K& key, Node*& outNodePtr, int& outEntryIdx) {
        return  BTreeSearch( pRoot, key, outNodePtr,  outEntryIdx);
    }
};
int main()
{

    BTree<int, int, 3> bTree;
    int keys[] = {78, 21, 14};
    int size = sizeof(keys) / sizeof(int);

    for (int idx = 0; idx < size; idx++)
    {
        bTree.insert(keys[idx], idx);
    }
    bTree.print();
    return 0;
}