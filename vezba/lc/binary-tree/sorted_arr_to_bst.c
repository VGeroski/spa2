/**
 * Problem (108):
 * Given an integer array nums where the elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
*  A height-balanced binary tree is a binary tree in which
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

struct TreeNode* createNode(const int val) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;

    return node;
}

struct TreeNode* helperArrToBST(int *arr, int left, int right) {
    if (left > right) return NULL;

    const int mid = (left + right) / 2;
    struct TreeNode* root = createNode(arr[mid]);

    root->left = helperArrToBST(arr, left, mid - 1);
    root->right = helperArrToBST(arr, mid + 1, right);

    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return helperArrToBST(nums, 0, numsSize - 1);
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

void print(struct TreeNode* p) {
    if (p) {
        print(p->left);
        printf("%5d", p->val);
        print(p->right);
    }
}

int main() {
    int nums[] = {-10, -3, 0, 5, 9};
    struct TreeNode* root = sortedArrayToBST(nums, 5);

    print(root);

    delete(&root);

    return 0;
}