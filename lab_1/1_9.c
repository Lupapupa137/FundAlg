// Пользователь вводит систему счисления (в диапазоне [2..36]) и затем
// числа в этой системе счисления. Окончанием ввода является ввод
// лексемы “Stop”. Найдите среди введённых чисел максимальное по
// модулю. Выведите на консоль значение найденного максимального по
// модулю числа в системах счисления с основаниями 9, 18, 27, 36.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum status
{
    OK,
    NOT_FALL_IN_RANGE_ERROR,
    NOT_VALID,
};

char *sc = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int impr_atoi(char *num)
{
    int n=0;
    int flag = 1;
    if (*num == '-')
    {
        flag = -1;
        num++;
        if (*num == '\0')
        {
            return NOT_VALID;
        }
    }

    while (*num)
    {
        if (*num == '-')
            flag -= 1;
        if (flag < -1)
            return NOT_VALID;
        n = (*num - '0') + 10 * n;
    
        num++;
    }
    n *= flag;
    printf("%d \n", n);
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

int impr_strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int print(char *res, int SIZE)
{
    for (int i = SIZE - 1; i >= 0; i--)
    {
        printf("%c", res[i]);
    }
}

void ten_into_n(unsigned int num, int base, char *res, size_t SIZE)
{
    int count = 0;
    int temp = num;
    int k = 0;
    int *for_realloc = NULL;
    for (int i = 0; i < SIZE; i++)
    {
        if (count >= SIZE)
        {
            if (!(for_realloc = (int *)realloc(res, sizeof(char*) * (SIZE << 1))))
                {
                    puts("pizdyau");
                }
        } // 10
        if (num < base)
        {
            k = num;
            res[i] = sc[k];
            count++;
            break;
        }
        else
        {
            num /= base;
            k = temp - (num * base);
            res[i] = sc[k];
            temp /= base;
            count++;
        }
    }
    print(res, count);
}

int to_dec(char *num, int x)
{
    int len = impr_strlen(num) - 1;
    int res = 0;
    int base = 1;
    int flag = 1;

    for (int i = len; i >= 0; i--)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            res += (num[i] - 48) * base;
            base *= x;
        }
        if (num[i] >= 'A' && num[i] <= 'Z')
        {
            res += (num[i] - 55) * base;
            base *= x;
        }
        if (num[i] == '-')
        {
            flag = -1;
        }
    }
    res *= flag;
    return res;
}

int proverka(char num[100], int r)
{
    int len = impr_strlen(num);
    for (int i = 0; i < len; i++)
    {
        if (num[i] >= sc[r])
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int base;
    char num[100];
    char *tmp = "Stop";
    size_t size = 10;
    char *res = NULL;

    printf("Enter base: ");
    if (!scanf("%d", &base) || base < 2 || base > 36)
    {
        puts("The number doesn't fall into the range [2...36]");
        return NOT_FALL_IN_RANGE_ERROR;
    }

    int num_max = 0;
    int num1;
    while (scanf("%100s", num))
    {
        if (impr_strcmp(num, tmp) == 0)
        {
            break;
        } else if (impr_atoi(num) == 0 && base <= 9)
        {
            printf("No number\n");
            continue;
        }
        else if ((proverka(num, base)) == 0)
        {
            printf("No number base\n");
            continue;
        }

        num1 = to_dec(num, base);
        if (fabs(num1) > num_max)
        {
            num_max = fabs(num1);
        }
    }

    printf("Max number: ");
    ten_into_n(num_max, base, res, size);

    int p = 1;
    while (p <= 4)
    {
        printf("\n");
        printf("Max number in the number system with a base %d: ", p * 9);
        ten_into_n(num_max, p * 9, res, size);
        p++;
    }

    free(res);

    return OK;
}
