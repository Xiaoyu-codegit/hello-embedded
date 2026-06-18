#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>

#define PORT 8888
#define BUFFER_SIZE 1024

void *hand(void *arg){
    // 6. 接收并回复
    int client_fd=*(int *)arg;
    free(arg);
    char buffer[BUFFER_SIZE] = {0};

    int bytes = read(client_fd, buffer, BUFFER_SIZE);
    if (bytes > 0) {
        printf("收到消息: %s\n", buffer);
        write(client_fd, buffer, bytes);
    }
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    

    // 1. 创建 socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }

    // 2. 设置地址复用（方便快速重启）
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 绑定地址和端口
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // 4. 监听
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("服务端已启动，监听端口 %d\n", PORT);

    // 5. 接受客户端连接
    while (1)
    {
        int *client_fd_ptr = malloc(sizeof(int));
        *client_fd_ptr = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (*client_fd_ptr == -1) {
            perror("accept");
            free(client_fd_ptr);
            continue;
        }
        printf("客户端已连接: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        pthread_t tid;
        pthread_create(&tid,NULL,hand,client_fd_ptr);
        pthread_detach(tid);
        
    }
    
    // 7. 关闭连接
    close(server_fd);

    printf("服务端关闭\n");
    return 0;
}