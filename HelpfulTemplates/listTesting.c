#include <stdio.h>
#include <stdlib.h>

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

typedef struct lnode
{
    unsigned barcode;
    product_type type;
    double price;
    struct lnode *next;
} listNode;

listNode *buffer = NULL;
int buffersize =0;

void push_front(unsigned p_bc,product_type p_type, double p_price)
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
    if(idx == 0)
    {
        listNode *temp = buffer;
        buffer = buffer->next;
        free(temp);
        buffersize--;
        return;
    }

    listNode *first = buffer, *second = buffer->next;
    for(int i=1; i <idx; i++)
    {
        first = first->next;
        second = second->next;
    }

    first->next = second->next;

    printf("(%d,%d,%.2lf) at index %d.\n", second->barcode, second->type, second->price, idx);

    free(second);

    buffersize--;
}

void printList()
{
    listNode *current = buffer;
    while(current)
    {
        printf("price is: %.2lf ", current->price);
        current = current->next;
    }
    putchar('\n');
}

int main()
{
    push_front(1,1,0.1);
    push_front(1,1,0.2);
    push_front(1,1,0.3);
    push_front(1,1,0.4);
    push_front(1,1,0.5);
    push_front(1,1,0.6);
    push_front(1,1,0.7);
    printList();
    remove_at(0);
    printList();
    remove_at(5);
    printList();
    remove_at(2);
    printList();

    FILE *fp = NULL;
    fclose(fp);

    return 0;
}