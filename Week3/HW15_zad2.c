#include <stdio.h>
#include "booklib.h"
#include <errno.h>

extern int errno;

// TO COMPILE AND RUN
// gcc HW15_zad2.c booklib.c -o program; ./program

listNode *read_list_from_file(FILE *fp)
{
    listNode tempNode;
    listNode *newNode = NULL;

    if(fread(&tempNode, sizeof(listNode), 1, fp))
    {
        newNode = malloc(sizeof(listNode));
        newNode->data = tempNode.data;
        newNode->next = read_list_from_file(fp);
    }
    
    return newNode;
}

int main()
{
    book bookArr[COUNT_BOOKS];

    char i_filename[100], o_filename[100];
    printf("Please enter input filename:\n");
    scanf("%s", i_filename);

    //open input file, save to array, convert array to list, sort list
        //open file
    FILE *fp = fopen(i_filename, "rb");
    if(!fp)
    {
        perror("Could not open file");
        return 1;
    }
        //read to array
    fread(&bookArr, sizeof(book), COUNT_BOOKS, fp);
    fclose(fp);

        //convert array to list
    listNode *head;
    for(int i =0; i <COUNT_BOOKS; i++)
    {
        push_front(&head, bookArr[i]);
    }
        //sort list
    mergeSort(&head, cmpTitle);

    //open output file, write list to output
    printf("Please enter output filename:\n");
    scanf("%s", o_filename);

        //open output
    fp = fopen(o_filename, "wb");
        
        //write each node to file
    listNode *current = head;
    while(current)
    {
        fwrite(current, sizeof(listNode), 1, fp);
        current = current->next;
    }
    fclose(fp);

    //CHECK IF WE REALLY SAVED THE LIST TO A FILE
    //THE LIST WILL BE IN REVERSE
    clearList(&head);

    fp = fopen(o_filename, "rb");

    head = read_list_from_file(fp);

    fclose(fp);


    printBooks_list(head);
    clearList(&head);
    return 0;
}