#include <stdio.h>
#include <stdint.h>

typedef union
{
    float number;
    struct
    {
        uint32_t bit0 : 1;
        uint32_t bit1 : 1;
        uint32_t bit2 : 1;
        uint32_t bit3 : 1;
        uint32_t bit4 : 1;
        uint32_t bit5 : 1;
        uint32_t bit6 : 1;
        uint32_t bit7 : 1;
        uint32_t bit8 : 1;
        uint32_t bit9 : 1;
        uint32_t bit10 : 1;
        uint32_t bit11 : 1;
        uint32_t bit12 : 1;
        uint32_t bit13 : 1;
        uint32_t bit14 : 1;
        uint32_t bit15 : 1;
        uint32_t bit16 : 1;
        uint32_t bit17 : 1;
        uint32_t bit18 : 1;
        uint32_t bit19 : 1;
        uint32_t bit20 : 1;
        uint32_t bit21 : 1;
        uint32_t bit22 : 1;
        uint32_t bit23 : 1;
        uint32_t bit24 : 1;
        uint32_t bit25 : 1;
        uint32_t bit26 : 1;
        uint32_t bit27 : 1;
        uint32_t bit28 : 1;
        uint32_t bit29 : 1;
        uint32_t bit30 : 1;
        uint32_t bit31 : 1;
    };
    
} floatBitField;


int main()
{
    floatBitField fBit;
    scanf("%f", &fBit.number);
    printf("%lu\n", sizeof(fBit));
    printf("%d %d %d %d ", fBit.bit0, fBit.bit1, fBit.bit2, fBit.bit3);
    printf("%d %d %d %d ", fBit.bit4, fBit.bit5, fBit.bit6, fBit.bit7);
    printf("%d %d %d %d ", fBit.bit8, fBit.bit9, fBit.bit10, fBit.bit11);
    printf("%d %d %d %d ", fBit.bit12, fBit.bit13, fBit.bit14, fBit.bit15);

    printf("%d %d %d %d ", fBit.bit16, fBit.bit17, fBit.bit18, fBit.bit19);
    printf("%d %d %d %d ", fBit.bit20, fBit.bit21, fBit.bit22, fBit.bit23);
    printf("%d %d %d %d ", fBit.bit24, fBit.bit25, fBit.bit26, fBit.bit27);
    printf("%d %d %d %d\n", fBit.bit28, fBit.bit29, fBit.bit30, fBit.bit31);
    return 0;
}