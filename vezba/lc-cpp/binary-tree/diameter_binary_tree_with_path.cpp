#include <iostream>
#include <vector>
#include <algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

struct DiameterResult
{
    int diameter;
    std::vector<TreeNode *> path;
};

void printPath(const std::vector<TreeNode *> &path)
{
    for (size_t i = 0; i < path.size(); ++i)
    {
        std::cout << path[i]->val;
        if (i != path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

std::pair<int, std::vector<TreeNode *>> dfs(TreeNode *node, DiameterResult &result)
{
    if (!node)
        return {0, {}};

    auto [leftDepth, leftPath] = dfs(node->left, result);
    auto [rightDepth, rightPath] = dfs(node->right, result);

    int tmpDiameter = leftDepth + rightDepth;

    if (tmpDiameter > result.diameter)
    {
        result.diameter = tmpDiameter;

        std::vector<TreeNode *> path;
        path.insert(path.end(), leftPath.begin(), leftPath.end());
        path.push_back(node);
        path.insert(path.end(), rightPath.begin(), rightPath.end());

        result.path = std::move(path);
    }

    // deeper path + current node
    if (leftDepth > rightDepth)
    {
        leftPath.push_back(node);
        return {1 + leftDepth, std::move(leftPath)};
    }
    else
    {
        rightPath.push_back(node);
        return {1 + rightDepth, std::move(rightPath)};
    }
}

DiameterResult getDiameterResult(TreeNode *root)
{
    DiameterResult result{0, {}};
    dfs(root, result);
    return result;
}

// Sample tree
TreeNode *createSampleTree()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);
    root->left->right->right = new TreeNode(7);
    return root;
}

void deleteTree(TreeNode *node)
{
    if (!node)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

int main()
{
    TreeNode *root = createSampleTree();
    DiameterResult result = getDiameterResult(root);

    std::cout << "Diameter (number of edges): " << result.diameter << std::endl;
    std::cout << "Path: ";
    printPath(result.path);

    delete (root);

    return 0;
}