/*
* Problem:
* Given the root of a binary tree, return its maximum depth.
* A binary tree's maximum depth is the number of nodes
* along the longest path from the root node down to the farthest leaf node.
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int max(const int a, const int b) {
    return a > b ? a : b;
}

int dfs(const struct TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;

    const int left = dfs(root->left);
    const int right = dfs(root->right);
    return 1 + max(left, right);
}

int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    return dfs(root);
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
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 3;
    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 9;
    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 20;
    root->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->left->val = 15;
    root->right->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right->val = 7;
    root->right->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right->left->val = 2;

    printf("%d\n", maxDepth(root));

    delete(&root);
}