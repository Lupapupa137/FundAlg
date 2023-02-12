#include <stdio.h>

enum status
{
    OK = 0,
    ERROR_INPUT_NAME,
    ERROR_OPEN_FILE,
    REMOVE_ERROR,
};

int main(int argc, char *argv[])
{
    FILE *start_file;
    FILE *final_file = fopen("final.txt", "w");
    char str1[100], str2[100], str3[100];
    if (argc != 2)
    {
        printf("File name not found \n");
        return ERROR_INPUT_NAME;
    }

    start_file = fopen(argv[1], "r");
    if (!start_file)
    {
        printf("Unable to open the file \n");
        return ERROR_OPEN_FILE;
    }

    while (fscanf(start_file, "%s%s%s", str1, str2, str3) != EOF)
    {
        fprintf(final_file, "%s %s %s \n", str3, str1, str2);
    }

    fclose(start_file);
    fclose(final_file);

    return OK;
}
