#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    // 网络地址赋值
    struct sockaddr_in server_addr;
    struct in_addr server_in_addr;
    in_addr_t server_in_addr_t;
    memset(&server_addr,0,sizeof(server_addr));
    memset(&server_in_addr,0,sizeof(server_in_addr));
    memset(&server_in_addr_t,0,sizeof(server_in_addr_t));
    
    // 打印16进制为参考 %x十六进制输出符
    printf("192.168.6.101:  0x%X 0x%X 0x%X 0x%X\n",192,168,6,101);

    //  点分十进制 ---》 二进制
    server_in_addr_t=inet_addr("192.168.6.101");
    printf("inet addr convert:0x%X\n",server_in_addr_t);

    //  点分十进制 ---》 二进制  ，结果存in_addr结构体，更安全
    inet_aton("192.168.6.101",&server_in_addr);
    printf("inet aton convert:0x%X\n",server_in_addr.s_addr);

    // 和上面aton一样，支持ipv6,更规范
    inet_pton(AF_INET,"192.168.6.101",&server_addr.sin_addr);
    printf("inet pton 后:0x%X\n",server_addr.sin_addr.s_addr);

    // 二进制 ---》点分十进制
    printf("打印转换后：%s\n",inet_ntoa(server_addr.sin_addr));

    // 提取本机低地址 101
    printf("local:0x%X\n",inet_lnaof(server_addr.sin_addr));

    // 提取本机高地址 192.168.6
    printf("number:0x%X\n",inet_netof(server_addr.sin_addr));

    // 网络和主机地址拼接,102取代101
    server_addr.sin_addr=inet_makeaddr(inet_netof(server_addr.sin_addr),102);

    printf("inet_makeaddr:0x%X\n",server_addr.sin_addr.s_addr);

    printf("拼接：%s\n",inet_ntoa(server_addr.sin_addr));
    return 0;
}
