#include <stdio.h>

unsigned sumDigits(int num)
{
    unsigned sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int recursiveFun(int *arr, int pos, unsigned n, int steps)
{
    //printf("-%d-\n", pos);
    if (pos < 0 || pos >= n || arr[pos] == -1)
        return steps;

    printf("%d ", arr[pos]);

    if (sumDigits(arr[pos]) % 2 == 0)
    {
        arr[pos] = -1;
        return recursiveFun(arr, pos + 3, n, steps + 1);
    }
    else
    {
        arr[pos] = -1;
        return recursiveFun(arr, pos - 2, n, steps + 1);
    }
}

int main()
{
    int arr1[] = {5, 23, 77, 123, 681, 9, 772, 16};
    int arr2[] = {71, 14, 90, 26, 11, 63, 81, 52};

    int result = recursiveFun(arr2, 0, 8, 0);
    putchar('\n');
    printf("Result: %d\n", result);
    return 0;
}