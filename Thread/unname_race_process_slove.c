#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>


int main(int argc, char const *argv[])
{
    // 两个目的一个管数据，一个管信号量
    char *shm_sem="unname_bin_process_sem";
    char *shm_name="unname_bin_process";
    // 创建共享内存
    int sem_fd=shm_open(shm_sem,O_CREAT | O_RDWR,0666);
    int fd=shm_open(shm_name,O_CREAT | O_RDWR,0666);
    // 调整大小
    ftruncate(sem_fd,sizeof(sem_t));
    ftruncate(fd,sizeof(int));
    // 映射
    sem_t *sem=mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE,MAP_SHARED,sem_fd,0);
    int *vlaue=mmap(NULL,sizeof(int),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
    // 初始化共享变量的值
    sem_init(sem,1,1);//进程通信第二个为1,为0进程会卡死
    *vlaue=0;

    int pid=fork();
    if (pid<0)
    {
        perror("fork");
    }else if(pid==0){
        sem_wait(sem);
        int tmp=*vlaue+1;
        sleep(1);
        *vlaue=tmp;
        sem_post(sem);
    }else{
        sem_wait(sem);
        int tmp=*vlaue+1;
        sleep(1);
        *vlaue=tmp;
        sem_post(sem);

        waitpid(pid,NULL,0);
        printf("父进程等待子进程\n");
        printf("%d\n",*vlaue);
    }
    if (pid>0)
    {
        // 销毁信号量
        if (sem_destroy(sem)==-1)
        {
            perror("sem destroy");
        }
        
    }
    


    if (munmap(sem,sizeof(sem))==-1)
    {
        perror("munmap sem");
    }
    if (munmap(vlaue,sizeof(int))==-1)
    {
        perror("munmap");
    }

    if (close(sem_fd)==-1)
    {
        perror("clock");
    }
    if (close(fd)==-1)
    {
        perror("clock");
    }
    
    if (pid>0)
    {
        if (shm_unlink(shm_sem)==-1)
        {
            perror("shm_unlink");
        }
        if (shm_unlink(shm_name)==-1)
        {
            perror("shm_unlink");
        }
        
    }
    
    return 0;
}
