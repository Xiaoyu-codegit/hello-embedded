#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char buf[100] = {0};

    // 1. 创建管道
    pipe(fd);

    // 2. 创建子进程
    pid = fork();

    if (pid == 0) {
        // 子进程：读数据
        close(fd[1]);          // 关闭写端（用不到）
        read(fd[0], buf, sizeof(buf));
        printf("子进程收到: %s\n", buf);
        close(fd[0]);
    } else {
        // 父进程：写数据
        close(fd[0]);          // 关闭读端（用不到）
        write(fd[1], "hello from parent", 18);
        close(fd[1]);          // 写完关闭
        wait(NULL);            // 等子进程结束
    }

    return 0;
}