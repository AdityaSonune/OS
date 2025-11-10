#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    sort(arr, n);  // Parent sorts array

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    if(pid == 0) { // CHILD PROCESS
        char *args[n+2];  
        args[0] = "./2bchild"; // Program to execute

        // Convert sorted numbers to string & pass as arguments
        for(i = 0; i < n; i++) {
            args[i+1] = (char *)malloc(10);
            sprintf(args[i+1], "%d", arr[i]);
        }

        args[n+1] = NULL; // Null termination

        execve("./2bchild", args, NULL);
        perror("execve failed");
    }
    else { // PARENT PROCESS
        wait(NULL);
        printf("\nParent: Child finished execution.\n");
    }

    return 0;
}
