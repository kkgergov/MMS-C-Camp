#include <stdio.h>

#define PI 3.1415

//TO COMPILE AND RUN FOLLOWING COMMAND
//gcc zad1.c -o program; ./program

int cylinder(double, double, double*, double*);


int main()
{
    double r, h, V, S;

    while(scanf("%lf%lf", &r, &h) != EOF)
    {
        if(cylinder(r, h , &V, &S) == -1)
        {
            fprintf(stderr, "Invalid data\n");
        }
        else
        {
            fprintf(stdout, "V = %.2lf, S = %.2lf\n", V, S);
        }
    }

    return 0;
}

int cylinder(double r, double h, double* V, double* S)
{
    if(r <= 0 || h <= 0)
    {
        return -1;
    }

    *S = 2 * PI * r * h + 2 * PI * r * r;
    *V = PI * r * r *h;

    return 0;
}
