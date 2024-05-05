#include "pch.h"
#include "Header.h"

struct Array {
	int* data;
	int size;
};

typedef struct Array Array;

void inorderTraversal(Node* root, Array* array) {
	if (root == NULL)
		return;

	inorderTraversal(root->left, array);
	array->data[array->size++] = root->data;
	inorderTraversal(root->right, array);
}

int isSorted(int n, Node* root) {
	Array arr;
	arr.data = (int*)malloc(sizeof(int) * n);
	arr.size = 0;

	inorderTraversal(root, &arr);

	for (int i = 0; i < n; ++i) {
		if (arr.data[i] != i) {
			free(arr.data);
			return 0;
		}
	}
	free(arr.data);
	return 1;
}

TEST(InsertTest, Nulltest) {
	Node* root = NULL;
	root = insert(root, 3);
	EXPECT_EQ(root->data, 3);
	EXPECT_EQ((void*)root->left, (void*)NULL);
	EXPECT_EQ((void*)root->right, (void*)NULL);
	EXPECT_TRUE(true);
}

TEST(InsertTest, sort_test_1000) {
	Node* root = NULL;

	for (int i = 0; i < 1000; ++i) {
		root = insert(root, i);
	}
	EXPECT_EQ(isSorted(1000, root), 1);

	EXPECT_TRUE(true);
}

TEST(InsertTest, unsort_test_1000) {
	Node* root = NULL;
	for (int i = 999; i >= 0; --i) {
		root = insert(root, i);
	}
	EXPECT_EQ(isSorted(1000, root), 1);

	EXPECT_TRUE(true);
}

#if 1

TEST(EraseTest, nulltest) {
	Node* root = NULL;
	root = erase(root, 2);
	EXPECT_EQ(root, (Node*)NULL);

	EXPECT_TRUE(true);
}

TEST(EraseTest, one_element_test) {
	Node* root = NULL;
	root = insert(root, 1);
	root = erase(root, 1);
	EXPECT_EQ(root, (Node*)NULL);

	EXPECT_TRUE(true);
}
#endif

TEST(EraseTest, three_element_test) {
	Node* root = NULL;
	root = insert(root, 1);
	root = insert(root, 0);
	root = insert(root, 2);
	root = erase(root, 1);
	EXPECT_EQ(root->data, 2);

	EXPECT_TRUE(true);
}

TEST(EraseTest, missing_element_test) {
	Node* root = NULL;
	for (int i = 999; i >= 0; --i) {
		root = insert(root, i);
	}
	root = erase(root, -4);
	root = erase(root, -5);
	root = erase(root, 1001);
	EXPECT_EQ(isSorted(1000, root), 1);

	EXPECT_TRUE(true);
}
