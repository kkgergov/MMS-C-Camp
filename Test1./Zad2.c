#include <stdio.h>
#include <stdarg.h>

//TO COMPILE AND RUN FOLLOWING COMMAND
//gcc zad2.c -o program; ./program

unsigned getBit(int, unsigned);
unsigned bitsNCount(unsigned count, unsigned bitscnt, ...);

int main()
{
    fprintf(stdout, "%u\n", bitsNCount(4, 2, 0x0a, 0xff, 0, 1));
    fprintf(stdout, "%u\n", bitsNCount(3, 8, 0xff, 0x13f1, 0xaaaa));
    fprintf(stdout, "%u\n", bitsNCount(5, 10, 0x0a, 0xa0ff, 0, 10, 0b1010111110111));
    return 0;
}

unsigned getBit(int mask, unsigned bit)
{
    return !!(mask & (1 << bit));
}

unsigned bitsNCount(unsigned count, unsigned bitscnt, ...)
{
    unsigned result = 0;
    int bits_per_mask = sizeof(int) * 8;

    va_list ap;
    va_start(ap, count);

    for(int i = 0; i < count; i++)
    {
        int current_mask = va_arg(ap, int);
        unsigned mask_set_bits_cnt = 0;

        for(int j = 0; j < bits_per_mask; j++)
        {
            mask_set_bits_cnt += getBit(current_mask, j);
        }

        if(mask_set_bits_cnt == bitscnt)
        {
            ++result;
        }
    }

    return result;
}
