#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ITEMS_COUNT 20

typedef struct
{
    uint16_t number;
    char description[250];
    double weight;
    double price;
} item;

typedef struct s_node
{
    item data;
    struct s_node *next;
} listNode;

void push_front(listNode **, item);
item pop_front(listNode **);
void clearList(listNode **);

void createItems_list(listNode **);
void printItems_list(listNode *);

double totalItemsWeight(listNode *);
listNode *minPriceItem(listNode *);

int main()
{
    listNode *head = NULL;
    createItems_list(&head);
    printItems_list(head);
    printf("\n\nTotal weight is: %.2lf\n\n\n", totalItemsWeight(head));
    listNode *cheapestNode = minPriceItem(head);
    printf("\n\nCheapest item is: (%d, %s, %.2lf, %.2lf)\n\n\n",
           cheapestNode->data.number, cheapestNode->data.description, cheapestNode->data.weight, cheapestNode->data.price);
    clearList(&head);
    return 0;
}

listNode *minPriceItem(listNode *head)
{
    if (!head)
    {
        return NULL;
    }

    listNode *current = head, *min_node = head;
    double min_price = current->data.price;

    current = current->next;
    while (current)
    {
        if (current->data.price < min_price)
        {   
            //printf("$%.2lf < %.2lf$\n",current->data.price, min_price);
            min_price = current->data.price;
            min_node = current;
        }
        current = current->next;
    }

    return min_node;
}

double totalItemsWeight(listNode *head)
{
    if (!head)
    {
        return -1;
    }

    double sum = 0;
    listNode *current = head;
    while (current)
    {
        sum += current->data.weight;
        current = current->next;
    }

    return sum;
}

void createItems_list(listNode **head)
{

    int unique_ids[ITEMS_COUNT];
    for (int i = 0; i < ITEMS_COUNT; i++)
    {
        item push_item;

        // generate number
        int unique_num = rand();
        for(int j =0 ; j< i; j++)
        {
            if(unique_num == unique_ids[j])
            {
                int unique_num = rand();
                j = 0;
            }
        }
        push_item.number = unique_num;

        //generate description
        int desc_words = 5 + rand() % 6;
        //generate first word
        push_item.description[0] = 'A' + rand() % ('Z' - 'A' + 1);
        int word_len = 1 + rand() % 10;

        for (int k = 1; k < word_len; k++)
        {
            push_item.description[k] = 'a' + rand() % ('z' - 'a' + 1);
        }
        push_item.description[word_len] = ' ';

        //generate rest of the words
        int index = word_len + 1;
        for (int j = 1; j < desc_words; j++)
        {
            word_len = 1 + rand() % 10;
            for (int k = 0; k < word_len; k++)
            {
                push_item.description[index++] = 'a' + rand() % ('z' - 'a' + 1);
            }
            push_item.description[index++] = ' ';
        }
        push_item.description[index++] = '\0';

        //printf("%s\n", push_item.description);

        // generate weight
        push_item.weight = 0.1 + ((double)rand() / RAND_MAX) * 99.9;

        // generate price
        push_item.price = 1 + ((double)rand() / RAND_MAX) * 1499;

        push_front(head, push_item);
    }
}

void printItems_list(listNode *head)
{
    printf("|Number|");
    printf("%*cDescription%*c|", 20, ' ', 20, ' ');
    printf("%*cWeight%*c|", 2, ' ', 3, ' ');
    printf("%*cPrice%*c|", 2, ' ', 3, ' ');
    putchar('\n');
    putchar('\n');
    putchar('\n');

    listNode *current = head;
    while (current)
    {
        putchar('|');
        printf("%d\t", current->data.number);
        putchar('|');
        printf("%s\t", current->data.description);
        putchar('|');
        printf("%.2lf\t", current->data.weight);
        putchar('|');
        printf("%.2lf", current->data.price);
        putchar('|');
        putchar('\n');

        current = current->next;
    }
}

void push_front(listNode **head, item val)
{
    listNode *newnode = (listNode *)malloc(sizeof(listNode));

    newnode->data = val;
    newnode->next = *head;

    *head = newnode;
}

item pop_front(listNode **head)
{
    if (!(*head))
        exit(-1);

    listNode *temp = *head;
    item result = temp->data;
    *head = (*head)->next;

    free(temp);
    return result;
}

void clearList(listNode **head)
{
    while (*head)
    {
        pop_front(head);
    }
}