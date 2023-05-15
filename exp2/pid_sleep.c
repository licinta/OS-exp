#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
int main(){
    int pid=fork();
    if(pid==0){
        printf("Parrent pid is %d\n",getppid());
        sleep(1);
    }else{
        int stat=0;
        pid=wait(&stat);
        printf("Child pid is %d\n",pid);
    }
    return 0;
}
