#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8888
#define BUFF 1024

void *hand(void *arg) {
    int client = *(int *)arg;
    free(arg);
    char buffs[BUFF] = {0};

    // 循环读取，支持多条消息
    while (1) {
        memset(buffs, 0, BUFF);
        int bytes = read(client, buffs, BUFF);
        if (bytes <= 0) {
            break;  // 客户端断开或出错
        }else{
            FILE *fp=fopen("login.txt","a");
            if (fp)
            {
                fprintf(fp,"%s",buffs);
                fclose(fp);
            }
             printf("收到消息: %s\n", buffs);
        }

    }

    close(client);
    return NULL;
}

int main() {
    int sockfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);

    // 1. 创建 socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    // 2. 设置地址复用
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 绑定地址和端口
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("bind");
        close(sockfd);
        return -1;
    }

    // 4. 监听
    if (listen(sockfd, 5) < 0) {
        perror("listen");
        close(sockfd);
        return -1;
    }

    printf("服务端已启动，监听端口 %d\n", PORT);

    // 5. 接受客户端连接
    while (1) {
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen);

        if (*client_fd < 0) {
            perror("accept");
            free(client_fd);
            continue;
        }

        printf("客户端已连接: %s:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        pthread_t tid;
        pthread_create(&tid, NULL, hand, client_fd);
        pthread_detach(tid);
    }

    close(sockfd);
    printf("服务端关闭\n");
    return 0;
}