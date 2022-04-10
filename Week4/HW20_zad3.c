#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

typedef struct
{
    char *msg;
    int thread_id;
    int process_id;
} info;

void *routine(void *arg)
{
    info *idmsg = (info *)arg;
    printf("Thread [%d] from process (%d) says: %s\n",
           idmsg->thread_id, idmsg->process_id, idmsg->msg);

    return NULL;
}

int main(int argc, char *argv[])
{
    int num_children = atoi(argv[1]);
    for (int i = 0; i < num_children; i++)
    {
        //printf("%d\n\n", num_children);
        int pid = fork();
        if (pid == -1)
        {
            printf("Error with creating process\n");
            return 1;
        }
        else if (pid == 0)
        {
            // Child process
            num_children = 0;
            break;
        }
        else
        {
        }
    }

    if(num_children != 0)
    {
        for (int i = 0; i < num_children; i++)
        {
            wait(NULL);
        }

        return 0;
    }

    int N = atoi(argv[2]);

    pthread_t threads[N];
    info *threadInfo[N];

    for (int i = 0; i < N; i++)
    {
        threadInfo[i] = malloc(sizeof(info));
        threadInfo[i]->thread_id = i;
        threadInfo[i]->process_id = getpid();
        threadInfo[i]->msg = argv[3];

        if (pthread_create(threads + i, NULL, routine, threadInfo[i]) != 0)
        {
            perror("Error creating thread");
            return 1;
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("Error joining thread");
            return 1;
        }

        free(threadInfo[i]);
    }

    return 0;
}