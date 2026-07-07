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
        printf("文件打开成功\n");
    }
    // get txt
    char fgetcR=fgetc(iofile);
    while(fgetcR!=EOF)
    {
        printf("%c\n",fgetcR);
        fgetcR=fgetc(iofile);
    }
    //close
    int closeR=fclose(iofile);
    if (closeR !=0)
    {
        printf("close error");
        return 1;
    }else{
        printf("close success\n");
    }
    return 0;
}
