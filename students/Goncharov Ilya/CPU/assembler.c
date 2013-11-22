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
    char command [10];
    int x = 0, i = 0, error_count = 0;

    reading = fopen("source.txt", "r");
    assert(reading != NULL);
    writing = fopen("prog.txt", "w");
    error = fopen("error.txt", "w");
    while(++i)
    {
        fscanf(reading, "%s", command);

        if ( (!error_count) && (!strcmp(command, "push_ax")) )
        {
            fprintf(writing, "%d ", push_ax);
        }

        else if ( (!error_count) && (!strcmp(command, "push")) )
        {
            fscanf(reading, "%d", &x);
            fprintf(writing, "%d %d ", push, x);
        }

        else if ( (!error_count) && (!strcmp(command, "mul")) )
        {
            fprintf(writing, "%d ", mul);
        }

        else if ( (!error_count) && (!strcmp(command, "add")) )
        {
            fprintf(writing, "%d ", add);
        }


        else if ( (!error_count) && (!strcmp(command, "end")) )
        {
            fprintf(writing, "%d", end);
            break;
        }

        else if (!error_count)
        {
            printf("ERROR in %d line", i);
            fprintf(error, "ERROR in %d line", i);
            error_count = 1;
        }
    }
    fclose(reading);
    fclose(error);
    if (error_count)
    {
        /*
        TRAMTARARAM!!!
        Find error => we delete all code
        so CPU.c call this prog.txt
        and if it will be with error, our CPU will fail.
        */
        fprintf(writing, "");
    }
    fclose(writing);
    return 0;
}
