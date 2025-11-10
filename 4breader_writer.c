#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;
int read_count = 0;
int data = 0;

void* reader(void* rno) {
    int id = *((int*)rno);

    for(int i = 0; i < 5; i++) {      // <--- LIMITED LOOP
        pthread_mutex_lock(&mutex);
        read_count++;
        if(read_count == 1)
            sem_wait(&wrt);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading data = %d\n", id, data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        read_count--;
        if(read_count == 0)
            sem_post(&wrt);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* wno) {
    int id = *((int*)wno);

    for(int i = 0; i < 5; i++) {      // <--- LIMITED LOOP
        sem_wait(&wrt);

        data++;
        printf("Writer %d wrote data = %d\n", id, data);
        sleep(1);

        sem_post(&wrt);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int rno[3] = {1,2,3};
    int wno[2] = {1,2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&r[0], NULL, reader, &rno[0]);
    pthread_create(&r[1], NULL, reader, &rno[1]);
    pthread_create(&r[2], NULL, reader, &rno[2]);
    pthread_create(&w[0], NULL, writer, &wno[0]);
    pthread_create(&w[1], NULL, writer, &wno[1]);

    pthread_join(r[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(r[2], NULL);
    pthread_join(w[0], NULL);
    pthread_join(w[1], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
