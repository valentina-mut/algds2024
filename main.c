
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int main() {
    Node* First = NULL;
    int key;
    printf("Enter new key: ");
    scanf_s("%d", &key);
    First = Add(First, key);
    printf("Enter new key: ");
    scanf_s("%d", &key);
    while (key != 0) {
        First = Add(First, key);
        printf("Enter new key: ");
        scanf_s("%d", &key);
    }
    printTree(First, nullptr, false);
    printf("Enter delete key: ");
    scanf_s("%d", &key);
    First = Delete(First, key);
    printTree(First, nullptr, false);
    printf("Enter delete key: ");
    scanf_s("%d", &key);
    First = Delete(First, key);
    printTree(First, nullptr, false);
    printf("Enter delete key: ");
    scanf_s("%d", &key);
    First = Delete(First, key);
    printTree(First, nullptr, false);
}
