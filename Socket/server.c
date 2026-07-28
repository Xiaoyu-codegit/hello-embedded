#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define handle_error(cmd,result)\
    if (result<0)               \
    {                           \
        perror(cmd);            \
        return -1;              \
    }                           \
    
void *read_pthread(void * arg){
    // 使用recv接收客户端发送的数据
    char * read_buf=NULL;
    int client_fd=*(int *)arg;
    read_buf=malloc(sizeof(char)*1024);
    ssize_t count=0;
    if (!read_buf)
    {
        perror("malloc err\n");
        return NULL;
    }
    // 接收数据
    while(count=recv(client_fd,read_buf,1024,0)){
        fputs(read_buf,stdout);
    }
    printf("客户端关闭pid_read\n");
    free(read_buf);
    return NULL;

}
void *write_pthread(void * arg){
    // 接收控制台的数据 写出去
    char * write_buf=NULL;
    int client_fd=*(int *)arg;
    write_buf=malloc(sizeof(char)*1024);
    ssize_t count=0;
    if (!write_buf)
    {
        perror("malloc err\n");
        return NULL;
    }
    while(fgets(write_buf,1024,stdin)!=NULL){
        count=send(client_fd,write_buf,1024,0);
        if (count<0)
        {
            perror("send");
        }
        
    }
    printf("关闭连接\n");
    // 可具体关闭一端
    shutdown(client_fd,SHUT_WR);
    free(write_buf);
    return NULL;
}
int main(int argc, char const *argv[])
{
    int sockfd,client_fd,temp_result,listen_num;
    pthread_t pid_read,pid_write;
    struct sockaddr_in server_addr,client_addr;
    // 清空
    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));

    // 填写服务端地址
    server_addr.sin_family=AF_INET;
    // 填写ip地址 0.0.0.0
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_pton(AF_INET,"0.0.0.0",server_addr.sin_addr.s_addr);
    // 填写端口号
    server_addr.sin_port=htons(6666);

    // 创建sock流程
    // 1.socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    handle_error("socket",sockfd);
    // 2.绑定地址
    temp_result=bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    handle_error("bind",temp_result);
    // 3.进入监听状态
    listen_num=listen(sockfd,128);
    handle_error("listen",listen_num);
    // 4.获取客户端连接
    socklen_t clientlen=sizeof(client_addr);
    client_fd=accept(sockfd,(struct sockaddr *)&client_addr,&clientlen);//这个文件描述符才能收发消息，没有连接会挂起等待
    handle_error("accept",client_fd);

    printf("与客户端%s %d连接，文件描述符%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),client_fd);

    // 创建线程 收
    pthread_create(&pid_read,NULL,read_pthread,(void *)&client_fd);

    // 创建线程 发
    pthread_create(&pid_write,NULL,write_pthread,(void *)&client_fd);

    // 阻塞主线程
    pthread_join(pid_read,NULL);
    pthread_join(pid_write,NULL);

    printf("释放资源\n");
    close(client_fd);
    close(sockfd);
    return 0;
}
