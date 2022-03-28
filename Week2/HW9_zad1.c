#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, size_t l, size_t r)
{
    int pivotIdx = l + rand() % (r - l + 1); //generate in the range [l, r]

    swap(arr + pivotIdx, arr + r);

    int i = l - 1;
    for(int j = l; j < r; j++)
    {
        if(arr[j] < arr[r])
        {
            i++;
            swap(arr + i, arr + j);
        }
    }

    swap(arr + i + 1, arr + r);
    return i + 1;
}

void quicksort(int *arr, int p, int q)
{
    if(p >= q)
        return;

    int j = partition(arr, p, q); // calls the partition function in [p,q] of the array
    // the partition function placed one element is it's correct place in the sorted array
    // now we call the algorithm on the left of it subarray and the right one
    quicksort(arr, p, j - 1); // we sort the left subarray
    quicksort(arr, j + 1, q); // we sort the right subarray
}

int main()
{
    int arr[] = {1,31,-31,24,1,-34,43,24,0,654,82,658659,4};
    quicksort(arr, 0, 12);
    for(int i = 0; i < 13; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return 0;
}