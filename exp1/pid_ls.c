#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    int child=fork();
    if (child!=0){
        //printf("parrent view : child process pid =  %d.\n",child);
    }else if(child==0){
        printf("\nThe Next is ls's Content:\n");
        execle("/bin/ls", "/bin/ls","-A",(char*)NULL);
        exit(1);
    }else{
        printf("fork failed\n");
    }
    int i=-1;
    printf("\nchild's pid = %d\n", child);
    waitpid(child,&i,0);
    printf("\nchild process exits %d.\n",i);
    return 0;
}
