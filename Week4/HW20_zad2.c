#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSIZ 100

int cmp_int(const void *vint1, const void *vint2)
{
    int int1 = *(int*)vint1;
    int int2 = *(int*)vint2;

    return int1 - int2;
}

void *routine(void *arg)
{
    char *filename = (char *)arg;
    FILE *fp = fopen(filename, "r+b");
    if(!fp)
    {
        printf("For \"%s\":\n", filename);
        perror("Could not open file");
    }

    int array[MAXSIZ];
    int n = fread(&array, sizeof(int), MAXSIZ, fp);

    qsort(array, n, sizeof(int), cmp_int);

    // for(int i =0; i < n; i++)
    // {
    //     printf("%d ", array[i]);
    // }
    // putchar('\n');

    fwrite(&array, sizeof(int), n, fp);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "Not enough arguments!\n");
        return 1;
    }

    int N = argc - 1;

    pthread_t threads[N];
    int *threadNums[N];

    for (int i = 0; i < N; i++)
    {
        threadNums[i] = malloc(sizeof(int));
        *threadNums[i] = i;

        if (pthread_create(threads + i, NULL, routine, (void*)argv[i+1]) != 0)
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

        free(threadNums[i]);
    }

    return 0;
}