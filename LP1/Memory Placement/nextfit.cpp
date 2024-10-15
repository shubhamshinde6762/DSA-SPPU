#include <bits/stdc++.h>
using namespace std;

class Allocator;

class mBlock
{
    int memoryLocation;
    int blockSize;
    bool status;

public:
    mBlock(int _memoryLocation, int _blockSize)
        : memoryLocation(_memoryLocation), blockSize(_blockSize), status(false) {}

    friend class Allocator;

    // To sort memory blocks by size
    bool operator()(const mBlock &left, const mBlock &right)
    {
        return left.blockSize >= right.blockSize;
    }
};

class Job
{
    int jobId;
    int memoryReq;

public:
    Job(int _jobId, int _memoryReq)
        : jobId(_jobId), memoryReq(_memoryReq) {}

    friend class Allocator;
};

class Allocator
{
    queue<Job *> jq;
    vector<mBlock *> mq;
    int lastAllocatedIndex; 

public:
    Allocator() : lastAllocatedIndex(0) 
    {
        int mcnt = 0;
        cout << "Enter the Number of Memory Blocks: " << endl;
        cin >> mcnt;

        cout << "Enter Memory Location and BlockSize: " << endl;
        for (int i = 0; i < mcnt; i++)
        {
            int _memoryLocation = 0, _blockSize = 0;
            cin >> _memoryLocation >> _blockSize;
            mq.push_back(new mBlock(_memoryLocation, _blockSize));
        }

        sort(mq.begin(), mq.end(), [](mBlock *p1, mBlock *p2)
             { return p1->blockSize < p2->blockSize; });

        int jcnt = 0;
        cout << "Enter the Number of Jobs: " << endl;
        cin >> jcnt;

        cout << "Enter jobId and Memory Required: " << endl;
        for (int i = 0; i < jcnt; i++)
        {
            int _JobId = 0, _req = 0;
            cin >> _JobId >> _req;
            jq.push(new Job(_JobId, _req));
        }
    }

    void nextFit()
    {
        while (!jq.empty())
        {
            auto job = jq.front();
            jq.pop();

            int mreq = job->memoryReq;
            int originalIndex = lastAllocatedIndex;

            while (true)
            {
                if (mq[lastAllocatedIndex]->status == false && mq[lastAllocatedIndex]->blockSize >= mreq)
                {
                    mq[lastAllocatedIndex]->status = true;
                    cout << "------------------------------------------------------------" << endl;
                    cout << "Lets assign memory to Job Id: " << job->jobId << endl;
                    cout << "Allocated Memory Block at Location " << mq[lastAllocatedIndex]->memoryLocation
                         << " of Size " << mq[lastAllocatedIndex]->blockSize << " to Job Id " << job->jobId << endl;
                    break;
                }

                lastAllocatedIndex = (lastAllocatedIndex + 1) % mq.size();

                if (lastAllocatedIndex == originalIndex)
                {
                    cout << "No suitable memory block found for Job Id " << job->jobId << endl;
                    break;
                }
            }
        }
    }
};

int main()
{
    Allocator *al = new Allocator();
    al->nextFit(); 
    delete al;
    return 0;
}
