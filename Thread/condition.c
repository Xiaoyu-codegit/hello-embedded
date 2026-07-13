#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//仓库 当前仓库产品量
int buff[5],count=0;
// 初始化锁
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void *producter(void *argv){
    // 产品编号
    int item=1;
    while (1)
    {
        // 获取互斥锁，拿不到就等（不指定谁先，看谁先拿到锁
        pthread_mutex_lock(&mutex);
        // 如果缓存满了等消费者读
        while (count==5)
        {
            // 停止线程，等待唤醒
            pthread_cond_wait(&cond,&mutex);
        }
        buff[count++]=item++;
        printf("product%d\n",buff[count-1]);

        // 唤醒等待线程
        pthread_cond_signal(&cond);
        // 释放锁让别人获取
        pthread_mutex_unlock(&mutex);
        
    }
    
}
void *consumer(void *argv){
    while (1)
    {
        // 获取互斥锁，拿不到就等
        pthread_mutex_lock(&mutex);
        // 如果缓存空了等生产者生产
        while (count==0)
        {
            // 停止线程，等待唤醒
            pthread_cond_wait(&cond,&mutex);
        }
        printf("consumer%d\n",buff[--count]);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        
    }
}
int main(int argc, char const *argv[])
{
    pthread_t product_thread,consum_thread;
    pthread_create(&product_thread,NULL,producter,NULL);
    pthread_create(&consum_thread,NULL,consumer,NULL);
    pthread_join(product_thread,NULL);
    pthread_join(consum_thread,NULL);

    return 0;
}
