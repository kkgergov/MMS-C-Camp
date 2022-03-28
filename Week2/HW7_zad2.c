#include <stdio.h>

unsigned digitsSum(int n)
{
    unsigned sum = 0;
    while(n != 0)
    {
        sum += n%10;
        n /= 10;
    }

    return sum;
}

unsigned sumArrayDigits(const int* arr, size_t n)
{
    unsigned sum = 0;
    for(int i =0; i < n; i++)
    {
        sum += digitsSum(arr[i]);
    }

    return sum;
}


int main()
{
    int arr[] = {12, 34 , 5 ,70};

    printf("%u\n", sumArrayDigits(arr, 4));

    return 0;
}