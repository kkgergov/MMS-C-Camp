#include <stdio.h>
#include <string.h>

#define COUNT 501 // char array of 500 symbols and \0

void codeNumber(char *);

int main()
{
    char number[500];
    printf("enter number:\n");
    scanf("%s", number);
    codeNumber(number);
    printf("Result:\n%s\n", number);
    return 0;
}

void codeNumber(char *numberStr)
{
    int lastIndex = strlen(numberStr) - 1;

    int isEven = 1;
    for (int i = lastIndex; i >= 0; i--)
    {
        if (isEven)
        {
            numberStr[i] += -'0' + 'A';
            isEven = 0;
        }
        else
        {
            switch (numberStr[i])
            {
            case '0':
                numberStr[i] = '!';
                break;
            case '1':
                numberStr[i] = '#';
                break;
            case '2':
                numberStr[i] = '/';
                break;
            case '3':
                numberStr[i] = '~';
                break;
            case '4':
                numberStr[i] = '=';
                break;
            case '5':
                numberStr[i] = '\'';
                break;
            case '6':
                numberStr[i] = '\\';
                break;
            case '7':
                numberStr[i] = '>';
                break;
            case '8':
                numberStr[i] = '.';
                break;
            case '9':
                numberStr[i] = ',';
                break;
            }
            isEven = 1;
        }
    }
}