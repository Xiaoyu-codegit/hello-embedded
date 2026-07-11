#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc !=2)
    {
        //没有传递数据会执行该条输出
        fprintf(stderr,"%s填写传递信息：\n",argv[0]);
        exit(1);
    }
    if (pipe(pipefd)==-1)
    {
        perror("创建管道失败\n");
        exit(1);
    }
    cpid=fork();
    if (cpid==0)
    {
        close(pipefd[1]);
        char str[100]={0};
        sprintf(str,"子进程%d收到\n",getpid());
        write(STDOUT_FILENO,str,sizeof(str));
        while (read(pipefd[0],&buf,1)>0)
        {
            //将读到的数据输出来
            write(STDOUT_FILENO,&buf,1);
        }
        write(STDOUT_FILENO,"\n",1);
        close(pipefd[0]);
        _exit(0);
    }else{
        close(pipefd[0]);
        printf("父进程%d收到\n",getpid());
        write(pipefd[1],argv[1],strlen(argv[1]));
        
        close(pipefd[1]);
        waitpid(cpid,NULL,0);
        _exit(0);
    }
    
    
    return 0;
}
