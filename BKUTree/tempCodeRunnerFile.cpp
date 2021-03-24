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
    CHECK INDEX DATA(TU CHECK TRUE FALSE)