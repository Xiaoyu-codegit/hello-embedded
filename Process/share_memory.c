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
    while (1)
    return 0;
}
