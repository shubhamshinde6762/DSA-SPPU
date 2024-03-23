//============================================================================
// Name        : Assi_5.cpp
// Author      : Shubham Shinde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class HT
{
    class Node
    {
        int key;
        string data;
        string meaning;
        Node *next;

    public:
        Node() : key(-1), data(""), next(nullptr), meaning("") {}
        Node(int _key, string _data, string _meaning) : key(_key), data(_data), next(nullptr), meaning(_meaning) {}
        friend class HT;
    };

    Node *mp[27];
    int hash(string data);

public:
    HT()
    {
        for (int i = 0; i < 27; i++)
            mp[i] = nullptr;
    }
    void insert(string data, string meaning);
    void find(string data);
    void deleteData(string data);
    void Display();
};

int HT::hash(string data)
{
    if (data[0] < 'a' || data[0] > 'z')
        return 26;
    return int(data[0] - 'a');
}

void HT::insert(string data, string meaning)
{
    int key = hash(data);
    if (!mp[key])
    {
        mp[key] = new Node(key, data, meaning);
        return;
    }

    Node *pre = nullptr;
    Node *curr = mp[key];
    Node *newNode = new Node(key, data, meaning);

    while (curr && curr->data < data)
    {
        pre = curr;
        curr = curr->next;
    }

    if (curr == mp[key])
    {
        newNode->next = mp[key];
        mp[key] = newNode;
    }
    else
    {
        pre->next = newNode;
        newNode->next = curr;
    }
}

void HT::find(string data)
{
    int key = hash(data);
    if (!mp[key])
    {
        cout << "Key Not Found" << endl;
        return;
    }

    Node *curr = mp[key];

    while (curr && curr->data < data)
        curr = curr->next;

    if (curr && curr->data == data)
    {
        cout << "Key Found" << endl;
        cout << key << " " << curr->data << " " << curr->meaning << endl;
    }
    else
        cout << "Key Not Found" << endl;
}

void HT::deleteData(string data)
{
    int key = hash(data);
    if (!mp[key])
    {
        cout << "Key Not Found" << endl;
        return;
    }

    Node *curr = mp[key];
    Node *pre = nullptr;

    while (curr && curr->data < data)
    {
        pre = curr;
        curr = curr->next;
    }

    if (curr && curr->data == data)
    {
        if (curr == mp[key])
        {
            mp[key] = curr->next;
            curr->next = nullptr;
            delete curr;
        }
        else
        {
            pre->next = curr->next;
            curr->next = nullptr;
            delete curr;
        }

        cout << "Deleted Successfully" << endl;
    }
    else
        cout << "Key Not Found" << endl;
}

void HT::Display()
{
    for (int i = 0; i < 27; i++)
    {
        cout << "key=> " << i << endl;
        if (!mp[i])
            continue;
        else
        {
            Node *temp = mp[i];
            while (temp)
            {
                cout << temp->data << " " << temp->meaning << endl;
                temp = temp->next;
            }
            cout << endl;
        }
    }
}

int main()
{
    HT t;
    int choice, key;
    string data;
    string meaning;

    do
    {
        cout << "\n\n1. Insert\n2. Display\n3. Search\n4.Delete\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter Data => ";
            cin >> data;
            cout << "Enter Meaning => ";
            cin >> meaning;
            t.insert(data, meaning);
            t.Display();
            break;
        }

        case 2:
            cout << "Display";
            t.Display();
            cout << endl;
            break;
        case 3:
            cout << "Search";
            cout << "Enter the Data";
            cin >> data;

            t.find(data);
            cout << endl;
            break;

        case 4:
            cout << "Delete";
            cout << "Enter the Data";
            cin >> data;

            t.deleteData(data);
            cout << endl;
            break;

        default:
            cout << "Invalid choice. Please try again.";
        }
    } while (choice != 5);

    return 0;
}
