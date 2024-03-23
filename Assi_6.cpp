//============================================================================
// Name        : Assi_6.cpp
// Author      : Shubham Shinde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Graph
{
	class Node{
		int dest;
		int fuel;
		Node* next;
	public:
		Node(int _dest, int _fuel) : dest(_dest), fuel(_fuel), next(nullptr) {}
		Node() : dest(-1), fuel(0), next(nullptr) {}
		friend class Graph;
	};


	Node **arr;
	int size;

public:
	Graph(int _size) : size(_size)
	{
		arr = new Node*[_size];
		for (int i = 0; i < size; i++)
			arr[i] = new Node(i, 0);
	}

	void addEdge(int src, int dest, int fuel)
	{
		if (src >= size || dest >= size)
		{
			cout<<"Invalid Source or Destination"<<endl;
			return;
		}

		Node* temp = arr[src];
		while(temp->next)
		{
			temp = temp->next;
			if (temp->dest == dest)
			{
				cout<<"Already Edge Present"<<endl;
				return;
			}
		}

		Node* newNode = new Node(dest, fuel);
		temp->next = newNode;
	}

	void dfsHelper(int src, bool visited[])
	{
		visited[src] = true;

		for (Node* temp = arr[src]->next; temp; temp = temp->next)
			if (!visited[temp->dest])
				dfsHelper(temp->dest, visited);
	}

	void degreeCnt()
	{
		int outDegree[size] = {};
		int inDegree[size] = {};

		for (int i = 0; i < size; i++)
		{
			Node* temp = arr[i]->next;
			while(temp)
			{
				inDegree[temp->dest]++;
				outDegree[i]++;
				temp = temp->next;
			}
		}

		cout<<"Indegree's and outDegree's are"<<endl;
		for (int i = 0; i < size; i++)
		{
			cout<<"Index"<<" InDegree"<<" OutDegree"<<endl;
			cout<<i<<"  "<<inDegree[i]<<"  "<<outDegree[i]<<endl;
		}
	}

	int DFS()
	{
		bool visited[size];

		int cnt = 0;

		for (int i = 0; i < size; i++)
		{
			if (!visited[i] && arr[i]->next)
			{
				dfsHelper(i, visited);
				cnt++;
			}
		}

		return cnt;

	}

};

int main() {
	Graph G(10);
	int choice;
	int src, dest, fuel;

	do {
		cout<< "\n\n1. Insert\n2. Degree\n3. No of Components\n4.Exit\nEnter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			cout<<"Enter the Source : ";
			cin>>src;
			cout<<"Enter the Destination : ";
			cin>>dest;
			cout<<"Enter the Fuel : ";
			cin>>fuel;

			G.addEdge(src, dest, fuel);
			break;
		}

		case 2:
			G.degreeCnt();
			break;
		case 3:
		{
			int components = G.DFS();
			cout<<"No of Components :- "<<components<<endl;
			break;
		}


		default:
			cout << "Invalid choice. Please try again.";
		}
	} while (choice != 5);

	return 0;
}

