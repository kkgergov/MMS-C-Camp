#include <stdio.h>
#include <math.h>

#define PI 3.1415

double water_vol1(double, double);
double water_vol2(double, double, double);

//TO COMPILE AND RUN PASTE THIS COMMAND IN THE TERMINAL:
//gcc homework1_ex2.c -lm  -o program; ./program

int main()
{
    double R, L, H;

    fprintf(stdout, "Enter the values in meters.\n---\n");

    fprintf(stdout, "a) Please, enter R of the barrel and H:\n");
    fscanf(stdin, "%lf%lf", &R, &H);
    fprintf(stdout, "Volume of water in the barrel in cubic meters is: %.2lf\n", water_vol1(R, H));

    fprintf(stdout, "\n---\n");
    fprintf(stdout, "b) Please, enter R and L of the barrel, then H:\n");
    fscanf(stdin, "%lf%lf%lf", &R, &L, &H);
    fprintf(stdout, "Volume of water in the barrel in cubic meters is: %.2lf\n", water_vol2(R, L, H));

    return 0;
}

double water_vol1(double R, double H)
{
    return PI * (R * R) * H;
}

double water_vol2(double R, double L, double H)
{
    return L * (acos(( R - H ) / R) * (R * R) - (R - H) * sqrt(2 * R * H - H * H));
}