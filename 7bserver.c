#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;

    // Create shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
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

    printf("Enter message to write to shared memory: ");
    fgets(shm_ptr, SHM_SIZE, stdin);

    printf("Server: Message written to shared memory.\n");

    // Detach
    shmdt(shm_ptr);

    return 0;
}
