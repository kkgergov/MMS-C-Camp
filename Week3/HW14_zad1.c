#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 20

typedef struct
{
    char title[150];
    char author[100];
    int pageCount;
    double price;
} book;

typedef struct s_node
{
    book data;
    struct s_node *next;
} listNode;

// list
void push_front(listNode **, book);
book pop_front(listNode **);
void clearList(listNode **);

// mergesort
listNode *sortedMerge(listNode *, listNode *, int (*)(const void*, const void*));
void split(listNode *, listNode **, listNode **);
void mergeSort(listNode **, int (*)(const void*, const void*));
int cmpPrice(const void*, const void*);

// misc
void createBooks(listNode **);
void printBooks(listNode *);
unsigned numDigits(int);
unsigned numWholeDigits(double);

int main()
{
    listNode *head = NULL;
    createBooks(&head);
    printBooks(head);
    mergeSort(&head, cmpPrice);
    printBooks(head);
    clearList(&head);
    return 0;
}

int cmpPrice(const void* vbook1, const void* vbook2)
{
    char *title1 = ((listNode*)vbook1)->data.title;
    char *title2 = ((listNode*)vbook2)->data.title;

    return strcmp(title1, title2);
}

listNode *sortedMerge(listNode *left, listNode *right, int (*cmp)(const void*, const void*))
{
    listNode *res_head = NULL;

    if (!left)
    {
        return right;
    }
    else if (!right)
    {
        return left;
    }
    else if(cmp(left, right) <= 0)
    {
        res_head = left;
        res_head->next = sortedMerge(left->next, right, cmp);
    }
    else
    {
        res_head = right;
        res_head->next = sortedMerge(left, right->next, cmp);
    }

    return res_head;
}

void split(listNode *head, listNode **left, listNode **right)
{
    listNode *fast = head, *slow = head;

    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left = head, *right = slow->next;
    slow->next = NULL;
}

void mergeSort(listNode **head, int (*cmp)(const void*, const void*))
{
    if (!(*head) || !(*head)->next)
    {
        return;
    }

    listNode *leftHalf = NULL, *rightHalf = NULL;
    split(*head, &leftHalf, &rightHalf);

    mergeSort(&leftHalf, cmp);
    mergeSort(&rightHalf, cmp);

    *head = sortedMerge(leftHalf, rightHalf, cmp);
}

void push_front(listNode **head, book val)
{
    listNode *newnode = (listNode *)malloc(sizeof(listNode));

    newnode->data = val;
    newnode->next = *head;

    *head = newnode;
}

book pop_front(listNode **head)
{
    if (!(*head))
        exit(-1);

    listNode *temp = *head;
    book result = temp->data;
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

void createBooks(listNode **head)
{
    for (int i = 0; i < COUNT; i++)
    {
        book push_book;

        // generate author - names start with capital letter
        int author_name_length = 10 + rand() % 11;
        push_book.author[0] = 'A' + rand() % ('Z' - 'A' + 1);
        for (int j = 1; j < author_name_length; j++)
        {
            char rand_lowercase = 'a' + rand() % ('z' - 'a' + 1);
            // if we are in the middle of the string start making second name
            if (j == author_name_length / 2)
            {
                push_book.author[j] = ' ';
                push_book.author[j + 1] = 'A' + rand() % ('Z' - 'A' + 1);

                j += 2;
            }
            push_book.author[j] = rand_lowercase;
        }
        push_book.author[author_name_length] = '\0';

        // generate title
        int book_title_length = 10 + rand() % 11;
        push_book.title[0] = 'A' + rand() % ('Z' - 'A' + 1);
        for (int j = 1; j < book_title_length; j++)
        {
            char rand_lowercase = 'a' + rand() % ('z' - 'a' + 1);
            char rand_uppercase = 'A' + rand() % ('Z' - 'A' + 1);
            int random_bit = rand() % 2;

            if (random_bit)
            {
                push_book.title[j] = rand_lowercase;
            }
            else
            {
                push_book.title[j] = rand_uppercase;
            }
        }
        push_book.title[book_title_length] = '\0';

        // generate pages
        push_book.pageCount = 5 + rand() % 2001;

        // generate price
        push_book.price = 1 + ((double)rand() / RAND_MAX) * 999;

        push_front(head, push_book);
    }
}

void printBooks(listNode *head)
{
    printf("|%*cAuthor%*c|", 7, ' ', 8, ' ');
    printf("%*cTitle%*c|", 8, ' ', 8, ' ');
    printf("%*cPages%*c|", 2, ' ', 3, ' ');
    printf("%*cPrice%*c|", 2, ' ', 3, ' ');
    putchar('\n');
    printf("|%*c|%*c|%*c|%*c|\n", 21, ' ', 21, ' ', 10, ' ', 10, ' ');
    for (int i = 0; i < 67; i++)
        putchar('-');
    putchar('\n');

    listNode *current = head;
    while (current)
    {
        putchar('|');
        printf("%s%*c", current->data.author, 21 - (int)strlen(current->data.author), ' ');
        putchar('|');
        printf("%s%*c", current->data.title, 21 - (int)strlen(current->data.title), ' ');
        putchar('|');
        printf("%u%*c", current->data.pageCount, 10 - numDigits(current->data.pageCount), ' ');
        putchar('|');
        printf("%.2lf%*c", current->data.price, 7 - numWholeDigits(current->data.price), ' ');
        putchar('|');
        putchar('\n');

        current = current->next;
    }
}

unsigned numDigits(int number)
{
    unsigned cnt = 0;
    while (number != 0)
    {
        number /= 10;
        cnt++;
    }

    return cnt;
}

unsigned numWholeDigits(double dNum)
{
    int number = (int)dNum;
    unsigned cnt = 0;
    while (number != 0)
    {
        number /= 10;
        cnt++;
    }

    return cnt;
}