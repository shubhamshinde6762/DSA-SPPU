#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// 1 95 1 45 1 87 1 62 1 10 1 2 1 54 1 91 1 52 0
// 1 50 1 30 1 20 1 35 1 32 1 34 1 33 1 40 1 38 1 45 1 46 1 47 1 43 1 80 1 90 1 100 1 110 0

class Node
{
public:
    bool rbit;
    bool lbit;
    Node *left;
    Node *right;
    int data;

    Node() : rbit(0), lbit(0), left(nullptr), right(nullptr), data(0) {}
    Node(int _data) : rbit(0), lbit(0), left(nullptr), right(nullptr), data(_data) {}
    friend class threadBinaryTree;
};

class threadBinaryTree
{
    Node *head;

public:
    threadBinaryTree() : head(nullptr) {}

    void create();
    void preOrder();
    void inOrder();
    void deleteNode(int key);
    void Insert(int);
};

void threadBinaryTree::create()
{
    head = new Node(-1);
    head->right = head->left = head;

    bool take = 1;

    do
    {
        int data = 0;
        cout << "Enter Data : " << endl;
        cin >> data;
        Insert(data);

        cout << "Are you want to continue ? " << endl;
        cin >> take;
    } while (take);

    cout << "Threaded Binary Tree Created.." << endl;
}

void threadBinaryTree::Insert(int data)
{
    if (!head->lbit)
    {
        head->left = new Node(data);
        head->lbit = 1;
        head->left->left = head->left->right = head;
        return;
    }

    Node *temp = head->left;
    while (temp)
    {
        if (temp->data < data)
        {
            if (temp->rbit)
                temp = temp->right;
            else
            {
                Node *node = new Node(data);
                node->right = temp->right;
                node->rbit = temp->rbit;
                node->left = temp;
                node->lbit = 0;
                temp->right = node;
                temp->rbit = 1;
                return;
            }
        }
        else if (temp->data > data)
        {
            if (temp->lbit)
                temp = temp->left;
            else
            {
                Node *node = new Node(data);
                node->right = temp;
                node->rbit = 0;
                node->left = temp->left;
                node->lbit = temp->lbit;
                temp->left = node;
                temp->lbit = 1;
                return;
            }
        }

        else
        {
            cout << "Data Already Present" << endl;
            return;
        }
    }
}

void threadBinaryTree::preOrder()
{
    Node *node = head->left;
    bool flag = 1;

    while (node != head)
    {
        while (flag)
        {
            cout << node->data << " ";
            if (node->lbit)
                node = node->left;
            else
                break;
        }

        flag = node->rbit;
        node = node->right;
    }
}

void threadBinaryTree::inOrder()
{
    Node *node = head->left;

    while (node->lbit)
        node = node->left;

    while (node != head)
    {
        cout << node->data << " ";
        if (node->rbit)
        {
            node = node->right;
            while (node->lbit)
                node = node->left;
        }
        else
            node = node->right;
    }
}

void threadBinaryTree::deleteNode(int key)
{
    Node *parent = head;
    Node *root = head->left;

    while (root != head && root->data != key)
    {
        if (root->rbit && root->data < key)
            parent = root, root = root->right;
        else if (root->lbit && root->data > key)
            parent = root, root = root->left;
        else
            break;
    }

    if (root == head || root->data != key)
    {
        cout << "Data Not Found" << endl;
        return;
    }

    if (!root->lbit && !root->rbit)
    {
        if (parent->left == root)
            parent->left = root->left, parent->lbit = root->lbit;
        else
            parent->right = root->right, parent->rbit = root->rbit;
        return;
    }
    else if ((!root->lbit && root->rbit) || (root->lbit && !root->rbit))
    {
        Node *child = root->lbit ? root->left : root->right;

        if (parent->left == root)
        {
            parent->left = child, parent->lbit = 1;
            while (child->rbit)
                child = child->right;
            child->right = parent;
        }
        else
        {
            parent->right = child, parent->rbit = 1;
            while (child->lbit)
                child = child->left;
            child->left = parent;
        }
        cout << "first" << endl;
        return;
    }

    Node *temp = root;
    Node *child = root->right;

    while (child->lbit)
        temp = child, child = child->left;

    root->data = child->data;

    if (temp->right == child)
    {
        temp->right = child->right, temp->rbit = child->rbit;
        delete child;

        if (temp->rbit)
        {
            child = temp->right;
            while (child->lbit)
                child = child->left;
            child->left = temp;
        }
    }
    else
    {
        temp->left = child->right, temp->lbit = child->rbit;
        delete child;

        if (temp->lbit)
        {
            child = temp->left;
            while (child->rbit)
                child = child->right;

            child->right = temp;
        }
    }
}

int main()
{
    threadBinaryTree tbt;
    int choice, data;

    do
    {
        cout << "\n\n1. Create TBT\n2. Preorder Traversal\n3. Inorder Traversal\n4. Delete Node\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tbt.create();
            break;
        case 2:
            cout << "Preorder Traversal: ";
            tbt.preOrder();
            cout << endl;
            break;
        case 3:
            cout << "Inorder Traversal: ";
            tbt.inOrder();
            cout << endl;
            break;
        case 4:
            cout << "Enter the data of the node to delete: ";
            cin >> data;
            tbt.deleteNode(data);
            break;
        case 5:
            cout << "Exiting...";
            break;
        default:
            cout << "Invalid choice. Please try again.";
        }
    } while (choice != 5);

    return 0;
}