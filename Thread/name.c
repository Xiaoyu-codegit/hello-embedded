#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

int main(int argc, char const *argv[])
{
    // 有名信号量前面有 /
    char *sem_name="/name_sem";
    char *shm_name="/name_shm";

    // 初始化信号量
    sem_t *sem=sem_open(sem_name,O_CREAT,0666,1);

    // 初始化内存共享
    int fd=shm_open(shm_name,O_CREAT|O_RDWR,0666);

    ftruncate(fd,sizeof(int));

    // 映射
    int *value=mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

    // 初始化共享变量指针指向的值
    *value=0;
    pid_t pid=fork();

    if (pid<0)
    {
        perror("fork");
    }
    
    sem_wait(sem);
    int tmp=*value+1;
    sleep(1);
    *value=tmp;
    sem_post(sem);

    // 关闭信号量连接
    sem_close(sem);
    if (pid>0)
    {
        waitpid(pid,NULL,0);
        printf("子进程结束%d\n",*value);

        // 有名信号只能取消一次
        sem_unlink(sem_name);

    }
    munmap(value,sizeof(int));
    close(fd);

    if (pid>0)
    {
        if (shm_unlink(shm_name)==-1)
        {
            perror("shm un");
        }
        
    }
    

    return 0;
}
