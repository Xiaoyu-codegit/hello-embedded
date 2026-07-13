#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    char *shm_name="unname_count_process";

    int fd=shm_open(shm_name,O_CREAT | O_RDWR,0666);
    ftruncate(fd,sizeof(sem_t));
    sem_t *sem=mmap(NULL,sizeof(sem_t),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
    sem_init(sem,1,0);

    int pid=fork();
    if (pid>0)
    {
        sem_wait(sem);//为0阻塞
        printf("父亲\n");
        waitpid(pid,NULL,0);
    }else if(pid==0){
        sleep(1);
        printf("儿子\n");
        sem_post(sem);
    }else{
        perror("fork");
    }
    
    // 销毁信号量
    if (pid>0)
    {
        if (sem_destroy(sem)==-1)
        {
            perror("destory");
        }
    }
    
    // 解除映射
    if (munmap(sem,sizeof(sem))==-1)
    {
        perror("munmap");
    }
    close(fd);
    if(pid>0){
        shm_unlink(shm_name);
    }
    
    return 0;
}
