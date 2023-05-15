#include<unistd.h>
#include<stdio.h>
#include<string.h>
int t=1;
void say(char *words,int t){
    for(int i=0;i<t;++i){
        printf("output %s \n",words);
        usleep(1000000);
    }
}

int main(int argc,char **args){
    int p1,p2;
    p1=fork();
    p2=fork();
    if (p1!=0 &&p2!=0)
        say("a",t);
    if (p1==0&&p2!=0){
        say("b", t);
    }else{
    }
    if (p2==0&&p1!=0){
        say("c", t);
    }else{
    }
    return 0;
}

