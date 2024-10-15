#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iomanip>

using namespace std;

vector<int> buff(2);
sem_t producer_lock;
sem_t consumer_lock;
const int p = 3;
const int c = 2;

void *producer(void *arg)
{
    int i = *(int *)arg;
    cout << "Producer " << i << " Waiting" << endl;
    // if (buff.size() == 2)
    //     sem_wait(&producer_lock);

    cout << "Producer " << i << " Produced ------------" << endl;
    buff.push_back(5);
    usleep(10000);

    if (buff.size() == 2)
    {
        cout << "Producer Lock by : " << i << endl;
        sem_post(&consumer_lock);
        sem_wait(&producer_lock);
    }

    return NULL;
}

void *consumer(void *arg)
{
    int i = *(int *)arg;
    cout << "Consumer " << i << " Waiting" << endl;
    // if (buff.size() == 0)
    //     sem_wait(&consumer_lock);

    cout << "Consumer " << i << " consumed ----------" << endl;
    buff.pop_back();
    usleep(10000);

    if (buff.size() == 0)
    {
        cout << "Consumer Lock by : " << i << endl;
        sem_post(&producer_lock);
        sem_wait(&consumer_lock);
    }

    return NULL;
}

int main()
{
    if (p < c || p - c > 2)
    {
        cout << "Wrong count " << endl;
        return 0;
    }
    void *(*arg);
    pthread_t pro[p], cons[c];
    sem_init(&producer_lock, 0, 1);
    sem_init(&consumer_lock, 0, 1);
    int pro_id[p], cons_id[c];

    for (int i = 0; i < p; i++)
    {
        pro_id[i] = i;
        pthread_create(&pro[i], NULL, producer, &pro_id[i]);
    }

    for (int i = 0; i < c; i++)
    {
        cons_id[i] = i;
        pthread_create(&cons[i], NULL, consumer, &cons_id[i]);
    }

    for (int i = 0; i < p; i++)
    {
        pthread_join(pro[i], NULL);
    }

    for (int i = 0; i < c; i++)
    {
        pthread_join(cons[i], NULL);
    }

    return 0;
}
