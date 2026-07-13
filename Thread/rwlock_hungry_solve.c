#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data=0;

void *lock_write(void *argv){
    // 加上读写锁
    pthread_rwlock_wrlock(&rwlock);
    int tmp=shared_data+1;
    sleep(1);
    shared_data=tmp;
    printf("%s++:%d\n",(char *)argv,shared_data);
    // 释放读写锁
    pthread_rwlock_unlock(&rwlock);
}
void *lock_read(void *argv){
    // 确保读时，写不会修改
    pthread_rwlock_rdlock(&rwlock);
    printf("%s,%d\n",(char *)argv,shared_data);

    sleep(1);
    // 释放读写锁
    pthread_rwlock_unlock(&rwlock);
}
int main(int argc, char const *argv[])
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    // 设置写优先
    pthread_rwlockattr_setkind_np(&attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&rwlock,&attr);
    pthread_rwlockattr_destroy(&attr);

    pthread_t write1,write2,reader1,reader2,reader3,reader4,reader5,reader6;
    pthread_create(&write1,NULL,lock_write,"writer1");
    pthread_create(&reader1,NULL,lock_read,"reader1");
    pthread_create(&reader2,NULL,lock_read,"reader2");
    pthread_create(&reader3,NULL,lock_read,"reader3");
    pthread_create(&write2,NULL,lock_write,"writer2");
    pthread_create(&reader4,NULL,lock_read,"reader4");
    pthread_create(&reader5,NULL,lock_read,"reader5");
    pthread_create(&reader6,NULL,lock_read,"reader6");

    pthread_join(write1,NULL);
    pthread_join(write2,NULL);
    pthread_join(reader1,NULL);
    pthread_join(reader2,NULL);
    pthread_join(reader3,NULL);
    pthread_join(reader4,NULL);
    pthread_join(reader5,NULL);
    pthread_join(reader6,NULL);

    // 销毁指向的对象，释放资源
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
