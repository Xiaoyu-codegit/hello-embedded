#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mqueue.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *mq_name="/pc_mq";
    struct mq_attr attr;
    // 队列容量
    attr.mq_maxmsg=10;
    attr.mq_msgsize=100;
    // 用不到的配置
    attr.mq_flags=0;
    attr.mq_curmsgs=0;

    mqd_t mqdes=mq_open(mq_name,O_RDWR |O_CREAT,0664,&attr);
    if (mqdes==(mqd_t)-1)
    {
        perror("mqd error");
        exit(1);
    }

    char write_buff[100];
    struct timespec time_info;

    while (1)
    {
        // 清空缓冲区    
        memset(write_buff,0,100);

        ssize_t read_c=read(0,write_buff,100);
        if (read_c==-1)
        {
            perror("read");
            continue;
        }
        clock_gettime(0,&time_info);
        time_info.tv_sec+=5;

        if (read_c==0)
        {
            printf("接收...\n");
            char eof=EOF;
            if (mq_timedsend(mqdes,&eof,1,0,&time_info)==-1)
            {
                perror("mq send error");
            }
        }
        
        if (mq_timedsend(mqdes,write_buff,strlen(write_buff),0,&time_info)==-1)
        {
            perror("mq send error");
        } 
        printf("收到数据，发送至消费者\n");
    }
    close(mqdes);

    return 0;
}
