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
    int c = 1;
    char command [10];
    int x = 0, i = 0, error_count = 0;

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
    fclose(reading);
    fclose(error);
    if (error_count)
    {
        /*
        Find error => we delete all code
        so CPU.c call this prog.txt
        and if it will be with error, our CPU will fail.
        */
        fprintf(writing, "");
    }
    fclose(writing);
    return 0;
}
