// Дан файл, содержащий некоторую информацию, которая представлена
// в трех столбцах (каждая строка файла содержит три лексемы).
// Необходимо перезаписать этот файл таким образом, чтобы первый
// столбец стоял на месте второго, второй – на месте третьего, а третий –
// на месте первого.

#include <stdio.h>

enum status
{
    OK = 0,
    ERROR_INPUT_FILENAME,
    ERROR_OPEN_FILE,
    REMOVE_ERROR,
};

int main(int argc, char *argv[])
{
    FILE *start_file;
    FILE *final_file = fopen("final.txt", "w");
    char str_one[200], str_two[200], str_three[100];
    if (argc != 2)
    {
        puts("File name not found");
        return ERROR_INPUT_FILENAME;
    }

    start_file = fopen(argv[1], "r");
    if (!start_file)
    {
        puts("Unable to open the file");
        return ERROR_OPEN_FILE;
    }

    while (fscanf(start_file, "%s%s%s", str_one, str_two, str_three) != EOF)
    {
        fprintf(final_file, "%s %s %s \n", str_three, str_one, str_two);
    }

    fclose(start_file);
    fclose(final_file);

    return OK;
}
