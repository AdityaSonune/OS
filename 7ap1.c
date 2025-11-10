#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define Max_Buff 1024

int main() {
    int fd1, fd2;
    char *myfifo1 = "myfifo1";
    char *myfifo2 = "myfifo2";
    char input[Max_Buff];
    char result[Max_Buff];

    if (mkfifo(myfifo1, 0666) == -1 && errno != EEXIST)
        perror("mkfifo1");
    if (mkfifo(myfifo2, 0666) == -1 && errno != EEXIST)
        perror("mkfifo2");

    while(1) {
        memset(input, 0, sizeof(input));
        memset(result, 0, sizeof(result));

        printf("Enter text (type 'exit' to quit):\n");
        fgets(input, Max_Buff, stdin);
        input[strcspn(input, "\n")] = 0;  // remove newline

        if(strcmp(input, "exit") == 0)
            break;

        fd1 = open(myfifo1, O_WRONLY);
        if(fd1 == -1) { perror("open fifo1"); continue; }

        write(fd1, input, strlen(input)+1);
        close(fd1);

        fd2 = open(myfifo2, O_RDONLY);
        if(fd2 == -1) { perror("open fifo2"); continue; }

        int n = read(fd2, result, Max_Buff-1);
        if(n > 0) result[n] = '\0';
        close(fd2);

        printf("Result from Process2:\n%s\n", result);
    }

    return 0;
}
