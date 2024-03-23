//============================================================================
// Name        : Tree.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//3 1 50 1 10 1 70 1 65 1 15 1 25 0 0 0 0 0 1 87 0 0 0 1 90 0 0


template<class T>
class stack1
{
	int size;
	T *arr;
	int t;

public:
	stack1(int _size) : size(_size), t(-1) {arr = new T(size);};

	void pop()
	{
		t--;
	}

	void push(T _data)
	{
		arr[++t] = _data;
	}

	T top()
	{
		return arr[t];
	}

	bool empty()
	{
		return t == -1;
	}
};


class queue
{

	class Node
	{
	public:
		int data;
		Node* next = nullptr;
		Node(int _data) : data(_data){}
	};

public:

	Node* head = nullptr;
	Node* tail = head;


	int front()
	{
		return head->data;
	}

	void pop()
	{
		Node* temp = head;
		if (!temp->next)
		{
			delete temp;
			head = nullptr;
			tail = head;
		}
		else
		{
			temp = head->next;
			head->next = nullptr;
			delete head;
			head = temp;
		}
	}

	bool empty()
	{
		return (head == nullptr);
	}


	void push(int _data)
	{
		if (head == nullptr)
		{
			head = new Node(_data);
			tail = head;
		}
		else
		{
			Node* newNode = new Node(_data);
			Node* temp = head;

			if (head->data < newNode->data)
			{
			    newNode->next = head;
			    head = newNode;
			    return;
			}

			while(temp->next && temp->next->data > _data)
				temp = temp->next;
			if (!temp->next)
			{
				tail->next = newNode;
				tail = tail->next;
			}
			else
			{
				newNode->next = temp->next;
				temp->next = newNode;
			}
		}
	}

	void print()
	{
		Node* temp = head;
		while(temp)
		{
			cout<<temp->data<<" ";
			temp = temp->next;
		}
		cout<<endl;
	}
};


class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int _data = 0) : data(_data), left(nullptr), right(nullptr) {}
};

class TreeNode
{
    Node *root;
    Node *createTree()
    {
        int _data;
        bool l, r;

        cout << "Enter Data: ";
        cin >> _data;
        Node *element = new Node(_data);

        cout << "Are you want to add left Link ";
        cin >> l;

        if (l)
            element->left = createTree();

        cout << "Are you want to add Right Link ";
        cin >> r;

        if (r)
            element->right = createTree();

        return element;
    }

public:
    TreeNode() : root(nullptr) {}
    TreeNode(Node* _root) : root(_root) {}

    TreeNode &operator=(TreeNode &tree)
    {
        TreeNode obj;
        obj.root = cpy(obj.root, tree.root);
        return obj;
    }

    void createTreeNonRec()
    {
        deque<Node *> dq;
        int data = 0;
        cout << "Enter Data; ";
        cin >> data;

        root = new Node(data);
        dq.push_back(root);

        while (!dq.empty())
        {
            int _data;
            bool l, r;

            cout << "Are you want to add left Link ";
            cin >> l;

            if (l)
            {
                cout << "Enter Data: ";
                cin >> _data;
                Node *element = new Node(_data);
                dq.front()->left = element;
                dq.push_back(element);
            }

            cout << "Are you want to add Right Link ";
            cin >> r;

            if (r)
            {
                cout << "Enter Data: ";
                cin >> _data;
                Node *element = new Node(_data);
                dq.front()->right = element;
                dq.push_back(element);
            }

            dq.pop_front();
        }
    }

    void initialize()
    {
        // createTreeNonRec();
        root = createTree();
        return;
    }

    void displayRecursive()
    {
        cout << "inOrder Traversal : ";
        inOrder(root);
        cout << endl;
        cout << "preOrder Traversal : ";
        preOrder(root);
        cout << endl;
        cout << "postOrder Traversal : ";
        postOrder(root);
        cout << endl;
    }

    void displayNonRecursive()
    {
        cout << "inOrder Traversal NonRecursive: ";
        inOrderNonRec();
        cout << endl;
        cout << "preOrder Traversal NonRecursive : ";
        preOrderNonRec();
        cout << endl;
        cout << "postOrder Traversal NonRecursive : ";
        postOrderNonRec();
        cout << endl;
    }

    void inOrder(Node *_root)
    {
        if (!_root)
            return;

        inOrder(_root->left);
        cout << _root->data << " ";
        inOrder(_root->right);
    }

    void inOrderNonRec()
    {
        Node *temp = root;
        stack<Node *> st;
        while (true)
        {
            while (temp)
            {
                st.push(temp);
                temp = temp->left;
            }

            if (st.empty())
                break;

            temp = st.top();
            cout << temp->data << " ";
            st.pop();
            temp = temp->right;
        }

        cout << endl;
    }

    void preOrderNonRec()
    {
        Node *temp = root;
        stack<Node *> st;
        while (true)
        {
            while (temp)
            {
                cout << temp->data << " ";

                if (temp->right)
                    st.push(temp->right);

                temp = temp->left;
            }

            if (st.empty())
                break;

            temp = st.top();
            st.pop();
        }

        cout << endl;
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

    void mirror()
    {
        mirrorHelper(root);
        return;
    }

    void mirrorHelper(Node *_root)
    {
        if (!_root)
            return;

        Node *temp = _root->left;
        _root->left = _root->right;
        _root->right = temp;

        mirrorHelper(_root->left);
        mirrorHelper(_root->right);

        return ;
    }
    Node *cpy(Node *root1, const Node *root2)
    {
        if (!root2)
            return nullptr;

        root1 = new Node(root2->data);
        root1->left = cpy(root1->left, root2->left);
        root1->right = cpy(root1->right, root2->right);

        return root1;
    }
    void preOrder(Node *_root)
    {
        if (!_root)
            return;

        cout << _root->data << " ";
        preOrder(_root->left);
        preOrder(_root->right);
    }

    void postOrder(Node *_root)
    {
        if (!_root)
            return;

        postOrder(_root->left);
        postOrder(_root->right);
        cout << _root->data << " ";
    }

    int heightHelper(Node *ele)
    {
        if (!ele)
            return 0;

        int left = heightHelper(ele->left);
        int right = heightHelper(ele->right);

        return 1 + max(left, right);
    }

    int height()
    {
        return heightHelper(root);
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

        _root->left = nullptr;
        _root->right = nullptr;

        delete _root;
    }

    ~TreeNode()
    {
        cout << "Tree Deleted Successfully" << endl;
    }
};

int menu()
{
    cout << "1.Create Recursively \n"
            "2.Create Non Recursively \n"
            "3.Display Recursively \n"
            "4.Display NonRecursively \n"
            "5.LeafNode Count \n"
            "6.Node Count \n"
            "7.Mirror Image \n"
            "8.Copy Tree \n"
            "9.Height of Tree \n"
            "10.Delete Tree \n"
            "11.exit \n"
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
        if (choice == 11)
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
            cout << "Creating Tree NonRecursively..." << endl;
            obj.createTreeNonRec();
            cout << "BT Created Successfully" << endl;
            break;
        }

        case 3:
        {
            cout << "Recursive" << endl;
            obj.displayRecursive();
            cout << endl;
            break;
        }

        case 4:
        {
            cout << "NonRecursive" << endl;
            obj.displayNonRecursive();
            cout << endl;
            break;
        }

        case 5:
        {
            cout << "LeafNode Count : " << endl;
            cout << obj.leafNode();
            cout << endl;
            break;
        }

        case 6:
        {
            cout << "Node Count : " << endl;
            cout << obj.NodeFindOut();
            cout << endl;
            break;
        }

        case 7:
        {
            cout << "Mirror Image : " << endl;
            obj.mirror();
            cout << endl;
            break;
        }
        case 8:
        {
            TreeNode newObj = obj;
            cout << "Recursive" << endl;
            newObj.displayRecursive();
            cout << endl;
            break;
        }

        case 9:
        {
            cout << "Height : " << obj.height();
            cout << endl;
            break;
        }

        case 10:
        {
            obj.delTree();
            break;
        }
        }
    }

    return 0;
}
