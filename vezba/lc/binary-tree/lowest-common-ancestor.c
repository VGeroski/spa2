/*
* Problem:
* Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
* According to the definition of LCA on Wikipedia:
* “The lowest common ancestor is defined between two nodes p and q as the lowest node in T
* that has both p and q as descendants (where we allow a node to be a descendant of itself).”
*/

#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* dfs(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL) return NULL;
    if (root == p || root == q) return root;
    if (!root->left && !root->right) return NULL;

    struct TreeNode *left = dfs(root->left, p, q);
    struct TreeNode *right = dfs(root->right, p, q);

    if (!left) return right;
    if (!right) return left;

    return root;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == p || root == q) return root;

    return dfs(root, p, q);
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

    struct TreeNode *p = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    p->val = 6;
    struct TreeNode *q = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    q->val = 4;

    root->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->val = 5;
    root->left->left = p;
    root->left->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->right->val = 2;
    root->left->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->left->right->left->val = 7;
    root->left->right->right = q;

    root->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->val = 1;
    root->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->left->val = 15;
    root->right->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right->val = 10;
    root->right->right->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->right->right->left->val = 8;

    printf("%d\n", lowestCommonAncestor(root, p, q)->val);
    printf("%d\n", lowestCommonAncestor(root, root->left, root->right)->val);

    delete(&root);
}
