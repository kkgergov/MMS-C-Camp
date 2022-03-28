#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int intCmp(const void* a, const void*b)
{
    return *((int*)a) - *((int*)b);
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

void (*getSorting(char* fname))(void*,size_t,size_t,int(*)(const void*,const void*))
{
    if(strcmp(fname, "qsort") == 0)
    {
        return qsort;
    }
    else if(strcmp(fname, "bubble Sort") == 0)
    {
        return bsort;
    }

    return NULL;
}

int main()
{
    int arr[] = {-123,- 4,6,4,124,346,9870,12,-9999};
    getSorting("bubble Sort")(arr,9,sizeof(int),intCmp);
    for(int i=0; i< 9; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return 0;
}