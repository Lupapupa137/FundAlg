// 1. Напишите функцию с переменным числом аргументов,
// вычисляющую среднее геометрическое переданных ей чисел.
// 2. Напишите рекурсивную функцию возведения в целую степень.
// Учтите, что показатель не обязан быть положительным числом.

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

enum Status
{
    OK = 0,
    MATH_CALCUL_ERROR = 666,
};

double find_geom_mean(int count, ...)
{
    double result = 1.0;
    va_list factor;
    va_start(factor, count);
    for (int i = 0; i < count; i++)
    {
        result *= va_arg(factor, double);
    }
    va_end(factor);
    if (count % 2 == 0 && result < 0.0)
    {
        return NAN;
    }
    else
    {
        return pow(result, 1.0 / count);
    }
}

double pow_recurs(int number, int upper_index)
{
    if (upper_index == 0)
    {
        return 1;
    }
    else if (upper_index == 1)
    {
        return number;
    }
    else if (upper_index > 1)
    {
        if (upper_index % 2 == 0)
        {
            return pow_recurs(number * number, upper_index / 2);
        }
        else
        {
            return pow_recurs(number * number, upper_index / 2) * number;
        }
    }
    else
    {
        return 1.0 / pow_recurs(number, -upper_index);
    }
}

int main(int argc, char *argv[])
{
    printf("pow: %lf \n", pow_recurs(3, 4));

    double result = find_geom_mean(3, 1.0, 1.0, -1.0);
    if (isnan(result))
    {
        puts("Error!");
        return MATH_CALCUL_ERROR;
    }
    else
    {
        printf("geom_mean: %f \n", result);
    }
    return OK;
}
