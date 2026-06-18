#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // 子进程
        printf("子进程 PID: %d\n", getpid());
        sleep(1);
        printf("子进程结束\n");
        exit(0);
    } else {
        // 父进程
        printf("父进程 PID: %d，等待子进程结束\n", getpid());
        wait(NULL);
        printf("父进程：子进程已结束\n");
    }

    return 0;
}