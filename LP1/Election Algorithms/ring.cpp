#include <bits/stdc++.h>
using namespace std;

class Node
{
    bool isLeader;
    int id;

public:
    Node(int _id) : id(_id), isLeader(false) {}

    int getId()
    {
        return this->id;
    }

    void setId(int _id)
    {
        this->id = _id;
    }

    bool getLeaderState()
    {
        return isLeader;
    }

    ~Node()
    {
        cout << "Destroyed " << id << endl;
    }
};

class election
{
private:
    int currentLeader;
    vector<Node *> nodeList;

public:
    election() : currentLeader(-1) {}

    void addNode(int id)
    {
        Node *newNode = new Node(id);
        nodeList.push_back(newNode);
    }

    void takeElection()
    {
        startElection(0);
    }

    void crashLeader()
    {
        int n = nodeList.size();
        for (int i = 0; i < n; i++)
        {
            if ((i + 1) == currentLeader)
            {
                nodeList.erase(nodeList.begin() + (i + 1) % n);
                if (i == n - 1)
                    i--;

                cout << i + 1 << " Node Crashed! Reported by " << i << endl;
                currentLeader = startElection(i);

                break;
            }
        }
    }

    int startElection(int idx)
    {
        cout << "Started election by " << idx << endl;
        vector<pair<int, int>> ids{{nodeList[idx]->getId(), idx}};
        int maxi = idx;
        int n = nodeList.size();

        for (int i = idx + 1; (i + n) % n != idx; i++)
        {
            i = i % n;
            cout << "Message Recieved By : " << i << endl;
            ids.push_back({nodeList[i]->getId(), i});

            if (nodeList[i]->getId() > nodeList[maxi]->getId())
                maxi = i;
        }

        cout << "__________________________________________" << endl;
        cout << "Message Recieved By : " << idx << endl;
        cout << "New Leader is : " << maxi << " Propogating to all" << endl;

        n = nodeList.size();
        for (int i = 0; i < n; i++)
        {
            cout << nodeList[i]->getId() << " ";
        }

        return currentLeader = maxi;
    }

    void getLeader()
    {
        int n = nodeList.size();
        for (int i = 0; i < n; i++)
        {
            cout << nodeList[i]->getId() << " ";
        }

        cout << endl;

        cout << "leader is : " << currentLeader << endl;
    }
};

int menu()
{
    cout << "Menu \n 1.Add Node \n 2.Crash Leader \n 3.Get Leader \n 4.Take Election \n 4.STOP" << endl;
    int option;
    cin >> option;
    return option;
}

int main()
{
    election ele;
    int id, option;
    while (true)
    {
        option = menu();

        switch (option)
        {
        case 1:
        {
            cin >> id;
            ele.addNode(id);
            break;
        }

        case 2:
        {
            ele.crashLeader();
            break;
        }

        case 3:
        {
            ele.getLeader();
            break;
        }

        case 4:
        {
            ele.takeElection();
            break;
        }

        default:
            return 0;
        }
    }
}