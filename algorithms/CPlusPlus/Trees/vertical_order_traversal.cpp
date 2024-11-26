#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;
class node
{
public:
    int data;
    node *left;
    node *right;
    node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
node *buildtree(node *&root)
{
    cout << "enter the data: " << endl;
    int data;
    cin >> data;

    if (data == -1)
    {
        return NULL;
    }
    root = new node(data);
    cout << "enter for left of " << data << endl;
    root->left = buildtree(root->left);
    cout << "enter for right of " << data << endl;
    root->right = buildtree(root->right);
    return root;
}
/**
 * This function performs a vertical order traversal of a binary tree.
 * The approach is to use a map of maps of vectors, where the outer map
 * uses the horizontal distance (hd) from the root as its key, the inner
 * map uses the level (lvl) as its key, and the vector contains the node
 * values at that hd and lvl.
 * The result is stored in the vector ans.
 */
void vertical(node *root, vector<int> &ans)
{
    map<int, map<int, vector<int>>> m; // outer map is hd, inner map is lvl, vector is node values
    queue<pair<node *, pair<int, int>>> q; // queue of nodes and their hd and lvl
    if (root == NULL)
    {
        return;
    }

    q.push({root, {0, 0}}); // push root node with hd 0 and lvl 0

    while (!q.empty())
    {
        pair<node *, pair<int, int>> temp = q.front();
        q.pop();
        node *frontnode = temp.first; // current node
        int hd = temp.second.first; // current hd
        int lvl = temp.second.second; // current lvl

        m[hd][lvl].push_back(frontnode->data); // store node value in map

        if (frontnode->left)
        {
            q.push({frontnode->left, {hd - 1, lvl + 1}}); // push left child with hd-1 and lvl+1
        }
        if (frontnode->right)
        {
            q.push({frontnode->right, {hd + 1, lvl + 1}}); // push right child with hd+1 and lvl+1
        }
    }

    for (auto i : m)
    {
        for (auto j : i.second)
        {
            for (auto k : j.second)
            {
                ans.push_back(k); // store node values in ans
            }
        }
    }
}
int main()
{
    node *root = NULL;
    root = buildtree(root);

    vector<int> ans;
    vertical(root, ans);
    for (auto i : ans)
    {
        cout << i << " ";
    }
} // 1 2 4 -1 -1 5 -1 -1 3 6 -1 8 -1 -1 7 -1 9 -1 -1