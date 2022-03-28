#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define EPS 0.001
#define COUNT 10

typedef struct
{
    char model[20];
    uint8_t maxspeed;
    double price;
} car;

int cmpModel(const void *, const void *);
int desc_cmpModel(const void *, const void *);
int cmpSpeed(const void *, const void *);
int desc_cmpSpeed(const void *, const void *);
int cmpPrice(const void *, const void *);
int desc_cmpPrice(const void *, const void *);

int (*getComparator(int))(const void *, const void *);

void createCars(car*);
void viewCars(car*);

int main()
{
    car carArr[COUNT];
    createCars(carArr);

    printf("enter number of cmp function:\n");
    int n;
    scanf("%d", &n);

    qsort(carArr, COUNT, sizeof(car), getComparator(n));
    viewCars(carArr);
    return 0;
}

int cmpModel(const void *vcar1, const void *vcar2)
{
    char *model1 = ((car *)vcar1)->model;
    char *model2 = ((car *)vcar2)->model;
    return strcmp(model1, model2);
}

int desc_cmpModel(const void *vcar1, const void *vcar2)
{
    return cmpModel(vcar2, vcar1);
}

int cmpSpeed(const void *vcar1, const void *vcar2)
{
    uint8_t speed1 = ((car *)vcar1)->maxspeed;
    uint8_t speed2 = ((car *)vcar2)->maxspeed;

    return speed1 - speed2;
}

int desc_cmpSpeed(const void *vcar1, const void *vcar2)
{
    return cmpSpeed(vcar2, vcar1);
}

int cmpPrice(const void *vcar1, const void *vcar2)
{
    double price1 = ((car *)vcar1)->price;
    double price2 = ((car *)vcar2)->price;

    if (price1 - price2 < EPS && price2 - price1 < EPS)
    {
        return 0;
    }

    return price1 - price2;
}

int desc_cmpPrice(const void *vcar1, const void *vcar2)
{
    return cmpPrice(vcar2, vcar1);
}

int (*getComparator(int n))(const void *, const void *)
{
    switch (n)
    {
    case 1:
        return cmpModel;
        break;
    case 2:
        return desc_cmpModel;
        break;
    case 3:
        return cmpSpeed;
        break;
    case 4:
        return desc_cmpSpeed;
        break;
    case 5:
        return cmpPrice;
        break;
    case 6:
        return desc_cmpPrice;
        break;
    default:
        return NULL;
        break;
    }
}

void createCars(car *carArr)
{
    for (int i = 0; i < COUNT; i++)
    {
        // create model
        int model_length = 4 + rand() % 7;
        for (int j = 0; j < model_length; j++)
        {
            char rand_lowercase = 'a' + rand() % ('z' - 'a' + 1);
            char rand_uppercase = 'A' + rand() % ('Z' - 'A' + 1);
            int random_bit = rand() % 2;

            if (random_bit)
            {
                carArr[i].model[j] = rand_lowercase;
            }
            else
            {
                carArr[i].model[j] = rand_uppercase;
            }
        }
        carArr[i].model[model_length] = '\0';

        // create speed
        carArr[i].maxspeed = 100 + rand() % 201;

        // create price
        carArr[i].price = 1000 + ((double)rand() / RAND_MAX) * 99000;
    }
}

void viewCars(car *carArr)
{
    printf("Model%*c", 10, ' ');
    printf("Speed%*c", 10, ' ');
    printf("Price%*c", 10, ' ');
    putchar('\n');
    for(int i = 0; i< COUNT; i++)
    {
        printf("%s%*c", carArr[i].model, 15 - (int)strlen(carArr[i].model), ' ');
        printf("%d%*c", carArr[i].maxspeed, 10, ' ');
        printf("%.2lf%*c", carArr[i].price, 10, ' ');
        putchar('\n');
    }
}
