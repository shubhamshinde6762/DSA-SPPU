//============================================================================
// Name        : Assi_2.cpp
// Author      : Shubham Shinde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

//11 1 56 1 45 1 78 1 98 1 752 1 74 1 25 1 84 0

class Node
{
public:
	int data;
	Node* left;
	Node* right;

	Node() : left(nullptr), right(nullptr), data(0) {}
	Node(int _data) : left(nullptr), right(nullptr), data(_data) {}
};

class BST
{
	Node* head;
public:
	BST() : head(nullptr) {}

	bool isSwapped = false;

	void Create();
	void Insert(int);
	void inOrder(Node*);
	int maxPath();
	int maxPathHelper(Node*);
	int maxElement();
	int minElement();
	void mirror();
	void mirrorHelper(Node*);
	void Search(int);
	void Delete(int);
	Node* DeleteHelper(Node*, int);
	void inOrderHelper()
	{
		inOrder(head);
		cout<<endl;
	}
};

void BST::Delete(int t)
{
	bool flag = 0;
	if (isSwapped)
	{
		mirror();
		flag = true;
	}


	head = DeleteHelper(head, t);


	if (flag)
		mirror();
	return;
}

Node* BST::DeleteHelper(Node* root, int target)
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

int BST::maxElement()
{
	if(!head)
	{
		cout<<"Tree Not Created yet!"<<endl;
		return -1;
	}

	bool flag = 0;
	if (isSwapped)
	{
		mirror();
		flag = true;
	}



	Node* temp = head;
	while(temp)
	{
		if (temp->right)
			temp = temp->right;
		else
			return temp->data;
	}

	if (flag)
		mirror();

	return -1;
}

int BST::minElement()
{
	if(!head)
	{
		cout<<"Tree Not Created yet!"<<endl;
		return -1;
	}


	bool flag = 0;
	if (isSwapped)
	{
		mirror();
		flag = true;
	}


	Node* temp = head;
	while(temp)
	{
		if (temp->left)
			temp = temp->left;
		else
			return temp->data;
	}

	if (flag)
		mirror();

	return -1;
}

int BST::maxPath()
{
	if(!head)
	{
		cout<<"Tree Not Created yet!"<<endl;
		return -1;
	}
	return maxPathHelper(head);
}

int BST::maxPathHelper(Node* root)
{
	if (!root)
		return 0;

	int left = 0, right = 0;

	if (root->left)
		left = maxPathHelper(root->left);
	if (root->right)
		right = maxPathHelper(root->right);

	return 1 + max(left, right);
}

void BST::inOrder(Node* _root)
{
	if (!_root)
		return;

	inOrder(_root->left);
	cout << _root->data << " ";
	inOrder(_root->right);
}

void BST::Insert(int d)
{
	if (!head)
	{
		head = new Node(d);
		return;
	}

	bool flag = 0;
	if (isSwapped)
	{
		mirror();
		flag = true;
	}

	Node* temp = head;
	Node *parent = nullptr;

	while(1)
	{
		if (!temp)
		{
			temp = new Node(d);
			if (parent->data < d)
				parent->right = temp;
			else
				parent->left = temp;
			break;
		}


		if (temp->data == d)
		{
			cout<<"Duplicate Data"<<endl;
			if (flag)
				mirror();
			return;
		}


		parent = temp;
		if (temp->data < d)
			temp = temp->right;
		else
			temp = temp->left;
	}
	if (flag)
		mirror();
}

void BST::Create()
{
	bool flag = 0;
	if (isSwapped)
	{
		mirror();
		flag = true;
	}


	while(1)
	{
		cout<<"Enter the Element to Insert : "<<endl;
		int d;
		cin>>d;
		Insert(d);
		cout<<"Are you want to continue? (1 / 0)"<<endl;
		bool b;
		cin>>b;
		if (!b)
			break;
	}

	if (flag)
		mirror();

	inOrder(head);

	cout<<endl;

	cout<<"BST Created Successfully...."<<endl;
}


void BST::mirror()
{
	mirrorHelper(head);
	isSwapped = !isSwapped;
	return;
}

void BST::mirrorHelper(Node *_root)
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

void BST::Search(int d)
{
	bool flag = 0;
	if (isSwapped)
	{
		mirror();
		flag = true;
	}


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
			if (flag)
				mirror();
			return;
		}
	}

	cout<<"Element is Absent! "<<endl;
	if (flag)
		mirror();
}

int menu()
{
	cout<<endl;
	cout<<"1.Create The Tree\n"
			"2.Insert an Element\n"
			"3.Change the Role of left Link and Right Link\n"
			"4.Minimum and Maximum Element\n"
			"5.Search the Tree\n"
			"6.Print the Tree\n"
			"7.Longest Length\n"
			"8.Delete\n"
			"9.Exit\n";

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
        if (choice == 9)
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
        	int d;
        	cout<<"Enter the Element ";
        	cin>>d;
            tree.Insert(d);
            tree.inOrderHelper();
            cout<<endl;
            break;
        }

        case 3:
        {
            tree.mirror();
            tree.inOrderHelper();
            break;
        }

        case 4:
        {
            cout<<"Minimum : "<<tree.minElement()<<endl;
            cout<<"Maximum : "<<tree.maxElement()<<endl;
            cout<<endl;
            break;
        }



        case 5:
        {
            cout<<"Enter the Data to Search : ";
            int d;
            cin>>d;
            tree.Search(d);
            break;
        }

        case 6:
		{

			tree.inOrderHelper();
			break;
		}
        case 7:
		{

			cout<<tree.maxPath()<<endl;
			break;
		}
        case 8:
		{
			int t;
			cout<<"Enter Target to Delete "<<endl;
			cin>>t;
			tree.Delete(t);
			break;
		}

        default:
        	return 0;
        }
    }

	return 0;
}
