#include <stdio.h>
int main(int argc, char const *argv[])
{
    //open
    char *filename="io.txt";
    FILE *iofile=fopen(filename,"a+");
    if (iofile==NULL)
    {
        printf("文件打开失败");
    }else{
        printf("文件打开成功");
    }
    //format printf
    char *name="椰子";
    int fprintfR=fprintf(iofile,"格式化字符串:%s\n",name);
    if (fprintfR==EOF)
    {
        printf("printf error\n");
    }else{
        printf("printf success\n");
    }
    //close
    int closeR=fclose(iofile);
    if (closeR !=0)
    {
        printf("close error");
    }else{
        printf("close success");
    }
    return 0;
}
