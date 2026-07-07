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
    //write
    int putcR=fputc(97,iofile);
    if (putcR==EOF)
    {
        printf("写入失败");
    }else{
        printf("写入成功");
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
