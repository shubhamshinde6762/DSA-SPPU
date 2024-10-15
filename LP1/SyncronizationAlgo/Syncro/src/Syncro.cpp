#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int NUM_READERS = 5;
const int NUM_WRITERS = 2;

int shared_variable = 0;
int reader_count = 0;

sem_t mutex, write_lock;

void* reader(void* arg) {
    int id = *(int*)arg;

    sem_wait(&mutex);
    reader_count++;
    if (reader_count == 1) {
        sem_wait(&write_lock);
    }
    sem_post(&mutex);

    std::cout << "Reader " << id << " reads: " << shared_variable << std::endl;

    sem_wait(&mutex);
    reader_count--;
    if (reader_count == 0) {
        sem_post(&write_lock);
    }
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&write_lock);

    shared_variable += 5;
    std::cout << "Writer " << id << " writes: " << shared_variable << std::endl;

    sem_post(&write_lock);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&write_lock, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}

// Compilation instructions:
// g++ -std=c++11 reader_writer.cpp -o reader_writer -pthread
