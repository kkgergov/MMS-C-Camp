#include <stdio.h>
#include <math.h>
#include <ctype.h>


int convert_any_decimal(int, const char*, int*);
void convert_decimal_any(int, int, char*);
int convert_any_any(int, const char*, int, char*);

int main()
{
    char number[100], result[100];
    int base_from, base_to;

    scanf("%s%d%d", number, &base_from, &base_to);

    if(convert_any_any(base_from, number, base_to, result) == -1)
    {
        printf("BAD INPUT\n");
    }
    else
    {
        printf("%s\n", result);
    }
}

int convert_any_decimal(int base, const char *number, int *result)
{
    int dec_num = 0;
    int i = 0;

    while(number[i])
    {
        int remainder;

        char digit = number[i];
        if(isalpha(digit))
        {
            remainder = (int)(digit - 'a') + 10;
        }
        else if(isdigit(digit))
        {
            remainder = (int)(digit - '0');
        }
        else
        {
            return -1;
        }

        dec_num = dec_num * base + remainder;

        i++;
    }

    *result = dec_num;
}

void convert_decimal_any(int base, int num, char *result)
{

    int lastPos = log(num) / log(base) + (*result == '-');

    while(num != 0)
    {
        int remainder = num % base;

        char digit;
        if(remainder > 9)
        {
            digit = (char)remainder + 'a' - 10;
        }
        else
        {
            digit = (char)remainder + '0';
        }

        result[lastPos] = digit;

        lastPos--;
        num /= base;
    }
}

int convert_any_any(int base_from, const char *number, int base_to, char *result)
{
    if(base_from < 2 || base_from > 36)
    {
        return -1;
    }

    int is_positive_flag = 1;
    if(*number == '-')
        is_positive_flag = 0;

    int number_in_decimal;
    int bad_input = (is_positive_flag) ? convert_any_decimal(base_from, number,     &number_in_decimal)
                                       : convert_any_decimal(base_from, number + 1, &number_in_decimal);
    
    if(bad_input == -1)
        return -1;


    if(!is_positive_flag)
        result[0] = '-';

    convert_decimal_any(base_to ,number_in_decimal, result);

    return 0;
}