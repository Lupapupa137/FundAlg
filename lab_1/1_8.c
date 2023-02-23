// Из файла считывается числовой массив, размерность которого не
// превосходит 128 элементов. В зависимости от выбора пользователя
// перепишите в новый массив:
// a) числа, стоящие на нечётных позициях;
// b) чётные числа;
// c) для текущего элемента: наиболее далёкое (по значению) от него
// значение из этого же массива;
// d) для текущего элемента: сумму элементов, которые ему
// предшествуют;
// e) для текущего элемента: сумму элементов, которые меньше него.
// Значение индекса текущего элемента для пунктов c-e должно быть
// получено из стандартного потока ввода.

#include <stdio.h>
#include <stdlib.h>

enum status
{
    OK = 0,
    OPENING_FILE_ERROR,
    NOT_VALID,
    MEMORY_ALLOCATION_ERROR,
    INPUT_SELECT_ERROR,
    INPUT_INDEX_ERROR,
    INCORRECT_INDEX_ERROR,
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
    return n;
}

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

void print_array(int *arr, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int read_symbol(char s)
{
    if ((s <= 47 && s != '-') || (s >= 58 && s <= 64) || (s >= 91 && s <= 96) || (s >= 123))
        return 1;
    else
        return 0;
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
            if (num[i] >= 'a' && num[i] <= 'z' || num[i] >= 'A' && num[i] <= 'Z' || read_symbol(num[i]))
            {
                return NOT_VALID;
            }
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if (num[i] == '-')
            {
                minus_count++;
            }
            if (minus_count > 0)
            {
                return NOT_VALID;
            }
            if (num[i] >= 'a' && num[i] <= 'z' || num[i] >= 'A' && num[i] <= 'Z' || read_symbol(num[i]))
            {
                return NOT_VALID;
            }
        }
    }

    return OK;
}

int read_file(FILE *file, int *arr_in_file)
{
    char symbol;
    int number;
    char num[200];
    int i = 0;
    int j = 0;

    while ((symbol = fgetc(file)) != EOF)
    {
        while (symbol == ' ' || symbol == '\t' || symbol == '\n')
        {
            symbol = fgetc(file);
        }
        while (impr_isdigit(symbol) || impr_isalpha(symbol) || read_symbol(symbol) == 0 || symbol == '-')
        {
            num[i] = symbol;
            i++;
            symbol = fgetc(file);
        }
        num[i] = '\0';


        if (check_validation(num, i) == OK)
        {
            printf("%s\n", num);
            number = impr_atoi(num);
            
            arr_in_file[j] = number;
            j++;
        }
        i = 0;
    }
    printf("%d\n", j);

    int *tmp;
    tmp = (int *)realloc(arr_in_file, sizeof(int) * j);
    if (tmp == NULL)
    {
        free(arr_in_file);
        return MEMORY_ALLOCATION_ERROR;
    }
    else
        arr_in_file = tmp;
    return j;
}

// TODO: a) перепишите в новый массив числа, стоящие на нечётных позициях;
int func_select_1(int *arr, int *res, int size)
{
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            res[j] = arr[i];
            j++;
        }
    }

    int *tmp;
    tmp = (int *)realloc(res, sizeof(int) * j);
    if (tmp == NULL)
    {
        free(res);
        return MEMORY_ALLOCATION_ERROR;
    }
    else
        *res = *tmp;
    return j;
}

// TODO: b) перепишите в новый массив чётные числа
int func_select_2(int *arr, int *res, int size)
{
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            res[j] = arr[i];
            j++;
        }
    }

    int *tmp;
    tmp = (int *)realloc(res, sizeof(int) * j);
    if (tmp == NULL)
    {
        free(res);
        return MEMORY_ALLOCATION_ERROR;
    }
    else
        *res = *tmp;
    return j;
}

// TODO: c) перепишите в новый массив для текущего элемента:
// наиболее далёкое (по значению) от него значение из этого же массива;
int func_select_3(int index, int *arr, int size)
{
    int res = 0;
    int max_dif = 0;
    for (int i = 0; i < size; i++)
    {
        int tmp = abs(arr[index] - arr[i]);
        if (tmp > max_dif)
        {
            max_dif = tmp;
            res = arr[i];
        }
    }
    return res;
}

// TODO: d) перепишите в новый массив для текущего элемента: сумму элементов, которые
//  предшествуют;
int func_select_4(int *arr, int index, int size)
{
    int sum = 0;
    for (int i = 0; i <= index; i++)
    {
        sum += arr[i];
    }
    return sum;
}

// TODO: e) для текущего элемента: сумму элементов, которые меньше него.
int func_select_5(int *arr, int index, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < arr[index])
            sum += arr[i];
    }
    return sum;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen("test.txt", "r");
    if (!file)
    {
        puts("Unable to open the file");
        return OPENING_FILE_ERROR;
    }

    unsigned int max_size = 128;
    int *arr = (int *)malloc(sizeof(int) * max_size);
    int *res = (int *)malloc(sizeof(int) * max_size);

    if (arr == NULL || res == NULL)
    {
        puts("Out of memory!!!");
        fclose(file);
        free(arr);
        free(res);
        return MEMORY_ALLOCATION_ERROR;
    }

    int new_size = read_file(file, arr);

    puts("Select an action");
    puts("1. Numbers in odd positions");
    puts("2. Even numbers");
    puts("3. The most distant by value");
    puts("4. The sum of the elements that precede it");
    puts("5. The sum of the elements that are smaller than it");
    printf("Enter: ");

    int select;
    if (!scanf("%d", &select))
    {
        puts("Error of input select");
        fclose(file);
        free(arr);
        free(res);
        return INPUT_SELECT_ERROR;
    }

    puts("Array from file:");
    print_array(arr, new_size);

    unsigned int index;
    switch (select)
    {
    case 1:
        puts("Result:");
        int result_size_for_case_1 = func_select_1(arr, res, new_size);
        print_array(res, result_size_for_case_1);
        break;
    case 2:
        puts("Result:");
        int result_size_for_case_2 = func_select_2(arr, res, new_size);
        print_array(res, result_size_for_case_2);
        break;
    case 3:
        printf("Input index of number: ");
        if (!scanf("%d", &index))
        {
            puts("Error of input index");
            fclose(file);
            free(arr);
            free(res);
            return INPUT_INDEX_ERROR;
        }
        if (index > new_size - 1)
        {
            puts("Incorrect input index");
            fclose(file);
            free(arr);
            free(res);
            return INPUT_INDEX_ERROR;
        }
        puts("Result:");
        printf("%d \n", func_select_3(index, arr, new_size));
        break;
    case 4:
        printf("Input index of number: ");
        if (!scanf("%d", &index))
        {
            puts("Error of input index");
            fclose(file);
            free(arr);
            free(res);
            return INPUT_INDEX_ERROR;
        }
        if (index > (new_size - 1))
        {
            puts("Incorrect input index");
            fclose(file);
            free(arr);
            free(res);
            return INPUT_INDEX_ERROR;
        }
        puts("Result:");
        printf("%d \n", func_select_4(arr, index, new_size));
        break;
    case 5:
        printf("Input index of number: ");
        if (!scanf("%d", &index))
        {
            puts("Error of input index");
            fclose(file);
            free(arr);
            free(res);
            return INPUT_INDEX_ERROR;
        }
        if (index > (new_size - 1))
        {
            puts("Incorrect input index");
            fclose(file);
            free(arr);
            free(res);
            return INPUT_INDEX_ERROR;
        }
        puts("Result:");
        printf("%d \n", func_select_5(arr, index, new_size));
        break;
    default:
        printf("Incorrect select");
        fclose(file);
        free(arr);
        free(res);
        return INCORRECT_INDEX_ERROR;
    }

    fclose(file);
    free(arr);
    free(res);

    return OK;
}
