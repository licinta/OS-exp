#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int myglobal;
pthread_mutex_t mytmutex=PTHREAD_MUTEX_INITIALIZER;
void *thread_function(void *args){
    int i,j;
    for (int i=0;i<100000000;++i){
        pthread_mutex_lock(&mytmutex);
        j=myglobal;
        j++;
        //printf("added one . myglobal = %d\n",myglobal);
        //fflush(stdout);
        //usleep(10000);
        myglobal=j;
        pthread_mutex_unlock(&mytmutex);
    }
    return NULL;
}


int main(){
    pthread_t mythread;
    if(pthread_create(&mythread,NULL,thread_function,NULL)){
        printf("error create");
        abort();
    }
    pthread_t mythread2;
    if(pthread_create(&mythread2,NULL,thread_function,NULL)){
        printf("error create");
        abort();
    }
    for(int i=0;i<100000000;++i){
        pthread_mutex_lock(&mytmutex);
        myglobal++;
        pthread_mutex_unlock(&mytmutex);
        //printf("added one . myglobal = %d\n",myglobal);
        //fflush(stdout);
        //usleep(10000);
    }
    if(pthread_join(mythread,NULL)){
        printf("error joinning");
        abort();
    }
    if(pthread_join(mythread2,NULL)){
        printf("error joinning");
        abort();
    }
    printf("myglobal = %d\n",myglobal);
    exit(0);
}



