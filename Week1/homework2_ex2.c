#include <stdio.h>

int logical_XOR(int, int);

//TO COMPILE AND RUN PASTE THE FOLLOWING COMMANDS IN THE TERMINAL:

//Create file and put numbers inside:
//touch numbers.txt; echo 1 1 1 0 1 > numbers.txt;
//Compile and run the program:
//gcc homework2_ex2.c -o program; ./program < numbers.txt

int main()
{
    //because 0 XOR A == A 
    int result = 0;
    int num;

    while(scanf("%d", &num) != EOF)
    {
        result = logical_XOR(result, num);
    }

    printf("%d\n", result);

    return 0;
}


//We assume that the input of the function is only 0s and 1s
int logical_XOR(int num1, int num2)
{
    if(num1 != num2)
    {
        return 1;
    }

    return 0;
}