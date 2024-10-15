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

public:
    Allocator()
    {
        int mcnt = 0;
        cout << "Enter the Number of Memory Blocks : " << endl;
        cin >> mcnt;

        cout << "Enter Memory Location and BlockSize : " << endl;
        for (int i = 0; i < mcnt; i++)
        {
            int _memoryLocation = 0, _blockSize = 0;
            cin >> _memoryLocation >> _blockSize;
            mq.push_back(new mBlock(_memoryLocation, _blockSize));
        }

        sort(mq.begin(), mq.end(), [](mBlock *p1, mBlock *p2)
             { return p1->blockSize < p2->blockSize; });

        int jcnt = 0;
        cout << "Enter the Number of Jobs : " << endl;
        cin >> jcnt;

        cout << "Enter jobId and Memory Required : " << endl;
        for (int i = 0; i < jcnt; i++)
        {
            int _JobId = 0, _req = 0;
            cin >> _JobId >> _req;
            jq.push(new Job(_JobId, _req));
        }
    }

    void bestFit()
    {
        while (!jq.empty())
        {
            auto job = jq.front();
            jq.pop();

            int mreq = job->memoryReq;
            int bestIdx = -1;
            int minSize = INT_MAX;

            for (int i = 0; i < mq.size(); i++)
            {
                if (!mq[i]->status && mq[i]->blockSize >= mreq)
                {
                    if (mq[i]->blockSize < minSize)
                    {
                        minSize = mq[i]->blockSize;
                        bestIdx = i;
                    }
                }
            }

            cout << "------------------------------------------------------------" << endl;
            cout << "Lets assign memory to Job Id : " << job->jobId << endl;

            if (bestIdx != -1)
            {
                mq[bestIdx]->status = true;
                cout << "Allocated Memory Block at Location " << mq[bestIdx]->memoryLocation
                     << " of Size " << mq[bestIdx]->blockSize << " to Job Id " << job->jobId << endl;
            }
            else
            {
                cout << "No suitable memory block found for Job Id " << job->jobId << endl;
            }
        }
    }
};

int main()
{
    Allocator *al = new Allocator();
    al->bestFit();
    delete al;
    return 0;
}
