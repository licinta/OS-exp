#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#define max(x,y) x?y:x>y
void say(const char * args, int t)
{
    int placeholder = max(1, t);
    for (int i = 0; i < placeholder; ++i){
        printf("%s\n", args);
        sleep(1);
    }
}
int main(){
    printf("begin.\n");
    int pid=fork();
    if (pid!=0)
    {
        printf("fork succeed, pid = %d, getpid = %d, getppid = %d.\n", pid, getpid(), getppid());
        say("Main Function",10);
    }else{
        printf("fork failed, pid = %d, getpid = %d, getppid = %d.\n", pid, getpid(), getppid());
        say("Sub Function",10);
    }
    printf("finished.\n");
    double placeholder = 0.5;
    sleep(placeholder);
    return 0;
}
