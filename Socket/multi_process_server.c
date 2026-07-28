#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>
#include <signal.h>

#define handle_error(cmd,result)\
    if (result<0)               \
    {                           \
        perror(cmd);            \
        return -1;              \
    }                           \
    
void * read_from_client_then(void * arg){
    // 读取客户端发送过来的数据 回复收到
    int client_fd=*(int * )arg;
    char * read_buf=NULL;
    char * write_buf=NULL;
    ssize_t count=0,send_count=0;

    read_buf=malloc(sizeof(char)*1024);
    write_buf=malloc(sizeof(char)*1024);

    if (!read_buf)
    {
        perror("初始化读缓冲失败");
        close(client_fd);
        perror("read_buf");
        return NULL;
    }
    if (!write_buf)
    {
        perror("初始化读缓冲失败");
        close(client_fd);
        perror("write_buf");
        return NULL;
    }
    while (count=recv(client_fd,read_buf,1024,0))
    {
        if (count<0)
        {
            perror("recv");
        }
        // 接收数据打印到控制台
        printf("从%d接收到的数据为：%s\n",client_fd,read_buf);
        // 把收到的信息写到写缓存
        strcpy(write_buf,"收到\n");
        send_count=send(client_fd,write_buf,1024,0);
        if (send_count<0)
        {
            perror("send");
        }
        
        
    }
    // 当ctrl+d退出循环
    close(client_fd);
    free(read_buf);
    free(write_buf);
    
}
void zombie_dealer(int sig){
    pid_t pid;
    int status;
    // 循环回收所有退出的子进程，避免僵尸
    while ((pid=waitpid(-1,&status,WNOHANG))>0)
    {
        if (WIFEXITED(status))
        {
            printf("子进程：%d以%d状态正常退出，已被回收\n",pid,WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){
            printf("子进程：%d被%d信号杀死，已被回收\n",pid,WTERMSIG(status));
        }else{
            printf("子进程：%d因其他原因退出，已被回收\n",pid);
        }
        
    }
    
}
int main(int argc, char const *argv[])
{
    int sockfd,temp_result,listen_num;
    struct sockaddr_in server_addr,client_addr;
    // 注册信号处理函数
    signal(SIGCLD,zombie_dealer);
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
    // 需要能够接收多个连接
    while (1)
    {
        pthread_t pid_read_write;
        socklen_t client_len=sizeof(client_addr);
        int client_fd=accept(sockfd,(struct sockaddr *)&client_addr,&client_len);
        handle_error("accept",client_fd);
        // 创建单独子进程和连接的客户端交互
        pid_t pid=fork();
        if (pid<0)
        {
            perror("fork");
        }else if(pid==0){
            // 关闭不使用的sockfd
            close(sockfd);
            printf("与%s %d建立连接%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),client_fd);
            // 从客户端读取数据并回复
            read_from_client_then((void *)&client_fd);
            // 关闭clientfd
            close(client_fd);
            exit(EXIT_SUCCESS);
        }else{
            // 关闭不使用的clientfd
            close(client_fd);
        }
        
    }
    printf("释放资源\n");
    close(sockfd);
    return 0;
}
