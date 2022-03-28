#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef union 
{
    uint16_t num;
    struct{
        uint16_t byte1 : 8;
        uint16_t byte2 : 8;
    };
} Bytes;

void swapBytes(uint16_t* numtoSwap)
{
    Bytes u;
    u.num = *numtoSwap;

    uint8_t lByte = u.byte1, rByte = u.byte2;
    u.byte1 = rByte;
    u.byte2 = lByte;

    *numtoSwap = u.num;
}

int main()
{
    //printf("%lu\n", sizeof(Bytes));
    uint16_t number = 0xabcd;
    swapBytes(&number);
    printf("%x\n", number);
    return 0;
}