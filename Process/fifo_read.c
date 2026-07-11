#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path="/tmp/myfifo";
    //打开文件
    fd=open(pipe_path,O_RDONLY);
    if (fd==-1)
    {
        perror("open error");
        close(fd);
        exit(1);
    }
    char read_buf[100];
    ssize_t read_num;
    while ((read_num=read(fd,read_buf,100))>0)
    {
        write(STDOUT_FILENO,read_buf,read_num);
    }
    if (read_num<0)
    {
        perror("read");
        printf("data err");
        exit(1);
    }
    printf("接收管道推出，结束\n");
    close(fd);

    return 0;
}
