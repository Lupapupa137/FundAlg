#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Status
{
    MEMMORY_ALLOCATION_ERROR = 666,
    ARRAY_LENGTH_ZERO_ERROR = -67,
    INPUT_ERROR = 1,
    OK = 0
};

int fill_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    return OK;
}

int output_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return OK;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int size_a = 0;
    int size_b = 0;

    printf("Enter size of 1st array: ");
    scanf("%d", &size_a);
    printf("Enter size of 2nd array: ");
    scanf("%d", &size_b);

    int *a = (int *)malloc(sizeof(int) * size_a);
    int *b = (int *)malloc(sizeof(int) * size_b);

    if (size_a < 0 || size_b < 0)
    {
        puts("Incorrect input!!!");
        return INPUT_ERROR;
    }

    if (a == NULL)
    {
        puts("Out of memory!");
        return MEMMORY_ALLOCATION_ERROR;
    }

    if (b == NULL)
    {
        puts("Out of memory!");
        return MEMMORY_ALLOCATION_ERROR;
    }

    fill_array(a, size_a);
    output_array(a, size_a);
    puts("--------------------");
    fill_array(b, size_b);
    output_array(b, size_b);
    puts("--------------------");

    int *c = (int *)malloc(sizeof(int) * size_a);
    if (c == NULL)
    {
        puts("Out of memory!");
        return MEMMORY_ALLOCATION_ERROR;
    }

    if (size_a == 0 && size_b == 0)
    {
        puts("Array length zero error!!!");
        return ARRAY_LENGTH_ZERO_ERROR;
    }

    if (size_a > 0 && size_b == 0)
    {
        for (int i = 0; i < size_a; i++)
            c[i] = a[i];

        output_array(c, size_a);

        free(a);
        free(b);
        free(c);

        return OK;
    }

    if (size_a == 0 && size_b > 0)
    {
        puts("Array length zero error!!!");
        return ARRAY_LENGTH_ZERO_ERROR;
    }

    if (size_a > size_b)
    {
        for (int i = 0; i < size_a; i++)
        {
            if (i < size_b)
                c[i] = a[i] + b[i];
            else
                c[i] = a[i] + b[size_b - 1];
        }
    }

    if (size_a < size_b)
        for (int i = 0; i < size_a; i++)
            c[i] = a[i] + b[i];

    output_array(c, size_a);

    free(a);
    free(b);
    free(c);

    return OK;
}
