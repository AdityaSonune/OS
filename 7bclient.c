#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;

    // Get shared memory created by server
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if(shmid < 0) {
        perror("shmget");
        return 1;
    }

    // Attach shared memory
    shm_ptr = (char*) shmat(shmid, NULL, 0);
    if(shm_ptr == (char*) -1) {
        perror("shmat");
        return 1;
    }

    printf("Client: Message from shared memory:\n%s\n", shm_ptr);

    // Detach
    shmdt(shm_ptr);

    // Remove shared memory (optional, usually done by client)
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
