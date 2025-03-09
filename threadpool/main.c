#include <stdio.h>
#include "threadpool.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 任务函数
void taskFunc(void *arg)
{
    int num = *(int *)arg;

    printf("thread %ld is working..., number = %d, tid = %ld\n", num, pthread_self());

    usleep(1000);
}

int main()
{
    // 创建线程池
    ThreadPool *pool = ThreadPoolCreate(3, 10, 100);

    // 添加任务到线程池
    for (int i = 0; i < 100; ++i)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = i + 100;
        threadPoolAdd(pool, taskFunc, num);
    }

    sleep(30);

    // 销毁线程池
    threadPoolDestroy(pool);

    printf("All tasks have been executed.\n");

    return 0;
  
}