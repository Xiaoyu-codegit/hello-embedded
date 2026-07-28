#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    FILE * file=fopen("io.txt","w");

    // 修改刷写模式(无缓冲，直接写入)
    setvbuf(file,NULL,_IONBF,0);//行缓冲，_IOLBF，直接执行没有，hello\n满足条件
    // 文件写入默认全缓冲，缓冲不满不会写入（IO文件会没有内容，采取上下两种方法解决）
    fprintf(file,"hello");
    // 可以使用手动刷写
    // fflush(file);
    char *args[]={"/usr/bin/ping","-c","1","www.baidu.com",NULL};
    char *envs[]={NULL};
    execve(args[0],args,envs);

    // 如果跳转失败
    perror("execve");

    return 0;
}
