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

    // 初始化信号量
    sem_t *sem=sem_open(sem_name,O_CREAT,0666,0);

    pid_t pid=fork();

    if (pid<0)
    {
        perror("fork");
    }else if(pid==0){
        sleep(1);
        printf("son\n");
        sem_post(sem);//父子交替执行，子先
         // 关闭信号量连接
        sem_close(sem);
    }else{
        sem_wait(sem);
        printf("father\n");
        waitpid(pid,NULL,0);
        // 关闭信号量连接
        sem_close(sem);
        if (sem_unlink(sem_name)==-1)
        {
            perror("sem un");
        }
    }

    return 0;
}
