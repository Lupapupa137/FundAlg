// Заполнить массив фиксированного размера случайными числами.(пусть это будут целые числа)
// Реализовать поиск максимального и минимального элементов, DONE
// поменять местами максимальный и минимальный элементы массива.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 10

int create_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 - 30;
    }
    return 0;
}

void output(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

int find_max(int *arr, int size, int **maxPtr)
{
    *maxPtr = arr;
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            *maxPtr = arr + i;
        }
    }
    return max;
}

int find_min(int *arr, int size, int **minPtr)
{
    *minPtr = arr;
    ;
    int min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            *minPtr = arr + i;
        }
    }
    return min;
}

int swap(int *max, int *min)
{
    int add = *max;
    *max = *min;
    *min = add;
}

int main(int argc, char *argv[])
{
    int a[SIZE];
    int *minPtr, *maxPtr;

    srand(time(0));

    create_array(a, SIZE);
    output(a, SIZE);
    printf("\n");

    int max = find_max(a, SIZE, &maxPtr);
    printf("Max item of array: %d \n", max);

    int min = find_min(a, SIZE, &minPtr);
    printf("Min item of array: %d \n", min);

    swap(maxPtr, minPtr);
    output(a, SIZE);

    return 0;
}
