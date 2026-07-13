#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>


// 结果结构体
typedef struct Result{
    char *p;
    int len;
}Result;


void *red_thread(void *argv){
    Result *result=malloc(sizeof(Result));
    char code=*((char *)argv);

    //存放回信
    char *ans=malloc(101);
    while (1)
    {
        fgets(ans,100,stdin);//读取字符串（键盘输入
        if(ans[0]==code){
            // 接收到了信息
            free(ans);
            printf("red离开\n");
            char *mes=strdup("red去了宁波\n");
            // 结构体指针，存放p和len
            result->p=mes;
            result->len=strlen(mes);
            // 结束线程，输出返回值
            pthread_exit((void *)result);//结果返回出去
        }else{printf("red等待\n");}
    }
}

void *white_thread(void *argv){
    Result *result=malloc(sizeof(Result));
    char code=*((char *)argv);

    //存放回信
    char *ans=malloc(101);
    while (1)
    {
        fgets(ans,100,stdin);//读取字符串（键盘输入
        if(ans[0]==code){
            // 接收到了信息
            free(ans);
            printf("white离开\n");
            char *mes=strdup("white去了杭州\n");
            result->p=mes;
            result->len=strlen(mes);
            // 结束线程，输出返回值
            pthread_exit((void *)result);
        }else{printf("white等待\n");}
    }
}
int main()
{
    pthread_t pid_red,pid_white;
    char red_code='r',white_code='w';
    Result *red_result=NULL,*white_result=NULL;

    // 创建线程
    pthread_create(&pid_red,NULL,red_thread,&red_code);
    pthread_create(&pid_white,NULL,white_thread,&white_code);

    // 等待结果（输出result传递的数据，利用exit和join传递
    pthread_join(pid_red,(void **)&red_result);//将收到的结果放到red_result中
    printf("red结局：%s\n",red_result->p);

    // 释放内存
    free(red_result->p);
    free(red_result);
    
    // 等待结果
    pthread_join(pid_white,(void **)&white_result);
    printf("white结局：%s\n",white_result->p);

    // 释放内存
    free(white_result->p);
    free(white_result);
    
    return 0;
}
