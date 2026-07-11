#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>

int main(int argc, char const *argv[])
{
    // 创建队列
    struct mq_attr attr;
    // 队列容量
    attr.mq_maxmsg=10;
    attr.mq_msgsize=100;
    // 用不到的配置
    attr.mq_flags=0;
    attr.mq_curmsgs=0;

    char *mq_name="/fa_son_mq";
    mqd_t mqdes=mq_open(mq_name,O_RDWR |O_CREAT,0664,&attr);
    if (mqdes==(mqd_t)-1)
    {
        perror("mqd error");
        exit(1);
    }
    
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork error");
        exit(1);
    }else if(pid==0){
        char read_buff[100];
        struct timespec time_info;
        
        for (size_t i = 0; i < 10; i++)
        {
            // 清空缓冲区
            memset(read_buff,0,100);
            // 设置等待时间
            clock_gettime(0,&time_info);
            time_info.tv_sec+=15;

            if (mq_timedreceive(mqdes,read_buff,100,NULL,&time_info)==-1)
            {
                perror("mq receive error");
            }
            printf("子进程收到数据%s\n",read_buff);
            
        }
    }else{
        char send_buff[100];
        struct timespec time_info;

        for (size_t i = 0; i < 10; i++)
        {
             // 清空缓冲区
            memset(send_buff,0,100);
            // 格式化字符串加入数组
            sprintf(send_buff,"父进程%d次发送消息\n",(int)(i+1));

            // 获取时间
            clock_gettime(0,&time_info);
            time_info.tv_sec+=5;

            if (mq_timedsend(mqdes,send_buff,strlen(send_buff),0,&time_info)==-1)
            {
                perror("mq send error");
            }
            printf("父进程发送一条消息，休息1s\n");
            sleep(1);
        }
        
    }
    close(mqdes);
    if (pid>0)
    {
        mq_unlink(mq_name);
    }
    
    return 0;
}
