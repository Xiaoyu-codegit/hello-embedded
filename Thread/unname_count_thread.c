#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>


sem_t *full,*empty;
int share_num;

int rand_num(){
    // 返回1970年1.1到现在的秒数 为种子给srand
    srand(time(NULL));
    return rand();
}
void *product(){
    for (size_t i = 0; i < 5; i++)
    {
        sem_wait(empty);
        printf("==============第%d轮==============\n",i+1);
        sleep(1);
        share_num=rand_num();
        printf("生产者发送数据\n");
        sem_post(full);
    }
    
}
void *consumer(){
    for (size_t i = 0; i < 5; i++)
    {
        sem_wait(full);
        printf("消费者读数据\n");
        printf("%d\n",share_num);
        sleep(1);
        sem_post(empty);
    }
}
int main(int argc, char const *argv[])
{
    full=malloc(sizeof(sem_t));
    empty=malloc(sizeof(sem_t));

    // 初始值不一样，两个线程交替执行
    sem_init(empty,0,1);
    sem_init(full,0,0);

    pthread_t product_id,consumer_id;
    pthread_create(&product_id,NULL,product,NULL);
    pthread_create(&consumer_id,NULL,consumer,NULL);

    pthread_join(product_id,NULL);
    pthread_join(consumer_id,NULL);

    sem_destroy(full);
    sem_destroy(empty);
    return 0;
}
