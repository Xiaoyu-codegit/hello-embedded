#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT 20000

void *add_thread(void *argv){
    int *p=argv;
    (*p)++;
    return (void *)0;
}
int main(int argc, char const *argv[])
{
    pthread_t pid[COUNT];
    
    int num=0;

    for (size_t i = 0; i < COUNT; i++)
    {
        pthread_create(pid+i,NULL,add_thread,&num);
    }
    
    for (size_t i = 0; i < COUNT; i++)
    {
        pthread_join(pid[i],NULL);
    }

    printf("结果为：%d\n",num);
    return 0;
}
