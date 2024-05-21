
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
struct Node {
	struct Node* left;
	struct Node* right;
	int data;
	int height;
};
struct Trunk
{
	Trunk* prev;
	std::string str;

	Trunk(Trunk* prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};
typedef struct Node Node;

Node* Add(Node* root, int data);
Node* Delete(Node* root, int deldata);
void printTree(Node* root, Trunk* prev, bool isLeft);
