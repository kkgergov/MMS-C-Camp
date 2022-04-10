#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>

void printd(int output_fd, int n) {
    if(n < 0)
    {
        write(output_fd, "-", 1);
        printd(output_fd, -n);
        return;
    }
    else if(n == 0)
    {
        return;
    }
    else
    {
        printd(output_fd, n / 10);
    }

    char lastDigit = n % 10 + '0';
    write(output_fd, &lastDigit, 1);
}

// works for ints and (NOT YET, TOO HARD)floats
int my_fprintf(int output_fd, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // calculate number of arguments
    int n_fArgs = 0;
    const char *scanner = format;
    while (*scanner)
    {
        if (*scanner == '%')
        {
            if (*(scanner + 1) == 'f' || *(scanner + 1) == 'd')
            {
                n_fArgs++;
            }
            else
            {
                write(STDERR_FILENO, "Error in formatting\n", 20);
            }
        }

        scanner++;
    }

    const char *reader = format;
    for (int i = 0; i < n_fArgs || *reader; i++)
    {
        while(*reader && *reader != '%')
        {
            write(output_fd, reader, sizeof(char));
            reader++;
        }

        if(*reader == '%')
        {
            if(*(reader + 1) == 'd')
            {
                int current_int = va_arg(ap, int);
                printd(output_fd, current_int);
            }
            else if(*(reader + 1) == 'f')
            {
                int current_float = va_arg(ap, double);
                printd(output_fd, current_float);
            }

            reader += 2;
            continue;
        }

    }

    va_end(ap);
    return 0;
}

int main()
{
    my_fprintf(STDOUT_FILENO, "Baba ganka e na %d godini s %f leva zaplata!\n", 55, 150.37);
    //printd(STDOUT_FILENO, -1);
    return 0;
}