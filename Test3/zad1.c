#include <stdio.h>
#include <stdlib.h>

#define COUNT 20

typedef struct
{
    double x;
    double y;
} point_t;

typedef struct
{
    point_t A;
    point_t B;
} rectangle_t;

typedef struct s_node
{
    rectangle_t data;
    struct s_node *next;
} listNode;

// basic list functionality
void push_front(listNode **, rectangle_t);
rectangle_t pop_front(listNode **);
void clearList(listNode **);

// functions for the task
void createRectangles_list(listNode **);
double area_sum(listNode *);
void filterRects(listNode **, double, double);
void print_rectangles(listNode *list);

// misc
double area_rec(rectangle_t);

int main()
{
    listNode *head = NULL;
    createRectangles_list(&head);
    printf("Sum of areas is %.2lf.\n", area_sum(head));

    print_rectangles(head);
    filterRects(&head, 10., 100.);
    printf("----after filter----\n\n");
    print_rectangles(head);
    clearList(&head);

    return 0;
}

void filterRects(listNode **list, double min, double max)
{
    if (!(*list))
    {
        return;
    }

    listNode *filtered_list = NULL;

    listNode *current = *list;
    while (current)
    {
        double cur_area = area_rec(current->data);
        //printf("CURRENT AREA IS: %.2lf\n", cur_area);
        if (cur_area >= min && cur_area <= max)
        {
            //printf("\tPUSHED\n");
            push_front(&filtered_list, current->data);
        }

        current = current->next;
    }

    clearList(list);
    *list = filtered_list;
}

double area_rec(rectangle_t rec)
{
    double a = rec.A.x - rec.B.x;
    double b = rec.A.y - rec.B.y;
    double area = a * b;

    if (area < 0)
    {
        area = -area;
    }

    return area;
}

void print_rectangles(listNode *list)
{
    while (list)
    {
        printf("rectangle: A(%.2lf, %.2lf), B(%.2lf, %.2lf) and area = %.2lf.\n",
               list->data.A.x, list->data.A.y, list->data.B.x, list->data.B.y, area_rec(list->data));

        list = list->next;
    }
}

double area_sum(listNode *list)
{
    double sum = 0;

    while (list)
    {
        sum += area_rec(list->data);

        list = list->next;
    }

    return sum;
}

void createRectangles_list(listNode **list)
{
    for (int i = 0; i < COUNT; i++)
    {
        rectangle_t rec;
        rec.A.x = -10 + ((double)rand() / RAND_MAX) * 20;
        rec.A.y = -10 + ((double)rand() / RAND_MAX) * 20;
        rec.B.x = -10 + ((double)rand() / RAND_MAX) * 20;
        rec.B.y = -10 + ((double)rand() / RAND_MAX) * 20;

        push_front(list, rec);
    }
}

void push_front(listNode **head, rectangle_t val)
{
    listNode *newnode = (listNode *)malloc(sizeof(listNode));

    newnode->data = val;
    newnode->next = *head;

    *head = newnode;
}

rectangle_t pop_front(listNode **head)
{
    if (!(*head))
        exit(1);

    listNode *temp = *head;
    rectangle_t result = temp->data;

    *head = (*head)->next;

    free(temp);
    return result;
}

void clearList(listNode **head)
{
    while (*head)
    {
        pop_front(head);
    }
}
