#include <iostream>
#include <vector>
#include <map>

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int v)
        : val(v)
    {
        left = nullptr;
        right = nullptr;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r)
        : val(v), left(l), right(r)
    {
    }
};

class Solution
{
public:
    std::map<int, int> myMap;
    int pid = 0;
    TreeNode *buildBinaryTree(std::vector<int> preorder, std::vector<int> inorder)
    {
        for (int i = 0; i < inorder.size(); i++)
        {
            myMap[inorder[i]] = i;
        }

        return build(preorder, inorder, 0, inorder.size() - 1);
    }

    TreeNode *build(std::vector<int> preorder, std::vector<int> inorder, int start, int end)
    {
        if (start > end)
            return nullptr;

        TreeNode *node = new TreeNode(preorder[pid++]);

        int iid = myMap[node->val];

        node->left = build(preorder, inorder, start, iid - 1);
        node->right = build(preorder, inorder, iid + 1, end);

        return node;
    }
};

class Solution2
{
public:
    std::map<int, int> myMap;
    int pid;

    TreeNode *buildBinaryTree(std::vector<int> postorder, std::vector<int> inorder)
    {
        for(int i=0;i<inorder.size();i++)
        {
            myMap[inorder[i]]=i;
        }
        pid=postorder.size()-1;
        return build(postorder, inorder, 0, inorder.size()-1);
    }

    TreeNode *build(std::vector<int> postorder, std::vector<int> inorder, int start, int end)
    {
        if(start>end)
            return nullptr;

        TreeNode *node = new TreeNode(postorder[pid--]);

        int iid = myMap[node->val];

        node->right = build(postorder, inorder, iid+1, end);
        node->left = build(postorder, inorder, start, iid-1);
        
        return node;
    }
};

//inorder print
void Print(const TreeNode *root)
{
    if(root==NULL)
        return;

    Print(root->left);
    std::cout<<root->val<<"\t";
    Print(root->right);
}

int main(void)
{
    //build binary tree from preorder and inorder
    Solution sol;
    std::vector<int> preorder = {3,9,20,15,7};
    std::vector<int> inorder = {9,3,15,20,7};
    TreeNode *root=sol.buildBinaryTree(preorder, inorder);
    Print(root);

    std::cout<<"\n----------------------------------------------\n";
    //build binary tree from postorder and inorder
    Solution2 sol2;
    std::vector<int> in = {4, 8, 2, 5, 1, 6, 3, 7};
    std::vector<int> post = {8, 4, 5, 2, 6, 7, 3, 1};
    TreeNode *root2 = sol2.buildBinaryTree(post, in);
    Print(root2);

    return 0;
}