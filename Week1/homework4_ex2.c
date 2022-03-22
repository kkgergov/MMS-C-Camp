#include <stdio.h>
#include <stdint.h>

//OPERATIONS
int checkBit(uint32_t mask, unsigned bit)
{
    return !!(mask & (1 << bit));
}

void setBit(uint32_t *mask, unsigned bit)
{
    *mask |= (1 << bit); 
}

void clearBit(uint32_t *mask, unsigned bit)
{
    *mask &= ~(1 << bit);
}

void flipBit(uint32_t *mask, unsigned bit)
{
    *mask ^= (1 << bit);
}

//FUNCTIONS
void displayPresent(uint32_t mask)
{   
    fprintf(stdout, "Present students are numbers:\n");

    for(int i = 31; i >= 0; i--)
    {
        if(checkBit(mask, i))
        {
            fprintf(stdout, "%d ", i + 1);
        }
    }

    fprintf(stdout, "\n\n\n");
}

void displayAbsent(uint32_t mask)
{   
    fprintf(stdout, "Absent students are numbers:\n\n");

    for(int i = 31; i >= 0; i--)
    {
        if(!checkBit(mask, i))
        {
            fprintf(stdout, "%d ", i + 1);
        }
    }

    fprintf(stdout, "\n\n");
}

void setStudent(uint32_t *mask, unsigned num)
{
    setBit(mask, num - 1);
}

void clearStudent(uint32_t *mask, unsigned num)
{
    clearBit(mask, num - 1);
}

void flipStudent(uint32_t *mask, unsigned num)
{
    flipBit(mask, num -1);
}

int main()
{
    uint32_t attendance = 0;
    int option;

    //operations on students
    void (*operations[3]) (uint32_t*, unsigned);
    operations[0] = &setStudent;
    operations[1] = &clearStudent;
    operations[2] = &flipStudent;

    while (1)
    {
        printf("1. Set attendance\n");
        printf("2. Clear attendance\n");
        printf("3. Change attendance\n");
        printf("4. Attendance info\n");
        printf("5. Absence info\n");
        printf("6. Exit\n");
        scanf("%d", &option);
        

        if(option < 0 || option > 6)
        {
            printf("Unknown command, try again..\n");
            continue;
        } 
        else if(option == 6)
        {
            printf("Exiting..\n");
            break;
        }
        else if(option > 0 && option < 4)
        {
            unsigned num;
            while(1)
            {
                printf("Enter student number:\n");
                scanf("%d",&num);

                if(num < 1 || num > 32)
                {
                    printf("No such number in classroom!\n");
                    continue;
                }
                else
                {
                    operations[option-1](&attendance, num);
                    break;
                }
            }
        }
        else if(option == 4)
        {
            displayPresent(attendance);
        }
        else if(option == 5)
        {
            displayAbsent(attendance);
        }
        else{
            printf("No such option!\n");
        }
    }

    return 0;
}