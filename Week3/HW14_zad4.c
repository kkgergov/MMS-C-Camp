#include <stdio.h>
#include <stdlib.h>

double *movingAverage(double *x, size_t len, size_t window)
{
    if (window > len)
    {
        return NULL;
    }

    double *res = malloc(sizeof(double) * (len - window + 1));

    for (int i = window - 1; i < len; i++)
    {
        double avg = 0;
        for (int j = i - window + 1; j <= i; j++)
        {
            avg += x[j];
        }

        avg = avg / window;
        res[i - window + 1] = avg;
    }

    return res;
}

int main()
{
    double arr[] = {0.32, 0.8, 0.99, 12.3, 7.5, 11};

    double *avgArr = movingAverage(arr, 6, 2);
    for(int i=0; i < 5; i++)
    {
        printf("%.2lf ", avgArr[i]);
    }
    putchar('\n');

    return 0;
}