#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
using namespace std;

Node* NewNode(int data) {
	Node* root;
	root = (Node*)malloc(sizeof(Node));
	root->right = NULL;
	root->left = NULL;
	root->data = data;
	root->height = 0;
	return root;
}
void showTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	cout << p->str;
}

void printTree(Node* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr) {
		return;
	}
	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);
	printTree(root->right, trunk, true);
	if (!prev) {
		trunk->str = "---";
	}
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else {
		trunk->str = "'---";
		prev->str = prev_str;
	}
	showTrunks(trunk);
	printf(" %d, %d\n", root->data, root->height);
	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}

int balance_factor(Node* root)
{
	int lh, rh;
	if (root == NULL)
		return 0;
	if (root->left == NULL)
		lh = 0;
	else
		lh = 1 + root->left->height;
	if (root->right == NULL)
		rh = 0;
	else
		rh = 1 + root->right->height;
	return lh - rh;
}

Node* find(int x, Node* root) {
	if (root == NULL)
		return NULL;
	if (x < root->data)
		return find(x, root->left);
	else if (x > root->data)
		return find(x, root->right);
	else return root;
}

int height(Node* root) {
	if (root != NULL) {
		return root->height;
	}
	else return -1;
}

int findheight(Node* root) {
	int left, right;
	if (root == NULL) {
		return -1;
	}
	if (root->left == NULL) left = 0;
	else left = 1 + height(root->left);
	if (root->right == NULL) right = 0;
	else right = 1 + height(root->right);
	if (left > right) return left;
	return right;
}

Node* leftrotate(Node* root) {
	Node* root1 = NULL;
	root1 = root->left;
	root->left = root1->right;
	root1->right = root;
	if (height(root->left) >= height(root->right)) root->height = height(root->left) + 1;
	else root->height = height(root->right) + 1;
	if (height(root1->left) >= height(root)) root1->height = height(root1->left) + 1;
	else root1->height = height(root) + 1;
	return root1;
}

Node* rightrotate(Node* root) {
	Node* root1 = NULL;
	root1 = root->right;
	root->right = root1->left;
	root1->left = root;
	if (height(root->left) >= height(root->right)) root->height = height(root->left) + 1;
	else root->height = height(root->right) + 1;
	if (height(root1->right) >= height(root)) root1->height = height(root1->right) + 1;
	else root1->height = height(root) + 1;
	return root1;
}

Node* doubleleftrotate(Node* root) {
	root->left = rightrotate(root->left);
	return leftrotate(root);
}

Node* doublerightrotate(Node* root) {
	root->right = leftrotate(root->right);
	return rightrotate(root);
}

Node* Add(Node* root, int data) {
	if (root == NULL) {
		root = NewNode(data);
	}
	else if (data < root->data) {
		root->left = Add(root->left, data);
		if (height(root->left) - height(root->right) == 2) {
			if (data < root->left->data) root = leftrotate(root);
			else root = doubleleftrotate(root);
		}
	}
	else if (data > root->data) {
		root->right = Add(root->right, data);
		if (height(root->right) - height(root->left) == 2) {
			if (data > root->right->data) root = rightrotate(root);
			else root = doublerightrotate(root);
		}
	}
	if (height(root->left) >= height(root->right)) root->height = height(root->left) + 1;
	else root->height = height(root->right) + 1;
	return root;
}

Node* Delete(Node* root, int deldata) {
	Node* root1;
	if (root == NULL) {
		return root;
	}
	if (deldata > root->data) {
		root->right = Delete(root->right, deldata);
		if (balance_factor(root) == 2) {
			if (balance_factor(root->left) >= 0) root = leftrotate(root); //pomenyal
			else {
				root = doubleleftrotate(root); //pomen
			}
		}

	}
	else if (deldata < root->data) {
		root->left = Delete(root->left, deldata);
		if (balance_factor(root) == -2) {
			if (balance_factor(root->right) <= 0) root = rightrotate(root); //pomenyal
			else root = doublerightrotate(root); //pomen
		}
	}
	else {
		if (root->right != NULL) {
			root1 = root->right;
			while (root1->left != NULL) root1 = root1->left;
			root->data = root1->data;
			root->right = Delete(root->right, root1->data);
			if (balance_factor(root) == 2) {
				if (balance_factor(root->left) >= 0) root = leftrotate(root); //pomenyal
				else root = doubleleftrotate(root); //pomen

			}
		}
		else return (root->left);
	}
	root->height = findheight(root);
	return(root);
}