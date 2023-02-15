// На вход программе подается строка и флаг, определяющий действие с
// этой строкой. Программа распознает следующие флаги:
// i) -l подсчет длины строки;
// ii) -r переворот (reverse) строки;
// iii)-u преобразовать каждый элемент, стоящий на нечетной позиции в
// верхний регистр;
// iv) -n переписать строку так, чтобы в начале строки были символы
// цифр, затем символы букв, а в конце – прочие символы в порядке,
// определённом исходной строкой;
// v) -c конкатенация со строкой, которая передается третьим аргументом.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum status
{
    OK = 0,
    ERROR_OF_COUNT_ARGUMENT,
    WRONG_FLAG_ERROR
};

int string_length(char *a)
{
    int length = 0;
    while (*a != '\0')
    {
        length++;
        a++;
    }

    return length;
}

void reverse_string(char *str)
{
    char *begin_str, *end_str, a;
    int l = string_length(str);

    begin_str = str;
    end_str = str + l - 1;

    for (int i = 0; i < (l - 1) / 2; i++)
    {
        a = *end_str;
        *end_str = *begin_str;
        *begin_str = a;

        begin_str++;
        end_str--;
    }
}

void func_flag_u(char *str)
{
    int len = string_length(str) - 1;

    for (int i = 0; i <= len; i += 2)
    {
        if (str[i] >= 97 && str[i] <= 122)
        {
            str[i] -= 32;
        }
    }
}

void func_flag_n(char *str, char *res)
{
    int len = string_length(str);
    int n = 0;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            res[n] = str[i];
            n++;
        }
    }
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            res[n] = str[i];
            n++;
        }
    }
    for (int i = 0; i < len; i++)
    {
        if (!isalnum(str[i]))
        {
            res[n] = str[i];
            n++;
        }
    }
    str[n] = '\0';
}

void func_flag_c(char *str1, char *str2, char *res)
{
    int len1 = string_length(str1);
    int len2 = string_length(str2);
    int n = 0;
    for (int i = 0; i < len1; i++)
    {
        res[n] = str1[i];
        n++;
    }
    for (int i = 0; i < len2; i++)
    {
        res[n] = str2[i];
        n++;
    }
    res[n] = '\0';
}

int main(int argc, char *argv[])
{

    if (string_length(argv[1]) != 2 || argv[1][0] != '-' && argv[1][0] != '/')
    {
        printf("Error: input wrong flag");
        return WRONG_FLAG_ERROR;
    }

    if (argv[1][1] == 'l')
    {
        if (argc != 3)
        {
            puts("Flag / string not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        printf("length: %d", string_length(argv[2]));
    }
    else if (argv[1][1] == 'r')
    {
        if (argc != 3)
        {
            puts("Flag / string not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        reverse_string(argv[2]);
        printf(argv[2]);
    }
    else if (argv[1][1] == 'u')
    {
        if (argc != 3)
        {
            puts("Flag / string not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        func_flag_u(argv[2]);
        printf(argv[2]);
    }
    else if (argv[1][1] == 'n')
    {
        if (argc != 3)
        {
            puts("Flag / string not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        char *res = (char *)malloc(sizeof(char) * (string_length(argv[2])+1));
        func_flag_n(argv[2], res);
        printf(res);
        free(res);
    }
    else if (argv[1][1] == 'c')
    {
        if (argc != 4)
        {
            puts("Flag / string not found");
            return ERROR_OF_COUNT_ARGUMENT;
        }
        char *res = (char *)malloc(sizeof(char) * (string_length(argv[2]) + string_length(argv[3])+1));
        func_flag_c(argv[2], argv[3], res);
        printf(res);
        free(res);
    }
    return OK;
}
