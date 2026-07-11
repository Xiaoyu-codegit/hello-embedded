#include <stdio.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    fopen("/opt","a+");
    // 打印错误编号
    printf("errno:%d\n",errno);
    // 错误说明
    perror("error");
    return 0;
}
