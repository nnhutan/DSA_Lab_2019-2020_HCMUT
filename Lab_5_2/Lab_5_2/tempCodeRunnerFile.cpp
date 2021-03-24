  int searchNode(Node *nodePtr, K target)
    {
        int walker = 0;
        if (target < nodePtr->entries[0].key)
            walker = 0;
        else
        {
            while(target>=nodePtr->entries[walker].key) walker++;
            // int walker = nodePtr->numEntries;
            // while (target < nodePtr->entries[walker-1].key)
            // {
            //     walker = walker - 1;
            // }
        }
        return walker;
    }
    bool insertNode(Node *root, Entry data, Entry upEntry)
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
            Node *subTree = root->firstPtr;
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
                    splitNode(root, entryNdx, upEntry);
                    taller = 1;
                    //root->numEntries = root->numEntries + 1;
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
    Node *BTreeInsert(Node *root, Entry data)
    {
        Entry upEntry = data;
        bool taller = insertNode(root, data, upEntry);
        if (taller)
        {
            // Tree has grown. Create new root.

            Node *newPtr = new Node();
            // newPtr->entries[1] = upEntry;
            newPtr->entries[0] = upEntry;
            newPtr->firstPtr = root;
            newPtr->numEntries = 1;
            root = newPtr;
            //root->entries[0] = root->entries[1];
        }
        return root;
    }
    void insert(const K &inKey, const V &inValue)
    {
        Entry newentry(inKey, inValue);

        pRoot=BTreeInsert(pRoot, newentry);
    }
