#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

int shopSize = 10;
int consumers = 6;
int producers = 5;
FILE *fp = NULL;

int programIsRunning = 1;

typedef enum
{
    RAKIYA,
    WHISKEY,
    SCOTCH,
    BOURBUN,
    RUM,
    SOFTBEVERAGE,
    CRACKERS,
    CHEESE,
    MEAT,
    SLANINA
} product_type;

char *typemap[10] = {
    "RAKIYA",
    "WHISKEY",
    "SCOTCH",
    "BOURBUN",
    "RUM",
    "SOFTBEVERAGE",
    "CRACKERS",
    "CHEESE",
    "MEAT",
    "SLANINA"
};

typedef struct lnode
{
    unsigned barcode;
    product_type type;
    double price;
    struct lnode *next;
} listNode;

listNode *buffer = NULL;
int buffersize = 0;

void push_front(unsigned p_bc, product_type p_type, double p_price)
{
    listNode *newNode = malloc(sizeof(listNode));
    newNode->barcode = p_bc;
    newNode->type = p_type;
    newNode->price = p_price;
    newNode->next = buffer;
    buffer = newNode;

    buffersize++;
}

void remove_at(int idx)
{
    if (idx == 0)
    {
        listNode *temp = buffer;
        buffer = buffer->next;
        printf("(%d,%s,%.2lf) at index %d.\n", temp->barcode, typemap[temp->type], temp->price, idx);
        free(temp);
        buffersize--;
        return;
    }

    listNode *first = buffer, *second = buffer->next;
    for (int i = 1; i < idx; i++)
    {
        first = first->next;
        second = second->next;
    }

    first->next = second->next;

    printf("(%d,%s,%.2lf) at index %d.\n", second->barcode, typemap[second->type], second->price, idx);
    free(second);


    buffersize--;
}

pthread_mutex_t buff_mux;
sem_t fullPos;
sem_t emptyPos;

void *produce(void *arg)
{
    while (1)
    {
        if(!programIsRunning)
        {
            sem_post(&fullPos);
            break;
        }

        sleep(1);
        sem_wait(&emptyPos);
        pthread_mutex_lock(&buff_mux);

        push_front(rand(), rand() % 10, 1 + ((double)rand() / RAND_MAX) * 99);
        printf("> Producer [%d] produced product (%d,%s,%.2lf).\n",
               *(int *)arg, buffer->barcode, typemap[buffer->type], buffer->price);

        pthread_mutex_unlock(&buff_mux);
        sem_post(&fullPos);
    }
    printf("Producer [%d] terminated.\n", *(int *)arg);
}

void *consume(void *arg)
{
    while (1)
    {
        if(!programIsRunning)
        {
            sem_post(&emptyPos);
            break;
        }

        sleep(1);
        sem_wait(&fullPos);
        pthread_mutex_lock(&buff_mux);

        int index = rand()%buffersize;
        printf("> Consumer [%d] consumed product ", *(int *)arg);
        remove_at(index);

        pthread_mutex_unlock(&buff_mux);
        sem_post(&emptyPos);
    }
    printf("Consumer [%d] terminated.\n", *(int *)arg);
}

listNode *read_list_from_file(FILE *fp)
{
    listNode tempNode;
    listNode *newNode = NULL;

    if(fread(&tempNode, sizeof(listNode), 1, fp))
    {
        newNode = malloc(sizeof(listNode));
        newNode->barcode = tempNode.barcode;
        newNode->type = tempNode.type;
        newNode->price = tempNode.price;
        newNode->next = read_list_from_file(fp);
        buffersize++;
    }
    
    return newNode;
}

void write_buff_to_file()
{
    char *o_filename = "shopInfo.data";
    printf("\nWriting list to a file...\n");
    fp = fopen(o_filename, "wb");
    if(fp == NULL)
    {
        printf("Could not open file for writing");
    }
    else
    {
        listNode *current = buffer;
        while(current)
        {
            fwrite(current, sizeof(listNode), 1, fp);
            current = current->next;
        }
        fclose(fp);
        sleep(0.5);
        printf("Done!\n");
    }
}

void deleteList()
{
    printf("Deleting list...\n");
    while(buffer)
    {
        listNode *temp = buffer;
        buffer = buffer->next;
        free(temp);
    }
    printf("Done!\n");
}

void handle_sigint()
{
    programIsRunning = 0;
}

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        shopSize = atoi(argv[1]);
    }
    if (argc >= 3)
    {
        consumers = atoi(argv[2]);
    }
    if (argc >= 4)
    {
        producers = atoi(argv[3]);
    }
    if (argc >= 5)
    {
        printf("Reading list from file...\n");
        fp = fopen(argv[4], "rb");
        if (fp == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        buffer = read_list_from_file(fp);
        if(shopSize < buffersize)
        {
            printf("Buffer from file is bigger, resizing...\n");
            shopSize = buffersize;
        }
        fclose(fp);
        printf("Done!\n");
    }

    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_INTERRUPT;
    sigaction(SIGINT, &sa, NULL);

    sem_init(&emptyPos, 0, shopSize);
    sem_init(&fullPos, 0, 0);
    pthread_mutex_init(&buff_mux, 0);

    int number_of_threads = consumers + producers;
    pthread_t th[number_of_threads];
    int *threadNum[number_of_threads];

    for (int i = 0; i < producers; i++)
    {
        threadNum[i] = malloc(sizeof(int));
        *threadNum[i] = i+1;

        if (pthread_create(th + i, NULL, produce, threadNum[i]) != 0)
        {
            perror("thread create error");
            return 1;
        }
    }

    for (int i = producers; i < producers + consumers; i++)
    {
        threadNum[i] = malloc(sizeof(int));
        *threadNum[i] = i - producers + 1;

        if (pthread_create(th + i, NULL, consume, threadNum[i]) != 0)
        {
            perror("thread create error");
            return 1;
        }
    }

    for (int i = 0; i < number_of_threads; i++)
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

    //printf("GOT HERE\n\n\n");
    write_buff_to_file();
    deleteList();

    printf("Bye Bye!\n");
    return 0;
}