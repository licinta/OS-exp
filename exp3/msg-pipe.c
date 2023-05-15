#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int err = 0;
int main()
{
    int pid = fork();
    if (pid == -1) {
        printf("Fork error!\n");
        return 0;
    }
    int fd[2];
    int pipeline = pipe(fd);
    if (pipeline == -1) {
        printf("Create pipe error!\n");
        return 0;
    }
    if (pid > 0) {
        char buff[20] = "Hello, ";
        char p[6];
        int ptr = 4, temp = pid;
        while (temp) {
            p[ptr--] = temp % 10 + 48;
            temp /= 10;
        }
        strcat(buff, p);
        strcat(buff, "!\n");
        close(fd[0]);
        write(fd[1], buff, strlen(buff));
        close(fd[1]);
        printf("msg has been dispatched-> %s", buff);
        wait(NULL);
    } else {
        char buff[20] = { 0 };
        close(fd[1]);
        read(fd[0], buff, 20);
        close(fd[0]);
        printf("msg has been recieved-> ");
        printf("%s", buff);
        exit(0);
    }
    return 0;
}
