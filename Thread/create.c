#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 1024
char *buff;


void *input_thread(void *argv){
    int i=0;
    while (1)
    {
        char c=fgetc(stdin);//读取一个字符（键盘输入
        if (c && c!='\n')//字符不为0 or 换行，写入缓存
        {
            buff[i++]=c;
            if (i>=BUF_LEN)
            {
                i=0;//溢出归0
            }
            
        }
        
    }
    
}
void *output_thread(void *argv){
    int i=0;
    while (1)
    {
        if (buff[i])//buff是char类型，对应字符，因为初始化0,如果没有字符就不会进入
        {
            fputc(buff[i],stdout);//输出一个字符（内容，标准输出
            fputc('\n',stdout);   

            buff[i++]=0;
            if (i>=BUF_LEN)
            {
                i=0;//溢出归0
            }
        }else{sleep(1);}
        
    }
    
}

int main(int argc, char const *argv[])
{
    pthread_t pid_input,pid_output;
    // 分配地址并初始化
    buff=malloc(BUF_LEN);
    for (size_t i = 0; i < BUF_LEN;i++)
    {
        buff[i]=0;
    }
    
    pthread_create(&pid_input,NULL,input_thread,NULL);
    pthread_create(&pid_output,NULL,output_thread,NULL);

    // 等待进程结束
    pthread_join(pid_input,NULL);
    pthread_join(pid_output,NULL);
    free(buff);

    return 0;
}
