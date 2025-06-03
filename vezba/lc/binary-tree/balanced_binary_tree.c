/**
 * Problem (110):
 * Given a binary tree, determine if it is height-balanced.
 *
 * A height-balanced binary tree is a binary tree in which
 * the depth of the two subtrees of every node never differs by more than one.
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

struct BalanceStatus {
    int isBalanced;
    int height;
};

int max(int a, int b) {
    return a > b ? a : b;
}

struct BalanceStatus checkBalanced(struct TreeNode* root) {
    if (!root) return (struct BalanceStatus){1, 0};

    struct BalanceStatus left = checkBalanced(root->left);
    if (!left.isBalanced) return left;

    struct BalanceStatus right = checkBalanced(root->right);
    if (!right.isBalanced) return right;

    int balanced = abs(left.height - right.height) <= 1;
    int height = 1 + max(left.height, right.height);

    return (struct BalanceStatus){balanced, height};
}

int isBalanced(struct TreeNode* root) {
    return checkBalanced(root).isBalanced;
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
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
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

    printf("%d\n", isBalanced(root));

    delete(&root);

    return 0;
}