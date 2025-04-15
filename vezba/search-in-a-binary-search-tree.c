/*
 * Problem:
 * You are given the root of a binary search tree (BST) and an integer val.
 * Find the node in the BST that the node's value equals val and return the subtree rooted with that node.
 * If such a node does not exist, return null.
 */

#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void printTree(const struct TreeNode *root) {
    if (root == NULL) return;

    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

void print(const struct TreeNode *root) {
    if (root == NULL) {
        printf("[]");
        return;
    }

    printf("[ ");
    printTree(root);
    printf("]");
}

struct TreeNode *searchBST(struct TreeNode *root, const int val) {
    if (root == NULL) return NULL;

    struct TreeNode *p = root;
    while (p != NULL) {
        if (p->val == val) return p;
        if (val < p->val) p = p->left;
        else p = p->right;
    }
    return NULL;
}

struct TreeNode *addNode(struct TreeNode *root, const int val) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;

    /* add new node in empty bst*/
    if (root == NULL) root = newNode;
    else {
        struct TreeNode *p = root;
        struct TreeNode *q = NULL;
        while (p != NULL) {
            q = p;
            if (val < p->val) p = p->left;
            else p = p->right;
        }

        if (val < q->val) q->left = newNode;
        else q->right = newNode;
    }
    return root;
}

int main() {
    struct TreeNode *root = NULL;
    printf("Enter how many numbers: ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = addNode(root, val);
    }

    printf("Value to search for?\n");
    int x;
    scanf("%d", &x);
    struct TreeNode *searchNode = searchBST(root, x);
    printf("Subtree rooted in searched node:\n");
    print(searchNode);
}


