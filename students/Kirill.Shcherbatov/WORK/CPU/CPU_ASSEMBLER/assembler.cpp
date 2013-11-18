//{==================================================================================================
//! @file "assembler.cpp"
//! @date 2013-11-09
//! @mainpage CPU assembler
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 2.0
//}===================================================================================================

//****************************************************************************************************
#define LABEL_MEMORY_MAX_SIZE 16
//****************************************************************************************************

//****************************************************************************************************
//#define DEBUG
//****************************************************************************************************

//****************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
//----------------------------------------------------------------------------------------------------
#include "../../debug_defines.h"
#include "assembler.h"
//****************************************************************************************************

int main (int argc, char * argv[])
{
    OUT ( "# %s \n"
          "# (%s)\n"
          "# %s %s:\n\n",
          argv[0], __FILE__, __DATE__, __TIME__ );

    fprintf (OUT_DEVICE, "CPU assembler v 3.0 (author Shcherbatov Kirill)\n");
    fprintf (OUT_DEVICE, "Using: \t  'CPU_assembler' in_program_file_name out_binary_file_name\n\n");

    fprintf (OUT_DEVICE, "Openning input file [ %s ]...\n", argv[1]);
    RETURN_ASSERT (argv[1] != NULL, -1);
    FILE *fin = fopen (argv[1], "r");
	RETURN_ASSERT (fin != NULL, -1);

    double *memory = (double*)calloc (CPU_MEMORY_SIZE, sizeof (double));
    RETURN_ASSERT (memory != NULL, -1);

    int   *label_memory = (int*)calloc (LABEL_MEMORY_MAX_SIZE, sizeof (int));
    RETURN_ASSERT (label_memory != NULL, -1);
    unsigned int program_size = 0;

    fprintf (OUT_DEVICE, "OK.\n"
                         "Start assembling iterations... \n");

   for (register int i = 0; i < ASSEMBLE_ITERATIONS; i++)
    {
        if (assemble_file (fin, memory, label_memory, &program_size) != 0)
        {
			fprintf (OUT_DEVICE, "Compilation error.\n");
			free (memory);
			free (label_memory);
			return -1;
		}
        fprintf (OUT_DEVICE, " Progress [%d / %d]\n", i+1, ASSEMBLE_ITERATIONS);
    }
    fprintf (OUT_DEVICE, "READY!\n");

    fclose (fin);
    fin = NULL;
    free (label_memory);
    label_memory = NULL;

    fprintf (OUT_DEVICE, "Openning output file [ %s ]...\n", argv[1]);
    RETURN_ASSERT (argv[2] != NULL, -1);
    FILE *fout = fopen (argv[2], "w");
	RETURN_ASSERT (fout != NULL, -1);

    fprintf (OUT_DEVICE, "Recording %s...\n", argv[1]);
    fprintf (fout, "%d %d ", SHCHERBATOV_KIRILL_PROGRAM_SIGNATURE, program_size);

    for (register unsigned int i=0; i < program_size; i++)
        fprintf(fout, "%lg ", memory[i]);

    free (memory);
    memory = NULL;
    fclose (fout);
    fout = NULL;

    fprintf (OUT_DEVICE, "OK.\n"
                         "Assembling finished successfully.\n");

    return 0;
}
