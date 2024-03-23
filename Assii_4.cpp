//============================================================================
// Name        : Assi_4.cpp
// Author      : Shubham Shinde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#define MAX 10

class HT
{

    class Data
    {
        long long data;
        int key;

    public:
        Data() : data(0), key(-1)
        {
        }
        Data(int _data, int _key) : data(_data), key(_key)
        {
        }

        friend class HT;
    };

    Data hashingTable[MAX];
    Data hashingTableR[MAX];

    void InsertHelper(Data d, int index)
    {
        int i = 0;

        while (hashingTable[index % MAX].key != -1 && i++ < 10)
            index++;

        if (hashingTable[index % MAX].key == -1)
            hashingTable[index % MAX] = d;
        else
        {
            cout << "hashingTable is Full" << endl;
        }
    }
    void replaceInsert(Data d, int index)
    {
        int i = 0;

        if (hashingTableR[index % MAX].key != -1 && hashingTableR[index % MAX].key % MAX != index)

        {
            Data temp = hashingTableR[index % MAX];
            hashingTableR[index % MAX] = d;
            d = temp;
            index++;
            i++;
        }

        while (hashingTableR[index % MAX].key != -1 && i++ < 10)
            index++;

        if (hashingTableR[index % MAX].key == -1)
            hashingTableR[index % MAX] = d;
        else
        {
            cout << "hashingTable is Full" << endl;
        }
    }

public:
    HT()
    {
        Data temp;
        for (int i = 0; i < MAX; i++)
        {
            hashingTable[i] = temp;
            hashingTableR[i] = temp;
        }
    }

    int hashingFunction(int);
    void Insert();
    void Search(int, int);
    void Display();
};

int HT::hashingFunction(int key)
{
    return (key % MAX);
}

void HT::Insert()
{
    Data d;
    bool isContinue = true;
    do
    {
        cout << "Enter Phone Number to Insert" << endl;
        cin >> d.data;

        if (d.data - 1000000000 < 0)
        {
            cout << "enter Valid Number" << endl;
            continue;
        }

        cout << "Enter Key:-" << endl;
        cin >> d.key;

        int index = hashingFunction(d.key);

        InsertHelper(d, index);
        replaceInsert(d, index);

        cout << "Are you want to Add" << endl;
        cin >> isContinue;
    } while (isContinue);
}

void HT::Display()
{
    cout << "Without Replace" << endl;
    for (auto i : hashingTable)
        cout << i.key << " " << i.data << endl;

    cout << "****************" << endl;
    cout << "With Replace" << endl;
    for (auto i : hashingTableR)
        cout << i.key << " " << i.data << endl;
}

void HT::Search(int key, int data)
{
    int index = key % MAX;
    // for without Replace Linear Probing
    int tempIndex = index;
    int i = 0;
    while (hashingTable[tempIndex % MAX].key != -1 && i++ < 10 && !(hashingTable[tempIndex % MAX].key == key && hashingTable[tempIndex % MAX].data == data))
        tempIndex++;

    if (hashingTable[tempIndex % MAX].key != -1 && hashingTable[tempIndex % MAX].key == key && hashingTable[tempIndex % MAX].data == data)
        cout << "Found Element after " << i << " Comparisons" << endl;
    else
        cout << "Element Not Found" << endl;

    // with Replace
    tempIndex = index;
    i = 0;
    while (hashingTableR[tempIndex % MAX].key != -1 && i++ < 10 && !(hashingTableR[tempIndex % MAX].key == key && hashingTableR[tempIndex % MAX].data == data))
        tempIndex++;

    if (hashingTableR[tempIndex % MAX].key != -1 && hashingTableR[tempIndex % MAX].key == key && hashingTableR[tempIndex % MAX].data == data)
        cout << "Found Element after " << i << " Comparisons" << endl;
    else
        cout << "Element Not Found" << endl;
}

int main()
{
    HT t;
    int choice, key;
    long long data;

    do
    {
        cout << "\n\n1. Insert\n2. Display\n3. Search\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            t.Insert();
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
            cout << "Enter the Key";
            cin >> key;
            cout << "Enter the Data";
            cin >> data;

            if (data - 1000000000 < 0)
            {
                cout << "enter Valid Number" << endl;
                break;
            }

            t.Search(key, data);
            cout << endl;
            break;

        default:
            cout << "Invalid choice. Please try again.";
        }
    } while (choice != 4);

    return 0;
}
