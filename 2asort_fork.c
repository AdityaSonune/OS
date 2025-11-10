#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int a[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-1-i; j++) {
            if(a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void selectionSort(int a[], int n) {
    int i, j, min;
    for(i = 0; i < n-1; i++) {
        min = i;
        for(j = i+1; j < n; j++) {
            if(a[j] < a[min])
                min = j;
        }
        int temp = a[min];
        a[min] = a[i];
        a[i] = temp;
    }
}

int main() {
    int n, i;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr1[n], arr2[n];
    printf("Enter %d integers:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
        arr2[i] = arr1[i]; // copy array for child
    }

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    // Child Process
    if(pid == 0) {
        printf("\n[CHILD] Child process sorting using Selection Sort...\n");
        selectionSort(arr2, n);
        printf("[CHILD] Sorted array: ");
        for(i = 0; i < n; i++)
            printf("%d ", arr2[i]);
        printf("\n");

        // Demonstrate Orphan
        printf("[CHILD] Becoming ORPHAN, parent will exit first.\n");
        sleep(5);
        printf("[CHILD] Now parent is gone. I am adopted by INIT.\n");
    }

    // Parent Process
    else {
        printf("\n[PARENT] Parent process sorting using Bubble Sort...\n");
        bubbleSort(arr1, n);
        printf("[PARENT] Sorted array: ");
        for(i = 0; i < n; i++)
            printf("%d ", arr1[i]);
        printf("\n");

        // WAIT to avoid zombie (remove wait() to create zombie)
        printf("[PARENT] Waiting for child to finish...\n");
        wait(NULL);
        printf("[PARENT] Child completed. No ZOMBIE.\n");

        // Demonstrate Zombie (uncomment below two lines and comment above wait(NULL))
        // printf("[PARENT] Not waiting. Child will become ZOMBIE.\n");
        // sleep(10);

        printf("[PARENT] Exiting now.\n");
    }

    return 0;
}
