// BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header.h"
using namespace std;

BST::BST()
{
	this->root = NULL;
}

BST::~BST()
{

}

BST::Node::Node()
{
	this->data = 0;
	this->left = this->right = NULL;
}
BST::Node::Node(int data)
{
	this->data = data;
	this->left = NULL;
	this->right = NULL;
}
BST::Node::Node(int data, Node* left, Node* right)
{
	this->data = data;
	this->left = left;
	this->right = right;
}

BST::Node::~Node()
{
}
void BST::Insert(int data)
{

	if (root == NULL) root = new Node(data);
	else {
		Node* pWalk = root;
		Node* parent = pWalk;
		while (pWalk != NULL) {
			parent = pWalk;
			if (parent->data > data) pWalk = pWalk->left;
			else pWalk = pWalk->right;
		}
		if (parent->data > data) parent->left = new Node(data);
		else parent->right = new Node(data);
	}
}

BST::Node* BST::DeleteItems(Node* root, int data)
{
	if (root == NULL) return root;
	if (root->data > data) root->left = DeleteItems(root->left, data);
	else if (root->data < data) root->right = DeleteItems(root->right, data);
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			return temp;
		}
		if (root->right == NULL) {
			Node* temp = root->left;
			delete root;
			return temp;
		}
		Node* temp = findSmallest(root->right);
		root->data = temp->data;
		root->right = DeleteItems(root->right, temp->data);
	}
	return root;
}

void BST::PreOrder(Node* root)
{
	if (root == NULL) return;
	cout << root->data << " ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void BST::InOrder(Node* root)
{
	if (root == NULL) return;
	InOrder(root->left);
	cout << root->data << " ";
	InOrder(root->right);
}

void BST::PostOrder(Node* root)
{
	if (root == NULL) return;
	PostOrder(root->left);
	PostOrder(root->right);
	cout << root->data << " ";
}

BST::Node* BST::findSmallest(Node* root)
{
	if (root == NULL) return NULL;
	Node* pWalk = root;
	Node* parent = pWalk;
	while (pWalk != NULL) {
		parent = pWalk;
		pWalk = pWalk->left;
	}
	return parent;
}

BST::Node* BST::findLargest(Node* root)
{
	if (root == NULL) return NULL;
	Node* pWalk = root;
	Node* parent = pWalk;
	while (pWalk != NULL) {
		parent = pWalk;
		pWalk = pWalk->right;
	}
	return parent;
}

BST::Node* BST::search(int target)
{
	if (root == NULL) return NULL;
	Node* pWalk = root;
	while (pWalk != NULL) {
		if (pWalk->data == target) return pWalk;
		else if (pWalk->data > target) pWalk = pWalk->left;
		else pWalk = pWalk->right;
	}
	return NULL;
}
bool BST::isEmpty()
{
	return root == NULL;
}

int main()
{
	BST Tree;
	Tree.Insert(34);
	//Tree.Insert(17);
	////Tree.Insert(25);
	Tree.Insert(66);
	/*Tree.Insert(71);
	Tree.Insert(68);
	Tree.Insert(50);
	Tree.Insert(94);*/
	Tree.InOrder(Tree.root);
	cout << endl;
	Tree.DeleteItems(Tree.root, 34);
	Tree.InOrder(Tree.root);
	return 0;
}

