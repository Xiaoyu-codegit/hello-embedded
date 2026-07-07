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
    //get data
    char name[20];
    int age;
    char wife[20];
    while (fscanf(iofile,"%s %d %s\n",name,&age,wife)!=EOF)
    {
        printf("%s在%d爱上%s\n",name,age,wife);
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
