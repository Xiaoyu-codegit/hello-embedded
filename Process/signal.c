#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 定义信号处理函数
void signal_hander(int signum){
    printf("\n受到%d信号，停止程序\n",signum);
    exit(signum);
}
int main(int argc, char const *argv[])
{
    if (signal(SIGINT,signal_hander)==SIG_ERR)
    {
        perror("注册失败");
        return 1;
    }
    while (1)
    {
        sleep(1);
        printf("nihao\n");
    }
    
    return 0;
}
