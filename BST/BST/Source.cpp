#include<iostream>
//#include"Header.h"
#include"BST.cpp"
using namespace std;
int main()
{
	BST<int> Tree;
	Tree.Insert(Tree.root, 34);
	Tree.Insert(Tree.root, 17);
	Tree.Insert(Tree.root, 25);
	Tree.Insert(Tree.root, 66);
	Tree.Insert(Tree.root, 71);
	Tree.Insert(Tree.root, 68);
	Tree.Insert(Tree.root, 50);
	Tree.Insert(Tree.root, 94);
	Tree.PreOrder(Tree.root);
	return 0;
}