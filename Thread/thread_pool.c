#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void task(gpointer data, gpointer user_data) {
    int task_n = *(int *)data;
    free(data);
    printf("Executing task is: %d...\n", task_n);
    sleep(1);
    printf("Task %d completed\n", task_n);
}

int main() {
    GThreadPool *thread_pool = g_thread_pool_new(task, NULL, 5, TRUE, NULL);

    for (int i = 0; i < 10; i++) {
        int *tmp = malloc(sizeof(int));
        *tmp = i + 1;
        g_thread_pool_push(thread_pool, tmp, NULL);
    }

    g_thread_pool_free(thread_pool, FALSE, TRUE);
    printf("所有任务已提交\n");

    return 0;
}