#include <stdio.h>
#include <math.h>

double my_sin(double x)
{
    return x - (x*x*x)/6 + (x*x*x*x*x)/120 - (x*x*x*x*x*x*x)/5040;
}

int main()
{
    printf("%.4lf\n", sin(15.3));
    return 0;
}