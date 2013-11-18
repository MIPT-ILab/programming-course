#include <stdio.h>
#include <string.h>

/*
0 - end
1 - push
2 - mul
3 - add
4 - push_ax
*/

int main()
{
    FILE* writing;
    FILE* reading;
    FILE* error;
    FILE* delete;
    char command [10];
    int x, i = 0, error_count = 0;

    reading = fopen("source.txt", "r");
    writing = fopen("prog.txt", "w");
    error = fopen("error.txt", "w");
    while(++i)
    {
        fscanf(reading, "%s", command);

        if (strcmp(command, "push_ax") == 0)
        {
            fprintf(writing, "%d", 4);
        }

        else if ( strcmp(command, "push") == 0 )
        {
            fscanf(reading, "%d", &x);
            fprintf(writing, "%d %d ", 1, x);
        }

        else if ( strcmp(command, "mul") == 0 )
        {
            fprintf(writing, "%d ", 2);
        }

        else if (strcmp(command, "add") == 0)
        {
            fprintf(writing, "%d ", 3);
        }


        else if (strcmp(command, "end") == 0)
        {
            fprintf(writing, "%d", 0);
            break;
        }

        else
        {
            printf("ERROR in %d line", i);
            fprintf(error, "ERROR in %d line", i);
            error_count = 1;
        }
    }
    fclose(reading);
    fclose(writing);
    fclose(error);
    if (error_count)
    {
        delete = fopen("prog.txt", "w");
        fprintf(delete, "");
    }

    return 0;
}
