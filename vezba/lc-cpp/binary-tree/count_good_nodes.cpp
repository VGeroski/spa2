/**
 * Problem (1448)
 * Given a binary tree root, a node X in the tree is named good
 * if in the path from root to X there are no nodes with a value greater than X.
 * Return the number of good nodes in the binary tree.
 */

#include <iostream>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int dfs(TreeNode *node, int maxValue)
{
    // No good nodes in an empty tree
    if (!node)
        return 0;

    int goodCount = node->val >= maxValue ? 1 : 0;

    maxValue = std::max(maxValue, node->val);

    goodCount += dfs(node->left, maxValue);
    goodCount += dfs(node->right, maxValue);

    return goodCount;
}

int goodNodes(TreeNode *root)
{
    return dfs(root, root->val);
}

TreeNode *createSampleTree()
{
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);

    root->left->left = new TreeNode(3);

    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(5);

    return root;
}

void deleteTree(TreeNode *node)
{
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main()
{
    TreeNode *root = createSampleTree();
    std::cout << "Numbers of good nodes: " << goodNodes(root) << std::endl;
    deleteTree(root);

    return 0;
}