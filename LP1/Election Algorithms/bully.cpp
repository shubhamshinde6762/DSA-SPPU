#include <bits/stdc++.h>
using namespace std;


// Class Process
class Process
{
public:
    int id;
    bool state;
    Process(int _id) : id(_id), state(true) {}
};

class Elect
{
public:
// Store the Processes
    vector<Process *> process;
    int leader;
    Elect()
    {
        cout << "Enter the Number of Processes" << endl;
        int cnt = 0;
        cin >> cnt;

        process.assign(cnt, NULL);
        int maxi = 0;
        leader = 0;

        for (int i = 0; i < cnt; i++)
        {
            int _id;
            cout << "Enter Id : ";
            cin>>_id;

            process[i] = new Process(_id);
            if (_id > maxi)
                maxi = _id, leader = i;
        }

        // Sorting processes by ids for efficiency in Message Passing
        sort(process.begin(), process.end(), [](Process *a, Process *b)
             { return a->id < b->id; });
    }

    void Crash()
    {
        int node = 0;

        // Random Detection of Node who detects Crashes except by Leader
        do
        {
            node = rand() % process.size();
        } while (node == leader);

        cout << "Detected Leader Crashed by : " << process[node]->id << endl;
        // mark Leader State as false
        process[leader]->state = false;
        leader = -1;
        initElecion(node);
    }

    bool initElecion(int idx)
    {
        //  Return NACK id Process is Crashed
        if (process[idx]->state == false)
            return false;

        cout << "Election Message received by : " << process[idx]->id << endl;

        for (int node = idx + 1; node < process.size(); node++)
        {
            // If ACK then Reciever take care remaning so STOP
            if (initElecion(node))
                return true;
            cout << "Negative Ack from " << process[node]->id  << " to " << process[idx]->id  << endl;
        }

        // if All NACK then Elect Current as Leader
        cout << "New Leader Elected : " << process[idx]->id << endl;
        leader = idx;
        return true;
    }

    bool crashProcess(int idx)
    {
        if (process[leader]->id == idx)
        {
            Crash();
            return true;
        }

        for (auto it : process)
        {
            if (idx == it->id)
            {
                it->id = -1;
                return true;
            }
        }

        return false;
    }
};

int menu()
{
    cout << " 1. Crash Leader \n 2.Crash Process \n 3.Get Leader \n 4.Exit" << endl;
    int option;
    cin >> option;
    return option;
}

int main()
{
    Elect obj;

    while (true)
    {
        int option = menu();
        int id;

        switch (option)
        {
        case 1:
        {
            obj.Crash();
            break;
        }
        case 2:
        {
            cout << "Enter Id of Process : ";
            cin >> id;
            if (obj.crashProcess(id))
                cout << "Crashed !" << endl;
            else
                cout << "Not Found " << endl;
            break;
        }
        case 3:
        {
            cout << "Leader is : " << obj.process[obj.leader]->id << endl;
            break;
        }
        default:
            return 0;
        }
    }
    return 0;
}