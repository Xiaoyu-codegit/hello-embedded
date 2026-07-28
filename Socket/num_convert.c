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
    //网络地址赋值
    // 小端（主机）低字节在前 34 12    
    //大端（网络   高字节在前 12 34
    // short 是 2 个字节（16位）
    unsigned short local_num=0x1234,network_num=0;
    network_num=htons(local_num);
    printf("主转网：0x%hX-----》0x%hX\n",local_num,network_num);

    local_num=ntohs(network_num);
    printf("网转主：0x%hX-----》0x%hX\n",network_num,local_num);

    return 0;
}
