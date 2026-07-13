#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


int shar_num=0;

void *plusOne(void *arg){
    int tmp=shar_num+1;
    shar_num=tmp;
}
int main(int argc, char const *argv[])
{
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
    return 0;
}
