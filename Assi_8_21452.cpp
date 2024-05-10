#include <iostream>
using namespace std;

// Define a structure for the nodes of the tree
struct Node
{
    int key;
    Node *left;
    Node *right;
    // Constructor
    Node(int k)
    {
        key = k;
        left = right = nullptr;
    }
};

class obst
{
    float a[20], b[20], wt[20][20], c[20][20];
    int r[20][20], n;

public:
    obst(int x)
    {
        n = x;
    }
    void input_prob();
    void initialize();
    void con_obst();
    void display();
    void print(int l1, int r1);
    // Functions for tree creation and traversal
    Node *construct_optimal_bst(int i, int j);
    void inorder(Node *root);
    void preorder(Node *root);
    void postorder(Node *root);
};

// obst functions

// Function to take input probabilities
void obst::input_prob()
{
    cout << "Enter the probabilities for successful search:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "p[" << i << "]" << "=";
        cin >> a[i];
    }
    cout << "Enter the probabilities for unsuccessful search:" << endl;
    for (int i = 0; i <= n; i++)
    {
        cout << "q[" << i << "]" << "=";
        cin >> b[i];
    }
}

// Function to initialize matrices
void obst::initialize()
{
    for (int i = 0; i < n; i++)
    {
        c[i][i] = 0.0;
        r[i][i] = 0;
        wt[i][i] = b[i];
        wt[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
        c[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
        r[i][i + 1] = i + 1;
    }
    c[n][n] = 0.0;
    r[n][n] = 0;
    wt[n][n] = b[n];
}

// Function to construct optimal BST
void obst::con_obst()
{
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= n - i; j++)
        {
            wt[j][j + i] = b[j + i] + a[j + i] + wt[j][j + i - 1];
            c[j][j + i] = 9999; // Initialize to a large value
            for (int k = j + 1; k <= j + i; k++)
            {
                if (c[j][j + i] > (c[j][k - 1] + c[k][j + i]))
                {
                    c[j][j + i] = c[j][k - 1] + c[k][j + i];
                    r[j][j + i] = k;
                }
            }
            c[j][j + i] += wt[j][j + i];
        }
    }
}

// Function to display matrices
void obst::display()
{
    cout << "Weight Matrix" << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << wt[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Cost Matrix" << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Row Matrix" << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to print optimal BST
void obst::print(int l1, int r1)
{
    if (l1 >= r1)
    {
        return;
    }
    if (r[l1][r[l1][r1] - 1] != 0)
        cout << "\n Left child of " << r[l1][r1] << " :: " << r[l1][r[l1][r1] - 1];
    if (r[r[l1][r1]][r1] != 0)
        cout << "\n Right child of " << r[l1][r1] << " :: " << r[r[l1][r1]][r1];
    print(l1, r[l1][r1] - 1);
    print(r[l1][r1], r1);
}

// Function to construct optimal BST recursively
Node *obst::construct_optimal_bst(int i, int j)
{
    if (i > j)
        return nullptr;
    int root_index = r[i][j];
    Node *root = new Node(root_index);
    root->left = construct_optimal_bst(i, root_index - 1);
    root->right = construct_optimal_bst(root_index, j);
    return root;
}

// Inorder traversal
void obst::inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Preorder traversal
void obst::preorder(Node *root)
{
    if (root == nullptr)
        return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder traversal
void obst::postorder(Node *root)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

int main()
{
    int x;
    cout << "Enter number of nodes:";
    cin >> x;
    obst o(x);
    int c = 1;
    while (c > 0)
    {
        cout << "MENU" << endl;
        cout << "1.Input probabilities" << endl;
        cout << "2.Initialize" << endl;
        cout << "3.Obst" << endl;
        cout << "4.Display" << endl;
        cout << "5.Print" << endl;
        cout << "6.Construct Optimal BST" << endl;
        cout << "7.Inorder Traversal" << endl;
        cout << "8.Preorder Traversal" << endl;
        cout << "9.Postorder Traversal" << endl;
        cout << "0.Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> c;
        if (c == 1)
        {
            o.input_prob();
        }
        else if (c == 2)
        {
            o.initialize();
        }
        else if (c == 3)
        {
            o.con_obst();
        }
        else if (c == 4)
        {
            o.display();
        }
        else if (c == 5)
        {
            o.print(0, x);
        }
        else if (c == 6)
        {
            Node *root = o.construct_optimal_bst(0, x);
            cout << "Optimal BST Constructed!" << endl;
        }
        else if (c == 7)
        {
            Node *root = o.construct_optimal_bst(0, x);
            cout << "Inorder Traversal: ";
            o.inorder(root);
            cout << endl;
        }
        else if (c == 8)
        {
            Node *root = o.construct_optimal_bst(0, x);
            cout << "Preorder Traversal: ";
            o.preorder(root);
            cout << endl;
        }
        else if (c == 9)
        {
            Node *root = o.construct_optimal_bst(0, x);
            cout << "Postorder Traversal: ";
            o.postorder(root);
            cout << endl;
        }
    }
    return 0;
}
