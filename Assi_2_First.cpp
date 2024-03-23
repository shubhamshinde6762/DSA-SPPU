//============================================================================
// Name        : Assi_2.cpp
// Author      : Shubham Shinde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <strings.h>
using namespace std;

//1 abc nothing 1 xyz no 1 operations aws 1 last last 0

class Node
{
public:
	string data;
	string meaning;
	Node* left;
	Node* right;

	Node() : left(nullptr), right(nullptr), data(""), meaning("") {}
	Node(string _data, string _meaning) : left(nullptr), right(nullptr), data(_data), meaning(_meaning) {}
};

class BST
{
	Node* head;
public:
	BST() : head(nullptr) {}

	bool isSwapped = false;

	void Create();
	void Insert(string, string);
	void inOrder(Node*);
	void Search(string);
	void Delete(string);
	Node* DeleteHelper(Node*, string);
	void inOrderHelper()
	{
		inOrder(head);
		cout<<endl;
	}

};

void BST::Delete(string t)
{
	head = DeleteHelper(head, t);
	return;
}

Node* BST::DeleteHelper(Node* root, string target)
{
	if (!root)
		return NULL;

	if (root->data < target)
	{
		root->right = DeleteHelper(root->right, target);
		return root;
	}
	else if (root->data > target)
	{
		root->left = DeleteHelper(root->left, target);
		return root;
	}


	if (!root->right)
	{
		Node* temp = root->left;
		root->left = nullptr;
		delete root;
		return temp;
	}


	if(!root->left)
	{
		Node* temp = root->right;
		root->right = nullptr;
		delete root;
		return temp;
	}

	Node* parent = root;
	Node* child = root->right;

	while(child->left)
	{
		parent = child;
		child = child->left;
	}


	if (parent != root)
		parent->left = child->right;
	else
		parent->right = child->right;

	root->data = child->data;
	delete child;
	return root;
}

void BST::inOrder(Node* _root)
{
	if (!_root)
		return;

	inOrder(_root->left);
	cout << _root->data << " "<<_root->meaning<<endl;
	inOrder(_root->right);
}

void BST::Insert(string d, string m)
{
	if (!head)
	{
		head = new Node(d, m);
		return;
	}


	Node* temp = head;
	Node *parent = nullptr;

	while(1)
	{
		if (!temp)
		{
			temp = new Node(d, m);
			if (parent->data < d)
				parent->right = temp;
			else
				parent->left = temp;
			break;
		}


		if (temp->data == d)
		{
			cout<<"Duplicate Data"<<endl;
			return;
		}


		parent = temp;
		if (temp->data < d)
			temp = temp->right;
		else
			temp = temp->left;
	}
}

void BST::Create()
{
	while(1)
	{
		cout<<"Enter the Element to Insert : "<<endl;
		string d;
		cin>>d;
		cout<<"Enter the Meaning : "<<endl;
		string m;
		cin>>m;
		Insert(d, m);
		cout<<"Are you want to continue? (1 / 0)"<<endl;
		bool b;
		cin>>b;
		if (!b)
			break;
	}


	inOrder(head);

	cout<<endl;

	cout<<"BST Created Successfully...."<<endl;
}


void BST::Search(string d)
{

	if (!head)
	{
		cout<<"Tree Not Exists!"<<endl;
		return;
	}

	Node* temp = head;
	int cnt = 0;

	while(temp)
	{
		cnt++;
		cout<<"Pass "<<cnt<<" data "<<temp->data<<endl;


		if (temp->data < d)
			temp=temp->right;
		else if (temp->data > d)
			temp = temp->left;
		else
		{
			cout<<"Element is Present!"<<endl;
			return;
		}
	}

	cout<<"Element is Absent! "<<endl;
}

int menu()
{
	cout<<endl;
	cout<<"1.Create The Tree\n"
			"2.Insert an Element\n"
			"3.Search the Tree\n"
			"4.Print the Tree\n"
			"5.Delete the Node\n"
			"6.Exit\n";

	int choice;
	cin>>choice;
	cout<<endl;
	return choice;
}


int main() {
	BST tree;
    while (true)
    {
        int choice = menu();
        if (choice == 6)
            return 0;

        switch (choice)
        {
        case 1:
        {
            tree.Create();
            break;
        }


        case 2:
        {
        	string d, m;
        	cout<<"Enter the Element ";
        	cin>>d;
        	cout<<"Enter the Meaning";
        	cin>>m;
            tree.Insert(d, m);
            tree.inOrderHelper();
            cout<<endl;
            break;
        }

        case 3:
        {
            cout<<"Enter the Data to Search : ";
            string d;
            cin>>d;
            tree.Search(d);
            break;
        }

        case 4:
		{

			tree.inOrderHelper();
			break;
		}

        case 5:
		{
			string n;
			cout<<"Enter the Target to Delete"<<endl;
			cin>>n;
			tree.Delete(n);
			break;
		}


        default:
        	return 0;
        }
    }

	return 0;
}
