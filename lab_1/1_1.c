// 1. Через аргументы командной строки пользователь вводит целое
// положительное число и флаг, определяющий действие с этим числом.
// Флаг начинается с символа “-” или “/”. Программа распознаёт
// следующие флаги:
// i) -h вывести в консоль числа в пределах 100, кратные введённому.
// Если таковых нету – вывести соответствующее сообщение;
// ii) -p определить, является ли введённое число простым или
// составным;
// iii)-s разделяет число на отдельные цифры и выводит отдельно каждую
// цифру, разделяя их пробелом;
// iv) -e вывести в консоль числа от 1 до 10, возводя их во все степени от 1
// до заданного числа (для этого флага работает ограничение на
// вводимое число: оно должно быть не больше 10);
// v) -a суммирует все числа от 1 до указанного числа включительно;
// vi) -f вычисляет факториал введенного числа.

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

enum status
{
    OK = 0,
    ERROR_OF_COUNT_ARGUMENT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR,
    WRONG_FLAG_ERROR,
    INCORRECT_NUMBER_ENTRY,
};

long int impr_atoi(char s[])
{
    int n = 0;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    {

        n = 10 * n + (s[i] - '0');
    }
    return n;
}

int impr_strlen(char s[])
{
    int len = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        len++;
    }
    return len;
}

int func_h(long int a, int **arr)
{
    int size_arr = 100;
    int final_size = 0;
    int *tmp;
    *arr = (int *)malloc(sizeof(int) * size_arr);
    if (arr == NULL)
        return MEMORY_ALLOCATION_ERROR;

    for (int i = 1; i < 101; i++)
    {
        if (i % a == 0)
        {
            (*arr)[final_size] = i;
            final_size++;
        }
    }

    if (final_size != 100)
        tmp = (int *)realloc(*arr, sizeof(int) * final_size);
    if (tmp == NULL)
    {
        free(arr);
        return MEMORY_ALLOCATION_ERROR;
    }
    else
        *arr = tmp;
    return final_size;
}

int func_p(long int a)
{
    if (a > 0)
    {
        if (a == 1)
            return 0;
        if (a == 2)
            return 0;
        for (int i = 2; i <= floor(sqrt(a)); i++)
        {
            if (a % i == 0)
                return 1;
        }
    }
    else
        return 1;
}

void func_s(char *a)
{
    int len = impr_strlen(a);
    for (int i = 0; i < len; i++)
    {
        printf("%c ", a[i]);
    }
}

int func_e(long int a)
{
    if (a > 10)
    {
        puts("Input number must be <= 10");
        return INCORRECT_NUMBER_ENTRY;
    }
    for (int i = 1; i <= 10; i++)
    {
        printf("For %d: ", i);
        long long final = 1;
        for (int j = 1; j < a; j++)
        {
            final *= i;
            printf("    %lld", final);
        }
        puts("");
    }
}

int func_a(long int a)
{
    int sum = 0;
    for (int i = 0; i <= a; i++)
    {
        if (INT_MAX - i < sum)
        {
            return OVERFLOW_ERROR;
        }
        sum += i;
    }
    return sum;
}

long long int func_f(long int a)
{
    unsigned long long int factorial = 1;
    for (int i = 2; i <= a; i++)
    {
        if (ULLONG_MAX / i < factorial)
        {
            return OVERFLOW_ERROR;
        }
        factorial *= i;
    }
    return factorial;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        puts("Flag / number not found");
        return ERROR_OF_COUNT_ARGUMENT;
    }

    if (impr_strlen(argv[1]) != 2 || argv[1][0] != '-' && argv[1][0] != '/')
    {
        printf("Error: input wrong flag");
        return WRONG_FLAG_ERROR;
    }

    if (argv[1][1] == 'h')
    {
        
        int *arr;
        int size = func_h(impr_atoi(argv[2]), &arr);
        for (int i = 0; i < size; i++)
        {
            printf("%d ", arr[i]);
        }
        free(arr);
        return OK;
    }
    else if (argv[1][1] == 'p')
    {
        if (func_p(impr_atoi(argv[2])) == 0)
        {
            puts("Prime number");
        }
        if (func_p(impr_atoi(argv[2])) == 1)
        {
            puts("Not prime number");
        }
    }
    else if (argv[1][1] == 's')
    {
        func_s(argv[2]);
    }
    else if (argv[1][1] == 'e')
    {
        func_e(impr_atoi(argv[2]));
    }
    else if (argv[1][1] == 'a')
    {
        int sum = func_a(impr_atoi(argv[2]));
        printf("Sum: %d \n", sum);
    }
    else if (argv[1][1] == 'f')
    {
        long long int factorial = func_f(impr_atoi(argv[2]));
        printf("Factorial: %lld \n", factorial);
    }
    else
    {
        printf("Input error: wrong flag!");
        return WRONG_FLAG_ERROR;
    }

    return OK;
}
