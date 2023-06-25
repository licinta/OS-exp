#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    for (int i = 0; i < 2; ++i) {
        int pid = fork();
        printf("hello\n");
    }
    for (int i = 0; i < 2; ++i) {
        wait(NULL);
    }
    return 0;
}
