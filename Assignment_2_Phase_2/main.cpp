#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
class Interval
{
public:
    int start;
    int end;

    Interval(int start = 0, int end = 0)
    {
        this->start = start;
        this->end = end;
    }
};

int minPark(vector<Interval> lInterval)
{
    vector<pair<int, string>> store;
    for (auto it : lInterval)
    {
        store.push_back(make_pair(it.start, "s")); //"s" TO MARK START
        store.push_back(make_pair(it.end, "e"));   //"e" TO MARK END
    }
    sort(store.begin(), store.end());
    int result = 0, temp = 0;
    for (auto it : store)
    {
        temp += (it.second == "s") ? 1 : -1;
        result = max(result, temp);
    }
    return result;
}

class BusParking
{
public:
    class IntervalTree;
    IntervalTree *tree;
    BusParking()
    {
        tree = NULL;
    }
    void add(int s, int t)
    {
        if (this->tree == NULL)
        {
            tree = new IntervalTree();
        }
        tree->add(s, t);
    }
    void find(int x)
    {
        vector<pair<int, int>> result;
        tree->findAllIntersection(tree->root, x, result, 1);
        for (auto it : result)
            cout << "[" << it.first << ", " << it.second << "]" << endl;
        result.clear();
    }
    void remove(int s, int t)
    {
        tree->remove(s, t);
    }

    int minPark()
    {
        return tree->MaxIntersection;
    }
    void print()
    {
        tree->print();
    }

public:
    class IntervalTree
    {
    public:
        class Node
        {
            int start;
            int end;
            int maxEnd;
            int balance;
            Node *left;
            Node *right;
            Node(int start, int end, int maxEnd)
            {
                this->start = start;
                this->end = end;
                this->maxEnd = maxEnd;
                this->balance = 0;
                this->left = NULL;
                this->right = NULL;
            }
            friend class IntervalTree;
        };
        friend class BusParking;

    public:
        Node *root;
        int MaxIntersection;
        vector<int> ListPointMaxOverlap;
        IntervalTree()
        {
            this->root = NULL;
            this->MaxIntersection = 0;
        }

    public:
        void rotateLeft(Node *&root)
        {
            Node *tempPtr = root->right;
            root->right = tempPtr->left;
            tempPtr->left = root;
            root = tempPtr;
            if (root->left->left != NULL && root->left->right != NULL)
                root->left->maxEnd = max(max(root->left->left->maxEnd, root->left->right->maxEnd), root->left->end);
            else
            {
                if (root->left->left == NULL && root->left->right == NULL)
                    root->left->maxEnd = root->left->end;
                else if (root->left->left == NULL)
                {
                    root->left->maxEnd = max(root->left->right->maxEnd, root->left->end);
                }
                else
                    root->left->maxEnd = max(root->left->left->maxEnd, root->left->end);
            }
            if (root->left != NULL && root->right != NULL)
                root->maxEnd = max(max(root->left->maxEnd, root->right->maxEnd), root->end);
            else
            {
                if (root->left == NULL)
                    root->maxEnd = max(root->right->maxEnd, root->end);
                else
                    root->maxEnd = max(root->left->maxEnd, root->end);
            }
        }
        void rotateRight(Node *&root)
        {
            Node *tempPtr = root->left;
            root->left = tempPtr->right;
            tempPtr->right = root;
            root = tempPtr;
            if (root->right->right != NULL && root->right->left != NULL)
                root->right->maxEnd = max(max(root->right->right->maxEnd, root->right->left->maxEnd), root->right->end);
            else
            {
                if (root->right->right == NULL && root->right->left == NULL)
                    root->right->maxEnd = root->right->end;
                else if (root->right->right == NULL)
                {
                    root->right->maxEnd = max(root->right->left->maxEnd, root->right->end);
                }
                else
                    root->right->maxEnd = max(root->right->right->maxEnd, root->right->end);
            }
            if (root->left != NULL && root->right != NULL)
                root->maxEnd = max(max(root->left->maxEnd, root->right->maxEnd), root->end);
            else
            {
                if (root->left == NULL)
                    root->maxEnd = max(root->right->maxEnd, root->end);
                else
                    root->maxEnd = max(root->left->maxEnd, root->end);
            }
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
        void insertAvlTree(Node *&root, int start, int end, bool &taller)
        {
            if (root == NULL)
            {
                root = new Node(start, end, end);
                taller = 1;
                return;
            }
            if (root->maxEnd < end)
            {
                root->maxEnd = end;
            }
            if (start < root->start)
            {
                insertAvlTree(root->left, start, end, taller);
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

            else
            {
                insertAvlTree(root->right, start, end, taller);
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
        }
        bool findInterval(Node *root, int start, int end)
        {
            if (root == NULL)
                return false;
            if (root->start <= start && root->end != end)
                return findInterval(root->right, start, end);
            else if (root->start > start && root->end != end)
                return findInterval(root->left, start, end);
            else if (root->start == start && root->end == end)
                return true;
            else
                return false;
        }
        void add(int start, int end)
        {
            if (findInterval(root, start, end))
                return;
            vector<pair<int, string>> ListOverlap;
            // findAllIntersection(root, start, ListOverlap, 1);
            // int NumIntersectionOfStart = ListOverlap.size();
            // ListOverlap.clear();
            // findAllIntersection(root, end, ListOverlap, 0);
            // int NumIntersectionOfEnd = ListOverlap.size();
            // ListOverlap.clear();
            // if (NumIntersectionOfStart > NumIntersectionOfEnd && NumIntersectionOfStart + 1 >= MaxIntersection)
            // {
            //     ListPointMaxOverlap.push_back(start);
            //     MaxIntersection = NumIntersectionOfStart + 1;
            // }
            // else if (NumIntersectionOfStart < NumIntersectionOfEnd && NumIntersectionOfEnd + 1 >= MaxIntersection)
            // {
            //     ListPointMaxOverlap.push_back(end);
            //     MaxIntersection = NumIntersectionOfEnd + 1;
            // }
            // else if (NumIntersectionOfStart == NumIntersectionOfEnd && NumIntersectionOfStart + 1 >= MaxIntersection)
            // {
            //     ListPointMaxOverlap.push_back(start);
            //     ListPointMaxOverlap.push_back(end);
            //     MaxIntersection = NumIntersectionOfEnd + 1;
            // }
            findAllOverlapWithInterval(root, start, end, ListOverlap);
            if ((ListOverlap.size() / 2) + 1 > MaxIntersection)
            {
                ListOverlap.push_back(make_pair(start, "s"));
                ListOverlap.push_back(make_pair(end, "e"));
                sort(ListOverlap.begin(), ListOverlap.end());
                int result = 0, temp = 0;
                bool flag = 0;
                for (auto it = ListOverlap.begin(); it != ListOverlap.end(); it++)
                {
                    temp += ((*it).second == "s") ? 1 : -1;
                    result = max(result, temp);
                    if (result > MaxIntersection)
                    {
                        MaxIntersection = result;
                        if (!flag)
                        {
                            ListPointMaxOverlap.clear();
                            flag = 1;
                        }
                        ListPointMaxOverlap.push_back((*(it + 1)).first);
                    }
                    else if (result == MaxIntersection)
                        ListPointMaxOverlap.push_back((*(it + 1)).first);
                }
            }
            bool taller = 1;
            insertAvlTree(root, start, end, taller);
        }
        void print(Node *root)
        {
            if (root == NULL)
                return;
            print(root->left);
            cout << "[" << root->start << ", " << root->end << ", " << root->maxEnd << "]" << endl;
            print(root->right);
        }
        void print()
        {
            print(root);
        }
        void findAllIntersection(Node *root, int point, vector<pair<int, int>> &ListOverlap, bool isStart)
        {
            if (root == NULL)
                return;
            if (root->start <= point && root->end > point && isStart)
                ListOverlap.push_back(make_pair(root->start, root->end));
            if (root->start < point && root->end > point && !isStart)
                ListOverlap.push_back(make_pair(root->start, root->end));
            if (root->left != NULL)
            {
                if (root->left->maxEnd > point)
                    findAllIntersection(root->left, point, ListOverlap, isStart);
            }
            if (root->right != NULL)
            {
                if (point > root->start && root->right->maxEnd > point)
                    findAllIntersection(root->right, point, ListOverlap, isStart);
            }
        }
        void findAllOverlapWithInterval(Node *root, int start, int end, vector<pair<int, string>> &lInterval)
        {
            if (root == NULL)
                return;
            if (!((root->start >= end) || (root->end <= start)))
            {
                lInterval.push_back(make_pair(root->start, "s"));
                lInterval.push_back(make_pair(root->end, "e"));
            }
            if ((root->left != NULL) && (root->left->maxEnd > start))
                findAllOverlapWithInterval(root->left, start, end, lInterval);
            findAllOverlapWithInterval(root->right, start, end, lInterval);
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
        Node *AVLDelete(Node *root, int start, int end, bool &shorter, bool &success)
        {
            if (root == NULL)
            {
                success = shorter = 0;
                return root;
            }
            else if (start < root->start)
            {
                root->left = AVLDelete(root->left, start, end, shorter, success);
                if (root->left == NULL)
                {
                    if (root->right == NULL)
                    {
                        root->maxEnd = root->end;
                    }
                    else
                        root->maxEnd = max(root->right->maxEnd, root->end);
                }
                else
                {
                    if (root->right != NULL)
                        root->maxEnd = max(max(root->left->maxEnd, root->right->maxEnd), root->end);
                    else
                        root->maxEnd = max(root->left->maxEnd, root->end);
                }
                if (shorter)
                    root = deleteRightBalance(root, shorter);
            }
            else if (start > root->start || (start == root->start && end != root->end))
            {
                root->right = AVLDelete(root->right, start, end, shorter, success);
                if (root->left == NULL)
                {
                    if (root->right == NULL)
                    {
                        root->maxEnd = root->end;
                    }
                    else
                        root->maxEnd = max(root->right->maxEnd, root->end);
                }
                else
                {
                    if (root->right != NULL)
                        root->maxEnd = max(max(root->left->maxEnd, root->right->maxEnd), root->end);
                    else
                        root->maxEnd = max(root->left->maxEnd, root->end);
                }
                if (shorter)
                    root = deleteLeftBalance(root, shorter);
            }
            else if (end == root->end)
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
                    root->start = findmax->start;
                    root->end = findmax->end;
                    root->maxEnd = max(root->left->maxEnd, root->right->maxEnd);
                    root->left = AVLDelete(root->left, findmax->start, findmax->end, shorter, success);
                    if (shorter)
                    {
                        root = deleteRightBalance(root, shorter);
                    }
                }
            }
            return root;
        }
        void remove(int start, int end)
        {
            if (!findInterval(root, start, end))
                return;
            cout << "remove: "
                 << "[" << start << ", " << end << ")\n";
            bool shorter = 0;
            bool success = 0;
            root = AVLDelete(root, start, end, shorter, success);
            int check = 0;
            for (int i = ListPointMaxOverlap.size() - 1; i >= 0; i--)
            {
                vector<pair<int, int>> ListOverlap;
                findAllIntersection(root, ListPointMaxOverlap[i], ListOverlap, 1);
                if (ListOverlap.size() == MaxIntersection)
                    return;
                int tmp = ListOverlap.size();
                check = max(check, tmp);
            }
            MaxIntersection = check;
        }
    };
};

int main()
{
    BusParking abc;
    // abc.add(3, 6);
    // abc.add(8, 11);
    // abc.add(5, 7);
    // abc.add(2, 5);
    // abc.add(1, 3);
    // abc.add(6, 8);
    // abc.add(4, 9);
    // abc.add(7, 10);
    // abc.print();
    // cout << endl;
    // abc.find(5);
    // cout << endl;
    // cout << abc.tree->findInterval(abc.tree->root, 7, 9);
    // cout << endl;
    // cout << abc.minPark();
    // abc.add(5, 11);
    // cout << endl;
    // cout << abc.minPark();
    // abc.add(1, 3);
    // cout << endl;
    // cout << abc.minPark();
    // abc.add(3, 4);
    // cout << endl;
    // cout << abc.minPark();
    // abc.add(10, 11);
    // cout << endl;
    // cout << abc.minPark();
    // abc.add(9, 10);
    // cout << endl;
    // cout << abc.minPark();
    // abc.add(8, 9);
    // cout << endl;
    // cout << abc.minPark();
    abc.add(3, 6);
    abc.add(8, 11);
    abc.add(5, 7);
    abc.add(2, 5);
    abc.add(1, 3);
    abc.add(6, 8);
    abc.add(4, 9);
    abc.add(7, 10);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.add(-1, 20);
    abc.add(12, 15);
    abc.add(11, 13);
    abc.add(9, 12);
    abc.add(1, 8);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.remove(-1, 20);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.remove(9, 12);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.remove(4, 9);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.remove(12, 15);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.remove(1, 8);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    abc.add(1, 6);
    abc.print();
    cout << endl;
    cout << abc.minPark();
    cout << endl;
    // abc.remove(5, 7);
    // abc.print();
    // cout << endl;
    // cout << abc.minPark();
    // cout << endl;
    // abc.remove(3, 6);
    // abc.print();
    // cout << endl;
    // cout << abc.minPark();
    // cout << endl;
    // abc.remove(4, 9);
    // abc.print();
    // cout << endl;
    // cout << abc.minPark();
    // cout << endl;
    // abc.remove(7, 10);
    // abc.print();
    // cout << endl;
    // cout << abc.minPark();
    // cout << endl;
    for (auto it : abc.tree->ListPointMaxOverlap)
    {
        cout << it << " ";
    }
    return 0;
}