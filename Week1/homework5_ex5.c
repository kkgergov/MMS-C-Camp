#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

int getBit(int mask, unsigned bit)
{
    return !!(mask & (1 << bit));
}

unsigned onesCount(size_t mask_size_bytes, unsigned count, ...)
{   
    unsigned onesCount = 0;
    int bits_per_mask = mask_size_bytes * 8;

    va_list ap;
    va_start(ap, count);

    for(int i = 0; i< count; i++)
    {
        int curr_mask = va_arg(ap, int);

        for(int j = 0; j < bits_per_mask; j++)
        {
            onesCount += getBit(curr_mask, j);
        }
    }
    va_end(ap);

    return onesCount;
}

int main()
{
    printf("%u\n", onesCount(4, 2, 23523, 5));
    return 0;
}