#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *routine(void *arg)
{
    int arg_num = *(int*)arg;
}

int main()
{
    int N;
    scanf("%d", &N);

    pthread_t threads[N];
    int *threadNums[N];

    for(int i=0; i <N; i++)
    {
        threadNums[i] = malloc(sizeof(int));
        *threadNums[i] = i;

        if(pthread_create(threads + i, NULL, routine, threadNums[i]) != 0)
        {
            perror("Error creating thread");
            return 1;
        }
    }

    for(int i=0; i <N; i++)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            perror("Error joining thread");
            return 1;
        }

        free(threadNums[i]);
    }

    return 0;
}