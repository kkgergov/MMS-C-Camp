#include <stdio.h>
#include <stdlib.h>

typedef struct dnode{
    int data;
    struct dnode *prev, *next;
} listNode;

void push_front(listNode **head, listNode **tail, int val)
{
    listNode *newNode = (listNode*)malloc(sizeof(listNode));
    newNode->prev = NULL;
    newNode->data = val;

    newNode->next = *head;

    if(*head == NULL)//if head is null, then tail is null
    {
        *tail = newNode;
        *head = newNode;
    }
    {
        (*head)->prev = newNode;
        *head = newNode;
    }
}

void push_back(listNode **head, listNode **tail, int val)
{
    listNode *newNode = (listNode*)malloc(sizeof(listNode));

    newNode->next = NULL;
    newNode->data = val;
    newNode->prev = *tail;

    if(*tail == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int pop_front(listNode **head, listNode **tail)
{
    if(!(*head))
    {
        printf("tried to pop from empty list\n");
        return -1;
    }

    listNode *temp = *head;

    if(*head == *tail)
    {
        *head = *tail = NULL;
    }
    else
    {
        *head = (*head)->next;
        (*head)->prev = NULL;
    }

    int result = temp->data;
    free(temp);
    return result;
}

int pop_back(listNode **head, listNode **tail)
{
    if(!(*tail))
    {
        printf("tried to pop from empty list\n");
        return -1;
    }

    listNode *temp = *tail;

    if(*tail == *head)
    {
        *tail = *head = NULL;
    }
    else
    {
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }

    int result = temp->data;
    free(temp);
    return result;
}

void printListForward(listNode *head)
{
    while(head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    putchar('\n');
}

void printListBackward(listNode *tail)
{
    while(tail)
    {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    putchar('\n');
}

void freeList(listNode **head, listNode **tail)
{
    while(*head)
    {
        pop_front(head, tail);
    }

    *head = NULL;
    *tail = NULL;
}

int main()
{
    listNode *head = NULL, *tail = NULL;

    push_front(&head, &tail, 5);
    push_front(&head, &tail, 6);
    push_back(&head, &tail, 7);
    push_back(&head, &tail, 8);

    pop_front(&head, &tail);
    pop_back(&head, &tail);

    push_front(&head, &tail, -1);
    push_back(&head, &tail, -2);

    printListForward(head);
    printListBackward(tail);

    freeList(&head, &tail);

    return 0;
}