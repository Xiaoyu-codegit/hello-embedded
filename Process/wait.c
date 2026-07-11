#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int formal_status;
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork erorr\n");
        return 1;
    }else if(pid==0){
        char *args[]={"/usr/bin/ping","-c","5","www.baidu.com",NULL};
        char *envs[]={NULL};
        printf("子%d联系5次\n",getpid());
        int exR=execve(args[0],args,envs);
        if (exR<0)
        {
            perror("execve\n");
            return 1;
        }   
    }else{
        printf("父%d等待子%d\n",getpid(),pid);
        waitpid(pid,&formal_status,0);
    }
    printf("父等待子完成\n");
    return 0;
}
