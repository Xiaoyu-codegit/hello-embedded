#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT 20000

// 静态初始化，不需要显式销毁锁
static pthread_mutex_t count_mutex=PTHREAD_MUTEX_INITIALIZER;

void *add_thread(void *argv){
    int *p=argv;
    // 添加互斥锁
    pthread_mutex_lock(&count_mutex);
    (*p)++;
    // 释放互斥锁
    pthread_mutex_unlock(&count_mutex);
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
