#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    char *iofile="io.txt";
    int fd=open(iofile,O_RDONLY);//only read
    if (fd==-1)
    {
        perror("fd");
        exit(1);
    }
    char buff[100];
    ssize_t readR;
    while ((readR=read(fd,buff,sizeof(buff)))>0)
    {
        write(STDOUT_FILENO,buff,readR);
    }
    if (readR==-1)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    return 0;
}
