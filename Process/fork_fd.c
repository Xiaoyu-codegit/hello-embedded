#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd=open("io.txt",O_CREAT | O_WRONLY |O_APPEND,0664);
    if (fd==-1)
    {
        perror("open error\n");
        return 1;
    }
    char buff[1024];
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork error\n");
        return 1;
    }else if(pid==0){
        strcpy(buff,"子进程写入\n");
    }else{
        sleep(1);
        strcpy(buff,"父进程写入\n");
    }
    ssize_t writeR=write(fd,buff,strlen(buff));
    if (writeR==-1)
    {
        perror("write error\n");
        close(fd);
        return 1;
    }
    printf("写入成功\n");
    close(fd);
    if (pid==0)
    {
        printf("子写完，释放\n");
    }else{
        printf("父写完，释放\n");
    }
    
    return 0;
}
