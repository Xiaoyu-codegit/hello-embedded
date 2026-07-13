#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    char *shm_name="unname_bin_process";
    // 创建共享内存
    int fd=shm_open(shm_name,O_CREAT | O_RDWR,0666);
    // 调整大小
    ftruncate(fd,sizeof(int));
    // 映射
    int *vlaue=mmap(NULL,sizeof(int),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
    // 初始化共享变量的值
    *vlaue=0;

    int pid=fork();
    if (pid<0)
    {
        perror("fork");
    }else if(pid==0){
        int tmp=*vlaue+1;
        sleep(1);
        *vlaue=tmp;
    }else{
        int tmp=*vlaue+1;
        sleep(1);
        *vlaue=tmp;

        waitpid(pid,NULL,0);
        printf("父进程等待子进程\n");
        printf("%d\n",*vlaue);
    }
    
    if (munmap(vlaue,sizeof(int))==-1)
    {
        perror("munmap");
    }

    if (close(fd)==-1)
    {
        perror("clock");
    }
    
    if (pid>0)
    {
        if (shm_unlink(shm_name)==-1)
        {
            perror("shm_unlink");
        }
        
    }
    
    return 0;
}
