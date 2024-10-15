#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iomanip>

// g++ -std=c++11 reader_writer.cpp -o reader_writer -pthread && ./reader_writer

using namespace std;

const int nReaders = 5;
const int nWriters = 4;
int sharedVariable = 0;
int readerCount = 0;

sem_t mutex, write_lock;

void *reader(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&mutex);
    readerCount++;
    if (readerCount == 1)
    {
        sem_wait(&write_lock);
        cout << "Reader " << id << " acquired write lock. Blocking writers." << endl;
    }
    sem_post(&mutex);

    cout << "Reader " << id << " is reading. Shared Variable: " << sharedVariable << endl;

    usleep(100000);

    sem_wait(&mutex);
    readerCount--;
    cout << "Reader " << id << " finished reading. Readers remaining: " << readerCount << endl;

    if (readerCount == 0)
    {
        sem_post(&write_lock);
        cout << "Last reader " << id << " released write lock. Writers can enter." << endl;
    }
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    cout << "Writer " << id << " is waiting to write. " << endl;
    sem_wait(&write_lock);
    cout << "writer " << id << " acquired write lock. Starting to write." << endl;

    sharedVariable += 5;

    cout << "Writer " << id << " wrote. New Shared Variable : " << sharedVariable << endl;

    usleep(200000);

    sem_post(&write_lock);
    cout << "Writer " << id << " finished writing and Released Lock. " << endl;
    return NULL;
}

int main()
{
    pthread_t readers[nReaders], writers[nWriters];
    int reader_ids[nReaders], writer_ids[nWriters];

    sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);

    cout << "----------------------------------------" << endl;

    for (int i = 0; i < nReaders; i++)
    {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < nWriters; i++)
    {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < nReaders; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < nWriters; i++)
    {
        pthread_join(writers[i], NULL);
    }

    cout << "----------------------------------------" << endl;
    cout << "Final Shared Variable Value: " << sharedVariable << endl;

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}

