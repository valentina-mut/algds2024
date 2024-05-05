#include "pch.h"
#include "Header.h"

// Структура узла дерева
struct TreeNode {
    int data;           // Данные
    int height;         // Высота узла
    TreeNode* left;     // Левый потомок
    TreeNode* right;    // Правый потомок
};

// Функция для получения высоты узла
int getHeight(TreeNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Правый поворот
TreeNode* rightRotate(TreeNode* node) {
    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    // Обновление высот
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}

// Левый поворот
TreeNode* leftRotate(TreeNode* node) {
    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    // Обновление высот
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}

// Получение разницы высот между левым и правым поддеревьями
int getBalance(TreeNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Балансировка узла
TreeNode* balance(TreeNode* node) {
    if (node == NULL)
        return node;

    int balanceFactor = getBalance(node);

    // Правый поворот
    if (balanceFactor > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // Левый поворот
    if (balanceFactor < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // Левый поворот, затем правый поворот
    if (balanceFactor > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Правый поворот, затем левый поворот
    if (balanceFactor < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Вставка узла в дерево
TreeNode* insertNode(TreeNode* root, int value) {
    if (root == NULL) {
        TreeNode* newNode = new TreeNode();
        newNode->data = value;
        newNode->height = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    return balance(root);
}

// Удаление узла из дерева
TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL || root->right == NULL) {
            TreeNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            TreeNode* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    return balance(root);
}
