#include <stdio.h>

int secondMax(const int*, size_t n, int*);


int main()
{
    int sm;
    int arr2[] = {12, 34, 5, 70, 46, 71 };
    //int arr2[9] = {3,12};

    printf("%d\n",secondMax(arr2, 2, &sm));
    printf("%d\n", sm);
    return 0;
}

int secondMax(const int* arr, size_t n, int* secondMax)
{
    if(n == 0)
    {
        return -1;
    }
    else if (n == 1)
    {
        return -2;
    }

    int firstMax = *arr;
    *secondMax = *(arr + 1);

    for(int i = 1; i < n; i++)
    {
        putchar('(');
        if(arr[i] > firstMax)
        {

            *secondMax = firstMax;
            firstMax = arr[i];
        }
        else if (arr[i] > *secondMax)
        {
            *secondMax = arr[i];
        }
        
        // printf("arr[%d], fmax = %d, smax = %d", i, firstMax, *secondMax);
        // putchar(')');
        // putchar('\n');
    }

    if(firstMax == *secondMax)
    {
        return -3;
    }

    return firstMax;
}