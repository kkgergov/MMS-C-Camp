#include <stdio.h>

//TO COMPILE AND RUN PASTE THE FOLLOWING COMMANDS IN THE TERMINAL:

//Create file and put numbers inside:
//touch numbers.txt; echo 1243 0.15 1243.1 1> numbers.txt;
//Compile and run the program:
//gcc homework2_ex1.c -o program; ./program < numbers.txt

int main()
{
    double num1, num2, num3;
    scanf("%lf%lf%lf", &num1, &num2, &num3);

    double max = (num1 > num2) ? num1 : num2;
    max = (num3 > max) ? num3 : max;

    printf("%.2lf\n", max);

    return 0;
}