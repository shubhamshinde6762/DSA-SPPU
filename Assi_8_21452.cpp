#include <iostream>
// #include <iomanip>
// #include <ios>
using namespace std;

class Node
{
    int key;
    Node *left;
    Node *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}

public:
    friend class OptimalBST;
};

class OptimalBST
{
    float p[20], q[20], cost[20][20], weight[20][20];
    int parent[20][20], n;
    Node *root;

public:
    OptimalBST(int x) : n(x)
    {
        // cout << fixed << setprecision(2) << endl;
        for (int i = 0; i < n; i++)
        {
            p[i] = q[i] = 0.0;
            for (int j = 0; j < n; j++)
            {
                cost[i][j] = weight[i][j] = 0.0;
                parent[i][j] = 0;
            }
        }
    }
    void input();
    void build();
    void displayMatrix();
    Node *buildTree(int i, int j);
    void inorder(Node *root);
    void preorder(Node *root);
    void postorder(Node *root);
    void treePrint();
};

void OptimalBST::treePrint()
{
    cout << "Tree is: ";
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    postorder(root);
    cout << endl;
    cout << endl;
}

void OptimalBST::input()
{
    cout << "Enter the P for successful search:" << endl;
    p[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cout << "p[" << i << "]" << "=";
        cin >> p[i];
    }
    cout << "Enter the P for unsuccessful search:" << endl;
    for (int i = 0; i <= n; i++)
    {
        cout << "q[" << i << "]" << "=";
        cin >> q[i];
    }

    build();
}

void OptimalBST::build()
{
    for (int i = 0; i < n; i++)
    {
        cost[i][i] = 0.0;
        parent[i][i] = 0;
        weight[i][i] = q[i];

        weight[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        cost[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        parent[i][i + 1] = i + 1;
    }

    cost[n][n] = 0.0;
    parent[n][n] = 0;
    weight[n][n] = q[n];

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= n - i; j++)
        {
            weight[j][j + i] = q[j + i] + p[j + i] + weight[j][j + i - 1];
            cost[j][j + i] = 999;
            for (int k = j + 1; k <= j + i; k++)
            {
                if (cost[j][j + i] > (cost[j][k - 1] + cost[k][j + i]))
                {
                    cost[j][j + i] = cost[j][k - 1] + cost[k][j + i];
                    parent[j][j + i] = k;
                }
            }
            cost[j][j + i] += weight[j][j + i];
        }
    }

    root = buildTree(0, n);
}

void OptimalBST::displayMatrix()
{
    cout << "Weight Matrix" << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            cout << weight[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    cout << "Cost Matrix" << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            cout << cost[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    cout << "Root Index Matrix" << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            cout << parent[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

Node *OptimalBST::buildTree(int i, int j)
{
    if (i >= j)
        return nullptr;

    cout << "Building tree from " << i << " to " << j << endl;

    int index = parent[i][j];
    cout << "Index: " << index << endl;
    Node *root = new Node(index > 0 ? index : j);
    if (parent[i][index - 1] != 0)
        root->left = buildTree(i, index - 1);
    if (parent[index][j] != 0)
        root->right = buildTree(index, j);
    return root;
}

void OptimalBST::inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void OptimalBST::preorder(Node *root)
{
    if (root == nullptr)
        return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void OptimalBST::postorder(Node *root)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

int main()
{
    int numberOfNodes;
    cout << "Enter number of nodes:";
    cin >> numberOfNodes;
    OptimalBST obst(numberOfNodes);
    int choice = 1;
    while (choice > 0)
    {
        cout << "MENU" << endl;
        cout << "1. Input probabilities" << endl;
        cout << "2. displayMatrix" << endl;
        cout << "3. Tree Print" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        if (choice == 1)
            obst.input();
        else if (choice == 2)
            obst.displayMatrix();
        else if (choice == 3)
            obst.treePrint();
    }
    return 0;
}
