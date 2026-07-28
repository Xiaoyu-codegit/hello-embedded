#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>

#define SOCKET_PATH "unix_domain.socket"
#define SERVER_MODE 1
#define CLIENT_MODE 2
#define BUF_LEN 1024

static struct sockaddr_un socket_addr;
static char *buf;

void handle_error(char *err_msg){
    perror(err_msg);   
    unlink(SOCKET_PATH);         
    exit (-1);              
}                         
void server_mode(int sockfd){
    // 服务端接收消息 收到eof结束
    int client_fd,msg_len;
    struct sockaddr_un client_addr;
    // 1.绑定
    if (bind(sockfd,(struct sockaddr *)&socket_addr,sizeof(socket_addr))<0)
    {
        handle_error("bind");
    }
    // 2.挂起监听
    if (listen(sockfd,128)<0)
    {
        handle_error("listen");
    }
    // 获取连接
    socklen_t client_len=sizeof(client_addr);
    client_fd=accept(sockfd,(struct sockaddr *)&client_addr,&client_len);
    printf("接收到客户端连接\n");
    do
    {
        memset(buf,0,BUF_LEN);
        msg_len=recv(client_fd,buf,BUF_LEN,0);
        if (strncmp(buf,"EOF",3)!=0)
        {
            printf("接收到客户端数据%s\n",buf);
            strcpy(buf,"ok\n");
        }else{
            printf("eof,停止发送\n");
        }
        send(client_fd,buf,strlen(buf),0);
    } while (strncmp(buf,"EOF",3)!=0);
    unlink(SOCKET_PATH);
}
void client_mode(int sockfd){
    int msg_len;
    // 连接服务端
    if(connect(sockfd,(struct sockaddr *)&socket_addr,sizeof(socket_addr))<0){
        handle_error("connect");
    }
    do{
        printf("请输入要发送的数据:\n");
        msg_len=read(STDIN_FILENO,buf,BUF_LEN);
        if(send(sockfd,buf,msg_len,0)<0){
            handle_error("send");
        }
        memset(buf,0,1024);
        recv(sockfd,buf,1024,0);
        printf("接收到服务端回复的信息%s\n",buf);
    }while(strncmp(buf,"EOF",3)!=0);
    shutdown(sockfd,SHUT_WR);
}
int main(int argc, char const *argv[])
{
    int fd=0,mode=0;
    // 设计结构
    // 通过mian方法传参 启动不同的客户端和服务端
    // 如果不填写参数 或者填写参数是server
    if (argc == 1 || strcmp(argv[1], "server") == 0) {
        mode = SERVER_MODE;
    } else if (strcmp(argv[1], "client") == 0) {
        mode = CLIENT_MODE;
    } else {
        perror("参数错误");
        exit(EXIT_FAILURE);
    }
    // 创建ipc通讯
    memset(&socket_addr,0,sizeof(socket_addr));
    buf=malloc(BUF_LEN);
    socket_addr.sun_family=AF_UNIX;
    strcpy(socket_addr.sun_path,SOCKET_PATH);
    fd=socket(AF_UNIX,SOCK_STREAM,0);
    if (fd<0)
    {
        handle_error("socket");
    }
    


    // 选择模式
    switch (mode)
    {
    case SERVER_MODE:
        server_mode(fd);
        break;
    case CLIENT_MODE:
        client_mode(fd);
        break;
    default:
        break;
    }

    close(fd);
    free(buf);
    return 0;
}
