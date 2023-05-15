#include<unistd.h>
#include<stdio.h>
int main(){
    for(int i=0;i<2;++i){
        int pid=fork();
        printf("hello\n");
    }
    for(int i=0;i<2;++i){
        wait();
    }
    return 0;
}
