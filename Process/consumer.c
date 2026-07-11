#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mqueue.h>
#include <unistd.h>
#include <stdlib.h>

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

    char read_buff[100];
    struct timespec time_info;

    while (1)
    {
        // 清空缓冲区    
        memset(read_buff,0,100);
        
        clock_gettime(0,&time_info);
        time_info.tv_sec+=86400;

        if (mq_timedreceive(mqdes,read_buff,100,NULL,&time_info)==-1)
        {
            perror("mq receive error");
        }
        if (read_buff[0]==EOF)
        {
            printf("接收到生产者终止信号\n");
            break;
        }
        
        printf("接受到生产者数据%s\n",read_buff);
    }
    close(mqdes);
    mq_unlink(mq_name);
    return 0;
}
