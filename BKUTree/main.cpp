#include <iostream>
#include <queue>
#include <list>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <assert.h>

#include "BKUTree.cpp"

using namespace std;

stringstream strList;

// Them 2 method sau vao BKUTree de dung
/*

//==========     TESTER     ==========//
void checkNode(vector<K> &nodeAVL, vector<K> &nodeSPLAY) {
    if (avl == NULL) return;
    checkTrueNode(nodeAVL, nodeSPLAY, avl->root);
}
void checkTrueNode(vector<K> &nodeAVL, vector<K> &nodeSPLAY, typename AVLTree::Node *f) {
    if (!f)  return;
    typename SplayTree::Node *r = f->corr;
    if (r->entry->key != f->entry->key) {
        nodeAVL.push_back(f->entry->key);
        nodeSPLAY.push_back(r->entry->key);
    }
    checkTrueNode(nodeAVL, nodeSPLAY, f->left);
    checkTrueNode(nodeAVL, nodeSPLAY, f->right);
}

*/

template <class K, class V>
void printData(K key, V value)
{
    cout << key << " ";
}

string transVector(vector<int> data)
{
    stringstream ss;
    for (auto it = data.begin(); it != data.end(); it++)
    {
        ss << *it;
        ss << ',';
    }
    string re = ss.str();
    re[re.size() - 1] = '\0';
    return re;
}

#define NotAdd "Duplicate key"
#define NotFound "Not found"

int main()
{
    // TEST BKU TREE
    BKUTree<int, int> myTree;
    // TEST ADD 1
    {
        int arr[30] = {79, 128, 64, 114, 137, 34, 47, 131, 88, 123, 89, 76, 114, 38, 12, 142, 123, 44, 114, 12, 110, 75, 27, 104, 13, 120, 113, 44, 64, 18};
        cout << "\n=====================TEST ADD 1====-================\n";
        vector<int> fail;
        for (int i = 0; i < 30; i++)
        {
            try
            {
                myTree.add(arr[i], arr[i] * 2);
            }
            catch (const char *msg)
            {
                string data = "Duplicate key";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
        }
        stringstream list;
        if (fail.size() != 0)
        {
            cout << "List fail add :";
            list << "List fail add :";
            for (int i = 0; i < fail.size(); i++)
            {
                cout << " " << fail[i];
                list << " ";
                list << fail[i];
            }
            cout << endl;
        }
        cout << "List key error: 114 123 114 12 44 64\n";
        string finalCheck = list.str();
        string check = "List fail add : 114 123 114 12 44 64";
        for (int i = 0; i < check.size(); i++)
            if (finalCheck[i] != check[i])
                throw std::out_of_range("FAIL ADD DATA _ SAME KEY INT TREE");
        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL ADD 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
    // TEST DELETE 1
    {
        cout << "\n===================TEST DELETE 1===================\n";
        vector<int> fail;
        int arr[15] = {3, 44, 38, 132, 79, 114, 150, 34, 113, 89, 149, 110, 27, 137, 137};
        for (int i = 0; i < 15; i++)
        {
            try
            {
                myTree.remove(arr[i]);
            }
            catch (const char *msg)
            {
                string data = "Not found";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
        }
        stringstream list;
        if (fail.size() != 0)
        {
            cout << "List not found :";
            list << "List not found :";
            for (int i = 0; i < fail.size(); i++)
            {
                cout << " " << fail[i];
                list << " ";
                list << fail[i];
            }
            cout << endl;
        }
        cout << "List not found : 3 132 150 149 137\n";
        string finalCheck = list.str();
        string check = "List not found : 3 132 150 149 137";
        for (int i = 0; i < check.size(); i++)
            if (finalCheck[i] != check[i])
                throw std::out_of_range("FAIL DELETE DATA _ SAME KEY INT TREE");
        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL DELETE 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
    // TEST ADD 2
    {
        int arr[10] = {6, 42, 34, 99, 145, 19, 116, 7, 15, 24};
        cout << "\n=====================TEST ADD 2=====================\n";
        vector<int> fail;
        for (int i = 0; i < 10; i++)
        {
            try
            {
                myTree.add(arr[i], arr[i] * 2);
            }
            catch (const char *msg)
            {
                string data = "Duplicate key";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
        }
        if (fail.size() != 0)
        {
            cout << "List fail add :";
            for (int i = 0; i < fail.size(); i++)
                cout << " " << fail[i];
            cout << endl;
        }
        cout << "All key is good\n";
        string check = "List fail add :";
        if (fail.size() != 0)
            throw std::out_of_range("FAIL ADD DATA _ HAVE FAIL KEY");
        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL ADD 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
    myTree.clear();
    cout << "\n=======================================================\n";
    cout << "================  CLEAR TREE COMPLETE  ================";
    cout << "\n=======================================================\n";
    {
        int arr[30] = {79, 128, 64, 114, 137, 34, 47, 131, 88, 123, 89, 76, 114, 38, 12, 142, 123, 44, 114, 12, 110, 75, 27, 104, 13, 120, 113, 44, 64, 18};
        cout << "\n=====================TEST ADD 1=====================\n";
        vector<int> fail;
        for (int i = 0; i < 30; i++)
        {
            try
            {
                myTree.add(arr[i], arr[i] * 2);
            }
            catch (const char *msg)
            {
                string data = "Duplicate key";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
        }
        stringstream list;
        if (fail.size() != 0)
        {
            cout << "List fail add :";
            list << "List fail add :";
            for (int i = 0; i < fail.size(); i++)
            {
                cout << " " << fail[i];
                list << " ";
                list << fail[i];
            }
            cout << endl;
        }
        cout << "List key error: 114 123 114 12 44 64\n";
        string finalCheck = list.str();
        string check = "List fail add : 114 123 114 12 44 64";
        for (int i = 0; i < check.size(); i++)
            if (finalCheck[i] != check[i])
                throw std::out_of_range("FAIL ADD DATA _ SAME KEY INT TREE");
        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL ADD 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
    // TEST DELETE 1
    {
        cout << "\n===================TEST DELETE 1===================\n";
        vector<int> fail;
        int arr[15] = {3, 44, 38, 132, 79, 114, 150, 34, 113, 89, 149, 110, 27, 137, 137};
        for (int i = 0; i < 15; i++)
        {
            try
            {
                myTree.remove(arr[i]);
            }
            catch (const char *msg)
            {
                string data = "Not found";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
        }
        stringstream list;
        if (fail.size() != 0)
        {
            cout << "List not found :";
            list << "List not found :";
            for (int i = 0; i < fail.size(); i++)
            {
                cout << " " << fail[i];
                list << " ";
                list << fail[i];
            }
            cout << endl;
        }
        cout << "List not found : 3 132 150 149 137\n";
        string finalCheck = list.str();
        string check = "List not found : 3 132 150 149 137";
        for (int i = 0; i < check.size(); i++)
            if (finalCheck[i] != check[i])
                throw std::out_of_range("FAIL DELETE DATA _ SAME KEY INT TREE");
        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL DELETE 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
    // TEST ADD 2
    {
        int arr[10] = {6, 42, 34, 99, 145, 19, 116, 7, 15, 24};
        cout << "\n=====================TEST ADD 2=====================\n";
        vector<int> fail;
        for (int i = 0; i < 10; i++)
        {
            try
            {
                myTree.add(arr[i], arr[i] * 2);
            }
            catch (const char *msg)
            {
                string data = "Duplicate key";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
        }
        if (fail.size() != 0)
        {
            cout << "List fail add :";
            for (int i = 0; i < fail.size(); i++)
                cout << " " << fail[i];
            cout << endl;
        }
        cout << "All key is good\n";
        string check = "List fail add :";
        if (fail.size() != 0)
            throw std::out_of_range("FAIL ADD DATA _ HAVE FAIL KEY");
        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL ADD 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
    //CHECK INDEX DATA(TU CHECK TRUE FALSE)
    {
        cout << "\n==================CHECK INDEX DATA==================\n";
        cout << endl
             << "AVL Tree : ";
        myTree.traverseNLROnAVL(&printData);
        cout << "\nAVL Tree : 76 18 12 6 7 13 15 42 24 19 34 64 47 75 128 104 88 99 120 116 123 142 131 145" << endl;

        cout << "\nSplay Tree : ";
        myTree.traverseNLROnSplay(&printData);
        cout << "\nSplay Tree : 24 15 7 6 13 12 18 19 99 34 42 88 75 47 64 76 116 104 142 123 120 131 128 145" << endl;
    }
    // SEARCH DATA
    {
        cout << "\n====================SEARCH DATA====================\n";
        int arr[10] = {18, 150, 49, 78, 67, 110, 104, 40, 75, 82};
        vector<int> fail;
        vector<int> value;
        string checkValue[10];
        {
            checkValue[0] = "Find key : 18, value is : 36\nList key travel : 24 19 76";
            checkValue[1] = "Find key : 150, NOT FOUND\nList key travel : 18 42 64 75 76 128 142 145";
            checkValue[2] = "Find key : 49, NOT FOUND\nList key travel : 18 42 64 47 76 18";
            checkValue[3] = "Find key : 78, NOT FOUND\nList key travel : 18 42 64 75 76 128 104 88";
            checkValue[4] = "Find key : 67, NOT FOUND\nList key travel : 18 42 64 75 76 18";
            checkValue[5] = "Find key : 110, NOT FOUND\nList key travel : 18 42 64 75 76 128 104 120 116";
            checkValue[6] = "Find key : 104, value is : 208\nList key travel : 18 42 64 75 76 128";
            checkValue[7] = "Find key : 40, NOT FOUND\nList key travel : 18 42 24 34 76 18";
            checkValue[8] = "Find key : 75, value is : 150\nList key travel : 18 42 64";
            checkValue[9] = "Find key : 82, NOT FOUND\nList key travel : 18 42 64 75 76 128 104 88";
        }
        for (int i = 0; i < 10; i++)
        {
            value.push_back(-1);
            vector<int> data;
            cout << "\nFind key : " << arr[i];
            try
            {
                value[i] = myTree.search(arr[i], data);
            }
            catch (const char *msg)
            {
                string data = "Not found";
                bool yes = 1;
                int size = data.size();
                for (int i = 0; i < size; i++)
                    if (msg[i] != data[i])
                    {
                        yes = 0;
                        break;
                    }
                if (yes == 1)
                    fail.push_back(arr[i]);
            }
            if (value[i] != -1)
                cout << ", value is : " << value[i] << endl;
            else
                cout << ", NOT FOUND\n";
            cout << "List key travel :";
            for (auto it = data.begin(); it != data.end(); it++)
                cout << " " << *it;
            cout << "\n\tDATA CHECK:\n";
            cout << checkValue[i];
            cout << endl;
        }
        cout << endl;
        stringstream list;
        if (fail.size() != 0)
        {
            cout << "List NOT FOUND :";
            list << "List NOT FOUND :";
            for (int i = 0; i < fail.size(); i++)
            {
                cout << " " << fail[i];
                list << " ";
                list << fail[i];
            }
            cout << endl;
        }
        cout << "List NOT FOUND : 150 49 78 67 110 40 82\n";
        string finalCheck = list.str();
        string check = "List NOT FOUND : 150 49 78 67 110 40 82";
        for (int i = 0; i < check.size(); i++)
            if (finalCheck[i] != check[i])
                throw std::out_of_range("FAIL SEARCH DATA _ SEARCH KEY NOT IN TREE");

        vector<int> AVL;
        vector<int> SPLAY;
        myTree.checkNode(AVL, SPLAY);
        if (AVL.size() != 0)
        {
            for (int i = 0; i < AVL.size(); i++)
                cout << AVL[i] << " -- " << SPLAY[i] << endl;
            throw std::out_of_range("FAIL ADD 1 _ CORR MISS NODE");
        }
        else
            cout << "GOOD CORR\n"; // GOOD CORR
    }
}