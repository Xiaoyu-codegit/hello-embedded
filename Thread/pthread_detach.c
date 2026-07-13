#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg){
    printf("线程开始\n");
    sleep(2);
    printf("线程结束\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);

    // 让线程自动回收资源
    pthread_detach(tid);

    printf("主线程在工作\n");
    sleep(3);//detach不会等待子线程，防止强制终止，让主等子结束
    printf("主线程下班了\n");
    
    return 0;
}
