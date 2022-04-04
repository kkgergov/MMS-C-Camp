#ifndef _BOOKS_H_
#define _BOOKS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 0.001
#define COUNT_BOOKS 30

typedef struct
{
    char title[150];
    char author[100];
    unsigned pageCount;
    double price;
} book;

typedef struct s_node
{
    book data;
    struct s_node *next;
} listNode;

// misc functions
unsigned numDigits(int);
unsigned numWholeDigits(double);

// ARRAY FUNCTIONS
void createBooks_arr(book *);
void printBooks_arr(book *);

void bsort(void *, size_t, size_t, int (*)(const void *, const void *));
void swap(void *, void *, size_t);
void *lsearch(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
void *bsearch(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));

// LIST FUNCTIONS

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
void createBooks_list(listNode **);
void printBooks_list(listNode *);

// different compare functions for books
int cmpTitle(const void *, const void *);
int rev_cmpAuthor(const void *, const void *);
int cmpPages(const void *, const void *);
int cmpPrice(const void *, const void *);

#endif
