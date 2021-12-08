#include "printTree.h"

BtNode* root = NULL;
void addNode(int element) {
    if (root == NULL) {
        root = (BtNode*)malloc(sizeof(BtNode));
        if (root != NULL)
        {
            root->Element = element;
            root->parent = NULL;
            root->left = NULL;
            root->right = NULL;
        }
        return;
    }
    BtNode* node = root;
    BtNode* parent = root;
    while (node != NULL) {
        parent = node;
        if (node->Element < element) {
            node = node->right;
        }
        else if (node->Element > element) {
            node = node->left;
        }
        else {
            node->Element = element;
            return;
        }
    }
    BtNode* newNode = (BtNode*)malloc(sizeof(BtNode));
    if (newNode != NULL) {
        newNode->parent = parent;
        newNode->Element = element;
        newNode->left = newNode->right = NULL;
        if (element < parent->Element) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }
}

int main(void) {
<<<<<<< HEAD
    srand((unsigned)time(NULL));
    for (int i = 0; i < 50; i++) {
        addNode(rand() % 1000);
        PrinterInit(root);
    }
    printf("添加完成\n");
    return 0;
}
