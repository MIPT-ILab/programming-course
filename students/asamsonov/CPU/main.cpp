//{-------------head----------------------------------
//
//! @file    main.cpp
//! @mainpage
//! @brief   This is CPU of 4th generation.
//!			 It works using jumps but still it's BETA version
//!			 Where you should write adress of jump by yourself.
//!
//!          $Version: 1.00, Revision: 1 $
//!          $Date: 2013-11-05 23:37 $
//!
//!          - Now here are some great changes:
//!			 -- 4 registers now;
//!			 -- many jumps and if-jumps;
//!			 -- PUSH without reg is now correct;
//!			 -- DUB is here. And MOV and OUT;
//!			 -- CPU: @index was changed to @cur as it's shorter and easier to understand (A. is it? Oo); 
//!			 -- ASM: Now it ignores marks (like :1). Ignoring is temporary though;
//!			 -- ASM: There is also a function now that identifies regnum when gets reg;
//!			 -- EJC -> OUT was changed to INFO and soon it will work without EJC and connect to logs;
//!			 -- STACK: Added '*' signs in Stack_dump;
//!			 -- HEADER: Added CPUVERSION define;
//!			 -- HEADER: Now it's checking in all files if header is connected or not;
//!			 -- CS: There are some separators now. I don't know if it's ok or I need more of them;
//!			 - insert 38 and 6 insted of ? and ?. 
//!
//! @todo	 write:
//!			 - Assembler doing marks itself;
//!			 - Friday jump;
//!
//}-------------head---------------------------------

#include "CPUheader.h"

#ifndef CPUHEADER 
	fprintf (stderr, "CPUwork.h is not existing.\n");
	abort ();
#endif

/* _______________________________________________________________________________________
   |																					 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   | 		   Separator		 Separator		   Separator		 Separator 			 |
   |  Separator			Separator		  Separator 		Separator		  Separator  |
   |_____________________________________________________________________________________|
*/

int main ()
{
//{-------------ASSEMBLER-PART----------------------------------
	FILE *fi = fopen (INPUT, "r");
	FILE *fo = fopen (MC, "w");

	CPU *myCPU = CPU_new (10);
	int x = assemble (fi, fo);
	if (x) { printf ("ERROR ASM: line # %d\n", x); return 1; }

	fclose (fi);
	fclose (fo);
//}-------------ASSEMBLER-PART----------------------------------

	fi = fopen (MC, "r");
	fo = fopen (OUTPUT, "w");

	double command = 0;
	int nCommands = 0;
	double *data = NULL;
	printf ("# hello?\n");

	getchar();

	//calculating number of commands.
	for (nCommands = 0; fscanf (fi, "%lf", &command) == 1; nCommands++)
		CENSORED ("# command scanned: %.3lf\n", command);
	CENSORED  ("# nCommands got.\n");

//{-------------CPU-PART----------------------------------------

	fseek (fi, 0, SEEK_SET);

	data = (double *)calloc (nCommands + 1, sizeof (double));

	CENSORED  ("# data created.\n");

	int i = 0, ok = 0;
	for (i = 0; i < nCommands; i ++) {
		ok = fscanf (fi, "%lf", &command);
		ASSERT (ok == 1);
		data[i] = command;
	}
	data[i] = INT_MIN;
	
	x = CPU_run (data, myCPU, fo);
	if (!x) { CENSORED  ("ERROR CPU!\n"); return 1; }
	
	CPU_delete (myCPU);
	fclose (fi);
	fclose (fo);

//}-------------CPU-PART---------------------------------------

	return 0;
}