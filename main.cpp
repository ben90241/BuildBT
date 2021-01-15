#include <iostream>
#include <vector>
#include <map>
#include <queue>

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
    TreeNode *buildBinaryTree(const std::vector<int>& preorder, const std::vector<int>& inorder)
    {
        for (int i = 0; i < inorder.size(); i++)
        {
            myMap[inorder[i]] = i;
        }

        return build(preorder, inorder, 0, inorder.size() - 1);
    }

    TreeNode *build(const std::vector<int>& preorder, const std::vector<int>& inorder, const int &start, const int &end)
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

    TreeNode *buildBinaryTree(const std::vector<int>& postorder, const std::vector<int>& inorder)
    {
        for (int i = 0; i < inorder.size(); i++)
        {
            myMap[inorder[i]] = i;
        }
        pid = postorder.size() - 1;
        return build(postorder, inorder, 0, inorder.size() - 1);
    }

    TreeNode *build(const std::vector<int>& postorder, const std::vector<int>& inorder, const int &start, const int &end)
    {
        if (start > end)
            return nullptr;

        TreeNode *node = new TreeNode(postorder[pid--]);

        int iid = myMap[node->val];

        node->right = build(postorder, inorder, iid + 1, end);
        node->left = build(postorder, inorder, start, iid - 1);

        return node;
    }
};

class Solution3
{
public:
    std::map<int, int> myMap;
    int preid=0;
    TreeNode *buildBinaryTree(const std::vector<int> &pre, const std::vector<int> &post)
    {
        for(int i=0;i<post.size();i++)
        {
            myMap[post[i]]=i;
        }

        return build(pre, 0, pre.size()-1);
    }

    TreeNode *build(const std::vector<int> &pre, const int &start, const int &end)
    {
        if(start>end)
            return nullptr;

        TreeNode *node = new TreeNode(pre[preid++]);
        if(start==end)
            return node;
        int postid = myMap[pre[preid]];

        node->left = build(pre, start, postid);
        node->right = build(pre, postid+1, end-1);
        return node;
    }
};

class Solution4
{
public:
    TreeNode *buildBinaryTree(const std::vector<int>& input)
    {
        TreeNode *root = build(input, root, 0, input.size());
        return root;
    }

    TreeNode *build(const std::vector<int>& input, TreeNode *root, const int &i, const int &n)
    {
        if(i<n)
        {
            TreeNode* node = new TreeNode(input[i]);
            root = node;

            root->left = build(input, root->left, 2*i+1, n);
            root->right = build(input, root->right, 2*i+2, n);
        }
        return root;
    }
};

// breadth first travesal
void bft_Print(TreeNode *root)
{
    if(root==nullptr)
        return;

    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        std::cout<<node->val<<"\t";
        if(node->left!=nullptr)
            q.push(node->left);
        if(node->right)
            q.push(node->right);
    }
    std::cout<<"\n";
}

//inorder print
void Print(const TreeNode *root)
{
    if (root == NULL)
        return;

    Print(root->left);
    std::cout << root->val << "\t";
    Print(root->right);
}

int main(void)
{
    //build binary tree from preorder and inorder
    std::cout << "\n--------- Build BT from Pre and In ---------\n";
    Solution sol;
    std::vector<int> preorder = {3, 9, 20, 15, 7};
    std::vector<int> inorder = {9, 3, 15, 20, 7};
    TreeNode *root = sol.buildBinaryTree(preorder, inorder);
    Print(root);

    std::cout << "\n--------- Build BT from Post and In ---------\n";
    //build binary tree from postorder and inorder
    Solution2 sol2;
    std::vector<int> in = {4, 8, 2, 5, 1, 6, 3, 7};
    std::vector<int> post = {8, 4, 5, 2, 6, 7, 3, 1};
    TreeNode *root2 = sol2.buildBinaryTree(post, in);
    Print(root2);

    std::cout << "\n--------- Build BT from Pre and Post ---------\n";
    Solution3 sol3;
    std::vector<int> pre = {1,2,4,5,3,6,7};
    post = {4,5,2,6,7,3,1};
    bft_Print(sol3.buildBinaryTree(pre, post));

    std::cout << "\n--------- Build BT from Given Array ---------\n";
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 6, 6, 6, 6};
    Solution4 sol4;
    TreeNode *root4 = sol4.buildBinaryTree(input);
    bft_Print(root4);

    return 0;
}