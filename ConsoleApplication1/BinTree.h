#pragma once
#include<iostream>
using namespace std;

struct node
{
	int data;
	node* left = NULL;
	node* right = NULL;
};

class BinTree
{
private:
	node* root;
public:
	BinTree(node* = NULL);

	void AddRight(int);
	void AddLeft(int);

	void PreOrder(node* root) {
		if (root == NULL) {
			return;
		}
		cout << root->data << "\t";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	void InOrder(node* root) {
		if (root == NULL) {
			return;
		}

		PreOrder(root->left);
		cout << root->data << "\t";
		PreOrder(root->right);
	}
};

