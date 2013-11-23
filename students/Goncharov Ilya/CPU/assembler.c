#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
0 - end
1 - push
2 - mul
3 - add
4 - push_ax
*/

enum {end, push, mul, add, push_ax};

int main()
{
    FILE* writing;
    FILE* reading;
    FILE* error;
    int c = 0;
    char command [10];
    int x = 0, i = 0, error_count = 0, end_count = 0;

    reading = fopen("source.txt", "r");
    assert(reading != NULL);
    writing = fopen("prog.txt", "w");
    error = fopen("error.txt", "w");

    while ((++i)&&(c!=EOF))
    {
        c = fscanf(reading, "%s", command);

        if (c!=EOF)
        {
            if ( !strcmp(command, "push_ax") )
            {
                fprintf(writing, "%d ", push_ax);
            }

            else if ( !strcmp(command, "push") )
            {
                fscanf(reading, "%d", &x);
                fprintf(writing, "%d %d ", push, x);
            }

            else if ( !strcmp(command, "mul") )
            {
                fprintf(writing, "%d ", mul);
            }

            else if ( !strcmp(command, "add") )
            {
                fprintf(writing, "%d ", add);
            }


            else if ( !strcmp(command, "end") )
            {
                fprintf(writing, "%d", end);
                end_count = 1;
                break;
            }

            else
            {
                printf("ERROR in %d line\n", i);
                fprintf(error, "ERROR in %d line\n", i);
                error_count = 1;
            }
        }
    }
    if (!end_count)
    {
        printf("ERROR, not found END");
        fprintf(error, "ERROR, not found END");
        error_count = 1;
    }
    fclose(writing);
    fclose(reading);
    fclose(error);
    if (error_count)
    {
        /*
        Find error => remove file with program
        */
        remove("prog.txt");
    }
    return 0;
}
