if (root == NULL)
        {
            success = shorter = 0;
            return NULL;
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
            Node *deleteNode = root;
            if (root->pRight == NULL)
            {
                Node *newRoot = root->pLeft;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else if (root->pLeft == NULL)
            {
                Node *newRoot = root->pRight;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
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