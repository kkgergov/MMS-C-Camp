#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define COUNT 30
#define SIZEBUFFER 50

int buffer[SIZEBUFFER];
int topBuff = 0;

pthread_mutex_t buff_mux;
sem_t fullPos;
sem_t emptyPos;

void *produce(void *arg)
{
    while (1)
    {
        sleep(1);
        sem_wait(&emptyPos);
        pthread_mutex_lock(&buff_mux);

        buffer[topBuff] = 1 + rand() % 10;
        printf("Producer [%d] produced %d.\n", *(int*)arg, buffer[topBuff]);
        topBuff++;

        pthread_mutex_unlock(&buff_mux);
        sem_post(&fullPos);
    }
}

void *consume(void *arg)
{
    while(1)
    {
        sleep(1);
        sem_wait(&fullPos);
        pthread_mutex_lock(&buff_mux);

        printf("Consumer [%d] consumed %d.\n", *(int*)arg, buffer[topBuff-1]);
        topBuff--;

        pthread_mutex_unlock(&buff_mux);
        sem_post(&emptyPos);
    }
}

int main()
{
    sem_init(&emptyPos,0, SIZEBUFFER);
    sem_init(&fullPos, 0, 0);
    pthread_mutex_init(&buff_mux, 0);

    pthread_t th[COUNT];
    int *threadNum[COUNT];

    for (int i = 0; i < COUNT; i++)
    {
        threadNum[i] = malloc(sizeof(int));
        *threadNum[i] = i;

        if (i % 2 == 0)
        {
            if (pthread_create(th + i, NULL, consume, threadNum[i]) != 0)
            {
                perror("thread create error");
                return 1;
            }
        }
        else
        {
            if (pthread_create(th + i, NULL, produce, threadNum[i]) != 0)
            {
                perror("thread create error");
                return 1;
            }
        }
    }

    for (int i = 0; i < COUNT; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("thread join error");
            return 1;
        }

        free(threadNum[i]);
    }

    sem_destroy(&fullPos);
    sem_destroy(&emptyPos);
    pthread_mutex_destroy(&buff_mux);

    return 0;
}