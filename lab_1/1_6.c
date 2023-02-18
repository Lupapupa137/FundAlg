// В текстовом файле находятся числа, записанные в разных системах
// счисления, при этом информация о конкретной системе счисления для
// каждого числа утеряна. В файле числа разделены произвольным
// количеством разделителей (разделителями могут являться символы
// пробела, табуляции, переноса строки). Напишете программу, которая
// для каждого числа определяет минимальную систему счисления, в
// которой представление этого числа корректно, и в выходной файл
// выводит число, определённую для него систему счисления и
// представление этого числа в десятичной системе счисления.

#include <stdio.h>

char *sc = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

enum status
{
    OK = 0,
    ERROR_OPENING_FILE,
    NOT_VALID,
};

int impr_isalpha(char s)
{
    if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z'))
        return 1;
    else
        return 0;
}

int impr_isdigit(char s)
{
    if (s >= '0' && s <= '9')
        return 1;
    else
        return 0;
}

unsigned int impr_strlen(char *a)
{
    unsigned int length = 0;
    while (*a != '\0')
    {
        length++;
        a++;
    }

    return length;
}

int read_symbol(char s)
{
    if ((s <= 47 && s != '-') || (s >= 58 && s <= 64) || (s >= 91 && s <= 96) || (s >= 123))
        return 1;
    else
        return 0;
}

int find_base(char *num, int length)
{
    int counter = 0;
    int flag = 0;
    if (num[0] == '-')
    {
        flag = 1;
    }
    for (int i = flag; i < length; i++)
    {
        if (num[i] >= sc[counter])
        {
            if (num[i] >= '0' && num[i] <= '9')
                counter = num[i] - 48;

            if (num[i] >= 'A' && num[i] <= 'Z')
                counter = num[i] - 55;
        }
    }
    counter += 1;
    return counter;
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

int check_validation(char *num, int len)
{
    int minus_count = 0;
    if (num[0] == '-')
    {
        for (int i = 1; i < len; i++)
        {
            if (num[i] == '-')
            {
                minus_count++;
            }
            if (minus_count > 1)
            {
                return NOT_VALID;
            }
            if (num[i] >= 'a' && num[i] <= 'z' || read_symbol(num[i]))
            {
                return NOT_VALID;
            }
        }
    }
    else
    {
        for (int i = 1; i < len; i++)
        {
            if (num[i] == '-')
            {
                minus_count++;
            }
            if (minus_count > 0)
            {
                return NOT_VALID;
            }
            if (num[i] >= 'a' && num[i] <= 'z' || read_symbol(num[i]))
            {
                return NOT_VALID;
            }
        }
    }

    return OK;
}

int read_and_write_file(FILE **file, FILE **file_output)
{
    char symbol;
    char c;
    char num[200];
    int i = 0;
    int base = 0, numdec = 0;

    while ((symbol = fgetc(*file)) != EOF)
    {
        while (symbol == ' ' || symbol == '\t' || symbol == '\n')
        {
            symbol = fgetc(*file);
        }
        while (impr_isdigit(symbol) || impr_isalpha(symbol) || read_symbol(symbol) == 0 || symbol == '-')
        {
            num[i] = symbol;
            i++;
            symbol = fgetc(*file);
        }
        num[i] = '\0';

        printf("%s\n", num);

        if (check_validation(num, i) == OK)
        {
            base = find_base(num, i);
            numdec = to_dec(num, base);
            fprintf(*file_output, "num: %s, base: %d, numdec: %d\n", num, base, numdec);
        }

        i = 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    FILE *infile = fopen("input.txt", "r");
    FILE *outfile = fopen("output.txt", "w");

    if (!infile || !outfile)
    {
        puts("Error of opening file!!!");
        return ERROR_OPENING_FILE;
    }

    read_and_write_file(&infile, &outfile);

    fclose(infile);
    fclose(outfile);

    puts("The work of the program is completed");

    return OK;
}
