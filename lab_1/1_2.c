//   Через аргументы командной строки в программу подается флаг,
// который определяет действие, и набор чисел. Флаг начинается с
// символа “-” или “/”. Необходимо проверять соответствие количества
// параметров введенному флагу. Программа распознаёт следующие
// флаги:
//   i) -q вводимые три параметра являются коэффициентами квадратного
// уравнения, необходимо вывести решения этого уравнения при
// всевозможных значениях параметров;
//   ii) -m необходимо задать два ненулевых целых числа, после чего
// определить, кратно ли первое число второму;
//   iii)-t считывает 3 ненулевых значения и проверяет, могут ли они быть
// сторонами прямоугольного треугольника.

#include <stdio.h>
#include <math.h>

enum status
{
    OK = 0,
    NOT_VALID,
    WRONG_FLAG_ERROR,
    ERROR_OF_COUNT_ARGUMENT,
    NO_ROOTS,
};

int impr_atoi(char s[])
{
    int n = 0, flag = 1;
    if (s[0] == '-')
        flag = -1;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++)
    {
        if (s[i] == '-')
            flag -= 1;
        if (flag < -1)
            return NOT_VALID;
        n = (s[i] - '0') + 10 * n;
    }
    n *= flag;
    return OK;
}

int impr_strlen(char s[])
{
    int length = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

double impr_atof(char *num)
{
    int sign = 1;
    int num_out = 0;
    int flag = 0;
    int power = 0;
    if (num[0] == '-')
    {
        sign = -1;
        num++;
    }
    while (*num != '\0')
    {
        if (flag == 1)
        {
            power++;
        }
        if (*num == '.')
        {
            num++;
            flag = 1;
        }
        else
        {
            num_out = num_out * 10 + (*num - '0');
            num++;
        }
    }
    return sign * num_out / pow(10, power);
}

int func_flag_q(double a, double b, double c, double *x1, double *x2, double epsilon)
{
    double D = 0;
    D = (b * b) - (4.0 * a * c);
    ;
    if (D < epsilon)
    {
        return 0;
    }
    else if (fabs(D) < epsilon)
    {
        *x1 = -b / (2.0 * a);
        return 1;
    }
    else
    {
        *x1 = (-b - sqrt(D)) / (2.0 * a);
        *x2 = (-b + sqrt(D)) / (2.0 * a);
        return 2;
    }
}

void func_flag_m(int a, int b)
{
    if (a % b == 0)
    {
        puts("Yes");
    }
    else
    {
        puts("No");
    }
}

int func_flag_t(int a, int b, int c)
{
    if (a + b > c && b + c > a && c + a > b)
    {
        double a2 = pow(a, 2);
        double b2 = pow(b, 2);
        double c2 = pow(c, 2);
        if (a2 + b2 == c2 || b2 + c2 == a2 || c2 + a2 == b2)
        {
            return 0;
        }
        else
            return 1;
    }
    else
    {
        return 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        puts("Flag / numbers not found");
        return ERROR_OF_COUNT_ARGUMENT;
    }

    if (impr_strlen(argv[1]) != 2 || argv[1][0] != '-' && argv[1][0] != '/')
    {
        printf("Error: input wrong flag");
        return WRONG_FLAG_ERROR;
    }

    if (argv[1][1] == 'q')
    {
        if (argc != 4)
        {
            puts("Flag / numbers not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        else
        {
            double x1 = 0, x2 = 0;
            double eps = 0;
            printf("Input epsilon: ");
            scanf("%lf", &eps);
            int res = func_flag_q(impr_atof(argv[2]), impr_atof(argv[3]), impr_atof(argv[4]), &x1, &x2, eps);
            if (res == 0)
            {
                puts("No roots");
                return NO_ROOTS;
            }
            else if (res == 1)
            {
                printf("Root: %lf \n", x1);
                return OK;
            }
            else if (res == 2)
            {
                printf("Root 1: %lf \n", x1);
                printf("Root 2: %lf \n", x2);
                return 0;
            }
        }
    }
    else if (argv[1][1] == 'm')
    {
        if (argc != 3)
        {
            puts("Flag / numbers not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        else
        {
            func_flag_m(impr_atoi(argv[2]), impr_atoi(argv[3]));
            return OK;
        }
    }
    else if (argv[1][1] == 't')
    {
        if (argc != 4)
        {
            puts("Flag / numbers not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        else
        {
            int final = func_flag_t(impr_atoi(argv[2]), impr_atoi(argv[3]), impr_atoi(argv[4]));
            if (final == 0)
            {
                puts("The triangle is rectangular.");
                return OK;
            }
            if (final == 1)
            {
                puts("The triangle is not rectangular.");
                return OK;
            }
        }
    }
    else
    {
        printf("Input error: wrong flag!");
        return WRONG_FLAG_ERROR;
    }

    return OK;
}
