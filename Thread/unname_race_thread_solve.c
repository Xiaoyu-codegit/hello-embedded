#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t unname_sem;
int shar_num=0;

void *plusOne(void *arg){
    // 等待 p
    sem_wait(&unname_sem);
    int tmp=shar_num+1;
    shar_num=tmp;
    // 释放 v
    sem_post(&unname_sem);
}
int main(int argc, char const *argv[])
{
    // 初始化 （值，0表非进程间，初始值
    sem_init(&unname_sem,0,1);

    pthread_t tid[10000];
    for (size_t i = 0; i < 10000; i++)
    {
        pthread_create(tid+i,NULL,plusOne, NULL);
    }
    for (size_t i = 0; i < 10000; i++)
    {
        pthread_join(tid[i], NULL);
    }
    printf("num:%d\n",shar_num);

    // 销毁
    sem_destroy(&unname_sem);
    return 0;
}
