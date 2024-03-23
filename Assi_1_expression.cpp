//============================================================================
// Name        : Tree.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// + - 1 * 2 3 / 4 5

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    char data;
    Node *left;
    Node *right;

    Node(int _data = 0) : data(_data), left(nullptr), right(nullptr) {}
};

class TreeNode
{
    Node *root;
    Node *createTree()
    {
        char _data;
        bool l, r;

        cout << "Enter Data: ";
        cin >> _data;
        Node *element = new Node(_data);

        if (_data - '0' >=0 && _data - '0' < 10)
        	return element;


        element->left = createTree();
        element->right = createTree();

        return element;
    }

public:
    TreeNode() : root(nullptr) {}

    void initialize()
    {
        // createTreeNonRec();
        root = createTree();
        return;
    }



    void postOrderNonRec()
    {
        if (!root)
            return;

        Node *temp = root;
        stack<Node *> st;

        do
        {
            while (temp)
            {
                if (temp->right)
                    st.push(temp->right);
                st.push(temp);
                temp = temp->left;
            }

            temp = st.top();
            st.pop();

            if (temp->right && !st.empty() && temp->right == st.top())
            {
                st.pop();
                st.push(temp);
                temp = temp->right;
            }
            else
            {
                cout << temp->data << " ";
                temp = nullptr;
            }
        } while (!st.empty());

        cout << endl;
    }



    int leafNodeHelper(Node *ele)
    {
        if (!ele->left && !ele->right)
            return 1;

        int left = 0, right = 0;

        if (ele->left)
            left = leafNodeHelper(ele->left);

        if (ele->right)
            right = leafNodeHelper(ele->right);

        return left + right;
    }

    int leafNode()
    {
        return leafNodeHelper(root);
    }

    int NodeHelper(Node *ele)
    {
        if (!ele->left && !ele->right)
            return 0;

        int left = 0, right = 0;

        if (ele->left)
            left = NodeHelper(ele->left);

        if (ele->right)
            right = NodeHelper(ele->right);

        return 1 + left + right;
    }

    int NodeFindOut()
    {
        return NodeHelper(root);
    }

    void delTree()
    {
        delTreeHelper(root);
        root = nullptr;
    }

    void delTreeHelper(Node *_root)
    {
        if (!_root)
            return;

        delTreeHelper(_root->left);
        delTreeHelper(_root->right);

        delete _root;
        _root = nullptr;
    }

    ~TreeNode()
    {
        delTree();
        cout << "Tree Deleted Successfully" << endl;
    }
};

int menu()
{
    cout << "1.Enter Expression \n"
            "2.Display PostOrder\n"
            "3.Operator Count \n"
            "4.Operand Count \n"
            "5.Delete Tree \n"
            "6.exit \n"
         << endl;
    int option = 0;
    cout << "Enter The Option : ";
    cin >> option;
    return option;
}

int main()
{
    TreeNode obj;

    while (true)
    {
        int choice = menu();
        if (choice == 6)
            return 0;

        switch (choice)
        {
        case 1:
        {
            cout << "Creating Tree Recursively..." << endl;
            obj.initialize();
            cout << "BT Created Successfully" << endl;
            break;
        }


        case 2:
        {
            cout << "PostOrder" << endl;
            obj.postOrderNonRec();
            cout << endl;
            break;
        }

        case 3:
        {
            cout << "Operator" << endl;
            cout<<obj.NodeFindOut();
            cout << endl;
            break;
        }

        case 4:
        {
            cout << "Operand : " << endl;
            cout << obj.leafNode();
            cout << endl;
            break;
        }



        case 5:
        {
            obj.delTree();
            break;
        }
        }
    }

    return 0;
}
