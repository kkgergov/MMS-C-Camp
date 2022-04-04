#include <stdio.h>
#include "booklib.h"

// TO COMPILE AND RUN
// gcc HW15_zad1.c booklib.c -o program; ./program

int main()
{
    book bookArr[COUNT_BOOKS];
    createBooks_arr(bookArr);

    // write to file
    char filename[100];
    printf("Please enter filename:\n");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "wb");
    fwrite(&bookArr, sizeof(book), COUNT_BOOKS, fp);
    fclose(fp);

    // CHECK IF WE REALLY SAVED TO ARRAY TO A FILE
    book bookArrTest[COUNT_BOOKS];

    fp = fopen(filename, "rb");
    fread(&bookArrTest, sizeof(book), COUNT_BOOKS, fp);

    printBooks_arr(bookArrTest);
    fclose(fp);

    return 0;
}