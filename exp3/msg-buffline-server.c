#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXSIZE 256
typedef struct msg {
    int mtype;
    char info[MAXSIZE];
} msg;
int main(int argc, char** args)
{
    msg m;
    int success;
    key_t key = ftok(".", 254);
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        printf("msgget error!\n");
        exit(1);
    }
    for (int i = 1; i < argc; ++i) {
        m.mtype = i;
        memset(m.info, 0, MAXSIZE);
        strcpy(m.info, args[i]);
        success = msgsnd(msgid, &m, MAXSIZE, 0);
        if (success == -1) {
            printf("msgsnd error!\n");
            exit(1);
        }
        printf("<----%s\n", m.info);
        usleep(1000000);
    }
    return 0;
}
