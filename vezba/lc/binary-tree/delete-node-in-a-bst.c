/*
* Problem:
* Given a root node reference of a BST and a key, delete the node with the given key in the BST.
* Return the root node reference (possibly updated) of the BST.
*
* Basically, the deletion can be divided into two stages:
*  - Search for a node to remove.
*  - If the node is found, delete the node.
*/

#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void printTreeInorder(const struct TreeNode *root) {
    if (root == NULL) return;

    printTreeInorder(root->left);
    printf("%d ", root->val);
    printTreeInorder(root->right);
}

struct TreeNode *find(struct TreeNode *p, int key, struct TreeNode **y) {
    if (p == NULL) return NULL;

    struct TreeNode *tmp = p;
    *y = NULL; /* parent of node to be deleted */
    while (tmp != NULL) {
        if (tmp->val == key) return tmp;

        *y = tmp;
        if (key < tmp->val) tmp = tmp->left;
        else tmp = tmp->right;
    }

    return NULL;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    struct TreeNode *y = NULL;
    struct TreeNode *x = find(root, key, &y);
    if (x == NULL) return root;

    struct TreeNode *q = NULL;
    if (x->left == NULL && x->right == NULL) q = NULL;

    if (x->right != NULL && x->left == NULL) q = x->right;
    if (x->right == NULL && x->left != NULL) q = x->left;

    if (x->right != NULL && x->left != NULL) {
        q = x->right;
        struct TreeNode *tmp = q;
        while (tmp->left != NULL) tmp = tmp->left;
        tmp->left = x->left;
    }

    if (y != NULL) {
        if (y->right == x) y->right = q;
        else y->left = q;
    } else
        root = q;

    free(x);
    return root;
}

struct TreeNode *addNode(struct TreeNode *root, const int val) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;

    /* add a new node in empty bst*/
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

    printf("Value to delete?\n");
    int x;
    scanf("%d", &x);
    deleteNode(root, x);

    printf("Tree after deletion:\n");
    printTreeInorder(root);
}