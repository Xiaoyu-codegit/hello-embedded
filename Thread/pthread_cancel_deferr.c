#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg){
    printf("线程开始\n");
    sleep(1);
    pthread_testcancel();//取消
    printf(" 之后 结束\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    void *res;
    pthread_create(&tid,NULL,task,NULL);

    // 发送取消请求，在取消点进行取消
    if (pthread_cancel(tid)!=0)
    {
        perror("cancel err");
    }
    
    pthread_join(tid,&res);
    
    if (res==PTHREAD_CANCELED)
    {
        printf("线程已取消\n");
    }else{
        printf("线程no取消:%ld\n",(long)res);
    }
    
    
    return 0;
}
