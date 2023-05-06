#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#define MAXSIZE 256
typedef struct msg {
    int mtype;
    char info[MAXSIZE];
} msg;
int main()
{
    msg m;
    int success;
    key_t key = ftok(".", 254);
    m.mtype = 0;
    int msgid = msgget(key, IPC_CREAT | 0666);
    while (1) {
        success = msgrcv(msgid, &m, MAXSIZE, 0, 0);
        if (success == -1) {
            printf("msgsnd error!\n");
            exit(1);
        }
        if (success == 0) {
            continue;
        }
        if (strcmp(m.info, "end") == 0) {
            printf("End!\n");
            break;
        } else {
            printf("---->%s\n", m.info);
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
