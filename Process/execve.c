#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *name="椰子";
    printf("%s %d现在在一楼\n",name,getpid());
    
    char *args[]={"/home/mieye/hello-embedded/Process/erlou",name,NULL};
    char *envs[]={NULL};
    
    int re=execve(args[0],args,envs);
    if (re==-1)
    {
        perror("sorry\n");
        return -1;
    }
    
    return 0;
}
