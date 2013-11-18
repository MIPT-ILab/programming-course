//{==================================================================================================
//! @file "cpu_core.cpp"
//! @date 2013-11-09
//! @mainpage Virtual CPU console UI
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 3.0
//}===================================================================================================


//****************************************************************************************************
//#define DEBUG
//****************************************************************************************************

//****************************************************************************************************
#include <stdio.h>
//----------------------------------------------------------------------------------------------------
#include "cpu_t.h"
#include "../../debug_defines.h"
//****************************************************************************************************

int main (int argc, char * argv[])
{
	OUT ( "# %s \n"
		  "# (%s)\n"
		  "# %s %s:\n\n",
		   argv[0], __FILE__, __DATE__, __TIME__ );

	fprintf (OUT_DEVICE, "CPU core emulator v 2.0 (author Shcherbatov Kirill).\n");
    fprintf (OUT_DEVICE, "Using: \t  'CPU-core' program_file_name\n\n");

	fprintf (OUT_DEVICE, "Openning file [ %s ]...\n", argv[1]);
    RETURN_ASSERT (argv[1] != NULL, -1);
    FILE *fin = fopen (argv[1], "r");
	RETURN_ASSERT (fin != NULL, -1);

	cpu_t *ilab_cpu = cpu_constructor();
	RETURN_ASSERT (ilab_cpu != NULL, -1);

    fprintf (OUT_DEVICE, "Load program...\n");
	RETURN_ASSERT (cpu_load_program (ilab_cpu, fin) == 0, -1);

    fclose (fin);
    fin = NULL;

	fprintf (OUT_DEVICE, "Start the program:\n");
	RETURN_ASSERT (cpu_run (ilab_cpu) == 0, -1);

	fprintf (OUT_DEVICE, "\n"
	        			 "Succcess (0). End of the program.\n");

	RETURN_ASSERT (cpu_destructor (ilab_cpu) == 0, -1);

	return 0;
}
