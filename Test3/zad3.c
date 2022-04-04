#include <stdio.h>
#include <stdlib.h>

typedef struct c_node
{
    int data;
    struct c_node *next;
} listNode;

// moves head ptr
void push_front(listNode **head, listNode **tail, int val)
{
    listNode *newnode = malloc(sizeof(listNode));

    if (!(*head))
    {
        newnode->data = val;
        newnode->next = newnode;

        *head = newnode;
        *tail = newnode;

        return;
    }
    else
    {
        newnode->data = val;
        newnode->next = *head;

        *head = newnode;
        (*tail)->next = *head;
    }
}

void clearList(listNode **head, listNode **tail)
{

    while (*head != *tail)
    {
        listNode *temp = *head;
        *head = temp->next;
        free(temp);
    }
    free(*head);


    *head = NULL;
    *tail = NULL;
}

int main()
{
    listNode *head = NULL, *tail = NULL;

    for (int i = 0; i < 5; i++)
    {
        push_front(&head, &tail, i);
    }

    clearList(&head, &tail);

    return 0;
}