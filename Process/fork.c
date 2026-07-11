#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("当前进程id：%d\n",getpid());
    pid_t pid=fork();
    if (pid<0)
    {
        perror("进程创建失败\n");
        return 1;
    }else if(pid==0){
        printf("子进程%d的父亲是%d\n",getpid(),getppid());
    }else{
        printf("父进程%d的儿子是%d\n",getpid(),pid);
    }
    
    return 0;
}
