/*
 * Problem (534)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode * createTreeNode(const int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;

    return node;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs_diameter_helper(struct TreeNode* root, int* max_diameter) {
    if (!root) return 0;

    int left_h= dfs_diameter_helper(root->left, max_diameter);
    int right_h = dfs_diameter_helper(root->right, max_diameter);

    // update diameter if the current diameter is bigger (we found a longer path)
    *max_diameter = max(*max_diameter, left_h + right_h);

    // return height of the current tree
    return 1 + max(left_h, right_h);
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int diameter = 0;
    dfs_diameter_helper(root, &diameter);
    return diameter;
}

void deleteTree(struct TreeNode* node)
{
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);

    free(node);
}

void delete(struct TreeNode** node) {
    deleteTree(*node);
    *node = NULL;
}

int main() {
    struct TreeNode* r = createTreeNode(1);
    r->left = createTreeNode(2);
    r->right = createTreeNode(3);
    r->left->left = createTreeNode(4);
    r->left->right = createTreeNode(5);

    printf("diameter of a given tree %d\n", diameterOfBinaryTree(r));

    delete(&r);

    return 0;
}