#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int arr[20];
    for (int i = 0; i < 20; i++)
    {
        arr[i] = rand() % 1000;
        //printf("%d ", arr[i]);
    }

    FILE *fp = fopen(argv[1], "wb");
    if(!fp)
    {
        perror("Could not open file");
        printf("argument: %s\n", argv[1]);
        return 1;
    }
    fwrite(&arr, sizeof(int), 20, fp);

    fclose(fp);
    return 0;
}