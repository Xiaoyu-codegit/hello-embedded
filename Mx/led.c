#include <stdio.h>//基础头文件
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

//设置默认端口号
#define PORT 8888

int main() {
    //创建套接字，ipv4,tcp，
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 判断异常，输入提示
    if (server_fd == -1) { perror("socket"); return 1; }

    int opt = 1;
    //允许端口复用
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 初始化一个ipv4地址，并0清空整个结构体
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;//ipv4
    addr.sin_addr.s_addr = INADDR_ANY;//监听所有网络
    addr.sin_port = htons(PORT);//小端转大端（主机字节序-网络字节序）

    //绑定地址
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) { perror("bind"); return 1; }
    //监听，最大连接5
    if (listen(server_fd, 5) == -1) { perror("listen"); return 1; }
    // 启动后输出
    printf("server start running,port: %d\n", PORT);

    // 客户地址定义
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    //接收客户地址（服务端fd，客户端地址，客户端长度），阻塞等待连接，返回fd用于通信
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    // 判断是否成功接收
    if (client_fd == -1) { perror("accept"); return 1; }

    //缓冲数据保存地址buff
    char buf[64];
    // 读客户端发送来的数据存入buf （客户端fd，存入位子，数据大小）
    read(client_fd, buf, sizeof(buf) - 1);//-1确保有结束符，不然会崩溃或者打印为空
    // 输出接收到的数据
    printf("received: %s\n", buf);

    close(client_fd);//关闭客户端
    close(server_fd);//关闭服务端
    return 0;
}