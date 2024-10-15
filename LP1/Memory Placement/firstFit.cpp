#include <iostream>
#include <vector>
using namespace std;

class Allocator;

class mBlock
{
    int memoryLocation;
    int blockSize;
    bool status;

public:
    mBlock(int _memoryLocation, int _blockSize) : memoryLocation(_memoryLocation), blockSize(_blockSize), status(false) {}
    friend class Allocator;
};

class Job
{
    int jobId;
    int memoryReq;

public:
    Job(int _jobId, int _memoryReq) : jobId(_jobId), memoryReq(_memoryReq) {}
    friend class Allocator;
};

class Allocator
{
    vector<Job *> jq;
    vector<mBlock *> mq;

public:
    Allocator()
    {
        int mcnt = 0;
        cout << "Enter the Number of Memory Blocks : " << endl;
        cin >> mcnt;

        cout << "Enter Memory Location and Block Size : " << endl;
        for (int i = 0; i < mcnt; i++)
        {
            int _memoryLocation = 0, _blockSize = 0;
            cin >> _memoryLocation >> _blockSize;
            mq.push_back(new mBlock(_memoryLocation, _blockSize));
        }

        int jcnt = 0;
        cout << "Enter the Number of Jobs : " << endl;
        cin >> jcnt;

        cout << "Enter job Id and Memory Required : " << endl;
        for (int i = 0; i < jcnt; i++)
        {
            int _JobId = 0, _req = 0;
            cin >> _JobId >> _req;
            jq.push_back(new Job(_JobId, _req));
        }
    }

    ~Allocator()
    {
        for (auto job : jq)
            delete job;
        for (auto block : mq)
            delete block;
    }

    void Process()
    {
        for (auto it : jq)
        {
            cout << "------------------------------------------------------------" << endl;
            cout << "Let's assign memory to Job Id : " << it->jobId << endl;

            int mreq = it->memoryReq;
            bool allocated = false;

            for (auto block : mq)
            {
                cout << "Pointing to memory : " << block->memoryLocation << endl;

                if (block->blockSize >= mreq && !block->status)
                {
                    cout << "Allocating Memory to : " << it->jobId << " at : " << block->memoryLocation << endl;
                    block->status = true;
                    allocated = true;
                    break;
                }
            }

            if (!allocated)
            {
                cout << "No Memory Block found for Job Id: " << it->jobId << "!" << endl;
            }
        }
    }
};

int main()
{
    Allocator *al = new Allocator();
    al->Process();
    delete al;
    return 0;
}
