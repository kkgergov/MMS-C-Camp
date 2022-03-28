#include <stdio.h>

#define EPS 0.001

int eq(double a, double b)
{
    return (a - b) < EPS && (b - a) < EPS;
}

double sqrt(double number)
{
    double step = 0.0001;
    double sqr = 0;

    for(; !eq(sqr*sqr, number); sqr += step);

    return sqr;
}

int main()
{
    double num = 96;
    printf("%.2lf\n", sqrt(num));
    return 0;
}