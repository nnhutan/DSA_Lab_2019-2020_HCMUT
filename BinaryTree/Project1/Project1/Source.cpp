#include<iostream>
using namespace std;
class BST
{
	int data;
	BST* left, * right;

public:
	BST();
	BST(int);
	BST* Insert(BST* root, int data);
	bool DeleteItems(BST* root, int data);
	void PreOrder(BST* root);
	void InOrder(BST* root);
	void PostOrder(BST* root);
	BST* findSmallest(BST* root);
	BST* findLargest(BST* root);
	BST* search(BST* root, int target);
};
BST::BST() {
	this->data = 0;
	this->left = this->right = NULL;
}

BST::BST(int value) {
	this->data = value;
	this->left = this->right = NULL;
}

BST* BST::Insert(BST* root, int value) {
	BST* parent = root, * pWalk = root;
	if (root == NULL) root = new BST(value);
	else {
		while (pWalk != NULL)
		{
			parent = pWalk;
			pWalk = (value > pWalk->data) ? pWalk->right : pWalk = pWalk->left;
		}
		if (value > parent->data) parent->right = new BST(value);
		else parent->left = new BST(value);
	}
	return root;
}
bool BST::DeleteItems(BST* root, int data)
{
	BST* parent = this->search(root, data);
	if (parent == NULL) {
		cout << "Items is not founded!" << endl;
		return 0;
	}
	if (parent->left == NULL) {
		BST* temp = parent;
		parent = parent->right;
		delete temp;
		return 1;
	}
	if (parent->right == NULL) {
		BST* temp = parent;
		parent = parent->left;
		delete temp;
		return 1;
	}
	BST* smallestSubRight = findSmallest(parent->right);
	swap(parent->data, smallestSubRight->data);
	BST* temp = smallestSubRight;
	smallestSubRight = NULL;
	//delete temp;
	return 1;
}
void BST::PreOrder(BST* root)
{
	if (root == NULL) return;
	cout << root->data << " ";
	PreOrder(root->left);
	PreOrder(root->right);
}
void BST::InOrder(BST* root) {
	if (root == NULL) return;
	InOrder(root->left);
	cout << root->data << " ";
	InOrder(root->right);
}
void BST::PostOrder(BST* root)
{
	if (root == NULL) return;
	PostOrder(root->left);
	PostOrder(root->right);
	cout << root->data << " ";
}
BST* BST::findSmallest(BST* root)
{
	if (root == NULL) return NULL;
	BST* pWalk = root;
	BST* parent = pWalk;
	while (pWalk != NULL) {
		parent = pWalk;
		pWalk = pWalk->left;
	}
	return parent;
}
BST* BST::findLargest(BST* root)
{
	if (root == NULL) return NULL;
	BST* pWalk = root;
	BST* parent = pWalk;
	while (pWalk != NULL) {
		parent = pWalk;
		pWalk = pWalk->right;
	}
	return parent;
}
BST* BST::search(BST* root, int target)
{
	if (root == NULL) return NULL;
	BST* pWalk = root;
	while (pWalk != NULL) {
		if (pWalk->data == target) return pWalk;
		else if (pWalk->data > target) pWalk = pWalk->left;
		else pWalk = pWalk->right;
	}
	return NULL;
}
int main() {
	BST b, * root = NULL;
	root = b.Insert(root, 34);
	b.Insert(root, 17);
	b.Insert(root, 25);
	b.Insert(root, 66);
	b.Insert(root, 71);
	b.Insert(root, 68);
	b.Insert(root, 50);
	b.Insert(root, 94);
	b.InOrder(root);
	cout << endl;
	b.DeleteItems(root,25);
	b.InOrder(root);

	return 0;
}