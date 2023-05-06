#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
void swap(char* a, char* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int main(void)
{
    char write_msg[BUFFER_SIZE] = { 0 };
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    pid = fork();

    if (pid < 0) {
        return 1;
    }
    if (pid > 0) {
        int t = pid;
        int ptr = 0;
        while (t) {
            write_msg[ptr++] = t % 10 + 48;
            t /= 10;
        }
        for (int i = 0; i * 2 < ptr; ++i) {
            swap(write_msg + i, write_msg + ptr - 1 - i);
        }
        printf("pid = %s, has been dispatched!\n", write_msg);
        close(fd[READ_END]);
        write(fd[WRITE_END], write_msg, BUFFER_SIZE);
        close(fd[WRITE_END]);
        wait(NULL);
    } else {
        close(fd[WRITE_END]);
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Received message: %s\n", read_msg);
        close(fd[READ_END]);
    }

    return 0;
}
