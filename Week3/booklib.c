#include "booklib.h"

int cmpTitle(const void *vbook1, const void *vbook2)
{
    const char *title1 = ((book *)vbook1)->title;
    const char *title2 = ((book *)vbook2)->title;

    return strcmp(title1, title2);
}

int rev_cmpAuthor(const void *vbook1, const void *vbook2)
{
    const char *author1 = ((book *)vbook1)->author;
    const char *author2 = ((book *)vbook2)->author;

    return strcmp(author2, author1);
}

int cmpPages(const void *vbook1, const void *vbook2)
{
    int pages1 = ((book *)vbook1)->pageCount;
    int pages2 = ((book *)vbook2)->pageCount;

    return pages1 - pages2;
}

int cmpPrice(const void *vbook1, const void *vbook2)
{
    double price1 = ((book *)vbook1)->price;
    double price2 = ((book *)vbook2)->price;

    if (price1 - price2 < EPS && price2 - price1 < EPS)
        return 0;
    else
    {
        return price1 - price2;
    }
}

void *lsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    for (int i = 0; i < nitems; i++)
    {
        if (compar(base + i * size, key) == 0)
        {
            return (void *)(base + i * size);
        }
    }

    return NULL;
}

void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    int l = 0, r = nitems - 1, m;
    while (l <= r)
    {
        m = l + (r - l) / 2;
        int comparRes = compar(base + m * size, key);

        if (comparRes == 0)
        {
            return (void *)(base + m * size);
        }
        else if (comparRes > 0)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    return NULL;
}

void swap(void *el1, void *el2, size_t size)
{
    char *temp = malloc(size);

    memcpy(temp, el1, size);
    memcpy(el1, el2, size);
    memcpy(el2, temp, size);

    free(temp);
}

void bsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    for (int i = 0; i < nitems; i++)
    {
        for (int j = 0; j < nitems - i - 1; j++)
        {
            if (compar(base + j * size, base + (j + 1) * size) > 0)
            {
                swap(base + j * size, base + (j + 1) * size, size);
            }
        }
    }
}

void printBooks_arr(book *bookArr)
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

    for (int i = 0; i < COUNT_BOOKS; i++)
    {
        putchar('|');
        printf("%s%*c", bookArr[i].author, 21 - (int)strlen(bookArr[i].author), ' ');
        putchar('|');
        printf("%s%*c", bookArr[i].title, 21 - (int)strlen(bookArr[i].title), ' ');
        putchar('|');
        printf("%u%*c", bookArr[i].pageCount, 10 - numDigits(bookArr[i].pageCount), ' ');
        putchar('|');
        printf("%.2lf%*c", bookArr[i].price, 7 - numWholeDigits(bookArr[i].price), ' ');
        putchar('|');
        putchar('\n');
    }
}

void createBooks_arr(book *bookArr)
{
    for (int i = 0; i < COUNT_BOOKS; i++)
    {
        // generate author - names start with capital letter
        int author_name_length = 10 + rand() % 11;
        bookArr[i].author[0] = 'A' + rand() % ('Z' - 'A' + 1);
        for (int j = 1; j < author_name_length; j++)
        {
            char rand_lowercase = 'a' + rand() % ('z' - 'a' + 1);
            // if we are in the middle of the string start making second name
            if (j == author_name_length / 2)
            {
                bookArr[i].author[j] = ' ';
                bookArr[i].author[j + 1] = 'A' + rand() % ('Z' - 'A' + 1);

                j += 2;
            }
            bookArr[i].author[j] = rand_lowercase;
        }
        bookArr[i].author[author_name_length] = '\0';

        // generate title
        int book_title_length = 10 + rand() % 11;
        bookArr[i].title[0] = 'A' + rand() % ('Z' - 'A' + 1);
        for (int j = 1; j < book_title_length; j++)
        {
            char rand_lowercase = 'a' + rand() % ('z' - 'a' + 1);
            char rand_uppercase = 'A' + rand() % ('Z' - 'A' + 1);
            int random_bit = rand() % 2;

            if (random_bit)
            {
                bookArr[i].title[j] = rand_lowercase;
            }
            else
            {
                bookArr[i].title[j] = rand_uppercase;
            }
        }
        bookArr[i].title[book_title_length] = '\0';

        // generate pages
        bookArr[i].pageCount = 5 + rand() % 2001;

        // generate price
        bookArr[i].price = 1 + ((double)rand() / RAND_MAX) * 999;
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

listNode *sortedMerge(listNode *left, listNode *right, int (*cmp)(const void *, const void *))
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
    else if (cmp(&(left->data), &(right->data)) <= 0)
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

void mergeSort(listNode **head, int (*cmp)(const void *, const void *))
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

void createBooks_list(listNode **head)
{
    for (int i = 0; i < COUNT_BOOKS; i++)
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

void printBooks_list(listNode *head)
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