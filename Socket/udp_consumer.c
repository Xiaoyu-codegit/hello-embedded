#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <unistd.h>

#define handle_error(cmd,result)\
    if (result<0)               \
    {                           \
        perror(cmd);            \
        return -1;              \
    }                           \

int main(int argc, char const *argv[])
{
    // 使用udp协议完成客户端和服务端的通信
    // eof作为关闭的信号
    int sockfd,temp_result,listen_num;
    char *buf=malloc(1024);
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

    // udp编程流程
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    handle_error("socket",sockfd);
    // 客户端不用绑定地址
    socklen_t server_len=sizeof(server_addr);
    socklen_t client_len=sizeof(client_addr);
   
    // 直接收发数据
    do
    {
        write(STDOUT_FILENO, "请输入发送的信息：\n", strlen("请输入发送的信息：\n"));
        // 从控制台读取数据
        int buf_len=read(STDIN_FILENO,buf,1023);
        sendto(sockfd,buf,buf_len,0,(struct sockaddr *)&server_addr,server_len);
        // 清空缓存区
        memset(buf,0,1024);
        int recv_len = recvfrom(sockfd, buf, 1024, 0, NULL, NULL);
        if (recv_len > 0) {
            buf[recv_len] = '\0';
        }
       
    } while (strncmp(buf,"EOF",3)!=0);
    free(buf);
    return 0;
}
