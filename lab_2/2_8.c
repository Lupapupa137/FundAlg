// Напишите функцию, которая находит корень уравнения методом
// дихотомии. Аргументами функции являются границы интервала, на
// котором находится корень и точность, с которой корень необходимо
// найти. Уравнение задается программно.
#include <stdio.h>
#include <math.h>

enum Status
{
    OK = 0,
    INPUT_LEFT_LIMIT_ERROR = 69,
    INPUT_RIGHT_LIMIT_ERROR = 70,
    INPUT_EPSILON_ERROR = 71,
    ERROR_OF_LIMITS = 199,
    ERROR_SIMPLE_LIMITS = 234,
};

double set_function(double x)
{
    return (x + 2);
}

double find_root_dichotomy(double a, double b, double accuracy)
{
    double c = 0.0;

    while (b - a > accuracy)
    {
        c = (a + b) / 2;
        if (fabs(set_function(c)) < accuracy)
        {
            return c;
        }
        else if (set_function(a) * set_function(c) < accuracy)
        {
            b = c;
        }
        else if (set_function(b) * set_function(c) < accuracy)
        {
            a = c;
        }
        else
            return NAN;
    }

    return (a + b) / 2;
}

int main(int argc, char *argv[])
{
    double left_lim, right_lim, epsilon;

    printf("Enter left limit: ");
    while (scanf("%lf", &left_lim) != 1)
    {
        return INPUT_LEFT_LIMIT_ERROR;
    }
    printf("Enter right limit: ");
    while (scanf("%lf", &right_lim) != 1)
    {
        return INPUT_RIGHT_LIMIT_ERROR;
    }
    printf("Enter accuracy: ");
    while (scanf("%lf", &epsilon) != 1)
    {
        return INPUT_EPSILON_ERROR;
    }

    // TODO: сделать проверку на то, что правая граница больше по значению, нежели левая
    if (left_lim > right_lim)
    {
        return ERROR_OF_LIMITS;
    }

    // TODO: сделать проверку на то, что правая граница не равна левой \ не забыть написать  сразу вывод

    if (left_lim == right_lim)
    {
        return ERROR_SIMPLE_LIMITS;
    }

    // if (left_lim == right_lim)
    // {
    //     // printf("Root: %lf \n", );
    //     double result_unknown = find_root_dichotomy(left_lim, right_lim, epsilon);
    //     printf("%lf \n", result_unknown);
    // }

    if(isnan(result_unknown_before)) {
        printf("No solutions in given interval");
    }
    else {
        printf("Result x = %f\n", result_unknown_before);
    }

    return OK;
}
