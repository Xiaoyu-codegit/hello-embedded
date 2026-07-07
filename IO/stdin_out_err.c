#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    //format input
    char *ch=malloc(100);
    fgets(ch,100,stdin);
    printf("输入内容为:%s\n",ch);
    //format output
    fputs(ch,stdout);
    fputs(ch,stderr);
    return 0;
}
