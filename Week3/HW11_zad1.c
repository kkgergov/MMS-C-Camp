#include <stdio.h>

#define MAX(x,y,z) ((x) > (((y) > (z))?(y):(z)) )? (x) : (((y) > (z))?(y):(z))
#define MIN(x,y,z) ((x) < (((y) < (z))?(y):(z)) )? (x) : (((y) < (z))?(y):(z))
#define SETBIT(mask,bit) mask |= (1 << bit)
#define CLEARBIT(mask,bit) mask &= ~(1 << bit)
#define SWITCHBIT(mask,bit) mask ^= (1 << bit)
#define CHECKBIT(mask,bit) !!(mask & (1 << bit))
#define SWAP(a,b) { int temp = a; a = b; b = temp; }


int main()
{
    //1.1 - 1.2
    printf("%d\n", MAX(0+1, 0+2, 0-2));
    printf("%d\n", MIN(0-3, -4, 0-2));

    //1.3 - 1.6
    unsigned mask = 1;
    SETBIT(mask,3);
    printf("%d\n", mask);

    mask = 1;
    CLEARBIT(mask,0);
    printf("%d\n", mask);

    mask = 5;
    SWITCHBIT(mask,3);
    SWITCHBIT(mask,2);    
    printf("%d\n", mask);

    mask = 13;
    printf("(%d, ", CHECKBIT(mask,3));
    printf("%d, ", CHECKBIT(mask,2));
    printf("%d, ", CHECKBIT(mask,1));
    printf("%d)\n", CHECKBIT(mask,0));

    //1.7
    int test1 = 123456, test2 = 7890;
    printf("(%d, %d)\n", test1, test2);
    SWAP(test1,test2);
    printf("(%d, %d)\n", test1, test2);

    return 0;
}