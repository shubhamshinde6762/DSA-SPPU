#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// 1 95 1 45 1 87 1 62 1 10 1 2 1 54 1 91 1 52 0

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
    head = new Node();
    head->rbit = 1;
    head->left = head;
    head->right = head;
    while (1)
    {
        cout << "Enter the Element to Insert : " << endl;
        int d;
        cin >> d;
        Insert(d);
        cout << "Are you want to continue? (1 / 0)" << endl;
        bool b;
        cin >> b;
        if (!b)
            break;
    }

    inOrder();

    cout << endl;

    cout << "Threaded BST Created Successfully...." << endl;
}

void threadBinaryTree::Insert(int d)
{
    if (!head->lbit)
    {
        Node *temp = new Node(d);

        temp->right = head->right;
        temp->left = head->left;

        head->left = temp;
        head->lbit = true;
        return;
    }

    Node *temp = head->left;

    while (1)
    {
        if (temp->data < d && !temp->rbit)
        {
            Node *temp2 = new Node(d);

            temp2->right = temp->right;
            temp2->rbit = 0;
            temp2->left = temp;
            temp2->lbit = 0;

            temp->rbit = 1;
            temp->right = temp2;
            return;
        }
        else if (temp->data > d && !temp->lbit)
        {
            Node *temp2 = new Node(d);

            temp2->left = temp->left;
            temp2->rbit = 0;
            temp2->right = temp;
            temp2->lbit = 0;

            temp->lbit = 1;
            temp->left = temp2;
            return;
        }

        if (temp->data == d)
        {
            cout << "Duplicate Data" << endl;
            return;
        }

        if (temp->rbit && temp->data < d)
            temp = temp->right;
        else if (temp->lbit)
            temp = temp->left;
    }
}

void threadBinaryTree::preOrder()
{
    if (!head)
    {
        cout << "Tree is Not Created!" << endl;
        return;
    }

    bool flag = 1;
    Node *temp = head->left;

    while (temp != head)
    {
        while (flag)
        {
            cout << temp->data << " ";
            if (temp->lbit)
                temp = temp->left;
            else
                break;
        }

        flag = temp->rbit;
        temp = temp->right;
    }
}

void threadBinaryTree::inOrder()
{
    if (!head->lbit)
    {
        cout << "Tree is not Created!" << endl;
        return;
    }

    Node *temp = head->left;

    while (temp->lbit)
        temp = temp->left;

    while (temp != head)
    {
        cout << temp->data << " ";

        if (!temp->rbit)
            temp = temp->right;
        else
        {
            temp = temp->right;
            while (temp->lbit)
                temp = temp->left;
        }
    }
}

void threadBinaryTree::deleteNode(int key)
{
    if (!head)
    {
        cout << "Tree is empty. Cannot delete." << endl;
        return;
    }

    Node *temp = head->left;
    Node *parent = head;

    while (temp != head && temp->data != key)
    {
        if (temp->lbit && key < temp->data)
        {
            parent = temp;
            temp = temp->left;
        }
        else if (temp->rbit)
        {
            parent = temp;
            temp = temp->right;
        }
        else
            break;
    }

    if (temp == head || temp->data != key)
    {
        cout << "Key not found in the tree." << endl;
        return;
    }

    if (!temp->lbit && !temp->rbit)
    {
        if (temp == parent->left)
        {
            parent->left = temp->left;
            parent->lbit = temp->lbit;

            temp->left = nullptr;
            temp->right = nullptr;
        }
        else
        {
            parent->right = temp->right;
            parent->rbit = temp->rbit;

            temp->left = nullptr;
            temp->right = nullptr;
        }
        delete temp;
    }
    else if ((temp->lbit && !temp->rbit) || (!temp->lbit && temp->rbit))
    {
        //     cout<<temp->lbit<<temp->rbit<<endl;
        Node *child = (temp->lbit) ? temp->left : temp->right;
        bool childBit = (temp->lbit) ? temp->lbit : temp->rbit;
        if (temp == parent->left)
        {
            parent->left = child;
            parent->lbit = childBit;

            while (child->rbit)
                child = child->right;

            child->right = parent;
        }
        else
        {
            parent->right = child;
            parent->rbit = childBit;

            while (child->lbit)
                child = child->left;

            child->left = parent;
        }
        delete temp;
    }
    else
    {
        Node *successor = temp->right;
        parent = temp;
        while (successor->lbit)
        {
            parent = successor;
            successor = successor->left;
        }
        temp->data = successor->data;
        if (successor == parent->left)
        {
            parent->left = successor->right;
            parent->lbit = 0;
        }
        else
        {
            parent->right = successor->right;
            parent->rbit = 0;
        }
        delete successor;
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
