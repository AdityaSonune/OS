#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;   // Counts empty buffer slots
sem_t full;    // Counts filled buffer slots
pthread_mutex_t mutex; // Mutex for critical section

void* producer(void* pno) {
    int item;
    for(int i = 0; i < 5; i++) {
        item = rand() % 100; // Produce item

        sem_wait(&empty); // Decrease empty count
        pthread_mutex_lock(&mutex); // Lock buffer

        buffer[in] = item;
        printf("Producer %d produced %d at buffer[%d]\n", *((int*)pno), item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Increase full count

        sleep(1);
    }
}

void* consumer(void* cno) {
    for(int i = 0; i < 5; i++) {
        sem_wait(&full);  // Wait for filled slot
        pthread_mutex_lock(&mutex); // Enter critical section

        int item = buffer[out];
        printf("Consumer %d consumed %d from buffer[%d]\n", *((int*)cno), item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Increase empty slot count

        sleep(1);
    }
}

int main() {
    pthread_t prod[2], cons[2];
    int pno[2] = {1,2};
    int cno[2] = {1,2};

    sem_init(&empty, 0, BUFFER_SIZE); // Initially buffer empty
    sem_init(&full, 0, 0);            // No filled slots initially
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod[0], NULL, producer, &pno[0]);
    pthread_create(&prod[1], NULL, producer, &pno[1]);
    pthread_create(&cons[0], NULL, consumer, &cno[0]);
    pthread_create(&cons[1], NULL, consumer, &cno[1]);

    pthread_join(prod[0], NULL);
    pthread_join(prod[1], NULL);
    pthread_join(cons[0], NULL);
    pthread_join(cons[1], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
