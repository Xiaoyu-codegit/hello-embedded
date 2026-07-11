#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    char *share;
    pid_t pid;
    char shmName[100]={0};
    sprintf(shmName,"/letter%d",getpid());
    int fd;
    // 创建共享内存
    fd=shm_open(shmName,O_CREAT | O_RDWR,0644);
    if (fd<0)
    {
        perror("share error");
        exit(1);
    }
    // 扩展内存
    ftruncate(fd,100);
    // 内存映射
    share=mmap(NULL,100,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    if (share==MAP_FAILED)
    {
        perror("共享内存映射失败\n");
        exit(1);
    }
    close(fd);

    pid=fork();
    if (pid==0){
        strcpy(share,"我是子进程\n");
        printf("子进程%d完成通信\n",getpid());
    }else{
        sleep(1);
        printf("父进程%d看到子%d的消息：%s",getpid(),pid,share);
        wait(NULL);

        // 释放映射
        int ret=munmap(share,100);
        if (ret==-1)
        {
            perror("munmap error");
            exit(1);
        }
    }

    // 删除共享内存对象
    shm_unlink(shmName);
    return 0;
}
