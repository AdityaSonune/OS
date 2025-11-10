#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define Max_Buff 1024

int main() {
    int fd1, fd2;
    char *myfifo1 = "myfifo1";
    char *myfifo2 = "myfifo2";
    char input[Max_Buff];
    char result[Max_Buff];

    // Create FIFOs if they don't exist
    if (mkfifo(myfifo1, 0666) == -1 && errno != EEXIST)
        perror("mkfifo1");
    if (mkfifo(myfifo2, 0666) == -1 && errno != EEXIST)
        perror("mkfifo2");

    while (1) {
        memset(input, 0, sizeof(input));
        memset(result, 0, sizeof(result));

        // Read message from Process1
        fd1 = open(myfifo1, O_RDONLY);
        if (fd1 == -1) { perror("open fifo1"); continue; }

        int n = read(fd1, input, Max_Buff-1);
        if (n > 0) input[n] = '\0';
        close(fd1);

        // Check for exit
        if (strcmp(input, "exit") == 0)
            break;

        // Simple processing: convert to uppercase
        for (int i = 0; i < strlen(input); i++)
            result[i] = toupper(input[i]);
        result[strlen(input)] = '\0';

        // Write result back to Process1
        fd2 = open(myfifo2, O_WRONLY);
        if (fd2 == -1) { perror("open fifo2"); continue; }

        write(fd2, result, strlen(result)+1);
        close(fd2);
    }

    return 0;
}
