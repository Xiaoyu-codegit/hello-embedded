#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    char *name="椰子";
    printf("%s %d现在在一楼\n",name,getpid());
    
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork error\n");
    }else if(pid==0){
        char *name="叶子";
        char *args[]={"/home/mieye/hello-embedded/Process/erlou",name,NULL};
        char *envs[]={NULL};
        int re=execve(args[0],args,envs);
        if (re==-1)
        {
            perror("sorry\n");
            return -1;
        }
    }else{
        printf("父亲%d邀请%d\n",getpid(),pid);
    }
    
    
    
    
    
    return 0;
}
