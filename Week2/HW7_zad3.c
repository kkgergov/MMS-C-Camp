#include <stdio.h>

int arrAverage(int* arr, int n)
{
    int sum = 0;

    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    return sum / n;
}

void arrayEvaluate(int* arr, size_t n, int(*f)(int*,int))
{
    printf("The average of the array in int is: %d\n", f(arr, n));
}

int main()
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    arrayEvaluate(arr, 10, arrAverage);
    return 0;
}