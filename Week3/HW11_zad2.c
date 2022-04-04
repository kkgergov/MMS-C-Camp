#include <stdio.h>
#include <stdlib.h>

double d_rand(double a, double b)
{
    return a + (((double)rand() / RAND_MAX) * (b - a));
}

int main()
{
    double *arr;

    int n;
    scanf("%d", &n);
    arr = (double *)malloc(sizeof(double) * n);

    for(int i = 0; i < n; i++)
    {
        arr[i] = d_rand(0,1);
    }

    int m;
    scanf("%d", &m);
    arr = (double*)realloc(arr, sizeof(double)*(n+m));
    for(int i = n; i < n+m; i++)
    {
        arr[i] = d_rand(1,2);
    }

    int p;
    scanf("%d", &p);
    arr = (double*)realloc(arr, sizeof(double)*(n+m+p));
    for(int i = n+m; i < n+m+p; i++)
    {
        arr[i] = d_rand(2,3);
    }

    putchar('[');
    for(int i = 0; i < n+m+p; i++)
    {
        printf("%.2lf ", arr[i]);
    }
    printf("\b]\n");

    free(arr);

    return 0;
}