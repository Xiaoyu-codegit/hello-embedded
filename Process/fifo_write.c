#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path="/tmp/myfifo";

    if (mkfifo(pipe_path,0664)!=0)
    {
        perror("mkfifo error");
        if (errno!=17)
        {
            exit(1);
        }
    }
    fd=open(pipe_path,O_WRONLY);
    if (fd==-1)
    {
        perror("open");
        exit(1);
    }
    char write_buf[100];
    ssize_t read_num;

    while ((read_num=read(STDIN_FILENO,write_buf,100))>0)
    {
        write(fd,write_buf,read_num);
    }
    
    if(read_num<0){
        perror("read");
        printf("error,out!");
        close(fd);
        exit(1);
    }
    printf("发送管道已退出\n");
    close(fd);
    // 有名管道使用后清除，控制台ll /tmp/myfifo查看
    if (unlink(pipe_path)==-1)
    {
        perror("fifo unlink");
    }
    
    return 0;
}
