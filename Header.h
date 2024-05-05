#pragma once

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	struct TreeNode* left;
	struct TreeNode* right;
	int data;
	int height;
};

typedef struct TreeNode Node;

Node* insert(Node* root, int val);
Node* erase(Node* root, int val);
