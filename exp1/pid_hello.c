#include<unistd.h>
#include<stdio.h>
int main(){
    int p1=fork();
    int p2=fork();
    int p3=fork();
    printf("hello from %d,%d,%d!\n",p1,p2,p3);
    return 0;
}
