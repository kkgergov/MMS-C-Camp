#include <stdio.h>
#include <math.h>

double bmi(double, double);
double bmi_new(double, double);


//TO COMPILE AND RUN PASTE THIS COMMAND IN THE TERMINAL:
//gcc homework1_ex1.c -lm  -o program; ./program

int main(void)
{
    double mass, height;

    fprintf(stdout, "Please, enter your mass and height(in meters):\n---\n");
    fscanf(stdin, "%lf %lf", &mass, &height);

    fprintf(stdout, "\n---\n");
    fprintf(stdout, "Your Body mass index is %.2lf according to the standart formula.\n", bmi(mass, height));
    fprintf(stdout, "Your BMI is %.2lf according to Trefethen's formula.\n", bmi_new(mass, height));

    return 0;
}

double bmi(double mass, double height)
{
    return mass / (height * height);
}

double bmi_new(double mass, double height)
{
    return 1.3 * (mass / pow(height, 2.5));
}