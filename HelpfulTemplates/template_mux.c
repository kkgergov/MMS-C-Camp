#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t print_mux;

void *routine(void *arg)
{
    int arg_num = *(int*)arg;
    printf("Thread [%d] waiting to start:\n", arg_num);
    pthread_mutex_lock(&print_mux);
    
    pthread_mutex_unlock(&print_mux);
    printf("Thread [%d] finished.\n", arg_num);

}

int main()
{
    pthread_mutex_init(&print_mux, 0);

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

    pthread_mutex_destroy(&print_mux);

    return 0;
}