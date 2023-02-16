// Заполните одномерный массив псевдослучайными числами из
// заданного диапазона (диапазон определяется пользователем). В
// зависимости от выбора пользователя:
// - поменяйте местами максимальный и минимальный элементы этого массива;
// - создайте новый массив, который содержит уникальные элементы исходного массива в порядке, определённом исходным массивом.
// Для обмена местами двух элементов массива реализуйте функцию, принимающую
// на вход адреса меняемых элементов

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum status
{
    OK = 0,
    MEMORY_ARRAY_A_ALLOCATION_ERROR,
    INPUT_ARRAY_A_ERROR,
    ERROR_OF_RANGE_LIMITS,
    ERROR_INPUT_OPTION,
    WRONG_OPTION_ERROR,
    MEMORY_ALLOCATION_ERROR,
    ERROR_OF_COUNT_ARGUMENT,
    MEMORY_ARRAY_ALLOCATION_ERROR,
};

int *fill_array(int *arr, int size, int a, int b, int *code)
{
    if (a > b)
    {
        *code = ERROR_OF_RANGE_LIMITS;
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % (b - a + 1) + a;
    }
    *code = OK;
    return arr;
}

void output_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *minPtr, int *maxPtr)
{
    *minPtr = *minPtr + *maxPtr;
    *maxPtr = *minPtr - *maxPtr;
    *minPtr = *minPtr - *maxPtr;
}

void replace(int *arr, int size)
{
    int min = arr[0];
    int max = arr[0];
    int *min_arr = arr;
    int *max_arr = arr;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            max_arr = arr + i;
        }
        if (arr[i] < min)
        {
            min = arr[i];
            min_arr = arr + i;
        }
    }
    swap(min_arr, max_arr);
}

int new_arr(int **arr, int *res, int size)
{
    int new_size = 1;
    res[0] = **arr;
    int *tmp;
    for (int i = 0; i < size; i++)
    {
        int flag = 0;
        for (int j = 0; j < new_size; j++)
            if ((*arr)[i] == res[j])
            {
                flag = 1;
                break;
            }
        if (flag == 0)
        {
            res[new_size] = (*arr)[i];
            new_size++;
        }
    }

    if (new_size < size)
        tmp = (int *)realloc(*arr, sizeof(int) * new_size);
    if (tmp == NULL)
    {
        free(*arr);
        return MEMORY_ALLOCATION_ERROR;
    }
    else
        *arr = *tmp;
    return new_size;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int size_a = 0;
    int x1 = 0;
    int x2 = 0;

    printf("Enter size of 1st array: ");
    if (!scanf("%d", &size_a))
    {
        printf("Incorrect input!!!");
        return INPUT_ARRAY_A_ERROR;
    }
    if (size_a <= 0)
    {
        puts("Incorrect input!!!");
        return INPUT_ARRAY_A_ERROR;
    }

    int *a = (int *)malloc(sizeof(int) * size_a);
    if (a == NULL)
    {
        puts("Out of memory!");
        return MEMORY_ARRAY_A_ALLOCATION_ERROR;
    }

    printf("Range of numbers: ");
    // scanf("%d%d", &x1, &x2);
    if (scanf("%d%d", &x1, &x2) != 2)
    {
        printf("Error of count arguments");
        free(a);
        return ERROR_OF_COUNT_ARGUMENT;
    }
    if (x1 > x2)
    {
        puts("Incorrect input limits of range!!!");
        free(a);
        return ERROR_OF_RANGE_LIMITS;
    }

    int status_code;
    fill_array(a, size_a, x1, x2, &status_code);
    if (status_code == ERROR_OF_RANGE_LIMITS)
    {
        printf("Incorrect input limits of range!!");
        return ERROR_OF_RANGE_LIMITS;
    }
    puts("Array: ");
    output_array(a, size_a);

    printf("1. Swap max and min elements \n");
    printf("2. Create a new array \n");
    printf("Enter: ");
    int option = 0;
    if (!scanf("%d", &option))
    {
        printf("Incorrect input option");
        free(a);
        return ERROR_INPUT_OPTION;
    }

    if (option == 1)
    {
        replace(a, size_a);
        output_array(a, size_a);
    }
    else if (option == 2)
    {
        int *result_array = (int *)malloc(size_a * sizeof(int));
        if (result_array == NULL)
        {
            puts("Out of memory!");
            return MEMORY_ARRAY_ALLOCATION_ERROR;
        }
        int size_final_array = new_arr(a, result_array, size_a);
        output_array(result_array, size_final_array);
        free(result_array);
    }
    else
    {
        printf("Wrong option!!!");
        free(a);
        return WRONG_OPTION_ERROR;
    }

    free(a);
    return OK;
}
