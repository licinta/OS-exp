#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main()
{
    int shmid, pid;
    char* shmaddr;
    key_t key = ftok(".", 'a');
    // 创建共享存储区

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget error\n");
        exit(1);
    }

    // 连接共享存储区
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char*)-1) {
        perror("shmat error\n");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork error!\n");
        exit(1);
    }

    if (pid) {
        // 使用共享存储区
        sprintf(shmaddr, "%d", pid);
        printf("<-- %d\n", pid);
        wait(NULL);
        // 分离共享存储区
        if (shmdt(shmaddr) == -1) {
            perror("shmdt error");
            exit(1);
        }

        // 删除共享存储区
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl error");
            exit(1);
        }
    } else {
        int p;
        sscanf(shmaddr, "%d", &p);
        printf("--> %d\n", p);
    }

    return 0;
}
